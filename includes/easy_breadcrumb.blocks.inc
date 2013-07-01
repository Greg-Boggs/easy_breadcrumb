<?php
/**
 * @file
 * Module's blocks.
 */

/**
 * Obtains the 'easy_breadcrumb' block.
 *
 * @return Assoc
 *   resulting renderizable array.
 */
function _easy_breadcrumb_block() {

  // Array storing the breadcrumb's segments.
  $breadcrumb = array();

  // Default classes for the segments.
  $segments_classes = array('easy-breadcrumb_segment');

  // Gets the flag saying if the front page segment should be included.
  $include_front_page_segment = variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT, TRUE);

  // Conditionally include the front page segment in the breadcrumb.
  if ($include_front_page_segment) {
    $front_text = variable_get(EasyBreadcrumbConstants::DB_VAR_HOME_SEGMENT_TITLE);
    if (isset($front_text) && function_exists('i18n_string')) {
      $front_text = i18n_string('node', $front_text);
    } else {
      $front_text = t('Home');
    }
    // Marks the front--segment with an identifier class (useful for CSS).
    $segments_classes[1] = 'easy-breadcrumb_segment-front';
    // Adds a segment for the front page.
    $breadcrumb[] = l($front_text, NULL, array('attributes' => array('class' => $segments_classes)));
  }

  // There won't be more segments if visiting the front page, the don't waste
  // resources.
  if (!drupal_is_front_page()) {

    // Gets the flag saying the capitalizator mode.
    $capitalizator_mode = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE, 'ucwords');

    // List of words to be ignored by the capitalizator.
    $capitalizator_ignored_words = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS,
    EasyBreadcrumbConstants::defaultIgnoredWords());

    // Flag for including invalid paths as plain-text segments.
    $include_invalid_paths = variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_INVALID_PATHS, TRUE);

    // List of path to be excluded while generating segments.
    $excluded_paths_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS,
      EasyBreadcrumbConstants::defaultExcludedPaths());

    // Obtains the alias of the current path.
    $alias = drupal_get_path_alias();

    // Get the segments of the current path.
    $alias_arr = explode('/', $alias);

    // Get the quantity of segments in the current path.
    $segments_quantity = count($alias_arr);

    $segment_url_arr = array();

    // Iterates over the segments of the current URL
    // ("blog/article/hello-world") excepting the last segment
    // (the title, 'hello-world' in that case).
    for ($idx_0 = 0, $idx_1 = 1; $idx_1 < $segments_quantity; ++$idx_0, ++$idx_1) {

      // Build an array containing the URL of the segment being currently
      // processed. E.g., having $alias as "blog/article/hello-world", at the
      // first iteration this array will be array('blog'), the second
      // (and last in that case) the array will be array('blog','article').
      $segment_url_arr[] = $alias_arr[$idx_0];

      // String with the potential path alias of the segment being processed
      // (e.g. 'blog/article').
      $segment_url = implode('/', $segment_url_arr);

      // If this segment is configured to be excluded.
      if (isset($excluded_paths_arr[$segment_url])) {
        continue;
      }

      $segments_classes[1] = 'easy-breadcrumb_segment-' . $idx_1;

      // Obtain the internal path it represents.
      $segment_normal_path = drupal_get_normal_path($segment_url);

      // Check if this is a valid path.
      $segment_valid_path = _easy_breadcrumb_validate_path($segment_normal_path);

      // Get the segment's raw text from the URL.
      $item = $alias_arr[$idx_0];
      // Normalized segment's text (e.g. 'Blog');
      $segment_text = _easy_breadcrumb_normalize_url_segment_text_url($segment_normal_path,
        $segment_valid_path, $item, $capitalizator_mode, $capitalizator_ignored_words);

      // Only adds the segment as link if its URL really exists; adds it as text
      // otherwise (if configured for doing so).
      if ($segment_valid_path) {
        // Adds the segment to the breadcrumb.
        $breadcrumb[] = l($segment_text, $segment_url, array(
          'attributes' => array('class' => $segments_classes),
          )
        );
      }
      elseif ($include_invalid_paths) {
        $classes = implode(' ', $segments_classes);
        $breadcrumb[] = '<span class="' . $classes . '">' . htmlspecialchars($segment_text) . '</span>';
      }
    }

    // Gets the flag saying if the title should be appended to the breadcrumb.
    $include_page_title_segment = variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT, TRUE);

    // Adds the page's title to the breadcrumb.
    if ($include_page_title_segment) {
      // Marks the page's-title-segment with an identifier class
      // (useful for CSS).
      $segments_classes[1] = 'easy-breadcrumb_segment-title';
      $use_page_title_when_available = variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_FROM_PAGE_WHEN_AVAILABLE, TRUE);
      // Tries to get the title of the current page (if available).
      if ($use_page_title_when_available) {
        $page_title = drupal_get_title();
      }
      // If the current page has not title, then deduce the title from the url.
      if (!isset($page_title) || trim($page_title) === '') {
        // The title is the last segment in the URL.
        $page_title = $alias_arr[$segments_quantity - 1];
        $page_title = _easy_breadcrumb_normalize_url_segment_text($page_title, $capitalizator_mode,
          $capitalizator_ignored_words);
      }
      $title_segment_as_link = variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_SEGMENT_AS_LINK, FALSE);
      // If the page's title will be a link or just a text.
      if ($title_segment_as_link) {
        $breadcrumb[] = l($page_title, $alias, array('attributes' => array('class' => $segments_classes)));
      }
      else {
        $classes = implode(' ', $segments_classes);
        $breadcrumb[] = '<span class="' . $classes . '">' . $page_title . '</span>';
      }
    }
  }

  // Gets the configured segments separator.
  $separator = variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR, '>>');
  $separator = check_plain($separator);
  $segments_quantity = count($breadcrumb);

  $build = array();
  $build['easy_breadcrumb'] = array(
    '#theme' => 'easy_breadcrumb',
    '#breadcrumb' => $breadcrumb,
    '#segments_quantity' => $segments_quantity,
    '#separator' => $separator,
  );

  return $build;
}

/**
 * Normalizes an URL segment's title. E.g., transforms "about-us" to "About Us"
 * or "About us", according to parameters.
 *
 * @param string $segment_normal_path
 *   Segment's normal path.
 * @param string $segment_valid_path
 *   Flag if the URL of the segment if valid.
 * @param string $segment_text
 *   Segment's title to be normalized.
 * @param string $uppercase_mode
 *   Specifies the type of uppercase transformation (if any) to be applied.
 *
 * @return string
 *   normalized segment title.
 */
function _easy_breadcrumb_normalize_url_segment_text_url($segment_normal_path,
$segment_valid_path, $segment_text, $uppercase_mode = 'ucwords', $capitalizator_ignored_words = array()) {

  // if path is valid then just try to infer it from the node's title (if available).
  if ($segment_valid_path) {
    $node = menu_get_object('node', 1, $segment_normal_path);
    if(is_object($node) && property_exists($node, 'title')) {
      return $node->title;
    }
  }

  return _easy_breadcrumb_normalize_url_segment_text($segment_text, $uppercase_mode,
            $capitalizator_ignored_words);
}

/**
 * Normalizes an URL segment's title. E.g., transforms "about-us" to "About Us"
 * or "About us", according to parameters.
 *
 * @param string $segment_text
 *   Segment's title to be normalized.
 * @param string $uppercase_mode
 *   Specifies the type of uppercase transformation (if any) to be applied.
 *
 * @return string
 *   normalized segment title.
 */
function _easy_breadcrumb_normalize_url_segment_text($segment_text, $uppercase_mode = 'ucwords',
$capitalizator_ignored_words = array()) {

  // Transforms '-hello--world_javascript-' on 'hello world javascript'.
  $segment_text_normalized = str_replace(array('-', '_'), ' ', $segment_text);
  $segment_text_normalized = trim($segment_text_normalized);
  $segment_text_normalized = preg_replace('/\s{2,}/', ' ', $segment_text_normalized);

  switch ($uppercase_mode) {
    // Transforms the text 'once a time' to 'Once a Time'.
    case 'ucwords':
      $segment_text_arr = explode(' ', $segment_text_normalized);
      // Transforms the non-ignored words of the segment.
      $segment_text_arr[0] = drupal_ucfirst($segment_text_arr[0]);
      for ($idx_1 = 1, $segments_words_quantity = count($segment_text_arr); $idx_1 < $segments_words_quantity; ++$idx_1) {
        // Transforms this word only if it is not in the list of ignored words.
        if (!isset($capitalizator_ignored_words[$segment_text_arr[$idx_1]])) {
          $segment_text_arr[$idx_1] = drupal_ucfirst($segment_text_arr[$idx_1]);
        }
      }
      $segment_text_normalized = join(' ', $segment_text_arr);
      break;

    // Transforms the text 'once a time' to 'Once a time'.
    case 'ucfirst':
      $segment_text_normalized = drupal_ucfirst($segment_text_normalized);
      break;

    default:
  }

  return $segment_text_normalized;
}

/**
 * Check if the given path is valid (exists).
 *
 * @param string $path_alias
 *   the path to be checked.
 *
 * @return boolean
 *   TRUE if the path is valid, false otherwise.
 */
function _easy_breadcrumb_validate_path($normal_path) {

  // Check if the path is stored in the actual menu router.
  $valid = drupal_valid_path($normal_path);

  return $valid;
}
