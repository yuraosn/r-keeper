<?php
/**
 * @file commerce_rkeeper_settings_ui.inc
 */

/*
 * @see hook_form()
 */
function commerce_rkeeper_settings_form($form, &$form_state) {
  $variables = variable_get('commerce_rkeeper_settings')? variable_get('commerce_rkeeper_settings'): FALSE;

  $form['ip_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Введите IP адрес сервера R-keeper'),
    '#description' => t('Пример: 192.168.0.1'),
    '#size' => 15,
    '#maxlength' => 15,
    '#required' => TRUE,
    '#default_value' => isset($variables['ip_address'])? $variables['ip_address']: '',
  );

  $form['port'] = array(
    '#type' => 'textfield',
    '#title' => t('Введите порт сервера R-keeper'),
    '#description' => t('Пример: 8080'),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#default_value' => isset($variables['port'])? $variables['port']: '',
  );

  $form['commerce_rkeeper_time'] = array(
    '#type' => 'select',
    '#title' => t('Период синхронизации продуктов'),
    '#description' => t('Выберите период для синхронизации продуктов'),
    '#options' => array(
      6 => t('6 ч.'),
      12 => t('12 ч.'),
      24 => t('24 ч.'),
      'other' => t('Другое'),
    ),
    '#default_value' => isset($variables['commerce_rkeeper_time'])? $variables['commerce_rkeeper_time']: 12,
  );

  $form['commerce_rkeeper_other_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Свое время обновления'),
    '#size' => 5,
    '#maxlength' => 3,
    '#field_suffix' => ' ч.',
    '#states' => array(
      'visible' => array(
        ':input[name="commerce_rkeeper_time"]' => array('value' => 'other'),
      ),
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );

  return $form;
}


/**
 * Проверяем введенве данные.
 */
function commerce_rkeeper_settings_form_validate($form, &$form_state) {
  $vall = $form_state['values'];
  $pattern_ip = '/^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$/';
  $pattern_port = '/^[0-9]{2,4}$/';

  if (!preg_match($pattern_ip, $vall['ip_address'])) {
    form_set_error($vall['ip_address'], t('Неверно введен IP Адрес'));
  }

  if (!preg_match($pattern_port, $vall['port'])) {
    form_set_error($vall['ip_address'], t('Неверно введен порт'));
  }

  if ($vall['commerce_rkeeper_time'] == 'other') {
    dpm($vall['commerce_rkeeper_time'], '$vallync_poduct_time]');
    $commerce_rkeeper_other_time = trim($vall['commerce_rkeeper_other_time']);
    if (!is_numeric($commerce_rkeeper_other_time) or is_float($commerce_rkeeper_other_time) or !empty($commerce_rkeeper_other_time) or $commerce_rkeeper_other_time > 168) {
      form_set_error($vall['commerce_rkeeper_other_time'], t('Неверно введено время. Должно содержать только цифры не более 168 (7 дней).'));
    }
  }
}

/**
 * Отправляем форму для сохранения.
 */
function commerce_rkeeper_settings_form_submit($form, &$form_state) {
  $vall = $form_state['values'];

  $variables = array();
  $variables['ip_address'] = $vall['ip_address'];
  $variables['port'] = $vall['port'];
  $commerce_rkeeper_time = ($vall['commerce_rkeeper_time'] == 'other')? $vall['commerce_rkeeper_other_time']: $vall['commerce_rkeeper_time'];
  $variables['commerce_rkeeper_time']['time'] = $commerce_rkeeper_time * 24 * 60 * 60;
  variable_set('commerce_rkeeper_settings', $variables);

  drupal_set_message('Настройки сохранены');
}









