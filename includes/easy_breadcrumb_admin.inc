<?php

/**
 * @file
 * Module's admin forms
 */

require_once 'EasyBreadcrumbConstants.inc';

/**
 * The default settings page.
 *
 * @param String $op
 *   operation
 *
 * @return String
 *   the rendered form
 *
 */
function easy_breadcrumb_settings_page($op = NULL) {
  return drupal_get_form('easy_breadcrumb_general_settings_form');
}

/**
 * General configuration form
 *
 * @return Assoc
 *   form
 *
 */
function easy_breadcrumb_general_settings_form() {

  $form = array();

  // Add fieldset for page specific settings.
  $form['easy_breadcrumb'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['easy_breadcrumb']['title_visible'] = array(
    '#type' => 'checkbox',
    '#title' => t("Display the current page's title in the breadcrumb"),
    '#default_value' => variable_get(
      EasyBreadcrumbConstants::DB_VAR_TITLE_VISIBLE, TRUE),
    '#description' => t("Should the current page title's be displayed in the
      breacrumb?"),
  );

  $form['easy_breadcrumb']['page_title_when_available'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use the Page's title when available"),
    '#default_value' => variable_get(
      EasyBreadcrumbConstants::DB_VAR_PAGE_TITLE_WHEN_AVAILABLE, TRUE),
    '#description' => t("Should the module uses the page's title when it is
      available instead of try to extract it from the URL?"),
  );

  $form['easy_breadcrumb']['segments_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Segments separator'),
    '#description' => t("Enter the separator to be displayed between the
      breadcrumb's segments."),
    '#default_value' => variable_get(
      EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR, '>>'),
  );

  $form['easy_breadcrumb']['segments_capitalize_mode'] = array(
    '#type' => 'select',
    '#title' => t("Segments title's transformation mode"),
    '#options' => array(
      'none' => t('None'),
      'ucwords' => t("Capitalize the first letter of each word in the segment"),
      'ucfirst' => t("Capitalize the first letter of the segment"),
    ),
    '#description' => t("Choose the transformation mode you want to apply to the
      segments's title ('blog/once-a-time' -> 'Home >> Blog >> Once a Time')."),
    '#default_value' => variable_get(
      EasyBreadcrumbConstants::DB_VAR_SEGMENTS_CAPITALIZE_MODE, 'ucwords'),
  );

  $capitalize_ignored_words_arr = variable_get(
    EasyBreadcrumbConstants::DB_VAR_SEGMENTS_CAPITALIZE_IGNORED_WORDS, '');
  $capitalize_ignored_words = @join(', ', $capitalize_ignored_words_arr);

  $form['easy_breadcrumb']['segments_capitalize_ignored_words'] = array(
    '#type' => 'textarea',
    '#title' => t("Words to be ignored by the 'capitalizator'"),
    '#description' => t("Only the words not at the beginning of the segment will
      be ignored."),
    '#default_value' => $capitalize_ignored_words,
  );

  $form['buttons'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    ),
    'reset' => array(
      '#type' => 'reset',
      '#value' => t('Reset to defaults'),
    ),
  );

  $form['#submit'] = array('easy_breadcrumb_admin_submit');
  $form['#theme'] = 'system_settings_form';

  return $form;
}

/**
 * Process the submitting of the administration form of this module
 *
 * @param Assoc $form
 *   form
 * @param Assoc $form_state
 *   form state
 *
 */
function easy_breadcrumb_admin_submit($form, &$form_state) {

  $segment_separator = $form_state['values']['segments_separator'];
  $title_visible = $form_state['values']['title_visible'];
  $page_title_when_available =
    $form_state['values']['page_title_when_available'];
  $capitalize_mode = $form_state['values']['segments_capitalize_mode'];

  $capitalize_ignored_words =
    $form_state['values']['segments_capitalize_ignored_words'];
  $capitalize_ignored_words_arr = array();
  $capitalize_ignored_words_arr_aux = explode(',', $capitalize_ignored_words);

  foreach($capitalize_ignored_words_arr_aux as $k => $v) {
    $v = trim($v);
    $capitalize_ignored_words_arr[$v] = $v;
  }

  variable_set(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR,
    $segment_separator);
  variable_set(EasyBreadcrumbConstants::DB_VAR_TITLE_VISIBLE, $title_visible);
  variable_set(EasyBreadcrumbConstants::DB_VAR_PAGE_TITLE_WHEN_AVAILABLE,
    $page_title_when_available);
  variable_set(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_CAPITALIZE_MODE,
    $capitalize_mode);
  variable_set(
    EasyBreadcrumbConstants::DB_VAR_SEGMENTS_CAPITALIZE_IGNORED_WORDS,
    $capitalize_ignored_words_arr);

  $success_msg = t("The module's settings have been saved.");
  $success_msg = check_plain($success_msg);
  drupal_set_message($success_msg);
}
