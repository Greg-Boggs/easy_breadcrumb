<?php

/**
 * @file
 * Module's contants.
 */

/**
 * EasyBreadcrumb module's contants
 */
interface EasyBreadcrumbConstants {

  /**
   * Module's name.
   */
  const MODULE_NAME = 'easy_breadcrumb';

  /**
   *  Separator between segments.
   */
  const SEGMENTS_SEPARATOR = 'easy_breadcrumb-segments_separator';

  /**
   * Flag for including or not the front page as a segment.
   */
  const INCLUDE_HOME_SEGMENT = 'easy_breadcrumb-include_home_segment';

  /**
   * Flag for including or not the page's title as a segment.
   */
  const INCLUDE_TITLE_SEGMENT = 'easy_breadcrumb-include_title_segment';

  /**
   * Flag for printing the page's title as a link, or printing it as a text.
   */
  const TITLE_SEGMENT_AS_LINK = 'easy_breadcrumb-title_segment_as_link';

  /**
   * Use the page's title when it is available instead of always trying to
   * deduce it from the URL.
   */
  const TITLE_FROM_PAGE_WHEN_AVAILABLE = 'easy_breadcrumb-title_from_page_when_available';

  /**
   * Transformation mode to apply to the segments.
   */
  const CAPITALIZATOR_MODE = 'easy_breadcrumb-capitalizator_mode';

  /**
   * List of words to be ignored by the 'capitalizator'. E.g.: of and.
   */
  const CAPITALIZATOR_IGNORED_WORDS = 'easy_breadcrumb-capitalizator_ignored_words';

  /**
   * Flag for disabling or not the default Drupal's breadcrumb.
   */
  const DISABLE_DEFAULT_DRUPAL_BREADCRUMB = 'easy_breadcrumb-disable_drupal_breadcrumb';

}
