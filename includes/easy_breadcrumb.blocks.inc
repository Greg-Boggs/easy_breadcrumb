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
    $front_text = t('Home');
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

      // Get the segment's raw text from the URL.
      $item = $alias_arr[$idx_0];
      // Normalized segment's text (e.g. 'Blog');
      $segment_text = _easy_breadcrumb_normalize_url_segment_text($item, $capitalizator_mode,
        $capitalizator_ignored_words);
      $segments_classes[1] = 'easy-breadcrumb_segment-' . $idx_1;

      // Check if this is a valid path.
      $valid_path = _easy_breadcrumb_validate_path_alias($segment_url);

      // Only adds the segment as link if its URL really exists; adds it as text
      // otherwise (if configured for doing so).
      if ($valid_path) {
        // Adds the segment to the breadcrumb.
        $breadcrumb[] = l($segment_text, $segment_url, array(
          'attributes' => array('class' => $segments_classes),
          )
        );
      }
      elseif ($include_invalid_paths) {
        $classes = implode(' ', $segments_classes);
        $breadcrumb[] = '<span class="' . $classes . '">' . $segment_text . '</span>';
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
 * @param string $segment
 *   Segment's title to be normalized.
 * @param string $uppercase_mode
 *   Specifies the type of uppercase transformation (if any) to be applied.
 *
 * @return string
 *   normalized segment title.
 */
function _easy_breadcrumb_normalize_url_segment_text($segment, $uppercase_mode = 'ucwords',
$capitalizator_ignored_words = array()) {

  // Transforms '-hello--world_javascript-' on 'hello world javascript'.
  $normalized_segment = str_replace(array('-', '_'), ' ', $segment);
  $normalized_segment = trim($normalized_segment);
  $normalized_segment = preg_replace('/\s{2,}/', ' ', $normalized_segment);

  switch ($uppercase_mode) {
    // Transforms the text 'once a time' to 'Once a Time'.
    case 'ucwords':
      $segments_arr = explode(' ', $normalized_segment);
      // Transforms the non-ignored words of the segment.
      $segments_arr[0] = drupal_ucfirst($segments_arr[0]);
      for ($idx_1 = 1, $segments_words_quantity = count($segments_arr); $idx_1 < $segments_words_quantity; ++$idx_1) {
        // Transforms this word only if it is not in the list of ignored words.
        if (!isset($capitalizator_ignored_words[$segments_arr[$idx_1]])) {
          $segments_arr[$idx_1] = drupal_ucfirst($segments_arr[$idx_1]);
        }
      }
      $normalized_segment = join(' ', $segments_arr);
      break;

    // Transforms the text 'once a time' to 'Once a time'.
    case 'ucfirst':
      $normalized_segment = drupal_ucfirst($normalized_segment);
      break;

    default:
  }

  return $normalized_segment;
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
function _easy_breadcrumb_validate_path_alias($path_alias) {

  // Check if the path is stored in the actual menu router.
  $valid = drupal_valid_path(drupal_get_normal_path($path_alias));

  // If don't exists in the actual menu router, then check if it's an url_alias
  // (was generated by the pathauto module).
  if (empty($valid)) {
    $drupal_path = drupal_lookup_path('source', $path_alias);
    $valid = !empty($drupal_path);
  }

  return $valid;
}
