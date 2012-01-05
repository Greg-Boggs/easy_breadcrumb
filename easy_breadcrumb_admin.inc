<?php

/**
 * The default settings page.
 * @param String $op
 * @return String the rendered form
 */
function easy_breadcrumb_settings_page($op = NULL) {
    return drupal_get_form('easy_breadcrumb_general_settings_form');
}

/**
 * General configuration form
 * @return Assoc form
 */
function easy_breadcrumb_general_settings_form() {

    $form = array();

    // Add fieldset for page specific settings
    $form['easy_breadcrumb'] = array(
        '#type' => 'fieldset',
        '#title' => t('General settings'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );
		
		$form['easy_breadcrumb']['title_visible'] = array(
      '#type' => 'checkbox',
      '#title' => t("Display the current page's title in the breadcrumb"),
      '#default_value' => variable_get(EasyBreadcrumb_Constants::DB_VAR_TITLE_VISIBLE, true),
      '#description' => t("Should the current page title's be displayed in the breacrumb?"),
    );

    $form['easy_breadcrumb']['segments_separator'] = array(
        '#type' => 'textfield',
        '#title' => t('Segments separator'),
				'#description' => t("Enter the separator to be displayed between the breadcrumb's segments."),
        '#default_value' => variable_get(EasyBreadcrumb_Constants::DB_VAR_SEGMENTS_SEPARATOR, '>>'),
    );
		
    $form['easy_breadcrumb']['segments_title_mode'] = array(
			 '#type' => 'select',
       '#title' => t("Segments title's transformation mode"),
       '#options' => array(
         'none' => t('None'),
         'ucwords' => t("Capitalize the first letter of each word in the title"),
         'ucfirst' => t("Capitalize the first letter of the title"),
       ),
       '#description' => t("Choose the transformation mode you want to apply to the segments's title."),
       '#default_value' => variable_get(EasyBreadcrumb_Constants::DB_VAR_SEGMENTS_TITLE_MODE, 'ucwords'),
    );

    $form['buttons'] = array(
        'submit' => array('#type' => 'submit', '#value' => t('Save configuration')),
        'reset' => array('#type' => 'reset', '#value' => t('Reset to defaults'))
    );

    $form['#submit'] = array('easy_breadcrumb_admin_submit');
    $form['#theme'] = 'system_settings_form';

    return $form;
}

/**
 * Process the submitting of the administration form of this module
 * @param Assoc $form
 * @param Assoc $form_state 
 */
function easy_breadcrumb_admin_submit($form, &$form_state) {

    $segmentSeparator = $form_state['values']['segments_separator'];
    $uppercaseMode = $form_state['values']['segments_title_mode'];
    $titleVisible = $form_state['values']['title_visible'];

    variable_set(EasyBreadcrumb_Constants::DB_VAR_SEGMENTS_SEPARATOR, $segmentSeparator);
    variable_set(EasyBreadcrumb_Constants::DB_VAR_SEGMENTS_TITLE_MODE, $uppercaseMode);
    variable_set(EasyBreadcrumb_Constants::DB_VAR_TITLE_VISIBLE, $titleVisible);

		$successMsg = t("The module's settings have been saved.");
    drupal_set_message($successMsg);
}
