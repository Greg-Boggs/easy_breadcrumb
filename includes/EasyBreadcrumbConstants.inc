<?php

/**
 * @file
 * Module's contants.
 */

/**
 * EasyBreadcrumb module's contants
 */
interface EasyBreadcrumbConstants {

  // The module's name.
  const MODULE_NAME = 'easy_breadcrumb';

  const SEGMENTS_SEPARATOR = 'segments_separator';
  const INCLUDE_FRONT_PAGE_SEGMENT = 'include_front_page';
  const INCLUDE_PAGE_TITLE_SEGMENT = 'inlcude_page_title';
  const PAGE_TITLE_WHEN_AVAILABLE = 'page_title_when_available';
  const CAPITALIZATOR_MODE = 'capitalizator_mode';
  const CAPITALIZATOR_IGNORED_WORDS = 'capitalizator_ignored_words';
  const DISABLE_DRUPAL_DEFAULT_BREADCRUMB = 'disable_drupal_breadcrumb';

  // Prefix for all the database variables.
  const DB_VARS_PREFIX = 'easy_breadcrumb.db_var.';
  
  const DB_VAR_SEGMENTS_SEPARATOR = 'easy_breadcrumb.db_var.segments_separator';
  const DB_VAR_INCLUDE_FRONT_PAGE_SEGMENT = 'easy_breadcrumb.db_var.include_front_page';
  const DB_VAR_INCLUDE_PAGE_TITLE_SEGMENT = 'easy_breadcrumb.db_var.inlcude_page_title';
  const DB_VAR_PAGE_TITLE_WHEN_AVAILABLE = 'easy_breadcrumb.db_var.page_title_when_available';
  const DB_VAR_CAPITALIZATOR_MODE = 'easy_breadcrumb.db_var.capitalizator_mode';
  const DB_VAR_CAPITALIZATOR_IGNORED_WORDS = 'easy_breadcrumb.db_var.capitalizator_ignored_words';
  const DB_VAR_DISABLE_DRUPAL_DEFAULT_BREADCRUMB = 'easy_breadcrumb.db_var.disable_drupal_breadcrumb';

}
