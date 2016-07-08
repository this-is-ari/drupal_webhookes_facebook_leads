<?php

/**
 * @file
 * Administrative settings forms for the GitHub WebHook module.
 */

/**
 * Administrative settings for the GitHub WebHook module.
 *
 * @see fbleads_webhook_settings_validate()
 * @see fbleads_webhook_settings_submit()
 *
 * @ingroup forms
 */
function fbleads_webhook_settings($form, &$form_state) {

  $form['fbleads_webhook_url'] = array(
    '#title' => t('WebHook URL'),
    '#type' => 'textfield',
    '#default_value' => variable_get('fbleads_webhook_url', 'fbleads/webhook'),
    '#description' => t('The relative URL of the FBleads webhook endpoint exposed by this application.'),
  );
	
  $form['fbleads_webhook_token'] = array(
    '#title' => t('Security token'),
    '#type' => 'textfield',
    '#default_value' => variable_get('fbleads_webhook_token', ''),
		'#maxlength' => 1024,
    '#states' => array(
      'visible' => array(
        ':input[name="fbleads_webhook_require_token"]' => array('checked' => TRUE),
      ),
    ),
  );



  $form['#submit'][] = 'fbleads_webhook_settings_submit';

  return system_settings_form($form);
}


/**
 * Form submission handler for fbleads_webhook_settings().
 *
 * Forces a menu rebuild if the webhook URL changes.
 *
 * @see fbleads_webhook_settings_validate()
 */
function fbleads_webhook_settings_submit($form, &$form_state) {
  $original_url = $form_state['complete form']['fbleads_webhook_url']['#default_value'];
  if ($original_url != $form_state['values']['fbleads_webhook_url']) {
    variable_set('menu_rebuild_needed', TRUE);
  }
}

/**
 * Returns the argument position of the %fbleads_webhook_token argument.
 *
 * @param string $path
 *   The path to the GitHub webhook endpoint.
 *
 * @retunr int|FALSE
 */
function fbleads_webhook_argument_position($path) {
  $position = 0;
  $parts = explode('/', $path);
  foreach ($parts as $part) {
    if ('%fbleads_webhook_token' == $part) {
      return $position;
    }
    elseif (0 === strpos($part, '%')) {
      $position++;
    }
  }
  return FALSE;
}
