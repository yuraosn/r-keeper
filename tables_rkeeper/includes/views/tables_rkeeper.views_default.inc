<?php

/**
 * Implementation of hook_views_default_views().
 */
function tables_rkeeper_views_default_views() {
  $view = new view();
  $view->name = 'tables_holl_1';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_product';
  $view->human_name = 'Столики Зал 1';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Свободные Столики';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'ещё';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Применить';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Сбросить';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Сортировать по';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'По возрастанию';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'По убыванию';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'rk_hall_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'title_1' => 'title_1',
    'rk_maxguests_1' => 'rk_maxguests_1',
    'status' => 'status',
    'rk_hall_1' => 'rk_hall_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rk_maxguests_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rk_hall_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Поле: Commerce Товар: Заголовок */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['label'] = 'Столик';
  $handler->display->display_options['fields']['title_1']['link_to_product'] = 0;
  /* Поле: Commerce Товар: Максимально мест */
  $handler->display->display_options['fields']['rk_maxguests_1']['id'] = 'rk_maxguests_1';
  $handler->display->display_options['fields']['rk_maxguests_1']['table'] = 'field_data_rk_maxguests';
  $handler->display->display_options['fields']['rk_maxguests_1']['field'] = 'rk_maxguests';
  $handler->display->display_options['fields']['rk_maxguests_1']['label'] = 'Мест';
  /* Поле: Commerce Товар: Статус */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Свободен';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Поле: Поле: Зал */
  $handler->display->display_options['fields']['rk_hall_1']['id'] = 'rk_hall_1';
  $handler->display->display_options['fields']['rk_hall_1']['table'] = 'field_data_rk_hall';
  $handler->display->display_options['fields']['rk_hall_1']['field'] = 'rk_hall';
  $handler->display->display_options['fields']['rk_hall_1']['exclude'] = TRUE;
  /* Критерий фильтра: Commerce Товар: Тип */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'commerce_product';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'tables' => 'tables',
  );

  /* Display: Столики */
  $handler = $view->new_display('block', 'Столики', 'rkeeper_tables');
  $handler->display->display_options['display_description'] = 'Столики';
  $handler->display->display_options['block_description'] = 'Свободные Столики';
  $translatables['tables_holl_1'] = array(
    t('Master'),
    t('Свободные Столики'),
    t('ещё'),
    t('Применить'),
    t('Сбросить'),
    t('Сортировать по'),
    t('По возрастанию'),
    t('По убыванию'),
    t('Столик'),
    t('Мест'),
    t('Свободен'),
    t('Зал'),
    t('Столики'),
  );

  $views[$view->name] = $view;

  return $views;
}