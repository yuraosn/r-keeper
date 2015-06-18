<?php

/**
 * Implementation of hook_views_default_views().
 */
function sync_rkeeper_views_default_views() {
  $view = new view();
  $view->name = 'menu';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Меню';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Меню';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'ещё';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access administration menu';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Применить';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Сбросить';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Сортировать по';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'По возрастанию';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'По убыванию';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Элементов на страницу';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Все -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Пропустить';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« первая';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ предыдущая';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'следующая ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'последняя »';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Связь: Содержимое: Категория (rk_kategori) */
  $handler->display->display_options['relationships']['rk_kategori_tid']['id'] = 'rk_kategori_tid';
  $handler->display->display_options['relationships']['rk_kategori_tid']['table'] = 'field_data_rk_kategori';
  $handler->display->display_options['relationships']['rk_kategori_tid']['field'] = 'rk_kategori_tid';
  $handler->display->display_options['relationships']['rk_kategori_tid']['label'] = 'термин';
  $handler->display->display_options['relationships']['rk_kategori_tid']['required'] = TRUE;
  /* Связь: Содержимое: Referenced products */
  $handler->display->display_options['relationships']['rk_product_product_id']['id'] = 'rk_product_product_id';
  $handler->display->display_options['relationships']['rk_product_product_id']['table'] = 'field_data_rk_product';
  $handler->display->display_options['relationships']['rk_product_product_id']['field'] = 'rk_product_product_id';
  $handler->display->display_options['relationships']['rk_product_product_id']['required'] = TRUE;
  /* Поле: Содержимое: Заголовок */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Поле: Commerce Товар: Price */
  $handler->display->display_options['fields']['commerce_price']['id'] = 'commerce_price';
  $handler->display->display_options['fields']['commerce_price']['table'] = 'field_data_commerce_price';
  $handler->display->display_options['fields']['commerce_price']['field'] = 'commerce_price';
  $handler->display->display_options['fields']['commerce_price']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['commerce_price']['label'] = 'Цена';
  $handler->display->display_options['fields']['commerce_price']['exclude'] = TRUE;
  $handler->display->display_options['fields']['commerce_price']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_price']['settings'] = array(
    'calculation' => '0',
  );
  /* Поле: Commerce Товар: Вес порции */
  $handler->display->display_options['fields']['rk_portion_weight']['id'] = 'rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['table'] = 'field_data_rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['field'] = 'rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_portion_weight']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rk_portion_weight']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['rk_portion_weight']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Поле: Commerce Товар: Форма добавления в корзину */
  $handler->display->display_options['fields']['add_to_cart_form']['id'] = 'add_to_cart_form';
  $handler->display->display_options['fields']['add_to_cart_form']['table'] = 'views_entity_commerce_product';
  $handler->display->display_options['fields']['add_to_cart_form']['field'] = 'add_to_cart_form';
  $handler->display->display_options['fields']['add_to_cart_form']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['add_to_cart_form']['exclude'] = TRUE;
  $handler->display->display_options['fields']['add_to_cart_form']['show_quantity'] = 1;
  $handler->display->display_options['fields']['add_to_cart_form']['default_quantity'] = '1';
  $handler->display->display_options['fields']['add_to_cart_form']['combine'] = 1;
  $handler->display->display_options['fields']['add_to_cart_form']['display_path'] = 0;
  $handler->display->display_options['fields']['add_to_cart_form']['line_item_type'] = 0;
  /* Поле: Commerce Товар: Единицы измерения */
  $handler->display->display_options['fields']['rk_portion_name']['id'] = 'rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['table'] = 'field_data_rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['field'] = 'rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_portion_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rk_portion_name']['type'] = 'text_plain';
  /* Поле: Поле: Изображение */
  $handler->display->display_options['fields']['rk_image_1']['id'] = 'rk_image_1';
  $handler->display->display_options['fields']['rk_image_1']['table'] = 'field_data_rk_image';
  $handler->display->display_options['fields']['rk_image_1']['field'] = 'rk_image';
  $handler->display->display_options['fields']['rk_image_1']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_image_1']['label'] = '';
  $handler->display->display_options['fields']['rk_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rk_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['rk_image_1']['settings'] = array(
    'image_style' => 'product_200_200',
    'image_link' => '',
  );
  /* Поле: Commerce Товар: Ссылка на редактирование */
  $handler->display->display_options['fields']['edit_product']['id'] = 'edit_product';
  $handler->display->display_options['fields']['edit_product']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['edit_product']['field'] = 'edit_product';
  $handler->display->display_options['fields']['edit_product']['relationship'] = 'rk_product_product_id';
  /* Поле: Commerce Товар: Ссылка на удаление */
  $handler->display->display_options['fields']['delete_product']['id'] = 'delete_product';
  $handler->display->display_options['fields']['delete_product']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['delete_product']['field'] = 'delete_product';
  $handler->display->display_options['fields']['delete_product']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['delete_product']['exclude'] = TRUE;
  $handler->display->display_options['fields']['delete_product']['text'] = 'Удалить';
  /* Поле: Глобальный: Пользовательский текст */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<table align="center" border="0">
 <caption>[title]</caption>
  <tr>
    <td>Вес порции:</td>
    <td>[rk_portion_weight] [rk_portion_name]</td>
  </tr>
  <tr>
    <td>Цена</td>
    <td>[commerce_price]</td>
  </tr>
  <tr>
    <td>[edit_product]</td>
    <td>[delete_product]</td>
  </tr>
  <tr>
    <td align="center" colspan="2">[add_to_cart_form]</td>
  </tr>
</table>
';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Критерий сортировки: Содержимое: Дата публикации */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Контекстный фильтр: Термин таксономии: ID термина */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['relationship'] = 'rk_kategori_tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['exception']['title'] = 'Все';
  $handler->display->display_options['arguments']['tid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['tid']['title'] = '%1';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Критерий фильтра: Содержимое: Опубликовано */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Критерий фильтра: Содержимое: Тип */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'product' => 'product',
  );

  /* Display: Меню */
  $handler = $view->new_display('page', 'Меню', 'page');
  $handler->display->display_options['display_description'] = 'Меню суши бара Токио';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    1 => '1',
    2 => '2',
  );
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Поле: Содержимое: Заголовок */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Поле: Commerce Товар: Price */
  $handler->display->display_options['fields']['commerce_price']['id'] = 'commerce_price';
  $handler->display->display_options['fields']['commerce_price']['table'] = 'field_data_commerce_price';
  $handler->display->display_options['fields']['commerce_price']['field'] = 'commerce_price';
  $handler->display->display_options['fields']['commerce_price']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['commerce_price']['label'] = 'Цена';
  $handler->display->display_options['fields']['commerce_price']['exclude'] = TRUE;
  $handler->display->display_options['fields']['commerce_price']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_price']['settings'] = array(
    'calculation' => '0',
  );
  /* Поле: Commerce Товар: Вес порции */
  $handler->display->display_options['fields']['rk_portion_weight']['id'] = 'rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['table'] = 'field_data_rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['field'] = 'rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_portion_weight']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rk_portion_weight']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['rk_portion_weight']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Поле: Commerce Товар: Форма добавления в корзину */
  $handler->display->display_options['fields']['add_to_cart_form']['id'] = 'add_to_cart_form';
  $handler->display->display_options['fields']['add_to_cart_form']['table'] = 'views_entity_commerce_product';
  $handler->display->display_options['fields']['add_to_cart_form']['field'] = 'add_to_cart_form';
  $handler->display->display_options['fields']['add_to_cart_form']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['add_to_cart_form']['exclude'] = TRUE;
  $handler->display->display_options['fields']['add_to_cart_form']['show_quantity'] = 1;
  $handler->display->display_options['fields']['add_to_cart_form']['default_quantity'] = '1';
  $handler->display->display_options['fields']['add_to_cart_form']['combine'] = 1;
  $handler->display->display_options['fields']['add_to_cart_form']['display_path'] = 0;
  $handler->display->display_options['fields']['add_to_cart_form']['line_item_type'] = 0;
  /* Поле: Commerce Товар: Единицы измерения */
  $handler->display->display_options['fields']['rk_portion_name']['id'] = 'rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['table'] = 'field_data_rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['field'] = 'rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_portion_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rk_portion_name']['type'] = 'text_plain';
  /* Поле: Поле: Изображение */
  $handler->display->display_options['fields']['rk_image_1']['id'] = 'rk_image_1';
  $handler->display->display_options['fields']['rk_image_1']['table'] = 'field_data_rk_image';
  $handler->display->display_options['fields']['rk_image_1']['field'] = 'rk_image';
  $handler->display->display_options['fields']['rk_image_1']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_image_1']['label'] = '';
  $handler->display->display_options['fields']['rk_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rk_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['rk_image_1']['settings'] = array(
    'image_style' => 'product_200_200',
    'image_link' => '',
  );
  /* Поле: Глобальный: Пользовательский текст */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<table align="center" border="0">
 <caption>[title]</caption>
  <tr>
    <td>Вес порции:</td>
    <td>[rk_portion_weight] [rk_portion_name]</td>
  </tr>
  <tr>
    <td>Цена</td>
    <td>[commerce_price]</td>
  </tr>
  <tr>
    <td align="center" colspan="2">[add_to_cart_form]</td>
  </tr>
</table>
';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'taxonomy/term/%';

  /* Display: Страница */
  $handler = $view->new_display('page', 'Страница', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Меню для администратора';
  $handler->display->display_options['path'] = 'taxonomy/term/%';

  /* Display: Блок Таксономии */
  $handler = $view->new_display('block', 'Блок Таксономии', 'block_taxonomy');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Категория';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Связь: Содержимое: Категория (rk_kategori) */
  $handler->display->display_options['relationships']['rk_kategori_tid']['id'] = 'rk_kategori_tid';
  $handler->display->display_options['relationships']['rk_kategori_tid']['table'] = 'field_data_rk_kategori';
  $handler->display->display_options['relationships']['rk_kategori_tid']['field'] = 'rk_kategori_tid';
  $handler->display->display_options['relationships']['rk_kategori_tid']['label'] = 'термин';
  $handler->display->display_options['relationships']['rk_kategori_tid']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Поле: Поле: Изображение */
  $handler->display->display_options['fields']['rk_image_1']['id'] = 'rk_image_1';
  $handler->display->display_options['fields']['rk_image_1']['table'] = 'field_data_rk_image';
  $handler->display->display_options['fields']['rk_image_1']['field'] = 'rk_image';
  $handler->display->display_options['fields']['rk_image_1']['relationship'] = 'rk_kategori_tid';
  $handler->display->display_options['fields']['rk_image_1']['label'] = '';
  $handler->display->display_options['fields']['rk_image_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rk_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rk_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['rk_image_1']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  /* Поле: Термин таксономии: Имя */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'rk_kategori_tid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Поле: Глобальный: Пользовательский текст */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[rk_image_1]      [name]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Контекстный фильтр: Термин таксономии: ID термина */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['relationship'] = 'rk_kategori_tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['exception']['title'] = 'Все';
  $handler->display->display_options['arguments']['tid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['tid']['title'] = '%1';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Критерий фильтра: Содержимое: Опубликовано */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $translatables['menu'] = array(
    t('Master'),
    t('Меню'),
    t('ещё'),
    t('Применить'),
    t('Сбросить'),
    t('Сортировать по'),
    t('По возрастанию'),
    t('По убыванию'),
    t('Элементов на страницу'),
    t('- Все -'),
    t('Пропустить'),
    t('« первая'),
    t('‹ предыдущая'),
    t('следующая ›'),
    t('последняя »'),
    t('термин'),
    t('Products referenced by rk_product'),
    t('Цена'),
    t('Вес порции'),
    t('Форма добавления в корзину'),
    t('Единицы измерения'),
    t('Ссылка на редактирование'),
    t('Ссылка на удаление'),
    t('Удалить'),
    t('<table align="center" border="0">
 <caption>[title]</caption>
  <tr>
    <td>Вес порции:</td>
    <td>[rk_portion_weight] [rk_portion_name]</td>
  </tr>
  <tr>
    <td>Цена</td>
    <td>[commerce_price]</td>
  </tr>
  <tr>
    <td>[edit_product]</td>
    <td>[delete_product]</td>
  </tr>
  <tr>
    <td align="center" colspan="2">[add_to_cart_form]</td>
  </tr>
</table>
'),
    t('Все'),
    t('%1'),
    t('Меню суши бара Токио'),
    t('<table align="center" border="0">
 <caption>[title]</caption>
  <tr>
    <td>Вес порции:</td>
    <td>[rk_portion_weight] [rk_portion_name]</td>
  </tr>
  <tr>
    <td>Цена</td>
    <td>[commerce_price]</td>
  </tr>
  <tr>
    <td align="center" colspan="2">[add_to_cart_form]</td>
  </tr>
</table>
'),
    t('Страница'),
    t('Меню для администратора'),
    t('Блок Таксономии'),
    t('Категория'),
    t('[rk_image_1]      [name]'),
  );


  $views[$view->name] = $view;









  $view = new view();
  $view->name = 'product';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Продукты';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Продукты';
  $handler->display->display_options['css_class'] = 'rk-product';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'ещё';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Применить';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Сбросить';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Сортировать по';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'По возрастанию';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'По убыванию';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Связь: Содержимое: Referenced products */
  $handler->display->display_options['relationships']['rk_product_product_id']['id'] = 'rk_product_product_id';
  $handler->display->display_options['relationships']['rk_product_product_id']['table'] = 'field_data_rk_product';
  $handler->display->display_options['relationships']['rk_product_product_id']['field'] = 'rk_product_product_id';
  $handler->display->display_options['relationships']['rk_product_product_id']['required'] = TRUE;
  /* Поле: Содержимое: Заголовок */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Поле: Commerce Товар: Price */
  $handler->display->display_options['fields']['commerce_price']['id'] = 'commerce_price';
  $handler->display->display_options['fields']['commerce_price']['table'] = 'field_data_commerce_price';
  $handler->display->display_options['fields']['commerce_price']['field'] = 'commerce_price';
  $handler->display->display_options['fields']['commerce_price']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['commerce_price']['label'] = 'Цена';
  $handler->display->display_options['fields']['commerce_price']['exclude'] = TRUE;
  $handler->display->display_options['fields']['commerce_price']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_price']['settings'] = array(
    'calculation' => '0',
  );
  /* Поле: Commerce Товар: Вес порции */
  $handler->display->display_options['fields']['rk_portion_weight']['id'] = 'rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['table'] = 'field_data_rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['field'] = 'rk_portion_weight';
  $handler->display->display_options['fields']['rk_portion_weight']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_portion_weight']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rk_portion_weight']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Поле: Commerce Товар: Единицы измерения */
  $handler->display->display_options['fields']['rk_portion_name']['id'] = 'rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['table'] = 'field_data_rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['field'] = 'rk_portion_name';
  $handler->display->display_options['fields']['rk_portion_name']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_portion_name']['exclude'] = TRUE;
  /* Поле: Commerce Товар: Форма добавления в корзину */
  $handler->display->display_options['fields']['add_to_cart_form']['id'] = 'add_to_cart_form';
  $handler->display->display_options['fields']['add_to_cart_form']['table'] = 'views_entity_commerce_product';
  $handler->display->display_options['fields']['add_to_cart_form']['field'] = 'add_to_cart_form';
  $handler->display->display_options['fields']['add_to_cart_form']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['add_to_cart_form']['exclude'] = TRUE;
  $handler->display->display_options['fields']['add_to_cart_form']['show_quantity'] = 0;
  $handler->display->display_options['fields']['add_to_cart_form']['default_quantity'] = '1';
  $handler->display->display_options['fields']['add_to_cart_form']['combine'] = 1;
  $handler->display->display_options['fields']['add_to_cart_form']['display_path'] = 0;
  $handler->display->display_options['fields']['add_to_cart_form']['line_item_type'] = 0;
  /* Поле: Поле: Изображение */
  $handler->display->display_options['fields']['rk_image']['id'] = 'rk_image';
  $handler->display->display_options['fields']['rk_image']['table'] = 'field_data_rk_image';
  $handler->display->display_options['fields']['rk_image']['field'] = 'rk_image';
  $handler->display->display_options['fields']['rk_image']['relationship'] = 'rk_product_product_id';
  $handler->display->display_options['fields']['rk_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rk_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['rk_image']['settings'] = array(
    'image_style' => 'rk-product_400_500',
    'image_link' => '',
  );
  /* Поле: Глобальный: Пользовательский текст */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div style="rk-prod-img">
[rk_image]
<div>
<div style="rk-prod-cont">
<strong>[title]</strong><br>
Вес порции: [rk_portion_weight] [rk_portion_name]<br>
Цена: [commerce_price]<br>
[add_to_cart_form]<br>
<div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Контекстный фильтр: Содержимое: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'Все';
  $handler->display->display_options['arguments']['nid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['nid']['title'] = '%1';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Критерий фильтра: Содержимое: Опубликовано */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Критерий фильтра: Содержимое: Тип */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'product' => 'product',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'node/%';
  $translatables['product'] = array(
    t('Master'),
    t('Продукты'),
    t('ещё'),
    t('Применить'),
    t('Сбросить'),
    t('Сортировать по'),
    t('По возрастанию'),
    t('По убыванию'),
    t('Products referenced by rk_product'),
    t('Цена'),
    t('Вес порции'),
    t('Единицы измерения'),
    t('Форма добавления в корзину'),
    t('Изображение'),
    t('<div style="rk-prod-img">
[rk_image]
<div>
<div style="rk-prod-cont">
<strong>[title]</strong><br>
Вес порции: [rk_portion_weight] [rk_portion_name]<br>
Цена: [commerce_price]<br>
[add_to_cart_form]<br>
<div>'),
    t('Все'),
    t('%1'),
    t('Page'),
  );

  $views[$view->name] = $view;

  return $views;
}