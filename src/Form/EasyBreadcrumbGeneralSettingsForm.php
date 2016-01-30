<?php

/**
 * @file
 * Contains \Drupal\easy_breadcrumb\Form\EasyBreadcrumbGeneralSettingsForm.
 */

namespace Drupal\easy_breadcrumb\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Render\Element;

class EasyBreadcrumbGeneralSettingsForm extends FormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return '_easy_breadcrumb_general_settings_form';
  }

  public function buildForm(array $form, \Drupal\Core\Form\FormStateInterface $form_state) {

    // @FIXME
// The Assets API has totally changed. CSS, JavaScript, and libraries are now
// attached directly to render arrays using the #attached property.
// 
// 
// @see https://www.drupal.org/node/2169605
// @see https://www.drupal.org/node/2408597
// drupal_add_js(drupal_get_path('module', 'easy_breadcrumb') . '/js/easy_breadcrumb.admin.js');


    // Fieldset for grouping general settings fields.
    $fieldset_general = [
      '#type' => 'fieldset',
      '#title' => t('General settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    ];

    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_DISABLE_DEFAULT_DRUPAL_BREADCRUMB] = array(
    //     '#type' => 'checkbox',
    //     '#title' => t("Disable the default Drupal's breadcrumb"),
    //     '#description' => t("Always disable the default Drupal's breadcrumb."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_DISABLE_DEFAULT_DRUPAL_BREADCRUMB, TRUE),
    //   );


    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_INCLUDE_INVALID_PATHS] = array(
    //     '#type' => 'checkbox',
    //     '#title' => t("Include invalid paths alias as plain-text segments"),
    //     '#description' => t("Include the invalid paths alias as plain-text segments in the breadcrumb."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_INVALID_PATHS, TRUE),
    //   );


    // Formats the excluded paths array as line separated list of paths
    // before displaying them.
    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $excluded_paths_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS,
    //     EasyBreadcrumbConstants::defaultExcludedPaths());

    $excluded_paths = @join("\r\n", $excluded_paths_arr);

    $fieldset_general[EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS] = [
      '#type' => 'textarea',
      '#title' => t("Paths to be excluded while generating segments"),
      '#description' => t("Enter a line separated list of paths to be excluded while generating the segments.
			Paths may use simple regex, i.e.: report/2[0-9][0-9][0-9]."),
      '#default_value' => $excluded_paths,
    ];

    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT] = array(
    //     '#type' => 'checkbox',
    //     '#title' => t("Include the front page as a segment in the breadcrumb"),
    //     '#description' => t("Include the front page as the first segment in the breacrumb."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT, TRUE),
    //   );


    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_HOME_SEGMENT_TITLE] = array(
    //     '#type' => 'textfield',
    //     '#title' => t("Title for the front page segment in the breadcrumb"),
    //     '#description' => t("Text to be displayed as the from page segment."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_HOME_SEGMENT_TITLE, t('Home')),
    //   );


    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT] = array(
    //     '#type' => 'checkbox',
    //     '#title' => t("Include the current page's title as a segment in the breadcrumb"),
    //     '#description' => t("Include the current page's title as the last segment in the breacrumb."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT, TRUE),
    //   );


    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_TITLE_FROM_PAGE_WHEN_AVAILABLE] = array(
    //     '#type' => 'checkbox',
    //     '#title' => t("Use the real page's title when available"),
    //     '#description' => t("Use the real page's title when it is available instead of always deducing it from the URL."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_FROM_PAGE_WHEN_AVAILABLE, TRUE),
    //   );


    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_TITLE_SEGMENT_AS_LINK] = array(
    //     '#type' => 'checkbox',
    //     '#title' => t("Make the page's title segment a link"),
    //     '#description' => t("Prints the page's title segment as a link."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_SEGMENT_AS_LINK, FALSE),
    //   );


    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR] = array(
    //     '#type' => 'textfield',
    //     '#title' => t('Segments separator'),
    //     '#description' => t("Separator to be used between the breadcrumb's segments."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR, '>>'),
    //   );


    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $fieldset_general[EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE] = array(
    //     '#type' => 'select',
    //     '#title' => t("Transformation mode for the segments' titles"),
    //     '#options' => array(
    //       'none' => t('None'),
    //       'ucwords' => t("Capitalize the first letter of each word in the segment"),
    //       'ucfirst' => t("Only capitalize the first letter of each segment"),
    //     ),
    //     '#description' => t("Choose the transformation mode you want to apply to the segments' titles. E.g.: 'blog/once-a-time' -> 'Home >> Blog >> Once a Time'."),
    //     '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE, 'ucwords'),
    //   );


    // Formats the ignored-words array as space separated list of words
    // (word1 word2 wordN) before displaying them.
    // @FIXME
    // // @FIXME
    // // The correct configuration object could not be determined. You'll need to
    // // rewrite this call manually.
    // $capitalizator_ignored_words_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS,
    //     EasyBreadcrumbConstants::defaultIgnoredWords());

    $capitalizator_ignored_words = @join(' ', $capitalizator_ignored_words_arr);

    $fieldset_general[EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS] = [
      '#type' => 'textarea',
      '#rows' => 3,
      '#title' => t("Words to be ignored by the 'capitalizator'"),
      '#description' => t("Enter a space separated list of words to be ignored by the 'capitalizator'. This will be applyed only to the words not at the beginning of each segment. E.g.: of and."),
      '#default_value' => $capitalizator_ignored_words,
    ];

    $form = [];

    // Inserts the fieldset for grouping general settings fields.
    $form[EasyBreadcrumbConstants::MODULE_NAME] = $fieldset_general;

    // Adds buttons for processing the form.
    $form['buttons'] = [
      'submit' => [
        '#type' => 'submit',
        '#value' => t('Save'),
      ]
      ];

    // Specifies the callback function for processing the form submission.
    $form['#submit'] = [
      '_easy_breadcrumb_admin_submit'
      ];

    // Specifies the theme for the form.
    $form['#theme'] = 'system_settings_form';

    return $form;
  }

}
