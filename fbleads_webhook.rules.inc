<?php

/**
 * Implements hook_rules_data_info().
 * @see rules_core_modules()
 */
function fbleads_webhook_rules_data_info() {
  return array(
    'fbleads_webhook_lead' => array(
      'label' => t('Facebook lead Entity'),
      'wrap' => TRUE,
      'property info' => array(
				'leadgen_id' => array(
					'type' => 'text',
					'label' => t('FB lead id'),
				),
				'ad_id' => array(
					'type' => 'text',
					'label' => t('FB lead AD id'),
				),
				'form_id' => array(
					'type' => 'text',
					'label' => t('Posted form id'),
				),
				'created_time' => array(
					'type' => 'text',
					'label' => t('FB lead created time'),
				),
				'page_id' => array(
					'type' => 'text',
					'label' => t('FB page id'),
				),
				'adgroup_id' => array(
					'type' => 'text',
					'label' => t('FB adgroup id'),
				),
			),
    ),
  );
}

/**
* Implements hook_rules_event_info()
*/
function fbleads_webhook_rules_event_info() {
  return array(
    'fbleads_webhook_lead_received' => array(
      'label' => t('FBlead webhook: request received'),
      'group' => t('FB Leads webhook'),
      'variables' => array(
        'leadgen_id' => array(
          'label' => t('Leadgen id'),
          'type' => 'text',
        ),
				'ad_id' => array(
					'type' => 'text',
					'label' => t('FB lead AD id'),
				),
				'form_id' => array(
					'type' => 'text',
					'label' => t('Posted form id'),
				),
				'created_time' => array(
					'type' => 'text',
					'label' => t('FB lead created time'),
				),
				'page_id' => array(
					'type' => 'text',
					'label' => t('FB page id'),
				),
				'adgroup_id' => array(
					'type' => 'text',
					'label' => t('FB adgroup id'),
				),				
      )
    ),
  );
}

/**
* Implements hook_rules_action_info()
*/
function fbleads_webhook_rules_action_info() {

  return array(
   'fbleads_webhook_write_leadgen' => array(
      'label' => t('Create entity with received data'),
      'group' => t('FB Leads webhook'),
      'parameter' => array(
        'leadgen_id' => array(
          'label' => t('Leadgen id'),
          'type' => 'text',
        ),
				'ad_id' => array(
					'type' => 'text',
					'label' => t('FB lead AD id'),
				),
				'form_id' => array(
					'type' => 'text',
					'label' => t('Posted form id'),
				),
				'created_time' => array(
					'type' => 'text',
					'label' => t('FB lead created time'),
				),
				'page_id' => array(
					'type' => 'text',
					'label' => t('FB page id'),
				),
				'adgroup_id' => array(
					'type' => 'text',
					'label' => t('FB adgroup id'),
				),				
      ),
      'provides' => array(
        'entity_id' => array(
          'type' => 'text',
          'label' => t('Created entity id'),
        ),
      ),
    ),
   );

}

/**
* Triggers the fbleads_webhook_write_leadgen
*/
function fbleads_webhook_write_leadgen($leadgen_id, $ad_id, $form_id, $created_time, $page_id, $adgroup_id) {

	$lead = entity_create('fblead', array(
		'leadgen_id' => $leadgen_id,
		'ad_id' => $ad_id,
		'form_id' => $form_id,
		'created_time' => $created_time,
		'page_id' => $page_id,
		'adgroup_id' => $adgroup_id,
		));
	$lead->save();	

	return array (
		'entity_id' => $lead->id,
	);		 
  
}



