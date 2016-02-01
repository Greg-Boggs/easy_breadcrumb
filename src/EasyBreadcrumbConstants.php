<?php
namespace Drupal\easy_breadcrumb;

/**
 * EasyBreadcrumb module's contants
 */
class EasyBreadcrumbConstants {

  /**
   * Module's name.
   */
  const MODULE_NAME = 'easy_breadcrumb';

  /**
   * Flag for including invalid paths while generating the breadcrumb segments.
   */
  const INCLUDE_INVALID_PATHS = 'include_invalid_paths';

  /**
   * List of paths to be excluded from the generated segments.
   */
  const EXCLUDED_PATHS = 'excluded_paths';

  /**
   *  Separator between segments.
   */
  const SEGMENTS_SEPARATOR = 'segments_separator';

  /**
   * Flag for including or not the front page as a segment.
   */
  const INCLUDE_HOME_SEGMENT = 'include_home_segment';

  /**
   * Title for the front page segment.
   */
  const HOME_SEGMENT_TITLE = 'home_segment_title';

  /**
   * Flag for including or not the page's title as a segment.
   */
  const INCLUDE_TITLE_SEGMENT = 'include_title_segment';

  /**
   * Flag for printing the page's title as a link, or printing it as a text.
   */
  const TITLE_SEGMENT_AS_LINK = 'title_segment_as_link';

  /**
   * Use the page's title when it is available instead of always trying to
   * deduce it from the URL.
   */
  const TITLE_FROM_PAGE_WHEN_AVAILABLE = 'title_from_page_when_available';

  /**
   * Transformation mode to apply to the segments.
   */
  const CAPITALIZATOR_MODE = 'capitalizator_mode';

  /**
   * List of words to be ignored by the 'capitalizator'. E.g.: of and.
   */
  const CAPITALIZATOR_IGNORED_WORDS = 'capitalizator_ignored_words';

  /**
   * Default list of excluded paths.
   *
   * @return array
   *   Default list of ignored paths.
   */
  public static function defaultExcludedPaths() {
    static $default_excluded_paths = array(
      'search',
      'search/node',
    );

    return $default_excluded_paths;
  }

  /**
   * Default list of ignored words.
   *
   * @return array
   *   Default list of ignored words.
   */
  public static function defaultIgnoredWords() {
    static $default_ignored_words = array(
      'of',
      'and',
      'or',
      'de',
      'del',
      'y',
      'o',
    );

    return $default_ignored_words;
  }
}
