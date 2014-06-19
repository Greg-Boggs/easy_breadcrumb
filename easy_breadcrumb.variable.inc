<?php

/**
 * @file
 * Definition of variables for Variable API module.
 */

/**
 * Implements hook_variable_group_info().
 */
function easy_breadcrumb_variable_group_info() {
  $groups['easy_breadcrumb'] = array(
    'title' => t('Easy Breadcrumb'),
    'description' => t('Easy Breadcrumb configuration'),
    'access' => 'administer easy_breadcrumb',
    'path' => array('admin/config/user-interface/easy-breadcrumb'),
  );
  
  return $groups;
}

/**
 * Implements hook_variable_info().
 */
function easy_breadcrumb_variable_info($options) {
  $variables[EasyBreadcrumbConstants::DB_VAR_HOME_SEGMENT_TITLE] = array(
    'title' => t('Title for the front page segment in the breadcrumb', array(), $options),
    'description' => t('Text to be displayed as the from page segment.', array(), $options),
    'type' => 'string',
    'default' => t('Home'),
    'localize' => TRUE,
    'required' => TRUE,
    'multidomain' => TRUE,
    'group' => 'easy_breadcrumb',
  );
  return $variables;
}