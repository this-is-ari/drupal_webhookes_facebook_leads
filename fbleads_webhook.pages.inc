<?php

/**
 * @file
 * Page callbacks for the GitHub WebHook module.
 */

/**
 * Page callback; GutHub WebHook endpoint.
 */
function fbleads_webhook_endpoint() {
  try {
		$fbdata = json_decode(file_get_contents('php://input'), true);
		
		foreach($fbdata['entry'] as $entry){
			foreach($entry['changes'] as $lead){
				$ldata = $lead['value'];
				$q = rules_invoke_event('fbleads_webhook_lead_received', $ldata['leadgen_id'], $ldata['page_id'], $ldata['form_id'], $ldata['adgroup_id'], $ldata['ad_id'], $ldata['created_time']);			
			}
		}


	}
  catch (Exception $e) {
    watchdog_exception('fbleads_webhook', $e);
    $response = array(
      'status' => 'error',
      'messages' => $e->getMessage(),
    );
  }

  return $response;
}

/**
 * Delivery callback; Convets the array to JSON and returns.
 *
 * @param array $page_callback_result
 *   The result of a page callback. The array is simply converted to JSON, which
 *   is the rendered output of the page request.
 */
function fbleads_webhook_json_deliver(array $page_callback_result) {
  //drupal_add_http_header('Content-Type', 'application/json; charset=utf-8');
  //print drupal_json_encode($page_callback_result);
	drupal_add_http_header('Status', '200 OK');
	echo $_GET['hub_challenge'];
  module_invoke_all('exit');
  drupal_session_commit();
}
