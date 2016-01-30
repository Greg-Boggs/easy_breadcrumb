<?php
/**
 * @file
 * The Easy Breadcrumb module provides a block to be embedded in any page,
 * typically at some place near the page's header.
 * Easy Breadcrumb uses the URL (path alias) and the current page's title
 * (when available) to obtain the breadcrumb's segments and its respective
 * links. The resulting block will be something like:
 * "Home >> Contact Us" or "Home / Contact us".
 * Such presentation could vary depending on the configuration of the module.
 */
namespace Drupal\easy_breadcrumb;

// mymodule/src/EasyBreadcrumbBuilder.php

namespace Drupal\easy_breadcrumb;

use Drupal\Core\Breadcrumb\BreadcrumbBuilderInterface;
use Drupal\Core\Routing\LinkGeneratorTrait;
use Drupal\Core\StringTranslation\StringTranslationTrait;

class EasyBreadcrumbBuilder implements BreadcrumbBuilderInterface {
  use LinkGeneratorTrait;
  use StringTranslationTrait;

  /**
   * {@inheritdoc}
   */
  public function applies(array $attributes) {
    if ($attributes['_route'] == 'node_page') {
      return $attributes['node']->bundle() == 'article';
    }
  }

  /**
   * {@inheritdoc}
   */
  public function build(array $attributes) {
    $breadcrumb = [Link::createFromRoute($this->t('Home'), '<front>')];
    // Presumably this link has been defined elsewhere.
    $breadcrumb[] = Link::createFromRoute($this->t('Articles'), 'articles_route');
    // Breadcrumbs should not include the current page. The theme system
    // will take care of that.
    return $breadcrumb;
  }
}