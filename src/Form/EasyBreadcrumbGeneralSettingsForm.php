<?php

namespace Drupal\easy_breadcrumb\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Render\Element;
use Drupal\easy_breadcrumb\EasyBreadcrumbConstants;

/**
 *  Build Easy Breadcrumb settings form.
 */
class EasyBreadcrumbGeneralSettingsForm extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'easy_breadcrumb_general_settings';
  }

  /**
   * {@inheritdoc}.
   */
  protected function getEditableConfigNames() {
    return ['easy_breadcrumb.settings'];
  }

  public function buildForm(array $form, FormStateInterface $form_state) {
    $config = $this->config('easy_breadcrumb.settings');

    // Fieldset for grouping general settings fields.
    $fieldset_general = [
      '#type' => 'fieldset',
      '#title' => t('General settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    ];

    $fieldset_general[EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS] = array(
      '#type' => 'checkbox',
      '#title' => t("Include invalid paths alias as plain-text segments"),
      '#description' => t("Include the invalid paths alias as plain-text segments in the breadcrumb."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS),
    );


    // Formats the excluded paths array as line separated list of paths
    // before displaying them.
    $excluded_paths = $config->get(EasyBreadcrumbConstants::EXCLUDED_PATHS);

    $fieldset_general[EasyBreadcrumbConstants::EXCLUDED_PATHS] = [
      '#type' => 'textarea',
      '#title' => t("Paths to be excluded while generating segments"),
      '#description' => t("Enter a line separated list of paths to be excluded while generating the segments.
			Paths may use simple regex, i.e.: report/2[0-9][0-9][0-9]."),
      '#default_value' => $excluded_paths,
    ];

    $fieldset_general[EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT] = array(
      '#type' => 'checkbox',
      '#title' => t("Include the front page as a segment in the breadcrumb"),
      '#description' => t("Include the front page as the first segment in the breacrumb."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT),
    );

    $fieldset_general[EasyBreadcrumbConstants::HOME_SEGMENT_TITLE] = array(
      '#type' => 'textfield',
      '#title' => t("Title for the front page segment in the breadcrumb"),
      '#description' => t("Text to be displayed as the from page segment."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::HOME_SEGMENT_TITLE),
    );

    $fieldset_general[EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT] = array(
      '#type' => 'checkbox',
      '#title' => t("Include the current page as a segment in the breadcrumb"),
      '#description' => t("Include the current page as the last segment in the breacrumb."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT),
    );

    $fieldset_general[EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE] = array(
      '#type' => 'checkbox',
      '#title' => t("Use the real page's title when available"),
      '#description' => t("Use the real page's title when it is available instead of always deducing it from the URL."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE),
    );

    $fieldset_general[EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK] = array(
      '#type' => 'checkbox',
      '#title' => t("Make the page's title segment a link"),
      '#description' => t("Prints the page's title segment as a link."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK),
    );

    $fieldset_general[EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT] = array(
      '#type' => 'checkbox',
      '#title' => t("Make the language path prefix a segment"),
      '#description' => t("On multilingual sites where a path prefix (\"/en\") is used, add this in the breadcrumb."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT),
    );

    /* @fixme todo: not coded yet.
    $fieldset_general[EasyBreadcrumbConstants::SEGMENTS_SEPARATOR] = array(
      '#type' => 'textfield',
      '#title' => t('Segments separator'),
      '#description' => t("Separator to be used between the breadcrumb's segments."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::SEGMENTS_SEPARATOR),
    );

    $fieldset_general[EasyBreadcrumbConstants::CAPITALIZATOR_MODE] = array(
      '#type' => 'select',
      '#title' => t("Transformation mode for the segments' titles"),
      '#options' => array(
        'none' => t('None'),
        'ucwords' => t("Capitalize the first letter of each word in the segment"),
        'ucfirst' => t("Only capitalize the first letter of each segment"),
      ),
      '#description' => t("Choose the transformation mode you want to apply to the segments' "
                         . "titles. E.g.: 'blog/once-a-time' -> 'Home >> Blog >> Once a Time'."),
      '#default_value' => $config->get(EasyBreadcrumbConstants::CAPITALIZATOR_MODE),
    );

    // Formats the ignored-words array as space separated list of words
    // (word1 word2 wordN) before displaying them.
    $capitalizator_ignored_words = $config->get(EasyBreadcrumbConstants::CAPITALIZATOR_IGNORED_WORDS);

    $fieldset_general[EasyBreadcrumbConstants::CAPITALIZATOR_IGNORED_WORDS] = [
      '#type' => 'textarea',
      '#rows' => 3,
      '#title' => t("Words to be ignored by the 'capitalizator'"),
      '#description' => t("Enter a space separated list of words to be ignored by the 'capitalizator'."
                          . " This will be applyed only to the words not at the beginning of each segment. E.g.: of and."),
      '#default_value' => $capitalizator_ignored_words,
    ];
    */

    $form = [];

    // Inserts the fieldset for grouping general settings fields.
    $form[EasyBreadcrumbConstants::MODULE_NAME] = $fieldset_general;

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    parent::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $config = $this->config('easy_breadcrumb.settings');

    $config
      ->set(EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS, $form_state->getValue(EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS))
      ->set(EasyBreadcrumbConstants::EXCLUDED_PATHS, $form_state->getValue(EasyBreadcrumbConstants::EXCLUDED_PATHS))
      ->set(EasyBreadcrumbConstants::SEGMENTS_SEPARATOR, $form_state->getValue(EasyBreadcrumbConstants::SEGMENTS_SEPARATOR))
      ->set(EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT, $form_state->getValue(EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT))
      ->set(EasyBreadcrumbConstants::HOME_SEGMENT_TITLE, $form_state->getValue(EasyBreadcrumbConstants::HOME_SEGMENT_TITLE))
      ->set(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT, $form_state->getValue(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT))
      ->set(EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK, $form_state->getValue(EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK))
      ->set(EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE, $form_state->getValue(EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE))
      ->set(EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT, $form_state->getValue(EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT))
      //->set(EasyBreadcrumbConstants::CAPITALIZATOR_MODE, $form_state->getValue(EasyBreadcrumbConstants::CAPITALIZATOR_MODE))
      //->set(EasyBreadcrumbConstants::CAPITALIZATOR_IGNORED_WORDS, $form_state->getValue(EasyBreadcrumbConstants::CAPITALIZATOR_IGNORED_WORDS))
      ->save();

    parent::submitForm($form, $form_state);
  }
}
