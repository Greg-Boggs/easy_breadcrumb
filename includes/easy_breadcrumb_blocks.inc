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
  $include_front_page_segment = variable_get(EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT, TRUE);

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
    $capitalizator_mode = variable_get(EasyBreadcrumbConstants::CAPITALIZATOR_MODE, 'ucwords');

    // List of words to be ignored by the capitalizator.
    $capitalizator_ignored_words = variable_get(EasyBreadcrumbConstants::CAPITALIZATOR_IGNORED_WORDS,
      array('of', 'and', 'de', 'del', 'y'));

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
    for ($c = 1, $i = 0; $c < $segments_quantity; ++$c, ++$i) {

      // Build an array containing the URL of the segment being currently
      // processed. E.g., having $alias as "blog/article/hello-world", at the
      // first iteration this array will be array('blog'), the second
      // (and last in that case) the array will be array('blog','article').
      $segment_url_arr[] = $alias_arr[$i];

      // String with the raw URL of the segment being processed
      // (e.g. 'blog/article').
      $segment_url = implode('/', $segment_url_arr);

      // Get the segment's raw text from the URL.
      $item = $alias_arr[$i];
      // Normalized segment's text (e.g. 'Blog');
      $segment_text = _easy_breadcrumb_normalize_url_segment_text($item, $capitalizator_mode,
        $capitalizator_ignored_words);
      $segments_classes[1] = 'easy-breadcrumb_segment-' . $c;

      // Check if this is a valid path.
      $valid_path = drupal_valid_path($segment_url);

      // Only adds the segment as link if its URL really exists; adds it as text
      // otherwise.
      if ($valid_path) {
        // Adds the segment to the breadcrumb.
        $breadcrumb[] = l($segment_text, $segment_url, array(
          'attributes' => array('class' => $segments_classes),)
        );
      } else {
        $classes = implode(' ', $segments_classes);
        $breadcrumb[] = '<span class="' . $classes . '">' . $segment_text . '</span>';
      }
    }

    // Gets the flag saying if the title should be appended to the breadcrumb.
    $include_page_title_segment = variable_get(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT, TRUE);

    // Adds the page's title to the breadcrumb.
    if ($include_page_title_segment) {
      // Marks the page's-title-segment with an identifier class
      // (useful for CSS).
      $segments_classes[1] = 'easy-breadcrumb_segment-title';
      $use_page_title_when_available = variable_get(EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE, TRUE);
      // Tries to get the title of the current page (if available).
      if ($use_page_title_when_available) {
        $page_title = drupal_get_title();
      }
      // If the current page has not title, then deduce the title from the url.
      if (!isset($page_title) || $page_title === '') {
        // The title is the last segment in the URL.
        $page_title = $alias_arr[$segments_quantity - 1];
        $page_title = _easy_breadcrumb_normalize_url_segment_text($page_title, $capitalizator_mode,
          $capitalizator_ignored_words);
      }
      $title_segment_as_link = variable_get(EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK, FALSE);
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
  $separator = variable_get(EasyBreadcrumbConstants::SEGMENTS_SEPARATOR, '>>');

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
 * or "About us", according to parameters.
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
function _easy_breadcrumb_normalize_url_segment_text($segment, $uppercase_mode = 'ucwords',
$capitalizator_ignored_words = array()) {

  // Transforms 'hello-world' on 'hello world'.
  $normalized_segment = str_replace('-', ' ', $segment);

  switch ($uppercase_mode) {
    // Converts the text 'once a time' to 'Once a Time'.
    case 'ucwords':
      $segments_arr = explode(' ', $normalized_segment);
      // Converts the non-ignored words of the segment.
      $segments_arr[0] = drupal_ucfirst($segments_arr[0]);
      for ($i = 1, $n = count($segments_arr); $i < $n; ++$i) {
        // Transforms this word only if it is not in the list of ignored words.
        if (!isset($capitalizator_ignored_words[$segments_arr[$i]])) {
          $segments_arr[$i] = drupal_ucfirst($segments_arr[$i]);
        }
      }
      $normalized_segment = join(' ', $segments_arr);
      break;

    // Converts the text 'once a time' to 'Once a time'.
    case 'ucfirst':
      $normalized_segment = drupal_ucfirst($normalized_segment);
      break;

    default:
  }

  return $normalized_segment;
}
