<?php
/**
 * @file sync_rkeeper_connect_query.inc
 */

/**
 * Подключение к socket rkeeper, отправка запроса, получение данных
 *
 * @param $query
 *   Запрос на сервер rkeeper
 *
 * @param $single
 *   Единичный запрос или множественный
 *
 * @return
 *   Данные обработанные simplexml_load_string()
 */
function sync_rkeeper_query_rkeeper($query, $single = FALSE) {
  $variables = variable_get('sync_rkeeper_settings')? variable_get('sync_rkeeper_settings'): FALSE;

  if ($variables and isset($variables['ip_address']) and isset($variables['port'])) {
    if (($socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) < 0) {
      //AF_INET - семейство протоколов
      //SOCK_STREAM - тип сокета
      //SOL_TCP - протокол
      return simplexml_load_string('<?xml version="1.0" encoding="UTF-8"?><RK7Query><error>Ошибка создания сокета</error></RK7Query>');
    }

    if ($connect = socket_connect($socket, $variables['ip_address'], $variables['port']) === false) {
      return simplexml_load_string('<?xml version="1.0" encoding="UTF-8"?><RK7Query><error>Ошибка при подключении к сокету</error></RK7Query>');
    }

    if ($single) {
      $query = '<?xml version="1.0" encoding="UTF-8"?>' . $query;

    } else {
      $query = '<?xml version="1.0" encoding="UTF-8"?><RK7Query>' . $query . '</RK7Query>';
    }
    //Отправляем серверу запрос
    socket_write($socket, $query, strlen($query));
    //Читаем ответ от сервера
    $xml = socket_read($socket, 10000);

    //Возвращаем объект
    if ($xml = simplexml_load_string($xml)) {
      return simplexml_load_string('<?xml version="1.0" encoding="UTF-8"?><RK7Query><error>Ошибка загрузки XML\n</error></RK7Query>');
    }

    socket_close($socket);

  } else {
    return simplexml_load_string('<?xml version="1.0" encoding="UTF-8"?><RK7Query><error>Введите в настройках данные сервера для подключения</error></RK7Query>');
  }

  return $xml;
}

/**
 * Тестовое соединение с rkeeper
 *
 * @param $query
 *   Запрос на сервер в xml
 *
 * @param $single
 *   TRUE - сразу несколько запросов
 *
 * @return
 *   Массив со столиками, товаром, категориями и в отдельности
 */
function sync_rkeeper_query_test_rkeeper($query, $single = FALSE, $cmd = FALSE) {

  if ($cmd == 'saveorder') {
    $file_xml = 'xml_saveorder.xml';
    $file = drupal_get_path('module', 'sync_rkeeper') . '/includes/test/' . $file_xml;

  } elseif ($cmd == 'addreservation') {
    $file_xml = 'xml_reservacion.xml';
    $file = drupal_get_path('module', 'sync_rkeeper') . '/includes/test/' . $file_xml;

  } else {
    $file_xml = $single ? 'xml_tables.xml' : 'xml.xml';
    $file = drupal_get_path('module', 'sync_rkeeper') . '/includes/test/' . $file_xml;
  }

  if (file_exists($file)) {
    $xml = simplexml_load_file($file);

  } else {
    $options = 'Failed to open xml.xml.';
    return $options;
  }

  return $xml;
}

/**
 * Запрос списка продуктов с r-keeper`а.
 *
 * @return
 *   Массив со столиками, товаром, категориями
 */
function sync_rkeeper_query_product() {
  $options = array();
  $query = '<RK7Command CMD="GetRefData" RefName="Menuitems" IgnoreEnums="1" WithChildItems="3" WithMacroProp="1" OnlyActive="1" PropMask="Code, Name, PortionWeight, PortionName, Kurs.Code, LargeImagePath"/>
          <RK7Command CMD="GetRefData" RefName="Categlist" IgnoreEnums="1" WithChildItems="3" WithMacroProp="1" OnlyActive="1" PropMask="Code, Name, VisualType_Image"/>
          <RK7Command CMD="GetRefData" RefName="Tables" IgnoreEnums="1" WithChildItems="3" WithMacroProp="1" PropMask="Code, Name, MaxGuests, Hall, Status"/>
          ';
//  Отправляем запрос и получаем данные с r-keeper`а
//  $xml = sync_rkeeper_query_rkeeper($query);
  $xml = sync_rkeeper_query_test_rkeeper($query);

  foreach ($xml->CommandResult as $key1 => $vall1) {

    $cmd = (string) $vall1->attributes();
    switch ($cmd['CMD']) { // Получение атрибутов элемента по индексу
      case 'Categlist':
        foreach ($vall1->RIChildItems as $key => $vall) {
          $vall = (array) $vall;
          $options['categlist'][$vall['Code']] = array(
            'code' => $vall['Code'],
            'name' => $vall['Name'],
            'parent' => $vall['Parent'],
            'visual_type_image' => $vall['VisualType_Image'],
          );
        }
        break;

      case 'Menuitems':
        foreach ($vall1->RIChildItems as $key => $vall) {
          $vall = (array) $vall;
          $options['menuitems'][$vall['Code']] = array(
            'code' => $vall['Code'],
            'name' => $vall['Name'],
            'portion_weight' => $vall['PortionWeight'],
            'portion_name' => $vall['PortionName'],
            'kurs_code' => $vall['KursCode'],
            'min_tarif_amount' => $vall['MinTarifAmount'],
            'large_image_path' => $vall['LargeImagePath'],
          );
        }
        break;

      case 'Tables':
        foreach ($vall1->RIChildItems as $key => $vall) {
          $vall = (array) $vall;
          $options['tables'][$vall['Code']] = array(
            'code' => $vall['Code'],
            'name' => $vall['Name'],
            'max_guests' => $vall['MaxGuests'],
            'hall' => $vall['Hall'],
            'status' => $vall['Status'],
          );
        }
        break;
    }
  }

  return $options;
}

/**
 * Получение от сервера списка свободных столиков
 *
 * @return
 *   Массив со столиками
 */
function sync_rkeeper_query_tables(){
  $query = '<RK7CMD CMD="GetRefData" RefName="Tables" IgnoreEnums="1" WithChildItems="3" WithMacroProp="1" OnlyActive="1" PropMask="Code"/>';

//  Отправляем запрос и получаем данные с r-keeper`а
//  $xml = sync_rkeeper_query_rkeeper($query, TRUE);
  $xml = sync_rkeeper_query_test_rkeeper($query, TRUE);
  $cmd = (string) $xml->attributes();
  if (isset($cmd['Status']) && $cmd['Status'] == 'No changes') {
    return 'No changes';
  };

  $options= array();
  foreach ($xml->RIChildItems as $key => $vall) {
    $options[] = (string) $vall->Code;
  }

  return $options;
}

/**
 * Резервируем столик на определенную дату и время
 *
 * @param $data
 *   Данные для резервирования стола
 */
function sync_rkeeper_query_addreservation($data) {
//  Пример запроса:
//  <RK7CMD CMD="AddReservation" Source="">
//    <Reservations>
//        <Reserv TableID="" HallID="" GuestsCount="" ReservDate="" ReservTime="" ClientName="" Comment=""/>
//    </Reservations>
//  </RK7CMD>
  $query = '<RK7CMD CMD="AddReservation" Source="' . RKEEPER_SOURCE . '">
              <Reservations>
                  <Reserv TableID="' . $data['tableid'] . '"
                    HallID="' . $data['hallid'] . '"
                    GuestsCount="' . $data['guestscount'] . '"
                    ReservDate="' . $data['reservdate'] . '"
                    ReservTime="' . $data['reservtime'] . '"
                    ClientName="' . $data['clientname'] . '"';
  $query .= !empty($data['comment'])? 'Comment="' . $data['comment'] . '"': '';
  $query .= '/>
              </Reservations>
            </RK7CMD>';

//  Отправляем запрос и получаем данные с r-keeper`а
//  $xml = sync_rkeeper_query_rkeeper($query, TRUE 'addreservation');
//	  //XML
//	  <Order orderIdent="..."/>
  $xml = sync_rkeeper_query_test_rkeeper($query, TRUE, 'addreservation');
  $orderIdent = (string) $xml->Order->attributes();

//  Возврящает номер заказа
  return $orderIdent;
}

/**
 * Отправка заказа на r-keeper и сохранение
 *
 * @param $data
 *   Данные для отправки заказа
 *
 * @return
 *   $orderIdent - номер заказа
 */
function sync_rkeeper_query_saveorder($data){
  // ! ID заказа
  $orderident = $data['orderident'];
  // ! Время, к которому блюда должны быть готовы, datetime
  $remindtime = $data['remindtime'];
  // Блюдо, refitem + unbounded
  $dish = $data['dish'];
  // ! Целое количество в тысячных долях
  // $data['dish']['quantity'];
  // ! Сумма предоплаты (в копейках), integer
  $amount = $data['amount'];
  // Причина, на которую сделана предоплата, refitem
  $reason = $data['reason'];
  // Код карточки, string для скидки
  $cardcode = $data['cardcode'];


//  Пример запроса:
//  <RK7CMD CMD="SaveOrder">
//    <Order orderIdent=""/>
//    <Session remindTime="">
//        <Dish quantity=""><refitem name="code"/></Dish>
//        <Dish quantity=""><refitem name="code"/></Dish>
//        <Prepay amount="" Reason="" cardCode=""/>
//    </Session>
//  </RK7CMD>
  $query = '<RK7CMD CMD="SaveOrder">
                  <Order orderIdent="' . $orderident . '"/>
                  <Session remindTime="' . $remindtime . '">
                  ';

  $query_dish = '';
  foreach ($dish as $key => $vall) {
    $query_dish .= '<Dish quantity="' . $vall['quantity'] . '"><refitem name="' . $vall['code'] . '"/></Dish>
    ';
  }

  $query .= $query_dish;
  $query .= '<Prepay amount="' . $amount . '" Reason="' . $reason . '" cardCode="' . $cardcode . '"/>
                  </Session>
                </RK7CMD>';

//  dpm($query, '$query');
//  Отправляем запрос и получаем данные с r-keeper`а
//  $xml = sync_rkeeper_query_rkeeper($query, TRUE 'saveorder');
//      return
//      <Order orderIdent=""/>
//	    <Error ErrorText="" RK7ErrorN=""/>
  $xml = sync_rkeeper_query_test_rkeeper($query, TRUE, 'saveorder');
  $orderIdent = (string) $xml->Order->attributes();

//  Возврящает номер заказа
  return $orderIdent;
}

/**
 * Тестовая функция для удаления товаров 'menuitems' 'tables' 'categlist' 'all' 'allall'
 */
function sync_rkeeper_delele($obj) {
  if (!defined('RKEEPER_VOCABULARY_VID')) {
    $voc = taxonomy_vocabulary_machine_name_load(RKEEPER_VOCABULARY_NAME);
    define('RKEEPER_VOCABULARY_VID', $voc->vid);
  }

  if ($obj == 'categlist') {
    $term = taxonomy_term_load_multiple(FALSE, array('vid' => RKEEPER_VOCABULARY_VID));
    foreach ($term as $key => $vall) {
      taxonomy_term_delete($key);
    }

  } elseif ($obj == 'allall') {
    $prod_load = commerce_product_load_multiple(FALSE);
    $product_id = array();
    foreach ($prod_load as $key => $vall) {
      $product_id[] = $key;
    }
    dpm($prod_load, '$product_id');
    commerce_product_delete_multiple($product_id);

  } elseif ($obj == 'all') {

//  Удаляем все заказы для удаления продуктов
    $rez = commerce_order_load_multiple(FALSE);
    commerce_order_delete_multiple(array_keys($rez));

    $term = taxonomy_term_load_multiple(FALSE, array('vid' => RKEEPER_VOCABULARY_VID));
    foreach ($term as $key => $vall) {
      taxonomy_term_delete($key);
    }

    $prod_load = commerce_product_load_multiple(FALSE, array('type' => 'menuitems'));
    $product_id = array();
    foreach ($prod_load as $key => $vall) {
      $product_id[] = $key;
    }
    commerce_product_delete_multiple($product_id);

    $prod_load = commerce_product_load_multiple(FALSE, array('type' => 'tables'));
    $product_id = array();
    foreach ($prod_load as $key => $vall) {
      $product_id[] = $key;
    }
    commerce_product_delete_multiple($product_id);

  } else {
    $prod_load = commerce_product_load_multiple(FALSE, array('type' => $obj));
    $product_id = array();
    foreach ($prod_load as $key => $vall) {
      $product_id[] = $key;
    }
    commerce_product_delete_multiple($product_id);
  }
}

function sync_rkeeper_test() {
  $result = 'Тестовая страница';

  $menuitems['menuitems'][14] = array(
    'code' => 14,
    'name' => 'nava',
    'portion_weight' => 234,
    'portion_name' => 'df',
    'kurs_code' => 2,
    'min_tarif_amount' => 12345,
    'large_image_path' => 'http://recepttoday.ru/_nw/2/66013019.jpg',
  );

  $menuitems['menuitems'][14]['categlist'][2] = array(
    'code' => 2,
    'name' => 'Name1',
    'parent' => 16,
    'visual_type_image' => 'http://recepttoday.ru/_nw/2/66013019.jpg',
  );
  $tid = array(
    'code' => 555,
    'name' => 'Name1',
    'parent' => 16,
    'visual_type_image' => 'http://recepttoday.ru/_nw/2/66013019.jpg',
  );
  $node = array(
    'title' => 'ИМЯ1',
    'tid' => 1,
    'code' => 1,
  );

//  $rez =  sync_rkeeper_category($tid);

//  ЗАМЕТКИ
//  функция отображения заказа пользователю
//  commerce_order_ui_order_view($order, $view_mode = 'administrator')

//  node_type_delete()
//  entity_delete('node', )
//  'categlist' 'all' FALSE
//  sync_rkeeper_delele('allall');
//  sync_rkeeper_delele('all');
//  sync_rkeeper_delele('categlist');

//  sync_rkeeper_category($tid);

//  $nids = db_select('node', 'n')
//    ->fields('n', array('nid'))
//    ->condition('n.type', RKEEPER_NODE_TYPE)
//    ->execute()
//    ->fetchCol();
//  foreach ($nids as $nid) {
//    node_delete($nid);
//  }


//  Возврящает номер заказа


//  Удаляем все заказы для удаления продуктов
//  $rez = commerce_order_load_multiple(FALSE);
//  commerce_order_delete_multiple(array_keys($rez));

//  $rez = sync_rkeeper_create();


  $rez = (isset($rez) and !is_null($rez) and !empty($rez))? $rez: 'Переменная $rez - пуста или isset is_null empty';
  dpm($rez, '$rez (Результат работы TEST)');
//  return $result? $result: 'uuu';
  $result = (isset($result) and !is_null($result) and !empty($result))? $rez: 'Переменная $result - пуста';
  return $result;
}

/**
 * Первая синхронизация с административной панели
 *
 * @return
 *   $count_update - массив колличеством созданных данных: categlist, tables, menuitems
 */
function sync_rkeeper_create() {
//  sync_rkeeper_delele('all');

//  получения списка блюд и свободных столиков от rkeeper
//  $options['menuitems'][$vall['Code']] = array('code' => $vall['Code'] ... ),
  $count_update = array();
  $product_list_rkeeper = sync_rkeeper_query_product();

  $count_update['categlist'] = sync_rkeeper_category($product_list_rkeeper['categlist'], TRUE);
  $count_update['tables'] = sync_rkeeper_tables($product_list_rkeeper['tables']);
  $count_update['menuitems'] = sync_rkeeper_product_site('create', array(
    'menuitems' => $product_list_rkeeper['menuitems'],
    'categlist' => $product_list_rkeeper['categlist'],
  ));

  variable_set('sync_rkeeper_settings_sync', TRUE);

  return $count_update;
}

/**
 * Сравнение данных сайта и rkeeper, добавление, отключения статуса.
 *
 * @return
 *   Синхронизируется товар, возвращается:
 *   array(menuitems_create, menuitems_disable, tables_update) статистика
 */
function sync_rkeeper_comparison_product(){
//  получения списка блюд и свободных столиков от rkeeper
//  $options['menuitems'][$vall['Code']] = array('code' => $vall['Code'] ... ),
  $product_list_rkeeper = sync_rkeeper_query_product();
  dpm($product_list_rkeeper, '$product_list_rkeeper получения списка блюд и свободных столиков от rkeeper');

//  Получения списка блюд и столиков с сайта
//  $product_id[$vall->type][$key] = $vall->status;
  $product_list_site = sync_rkeeper_product_site();
  dpm($product_list_site, '$product_list_rkeeper Получения списка блюд и столиков с сайта');

  $comparison_data = array();

  // Сравниваем меню и столики
  foreach ($product_list_rkeeper as $key => $vall) {
    switch ($key) {

//      Добавление удаление блюда
      case 'menuitems':
        foreach ($vall as $key1 => $vall1) {
          if (!array_key_exists($key1, $product_list_site['menuitems'])) {
            $comparison_data['menuitems_create'][$key1] = $vall1;
            $categlist = $product_list_rkeeper['categlist'][$vall1['kurs_code']];
            $comparison_data['menuitems_create'][$key1]['categlist'] = $categlist;
          }
        }

        foreach ($product_list_site['menuitems'] as $key2 => $vall2) {
          if (!array_key_exists($key2, $vall) and $vall2['status'] == 0) {
            $comparison_data['menuitems_disable'][] = $vall2['product_id'];
          }
        }
        break;
    }
  }

//  Create menuitems
  if (isset($comparison_data['menuitems_create'])) {
    sync_rkeeper_product_site('create', $comparison_data['menuitems_create']);
  }

//  Disable menuitems
  if (isset($comparison_data['menuitems_disable'])) {
    sync_rkeeper_product_site('disable', $comparison_data['menuitems_disable']);
  }

//  Update tables
  $tables_update = sync_rkeeper_tables();

//  Statistic
  $comparison_data = array(
    'menuitems_create' => isset($comparison_data['menuitems_create'])? count($comparison_data['menuitems_create']): 0,
    'menuitems_disable' => isset($comparison_data['menuitems_disable'])? count($comparison_data['menuitems_disable']): 0,
    'tables_update' => isset($tables_update)? $tables_update: 0,
  );

  return $comparison_data;
}

/**
 * Получение, создание нового продукта
 *
 * @param
 *   $action = FALSE Действие с товаром
 *
 * @param
 *   $data = FALSE Данные для действия
 *
 * @return
 *   array() product_id
 */
function sync_rkeeper_product_site($action = FALSE, $data = FALSE){
  $update_count = 0;
//  Для меню
//  $data[$vall['Code']] = array('code' => $vall['Code'] ... ),
  if ($action == 'create') {

    $form_state = array();
    $form_state['values'] = array();
    $form = array();
    $form['#parents'] = array();

    foreach ($data['menuitems'] as $key => $vall) {
      // Generate a new product object
      $new_product = commerce_product_new('menuitems');
      $new_product->status = 1;
      $new_product->uid = isset($GLOBALS['user'])? $GLOBALS['user']->uid: 1;
      $new_product->sku = 'menuitems-' . $vall['code'];
      $new_product->title = $vall['name'];
      $new_product->created = $new_product->changed = time();

      //commerce_price[und][0][amount] = 333 * 100;
      $price = array(
        LANGUAGE_NONE => array(
          0 => array(
            'amount' => $vall['min_tarif_amount'],
            'currency_code' => commerce_default_currency(),
          )
        )
      );
      $form_state['values']['commerce_price'] = $price;
      $tid = sync_rkeeper_category($data['categlist'][$vall['kurs_code']]);

      $form_state['values']['rk_code'][LANGUAGE_NONE][0]['value'] = $vall['code'];
      $form_state['values']['field_kurs_code'][LANGUAGE_NONE][0]['tid'] = $vall['kurs_code'];
      $form_state['values']['rk_portion_weight'][LANGUAGE_NONE][0]['value'] = $vall['portion_weight'];
      $form_state['values']['rk_portion_name'][LANGUAGE_NONE][0]['value'] = $vall['portion_name'];

      if (!empty($vall['large_image_path'])) {
        $file = sync_rkeeper_save_file($vall['large_image_path']);
        $form_state['values']['rk_image'][LANGUAGE_NONE][0] = (array) $file;
      }
      field_attach_submit('commerce_product', $new_product, $form, $form_state);

//      Создаем продукт
      if (commerce_product_save($new_product) == 0) {
        return FALSE;
      };

//      Создаем node для товара
      $node_vall = array(
        'title' => $vall['name'],
        'tid' => $tid,
        'product_id' => $new_product->product_id,
      );
      if (sync_rkeeper_create_node($node_vall) != TRUE) {
        return FALSE;
      };
      $update_count++;
    }
    return $update_count;

//    Отключаем продукт. Товар будет недоступен
  } elseif ($action == 'disable') {
    foreach ($data as $key => $vall) {
      db_update('commerce_product')
        ->fields(array('status' => 0))
        ->condition('product_id', $vall)
        ->execute();

      $update_count++;
    }

    return $update_count;

  } else {
    $prod_load = commerce_product_load_multiple(FALSE, array('type' => array('menuitems', 'tables')));
    $product_id = array();
    foreach ($prod_load as $key => $vall) {
      $product_id[$vall->type][$vall->rk_code['und'][0]['value']]['status'] = $vall->status;
      $product_id[$vall->type][$vall->rk_code['und'][0]['value']]['product_id'] = $key;
    }

    return $product_id;
  }
}

/**
 * Создаем node для товара
 *
 * @param $node_vall
 *   $node_vall = array(
 *     'title' => '',
 *     'tid' => '',
 *     'product_id' => '',
 *   );
 */
function sync_rkeeper_create_node($node_vall = array()) {

  $node = new stdClass(); // Создаем объект node
  $node->type = RKEEPER_NODE_TYPE; // Определяем тип создаваемого материала
  node_object_prepare($node); // добавляем настройки по-умолчанию

  $node->title    = $node_vall['title']; // Название материала
  $node->language = LANGUAGE_NONE; // Или например 'ru', если включен модуль locale
  $node->uid = 1; // UID пользователя

// Заполнение поля body
  $node->body[$node->language][0]['value'] = '';
  $node->body[$node->language][0]['summary'] = '';
  $node->body[$node->language][0]['format']  = 'filtered_html';

  $node->path = array('alias' => $node_vall['title']); // путь к материалу, для модуля path

  // Дополнительные  свойства ноды
  $node->status = 1; // Опуликовано (1) или нет (0)
  $node->promote = 0; // Размещено на главной  (1) или нет (0)
  $node->sticky = 1; // Закреплено вверху списков  (1) или нет (0)
  $node->comment = 2; // Комментарии включены  (2) или нет (1)
  $node->rk_kategori[LANGUAGE_NONE][]['tid'] = $node_vall['tid'];
  $node->rk_product[LANGUAGE_NONE][]['product_id'] = $node_vall['product_id'];

//  dpm($node, '$node$node$node');
  if($node = node_submit($node)) { // Подготовка к сохранению
    node_save($node); // Сохранение ноды, теперь доступен nid новой ноды $node->nid
  }

  return TRUE;
}

/**
 * Если $data - создаем столики
 * Иначе - обновляем статус столиков
 *
 * @param $data
 *   array(code) столика
 *
 * @param $complete
 *   array(code->status) столика (свободный)
 */
function sync_rkeeper_tables($data = FALSE) {
  $update_count = 0;
  $update = array();

  if ($data) {
    $form_state = array();
    $form_state['values'] = array();
    $form = array();
    $form['#parents'] = array();

    foreach ($data as $key => $vall) {
      // Generate a new product object
      $new_product = commerce_product_new('tables');
      $new_product->status = $vall['status'];
      $new_product->uid = isset($GLOBALS['user']) ? $GLOBALS['user']->uid : 1;
      $new_product->sku = 'tables-' . $vall['code'];
      $new_product->title = $vall['name'];
      $new_product->created = $new_product->changed = time();

      //commerce_price[und][0][amount] = 333 * 100;
      $price = array(
        LANGUAGE_NONE => array(
          0 => array(
            'amount' => 0,
            'currency_code' => commerce_default_currency(),
          )
        )
      );
      $form_state['values']['commerce_price'] = $price;
      $form_state['values']['rk_code'][LANGUAGE_NONE][0]['value'] = $vall['code'];
      $form_state['values']['rk_hall'][LANGUAGE_NONE][0]['value'] = $vall['hall'];
      $form_state['values']['rk_maxguests'][LANGUAGE_NONE][0]['value'] = $vall['max_guests'];

      field_attach_submit('commerce_product', $new_product, $form, $form_state);
      if (commerce_product_save($new_product) == 0) {
        return FALSE;
      };

      $update_count++;
    }
    return $update_count;

  } else {
    $update['count'] = 0;
//    return array('key' => 1);
    $data_tables = sync_rkeeper_query_tables();

    if ($data_tables == 'No changes') {
      return 0;
    }

//    Получения списка столиков с сайта
    $prod_load = commerce_product_load_multiple(array(), array('type' => array('tables')));

    db_update('commerce_product')
      ->fields(array('status' => 0))
      ->condition('type', 'tables')
      ->execute();

    foreach ($data_tables as $key => $vall) {
      foreach ($prod_load as $key1 => $vall1) {

        if ($vall == $vall1->rk_code['und'][0]['value']) {
          db_update('commerce_product')
            ->fields(array('status' => 1))
            ->condition('product_id', $vall1->product_id)
            ->execute();
          $update[$vall]['id'] = $vall;
          $update[$vall]['name'] = $vall1->title;
          $update[$vall]['hall'] = $vall1->rk_hall['und'][0]['value'];
          $update['count']++;
          break;
        }
      }
    }
  }

//  $update = array('id', 'name', 'hall', 'count');
  return $update;
}

/**
 * Получение, создание новой категории
 *
 * @param $tid
 *   id термина таксономии
 *
 * @param $create
 *   Если TRUE создаем новый товар
 */
function sync_rkeeper_category($tid = array(), $create = FALSE){

  if (!defined('RKEEPER_VOCABULARY_VID')) {
    $voc = taxonomy_vocabulary_machine_name_load(RKEEPER_VOCABULARY_NAME);
    define('RKEEPER_VOCABULARY_VID', $voc->vid);
  }

  $term_field_id = array();
  $update_count = 0;

  if ($create) {
    foreach ($tid as $key => $vall) {
      $tid_parent = db_select('field_data_rk_code', 'f')
        ->fields('f', array('entity_id'))
        ->condition('bundle', RKEEPER_VOCABULARY_NAME, '=')
        ->condition('rk_code_value', $vall['parent'], '=')
        ->execute()
        ->fetchField();

      $parent = empty($tid_parent)? 0: $tid_parent;
      $new_term = new stdClass();
      $new_term->vid = RKEEPER_VOCABULARY_VID;
      $new_term->name = $vall['name'];
      $new_term->parent = $parent;
      $new_term->rk_code[LANGUAGE_NONE][0]['value'] = $vall['code'];
      $new_term->rk_status[LANGUAGE_NONE][0]['value'] = 1;

      $file = sync_rkeeper_save_file($vall['visual_type_image']);
      if ($file) {
        $new_term->rk_image[LANGUAGE_NONE][] = (array) $file;
      }

      if (taxonomy_term_save($new_term) == 0) {
        return FALSE;
      };
      $update_count++;
    }
    return $update_count;

  } else {
    $term = taxonomy_term_load_multiple(FALSE, array('vid' => RKEEPER_VOCABULARY_VID));
    $term = array_keys($term);

    foreach ($term as $key => $vall) {
      $node_wrapper = entity_metadata_wrapper('taxonomy_term', $vall);
      $term_field_id[$node_wrapper->rk_code->value()] = $vall;
    }

//  Если нет теримна - создаем
    if (!array_key_exists($tid['code'], $term_field_id)) {
      $parent = isset($term_field_id[$tid['parent']])? $term_field_id[$tid['parent']]: 0;
      $new_term = new stdClass();
      $new_term->vid = RKEEPER_VOCABULARY_VID;
      $new_term->name = $tid['name'];
      $new_term->parent = $parent;
      $new_term->rk_code[LANGUAGE_NONE][0]['value'] = $tid['code'];
      $new_term->rk_status[LANGUAGE_NONE][0]['value'] = 1;

      $file = sync_rkeeper_save_file($tid['visual_type_image']);
      if ($file) {
        $new_term->rk_image[LANGUAGE_NONE][] = (array) $file;
      }

      taxonomy_term_save($new_term);
    }

//    Возвращаем TID с указаным code
    return $term_field_id[$tid['code']];
  }
}

/**
 * Загрузка указаного изображения на сайт
 *
 * @param $file_path
 *   url адрес для загрузки файла
 */
function sync_rkeeper_save_file($file_path) {
  //найдем расширение файла
  $basename = basename($file_path);
  if (strrpos($basename, '.') !== false) {
    $file_extension = substr($basename, strrpos($basename, '.')+1);
  } else {
    $file_extension = '';
  }
// путь для сохранения файла вместе с именем файла.
  $destination='public://logo_' . time() . '.' . $file_extension;
// Загружаем путь
  $data = drupal_http_request($file_path);
// Проверяем на успешную загрузку
  if($data->code == 200){
    //Сохраняем файл
    $file = file_save_data($data->data, $destination);
    return $file;
  }
}


