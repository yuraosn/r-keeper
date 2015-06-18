<?php
/**
 * @file pane.inc
 */

/**
 * Form callback.
 */
function prepay_rkeeper_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $prepay_amount = isset($order->data['prepay']['amount'])? $order->data['prepay']['amount'] / 100: 0;
  $order_total = $order_wrapper->commerce_order_total->value()['amount'];

  if (!variable_get('order_amount_total')) {
    variable_set('order_amount_total', $order_total);
  } else {
    $order_total = variable_get('order_amount_total');
  }

  $description = t('Вы можете оплатить только часть суммы, а остальную, оплатите на месте');
  $disabled = FALSE;
  $checked = 0;
  if ($prepay_amount > 0) {
    $checked = 1;
  } else {
    if ($order_total/100 < 500) {
      $disabled = TRUE;
      $description = t('Ваша сумма заказа менее 500 р. Предоплата разрешена при сумме более 500');
    }
  }

  $pane_form['prepay_checkbox'] = array(
    '#type' => 'checkbox',
    '#disabled' => $disabled,
    '#default_value' => $checked,
    '#title' => t('Оплатить частично'),
    '#description' => $description,
  );

  $description = t("Введите желаемую сумму.
    <br />- Сумма должна быть не более @amount
    <br />- Вводите только цифры, без заапятых, пробелов и букв.
    <br />- Сумма должна быть не менее 500 р.", array('@amount' =>
    commerce_currency_format($order_total, commerce_default_currency())));

  $pane_form['prepay'] = array(
    '#type' => 'textfield',
    '#title' => t('Введите сумму'),
    '#description' => $description,
    '#default_value' => $prepay_amount,
    '#field_suffix' => ' р.',
    '#states' => array(
      // Элемент будет показан тогда, когда чекбокс prepay_checkbox будет Включен.
      'visible' => array(
        ':input[name="prepay_rkeeper_pane[prepay_checkbox]"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $pane_form;
}

/**
 * Validation callback.
 */
function prepay_rkeeper_pane_checkout_form_validate($form, &$form_state, $checkout_pane, $order) {
  $amount_total = (variable_get('order_amount_total', 0) !=0) ? variable_get('order_amount_total', 0) / 100: 0;
  $amount_total_format = commerce_currency_format(variable_get('order_amount_total', 0), commerce_default_currency());
  $pane_values = $form_state['values'][$checkout_pane['pane_id']];
  str_replace(' ', '', $pane_values['prepay']);
  $errors = 0;

  if ($pane_values['prepay_checkbox'] == 1) {
    if (!is_numeric($pane_values['prepay'])) {
      form_set_error('prepay', t("Вводить можно только цифры, без символов, пробелов и буков"));
      $errors++;
    }

    if ($pane_values['prepay'] > $amount_total or $pane_values['prepay'] < 500) {
      form_set_error('prepay', t("Сумма должна быть не менее 500 р. и не более @amount", array('@amount' => $amount_total_format)));
      $errors++;
    }

    if ($errors > 0) {
      variable_set('prepay', FALSE);
      return FALSE;
    } else {
      variable_set('prepay', TRUE);
    }

  } else {
    variable_set('prepay', FALSE);
  }

  return TRUE;
};

/**
 * Checkout form submission callback.
 */
function prepay_rkeeper_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  if (!empty($form_state['values'][$checkout_pane['pane_id']])) {
    $pane_values = $form_state['values'][$checkout_pane['pane_id']];

    if (variable_get('prepay', FALSE)) {
      $order->data['prepay']['amount'] = $pane_values['prepay'] * 100;

    } else {
      $order->data['prepay']['amount'] = 0;
    }

    $profile_wrapper = entity_metadata_wrapper('commerce_customer_profile', $order->commerce_customer_billing['und'][0]['profile_id']);
    $profile_wrapper->field_rk_prepay->amount = $order->data['prepay']['amount'];
    $profile_wrapper->save();
  }
}

/**
 * Отображение информации на странице "review"
 */
function prepay_rkeeper_pane_review($form, $form_state, $checkout_pane, $order) {
  $content['prepay'] = array(
    '#type' => 'item',
    '#title' => t('Предоплата'),
    '#markup' => commerce_currency_format($order->data['prepay']['amount'], commerce_default_currency()),
  );

  return drupal_render($content);
}













