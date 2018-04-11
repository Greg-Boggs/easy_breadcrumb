<?php

namespace Drupal\easy_breadcrumb\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\easy_breadcrumb\EasyBreadcrumbConstants;

/**
 * Build Easy Breadcrumb settings form.
 */
class EasyBreadcrumbGeneralSettingsForm extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'easy_breadcrumb_general_settings';
  }

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return ['easy_breadcrumb.settings'];
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $config = $this->config('easy_breadcrumb.settings');

    // Fieldset for grouping general settings fields.
    $fieldset_general = [
      '#type' => 'fieldset',
      '#title' => $this->t('General settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    ];

    $fieldset_general[EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Include invalid paths alias as plain-text segments'),
      '#description' => $this->t('Include the invalid paths alias as plain-text segments in the breadcrumb.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS),
    ];

    // Formats the excluded paths array as line separated list of paths
    // before displaying them.
    $excluded_paths = $config->get(EasyBreadcrumbConstants::EXCLUDED_PATHS);

    $fieldset_general[EasyBreadcrumbConstants::EXCLUDED_PATHS] = [
      '#type' => 'textarea',
      '#title' => $this->t('Paths to be excluded while generating segments'),
      '#description' => $this->t('Enter a line separated list of paths to be excluded while generating the segments.
			Paths may use simple regex, i.e.: report/2[0-9][0-9][0-9].'),
      '#default_value' => $excluded_paths,
    ];
    // Formats the excluded paths array as line separated list of paths
    // before displaying them.
    $replaced_titles = $config->get(EasyBreadcrumbConstants::REPLACED_TITLES);

    $fieldset_general[EasyBreadcrumbConstants::REPLACED_TITLES] = [
      '#type' => 'textarea',
      '#title' => $this->t('Titles to be replaced while generating segments'),
      '#description' => $this->t('Enter a line separated list of titles with their replacements seperated by ::.
			For example TITLE::DIFFERENT_TITLE'),
      '#default_value' => $replaced_titles,
    ];

    $fieldset_general[EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Include the front page as a segment in the breadcrumb'),
      '#description' => $this->t('Include the front page as the first segment in the breadcrumb.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT),
    ];

    $fieldset_general[EasyBreadcrumbConstants::HOME_SEGMENT_TITLE] = [
      '#type' => 'textfield',
      '#title' => $this->t('Title for the front page segment in the breadcrumb'),
      '#description' => $this->t('Text to be displayed as the front page segment.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::HOME_SEGMENT_TITLE),
    ];

    $fieldset_general[EasyBreadcrumbConstants::HOME_SEGMENT_KEEP] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Display the front page segment on the front page'),
      '#description' => $this->t('If checked, the Home segment will be displayed on the front page.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::HOME_SEGMENT_KEEP),
      '#states' => [
        'visible' => [
          ':input[name="' . EasyBreadcrumbConstants::HOME_SEGMENT_TITLE . '"]' => ['empty' => FALSE],
        ],
      ],
    ];

    $fieldset_general[EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Include the current page as a segment in the breadcrumb'),
      '#description' => $this->t('Include the current page as the last segment in the breadcrumb.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT),
    ];

    $fieldset_general[EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Use the real page title when available'),
      '#description' => $this->t('Use the real page title when it is available instead of always deducing it from the URL.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE),
    ];

    $fieldset_general[EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Make the page title segment a link'),
      '#description' => $this->t('Prints the page title segment as a link.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK),
    ];

    $fieldset_general[EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Make the language path prefix a segment'),
      '#description' => $this->t('On multilingual sites where a path prefix ("/en") is used, add this in the breadcrumb.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT),
    ];

    $fieldset_general[EasyBreadcrumbConstants::USE_MENU_TITLE_AS_FALLBACK] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Use menu title as fallback'),
      '#description' => $this->t('Use menu title as fallback instead of raw path component.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::USE_MENU_TITLE_AS_FALLBACK),
    ];

    $fieldset_general[EasyBreadcrumbConstants::REMOVE_REPEATED_SEGMENTS] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Remove repeated identical segments'),
      '#description' => $this->t('Remove segments of the breadcrumb that are identical.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::REMOVE_REPEATED_SEGMENTS),
    ];

    // Flag for storing whether or not absolute paths are used as link.
    $fieldset_general[EasyBreadcrumbConstants::ABSOLUTE_PATHS] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Use absolute path for Breadcrumb links'),
      '#description' => $this->t('By selecting, absolute paths will be used (default: false) instead of relative.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::ABSOLUTE_PATHS),
    ];

    $fieldset_general[EasyBreadcrumbConstants::HIDE_SINGLE_HOME_ITEM] = [
      '#type' => 'checkbox',
      '#title' => $this->t("Hide link to home page if it's the only breadcrumb item"),
      '#description' => $this->t('Hide the breadcrumb when it only links to the home page and nothing more.'),
      '#default_value' => $config->get(EasyBreadcrumbConstants::HIDE_SINGLE_HOME_ITEM),
    ];

    $form = [];

    // Inserts the fieldset for grouping general settings fields.
    $form[EasyBreadcrumbConstants::MODULE_NAME] = $fieldset_general;

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $config = $this->config('easy_breadcrumb.settings');

    $config
      ->set(EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS, $form_state->getValue(EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS))
      ->set(EasyBreadcrumbConstants::EXCLUDED_PATHS, $form_state->getValue(EasyBreadcrumbConstants::EXCLUDED_PATHS))
      ->set(EasyBreadcrumbConstants::REPLACED_TITLES, $form_state->getValue(EasyBreadcrumbConstants::REPLACED_TITLES))
      ->set(EasyBreadcrumbConstants::SEGMENTS_SEPARATOR, $form_state->getValue(EasyBreadcrumbConstants::SEGMENTS_SEPARATOR))
      ->set(EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT, $form_state->getValue(EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT))
      ->set(EasyBreadcrumbConstants::HOME_SEGMENT_TITLE, $form_state->getValue(EasyBreadcrumbConstants::HOME_SEGMENT_TITLE))
      ->set(EasyBreadcrumbConstants::HOME_SEGMENT_KEEP, $form_state->getValue(EasyBreadcrumbConstants::HOME_SEGMENT_KEEP))
      ->set(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT, $form_state->getValue(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT))
      ->set(EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK, $form_state->getValue(EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK))
      ->set(EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE, $form_state->getValue(EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE))
      ->set(EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT, $form_state->getValue(EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT))
      ->set(EasyBreadcrumbConstants::USE_MENU_TITLE_AS_FALLBACK, $form_state->getValue(EasyBreadcrumbConstants::USE_MENU_TITLE_AS_FALLBACK))
      ->set(EasyBreadcrumbConstants::REMOVE_REPEATED_SEGMENTS, $form_state->getValue(EasyBreadcrumbConstants::REMOVE_REPEATED_SEGMENTS))
      ->set(EasyBreadcrumbConstants::ABSOLUTE_PATHS, $form_state->getValue(EasyBreadcrumbConstants::ABSOLUTE_PATHS))
      ->set(EasyBreadcrumbConstants::HIDE_SINGLE_HOME_ITEM, $form_state->getValue(EasyBreadcrumbConstants::HIDE_SINGLE_HOME_ITEM))
      ->save();

    parent::submitForm($form, $form_state);
  }

}
