<?php
/**
 * @file
 * Module's admin forms.
 */

/**
 * General configuration form.
 *
 * @return Assoc
 *   renderable form.
 */
function _easy_breadcrumb_general_settings_form() {

  drupal_add_js(drupal_get_path('module', 'easy_breadcrumb') . '/js/easy_breadcrumb.admin.js');

  // Fieldset for grouping general settings fields.
  $fieldset_general = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_DISABLE_DEFAULT_DRUPAL_BREADCRUMB] = array(
    '#type' => 'checkbox',
    '#title' => t("Disable the default Drupal's breadcrumb"),
    '#description' => t("Always disable the default Drupal's breadcrumb."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_DISABLE_DEFAULT_DRUPAL_BREADCRUMB, TRUE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_INCLUDE_INVALID_PATHS] = array(
    '#type' => 'checkbox',
    '#title' => t("Include invalid paths alias as plain-text segments"),
    '#description' => t("Include the invalid paths alias as plain-text segments in the breadcrumb."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_INVALID_PATHS, TRUE),
  );

  // Formats the excluded paths array as line separated list of paths
  // before displaying them.
  $excluded_paths_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS,
    EasyBreadcrumbConstants::defaultExcludedPaths());
  $excluded_paths = @join("\r\n", $excluded_paths_arr);

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS] = array(
    '#type' => 'textarea',
    '#title' => t("Paths to be excluded while generating segments"),
    '#description' => t("Enter a line separated list of paths to be excluded while generating the segments.
			Paths may use simple regex, i.e.: report/2[0-9][0-9][0-9]."),
    '#default_value' => $excluded_paths,
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT] = array(
    '#type' => 'checkbox',
    '#title' => t("Include the front page as a segment in the breadcrumb"),
    '#description' => t("Include the front page as the first segment in the breacrumb."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT, TRUE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_HOME_SEGMENT_TITLE] = array(
    '#type' => 'textfield',
    '#title' => t("Title for the front page segment in the breadcrumb"),
    '#description' => t("Text to be displayed as the from page segment."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_HOME_SEGMENT_TITLE, t('Home')),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT] = array(
    '#type' => 'checkbox',
    '#title' => t("Include the current page's title as a segment in the breadcrumb"),
    '#description' => t("Include the current page's title as the last segment in the breacrumb."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT, TRUE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_TITLE_FROM_PAGE_WHEN_AVAILABLE] = array(
    '#type' => 'checkbox',
    '#title' => t("Use the real page's title when available"),
    '#description' => t("Use the real page's title when it is available instead of always deducing it from the URL."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_FROM_PAGE_WHEN_AVAILABLE, TRUE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_TITLE_SEGMENT_AS_LINK] = array(
    '#type' => 'checkbox',
    '#title' => t("Make the page's title segment a link"),
    '#description' => t("Prints the page's title segment as a link."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_SEGMENT_AS_LINK, FALSE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_SEPERATOR_ENDING] = array(
    '#type' => 'checkbox',
    '#title' => t("Show segments separator at the end of the breadcrumb"),
    '#description' => t("Shows the segment seperator after the last breadcrumb element"),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_SEPERATOR_ENDING, FALSE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_SEGMENT_TEXT_AS_TITLE] = array(
    '#type' => 'checkbox',
    '#title' => t("Use segment text as title instead of main page title."),
    '#description' => t("Use the path as the title instead of main page title. Usefull for views page with contextual filters."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENT_TEXT_AS_TITLE, FALSE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE] = array(
    '#type' => 'checkbox',
    '#title' => t("Truncate the page's title to a maximum number"),
    '#description' => t("Example: if you set it to 10, from <em>Long page title</em> will be <em>Long page...</em>"),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE, FALSE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_LENGTH] = array(
    '#type' => 'textfield',
    '#title' => t("Limit of truncation"),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_LENGTH, 100),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE . '"]' => array('checked' => TRUE),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE . '"]' => array('checked' => FALSE),
      )
    )
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_DOTS] = array(
      '#type' => 'checkbox',
      '#title' => t("The truncated page's title will have 3 dots in its end."),
      '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_DOTS, TRUE),
      '#states' => array(
          'visible' => array(
              ':input[name="' . EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE . '"]' => array('checked' => TRUE),
          ),
          'invisible' => array(
              ':input[name="' . EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE . '"]' => array('checked' => FALSE),
          )
      )
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR] = array(
    '#type' => 'textfield',
    '#title' => t('Segments separator'),
    '#description' => t("Separator to be used between the breadcrumb's segments."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR, '>>'),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE] = array(
    '#type' => 'select',
    '#title' => t("Transformation mode for the segments' titles"),
    '#options' => array(
      'none' => t('None'),
      'ucwords' => t("Capitalize the first letter of each word in the segment"),
      'ucfirst' => t("Only capitalize the first letter of each segment"),
      'ucall' => t("Capitalize all the letters of each word in the segment"),
      'ucforce' => t("Capitalize only the words that are set below"),
    ),
    '#description' => t("Choose the transformation mode you want to apply to the segments' titles. E.g.: 'blog/once-a-time' -> 'Home >> Blog >> Once a Time'."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE, 'ucwords'),
  );

  // Formats the ignored-words array as space separated list of words
  // (word1 word2 wordN) before displaying them.
  $capitalizator_ignored_words_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS,
    EasyBreadcrumbConstants::defaultIgnoredWords());
  $capitalizator_ignored_words = @join(' ', $capitalizator_ignored_words_arr);

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS] = array(
    '#type' => 'textarea',
    '#rows' => 3,
    '#title' => t("Words to be ignored by the 'capitalizator'"),
    '#description' => t("Enter a space separated list of words to be ignored by the 'capitalizator'. This will be applied only to the words not at the beginning of each segment. E.g.: of and."),
    '#default_value' => $capitalizator_ignored_words,
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('value' => 'ucwords'),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('!value' => 'ucwords'),
      )
    )
  );

  // Formats the forced-words array as space separated list of words
  // (word1 word2 wordN) before displaying them.
  $capitalizator_forced_words_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS, '');
  $capitalizator_forced_words = @join(' ', $capitalizator_forced_words_arr);

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS] = array(
    '#type' => 'textarea',
    '#rows' => 3,
    '#title' => t("Words to be forced to capitalized by the 'capitalizator'"),
    '#description' => t("Enter a space separated list of words to be forced by the 'capitalizator'. This will be applied only to the words that are listed. E.g.: if you want to capitalize your brand's name."),
    '#default_value' => $capitalizator_forced_words,
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('!value' => 'ucforce'),
      )
    )
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS_CASE_SENSITIVITY] = array(
    '#type' => 'checkbox',
    '#title' => t("Use case sensitivity when matching words to be forced to capitalization."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS_CASE_SENSITIVITY, FALSE),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('!value' => 'ucforce'),
      )
    ),
    '#description' => t("If checked, it matches drupal with drupal, druPAL with druPAL. Unchecked, it matches drupal with Drupal, drupal with druPAL.")
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS_FIRST_LETTER] = array(
    '#type' => 'checkbox',
    '#title' => t("Make the first letters of each segment capitalized."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS_FIRST_LETTER, TRUE),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('!value' => 'ucforce'),
      )
    )
  );

  $form = array();

  // Inserts the fieldset for grouping general settings fields.
  $form[EasyBreadcrumbConstants::MODULE_NAME] = $fieldset_general;

  // Adds buttons for processing the form.
  $form['buttons'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
  );

  // Specifies the callback function for processing the form submission.
  $form['#submit'] = array('_easy_breadcrumb_admin_submit');

  // Specifies the theme for the form.
  $form['#theme'] = 'system_settings_form';

  return $form;
}

/**
 * Process the submitting of the administration form of this module.
 *
 * @param Assoc $form
 *   renderable form.
 * @param Assoc $form_state
 *   form state.
 */
function _easy_breadcrumb_admin_submit($form, &$form_state) {

  // Pre-processes the list of ignored words for storing them as an array.
  // Replaces line-endings by spaces and splits words by spaces.
  // E.g.: array('of','and').
  $ignored_words_arr = array();
  $ignored_words = $form_state['values'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS];
  $ignored_words = preg_replace('/\r*\n+/', ' ', $ignored_words);
  $ignored_words = trim($ignored_words);
  $ignored_words_arr_aux = $ignored_words === '' ? array() : preg_split('/\s+/', $ignored_words);
  foreach ($ignored_words_arr_aux as $word) {
    $ignored_words_arr[$word] = $word;
  }

  $excluded_paths_arr = array();
  $excluded_paths = $form_state['values'][EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS];
  $excluded_paths = trim($excluded_paths);
  $excluded_paths = preg_replace('/\s+/', "\r\n", $excluded_paths);
  $excluded_paths_arr_aux = $excluded_paths === '' ? array() : preg_split('/\r*\n+/', $excluded_paths);
  foreach ($excluded_paths_arr_aux as $path) {
    $path = trim($path, "/");
    $excluded_paths_arr[$path] = $path;
  }

  $forced_words_arr = array();
  $forced_words = $form_state['values'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS];
  $forced_words = preg_replace('/\r*\n+/', ' ', $forced_words);
  $forced_words = trim($forced_words);
  $forced_words_arr_aux = $forced_words === '' ? array() : preg_split('/\s+/', $forced_words);
  foreach ($forced_words_arr_aux as $word) {
    $forced_words_arr[$word] = $word;
  }
  // Updates the $form_state before passing it to the Drupal system.
  $form_state['values'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS] = $ignored_words_arr;
  $form_state['values'][EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS] = $excluded_paths_arr;
  $form_state['values'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS] = $forced_words_arr;

  // Delegates persistence to the existing Drupal system.
  system_settings_form_submit($form, $form_state);
}
