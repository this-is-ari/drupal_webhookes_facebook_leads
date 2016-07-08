<?php

/**
 * @file
 * Page callbacks for the GitHub WebHook module.
 */

/**
 * Page callback; GutHub WebHook endpoint.
 */
function fbleads_webhook_endpoint() {
	$apptoken = variable_get('fbleads_webhook_token', FALSE);
  try {
		$fbdata = json_decode(file_get_contents('php://input'), true);
		if(count($fbdata['entry'])){
			foreach($fbdata['entry'] as $entry){
				foreach($entry['changes'] as $lead){
					$ldata = $lead['value'];
					$q = rules_invoke_event('fbleads_webhook_lead_received', $ldata['leadgen_id'], $ldata['page_id'], $ldata['form_id'], $ldata['adgroup_id'], $ldata['ad_id'], $ldata['created_time']);	

					$leaddata = json_decode(file_get_contents("https://graph.facebook.com/v2.5/".$ldata['leadgen_id']."?access_token=".$apptoken));
					foreach($leaddata->field_data as $field){
						switch ($field->name) {
						case 'full_name':
							$userdata['full_name'] = implode(" ",$field->values);
							break;
						case 'email':
							$userdata['email'] = implode(" ",$field->values);
							break;
						}
					}
					rules_invoke_event('fbleads_webhook_leaddata_received', $ldata['leadgen_id'], $userdata['email'], $userdata['full_name']);
				}				
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
}

/**
 * Delivery callback; Checks 'hub_challenge' variable.
 *
 */
function fbleads_webhook_json_deliver() {
	drupal_add_http_header('Status', '200 OK');	
	if(isset($_GET['hub_challenge'])){
		echo $_GET['hub_challenge'];
	}
	else{
		echo t("no hub challenge found");
	}	
  module_invoke_all('exit');
  drupal_session_commit();
}
