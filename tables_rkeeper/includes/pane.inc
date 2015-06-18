<?php
/**
 * @file pane.inc
 */

module_load_include('inc', 'sync_rkeeper', 'includes/sync_rkeeper_connect_query');

/**
 * form callback.
 */
function tables_rkeeper_checkout_form($form, &$form_state, $checkout_pane, $order) {

//  Описание залов
  $pane_form['tables_fieldset'] = array(
    '#type' => 'fieldset',
    '#description' => t('В суши баре токио имеется 2 зала, выберите для себя подходящее место для резервации.'),
  );
  $pane_form['tables_fieldset']['item1'] = array(
    '#type' => 'item',
    '#title' => t('Зал №1'),
    '#description' => t('
      Зал ресторан. Играет спокойная музыка, больше всего подходит для семьи, детей, для людей, которые пришли спокойно посидеть, пообщаться.
      В зале расположены 6 мягких зон, 3 столика, 1 телевизор и 1 терминал по которому можно за 50 рублей заказать музыку.
      Вход в выходные и будние дни – бесплатный.'),
  );
  $pane_form['tables_fieldset']['fieldset1'] = array(
    '#type' => 'fieldset',
    '#title' => t('Смотреть план зала №1'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $pane_form['tables_fieldset']['fieldset1']['img'] = array(
    '#type' => 'markup',
    '#title' => t('Выберите столик'),
    '#markup' => _tables_img(1),
  );
  $pane_form['tables_fieldset']['item2'] = array(
    '#type' => 'item',
    '#title' => t('Зал №2'),
    '#description' => t('
      Караоке зал. Караоке работает с 9 вечера до 6 утра. До 9 часов вечера играет спокойная музыка,
      приходят гости пообедать или поужинать. После девяти часов вечера начинает работать караоке,
      имеется ди-джей, который принимает заявки на песни.
      Зал содержит в себе 8 мягких зон 2 столика, 4 телевизора на стенах и 4 в столах, на мягких зонах.
      Вход в будние дни – бесплатный, в выходные c 20:00 – депозит с человека 600 рублей -
      это минимальная сумму на которую должнен гость заказать по меню'),
  );
  $pane_form['tables_fieldset']['fieldset2'] = array(
    '#type' => 'fieldset',
    '#title' => t('Смотреть план зала №2'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $pane_form['tables_fieldset']['fieldset2']['img'] = array(
    '#type' => 'markup',
    '#title' => t('Выберите столик'),
    '#markup' => _tables_img(2),
  );

//  Выбор данных
  $pane_form['tables_fieldset_tables'] = array(
    '#type' => 'fieldset',
    '#description' => t('ВНИМАНИЕ!!!<rb>
            Выбрав столик на определенное время, администратор заведения проверит, на то, что бы он был свободен.
            В том случае если столик на выбранное время будет занят, вам в ближайшее время позвонят и предложат
            другой подходящий вариант.'),
  );

//  Выбор зала
  $pane_form['tables_fieldset_tables']['holl'] = array(
    '#type' => 'radios',
    '#title' => t('Зал'),
    '#options' => array(
      1 => t('№1'),
      2 => t('№2'),
    ),
    '#required' => TRUE,
  );

//  Выбор столика
  $tables = _tables_load();
  $pane_form['tables_fieldset_tables'][1]['tableid'] = array(
    '#type' => 'select',
    '#title' => t('Свободные столики зала №1'),
    '#options' => $tables[1],
    '#states' => array(
      'visible' => array(
        ':input[name="tables_rkeeper_pane[tables_fieldset_tables][holl]"]' => array('value' => 1),
      ),
    ),
  );
  $pane_form['tables_fieldset_tables'][2]['tableid'] = array(
    '#type' => 'select',
    '#title' => t('Свободные столики зала №2'),
    '#options' => $tables[2],
    '#states' => array(
      'visible' => array(
        ':input[name="tables_rkeeper_pane[tables_fieldset_tables][holl]"]' => array('value' => 2),
      ),
    ),
  );

  $form_state['table_name'] = $tables;

  return $pane_form;
}

/**
 * Изображение плана зала
 */
function _tables_img($hall) {
  $variables = array(
    'path' => drupal_get_path('module', 'tables_rkeeper') . '/img/holl_' . $hall . '.jpeg',
    'alt' => 'Расположение столиков в зале № ' . $hall,
    'title' => 'Расположение столиков в зале № ' . $hall,
    'width' => '600px',
    'height' => ($hall == 2)? '350px': '300px',
    'attributes' => array('class' => 'some-img', 'id' => 'my-img' . $hall),
  );
  $markup = theme_image($variables);

  return $markup;
}

/**
 * Получения списка свободных столов
 */
function _tables_load() {
  $tables = sync_rkeeper_tables();
  $tables_free = array();

  foreach ($tables as $key => $vall) {
    if ($vall['hall'] == 1) {
      $tables_free[1][$vall['id']] = $vall['name'];

    } elseif ($vall['hall'] == 2) {
      $tables_free[2][$vall['id']] = $vall['name'];
    }
  }

  return $tables_free;
}

/**
 * checkout form submission callback.
 */
function tables_rkeeper_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  $tables = $form_state['values']['tables_rkeeper_pane']['tables_fieldset_tables'];
  $tables_hall = $tables['holl'];
  $tables_id = $tables[$tables_hall]['tableid'];
  $tables_name = $form_state['table_name'][$tables_hall][$tables_id];
  $order->data['tables_id'] = $tables_id;

  if (isset($order->commerce_customer_billing['und'][0]['profile_id'])) {
    $profile_id = $order->commerce_customer_billing['und'][0]['profile_id'];

  } else {
    $profile = commerce_customer_profile_new();
    $profile->type = 'billing';
    commerce_customer_profile_save($profile);

    $profile_id = $profile->profile_id;
    $order->commerce_customer_billing['und'][0]['profile_id'] = $profile_id;
    commerce_order_save($order);
  }

  $profile_wrapper = entity_metadata_wrapper('commerce_customer_profile', $profile_id);
  $profile_wrapper->rk_hall = $tables_hall;
  $profile_wrapper->field_rk_tables = $tables_name;
  $profile_wrapper->field_rk_order = $order->order_id;
  $profile_wrapper->save();
}












