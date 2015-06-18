<?php
/**
 * @file sync_rkeeper_product_ui.inc
 */


module_load_include('inc', 'sync_rkeeper', 'includes/sync_rkeeper_connect_query');	// Загрузка файла flag.pages.inc, конкретного модуля

/**
 * Form sync_rkeeper_product
 */
function sync_rkeeper_product_form($form, &$form_state) {
  $form = array();
  $form['#tree'] = TRUE;

  if (!isset($form_state['count_update'])) {
    $form_state['count_update'] = array();
  }

  if (!variable_get('rkeeper_sync_settings', FALSE)) {
    $form_state['count_update'] = sync_rkeeper_create();
    variable_set('rkeeper_sync_settings', $form_state['count_update']);
  } else {
    $form_state['count_update'] = variable_get('rkeeper_sync_settings', FALSE);
  }

  $form['container_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Синхронизация'),
    '#prefix' => '<div id="sync_rkeeper_product_container_settings">',
    '#suffix' => '</div>',
  );

  $form['container_settings']['submit_settings'] = array(
    '#type' => 'submit',
    '#value' => t('Синхронизировать'),
    '#submit' => array('sync_rkeeper_product_submit_sync'),
    '#disabled' => variable_get('rkeeper_sync_settings', FALSE)? TRUE: FALSE,
    '#ajax' => array(
      'callback' => 'sync_rkeeper_product_callback',
      'wrapper' => 'sync_rkeeper_product_container',
    ),
  );

  $form['container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Данные синхронизации'),
    '#prefix' => '<div id="sync_rkeeper_product_container">',
    '#suffix' => '</div>',
  );

  if (!variable_get('rkeeper_sync_settings', FALSE)) {
    $form['container']['note'] = array(
      '#type' => 'item',
      '#title' => t('Внимание!!!'),
      '#description' => t('Вы еще не синхронизовались с R-Keeper`ом. Для синхронизиции, нажмите на кнопку.'),
    );

  } else {
    $form['container']['note'] = array(
      '#type' => 'item',
      '#title' => t('Синхронизация выполнена!'),
      '#description' => t('Синхронизация с R-Keeper`ом прошла успешно.'),
    );
    $form['container']['status_fieldset']['status'] = array(
      '#type' => t('markup'),
      '#markup' => t('Добавленные категории: <b>@kat</b> <br>
                    Добавленные блюда: <b>@dish</b> <br>
                    Добавленные столы: <b>@tab</b>', array('@kat' => $form_state['count_update']['categlist'],
                          '@dish' => $form_state['count_update']['menuitems'],
                          '@tab' => $form_state['count_update']['tables'])),
    );
  }
  return $form;
}

/**
 * ajax
 */
function sync_rkeeper_product_callback($form, $form_state) {
  return $form['container'];
}

/**
 * submit
 */
function sync_rkeeper_product_submit_sync($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

