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

  // Default class for the segments.
  $default_class = 'easy-breadcrumb_segment';
  $class_arr = array($default_class, 'easy-breadcrumb_segment-home');
  $breadcrumb = array();
  $home_text = t('Home');
  // Adds a segment for the home page.
  $breadcrumb[] = l($home_text, NULL, array('attributes' => array('class' => $class_arr)));

  // Don't waste resources if the 'home' is the current page.
  if (!drupal_is_front_page()) {

    $uppercase_mode = variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_CAPITALIZE_MODE, 'ucwords');

    // Obtains the alias of the current path.
    $url = drupal_get_path_alias();
    // Get the segments of the current path.
    $url_arr = explode('/', $url);
    $segment_url_arr = array();
    // Get the quantity of segments in the current path.
    $segments_quantity = count($url_arr);

    // Iterates over the segments of the URL; excepting the last one (title).
    for ($c = 1, $i = 0; $c < $segments_quantity; ++$c, ++$i) {

      // Get the raw segment text (e.g. 'hello-world');
      $item = $url_arr[$i];
      $segment_url_arr[] = $item;
      // URL of the segment being processed (e.g. 'news/hello-world').
      $segment_url = implode('/', $segment_url_arr);
      // Normalized segment's text (e.g. 'Hello World');
      $segment_text = _easy_breadcrumb_normalize_url_segment_text($item, $uppercase_mode);
      $class_arr[1] = 'easy-breadcrumb_segment-' . $c;

      // Adds the segment to the breadcrumb.
      $breadcrumb[$c] = l($segment_text, $segment_url, array(
        'attributes' => array('class' => $class_arr),)
      );
    }

    // Gets the flag saying if the title should be appended to the breadcrumb.
    $is_title_visible = variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_VISIBLE, TRUE);

    // Adds the page's title to the breadcrumb.
    if ($is_title_visible) {
      // Marks the breadcrumb title with an identifier class (useful for CSS).
      $class_arr[1] = 'easy-breadcrumb_segment-title';
      $use_page_title_when_available = variable_get(EasyBreadcrumbConstants::DB_VAR_PAGE_TITLE_WHEN_AVAILABLE, TRUE);
      // Tries to get the title of the current page (if available).
      if ($use_page_title_when_available) {
        $title = drupal_get_title();
      }
      // If the current page has not title, then deduce the title from the url.
      if (!isset($title) || $title === '') {
        // The title is the last segment in the URL.
        $title = $url_arr[$segments_quantity - 1];
        $title = _easy_breadcrumb_normalize_url_segment_text($title, $uppercase_mode);
      }
      // Adds the title to the breadcrumb.
      $breadcrumb[$segments_quantity] = l($title, $url, array(
        'attributes' => array('class' => $class_arr))
      );
    }
  }

  // Get the configured separator.
  $separator = variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR, '>>');

  $build = array();
  $build['easy_breadcrumb'] = array(
    '#theme' => 'easy_breadcrumb',
    '#breadcrumb' => $breadcrumb,
    '#segments_quantity' => count($breadcrumb),
    '#separator' => $separator,
  );

  return $build;
}

/**
 * Normalizes an URL segment's title. E.g., transforms "about-us" to "About Us"
 * or "About us", according to the configured menu's settings.
 *
 * @param string $segment
 *   Segment's title to be normalized.
 * @param string $uppercase_mode
 *   Specifies the type of uppercase transformation (if any) to be applied to
 *   the segment's title.
 *
 * @return string
 *   normalized segment title.
 */
function _easy_breadcrumb_normalize_url_segment_text($segment, $uppercase_mode = 'ucwords') {

  // Transforms 'hello-world' on 'hello world'.
  $normalized_segment = str_replace('-', ' ', $segment);

  switch ($uppercase_mode) {
    // Converts the text 'once a time' to 'Once a Time'.
    case 'ucwords':
      $segments_arr = explode(' ', $normalized_segment);
      // Ignored words.
      $capitalize_ignored_words_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_CAPITALIZE_IGNORED_WORDS, '');
      // Converts the non-ignored words of the segment.
      $segments_arr[0] = ucfirst($segments_arr[0]);
      for ($i = 1,$n = count($segments_arr); $i < $n; ++$i) {
        // Transforms this word if it is not in the list of ignored words.
        if (!isset ($capitalize_ignored_words_arr[$segments_arr[$i]])) {
          $segments_arr[$i] = ucfirst($segments_arr[$i]);
        }
      }
      $normalized_segment = join(' ', $segments_arr);
      break;

    // Converts the text 'once a time' to 'Once a time'.
    case 'ucfirst':
      $normalized_segment = ucfirst($normalized_segment);
      break;

    default:

  }

  return $normalized_segment;
}
