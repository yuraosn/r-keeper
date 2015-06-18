<?php
/**
 * @file sms_rkeeper_settings_ui.php.inc
 */

/**
 * СМС Настройка
 */
function sms_rkeeper_settings_form($form, &$form_state) {
  $data = variable_get('sms_rkeeper_settings', FALSE)? variable_get('sms_rkeeper_settings', FALSE): FALSE;
  $active = variable_get('sms_rkeeper_active', FALSE)? variable_get('sms_rkeeper_active', FALSE): FALSE;

  $form = array();

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Баланс'),
  );
  $form['fieldset']['balans'] = array(
    '#type' => 'markup',
    '#markup' => sms_rkeeper_sms('balans'),
  );

  $form['fieldset_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Настройки'),
  );
  $form['fieldset_set']['active'] = array(
    '#type' => 'radios',
    '#title' => t('Status'),
    '#default_value' => $active? $active: 0,
    '#options' => array(
      TRUE => 'Вкл',
      FALSE => 'Выкл',
    ),
    '#description' => t('Включите для отправки СМС.'),
  );

  $form['fieldset_set']['login'] = array(
    '#type' => 'textfield',
    '#title' => t('Логин'),
    '#default_value' => isset($data['login'])? $data['login']: '',
    '#size' => 20,
    '#maxlength' => 20,
    '#required' => TRUE,
  );

  $form['fieldset_set']['password'] = array(
    '#type' => 'password',
    '#title' => t('Пароль'),
    '#size' => 20,
    '#maxlength' => 20,
  );

  $form['fieldset_set']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Телефон'),
    '#default_value' => isset($data['phone'])? $data['phone']: '+7',
    '#size' => 20,
    '#maxlength' => 20,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Сохранить'),
  );

  return $form;
}

/**
 * Проверяем введенве данные.
 */
function sms_rkeeper_settings_form_validate($form, &$form_state) {
  if(!preg_match('|^[+0-9]+$|i', $form_state['values']['phone'])) {
    form_set_error($form_state['values']['phone'], t('Это не номер телефона'));
    return FALSE;
  }

  if (empty($form_state['values']['password'])) {
    $settings = variable_get('sms_rkeeper_settings', FALSE)? variable_get('sms_rkeeper_settings', FALSE): FALSE;

    if ($settings) {

      if (empty($settings['password'])) {
        form_set_error($form_state['values']['password'], t('Заполните поле - password!!'));

      } else {
        $form_state['values']['password'] = $settings['password'];
      }
    }
  }
}

/**
 * Отправляем форму для сохранения.
 */
function sms_rkeeper_settings_form_submit($form, &$form_state) {
  $active = $form_state['values']['active'];
  variable_set('sms_rkeeper_active', $active);

  $settings = array();
  $settings['login'] = $form_state['values']['login'];
  $settings['password'] = $form_state['values']['password'];
  $settings['phone'] = $form_state['values']['phone'];
  variable_set('sms_rkeeper_settings', $settings);

  drupal_set_message('Настройки сохранены');
}


