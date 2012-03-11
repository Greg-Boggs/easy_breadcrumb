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

  // Prefix for all the database variables.
  const DB_VARS_PREFIX = 'easy_breadcrumb.db_var.';
  const DB_VAR_SEGMENTS_SEPARATOR = 'easy_breadcrumb.db_var.segments_separator';
  const DB_VAR_TITLE_VISIBLE = 'easy_breadcrumb.db_var.title_visible';
  const DB_VAR_PAGE_TITLE_WHEN_AVAILABLE = 'easy_breadcrumb.db_var.page_title_when_available';
  const DB_VAR_SEGMENTS_CAPITALIZE_MODE = 'easy_breadcrumb.db_var.segments_capitalize_mode';
  const DB_VAR_SEGMENTS_CAPITALIZE_IGNORED_WORDS = 'easy_breadcrumb.db_var.segments_capitalize_ignored_words';

}
