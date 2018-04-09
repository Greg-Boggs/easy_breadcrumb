<?php

namespace Drupal\Tests\easy_breadcrumb\Kernel;

use Drupal\Core\Routing\RequestContext;
use Drupal\Core\Routing\RouteMatch;
use Drupal\easy_breadcrumb\EasyBreadcrumbBuilder;
use Drupal\KernelTests\KernelTestBase;
use Symfony\Component\Routing\Route;

/**
 * Tests the easy breadcrumb builder.
 *
 * @group easy_breadcrumb
 */
class EasyBreadcrumbBuilderTest extends KernelTestBase {

  public static $modules = ['easy_breadcrumb', 'system'];

  /**
   * Tests the front page with an invalid path.
   */
  public function testFrontpageWithInvalidPaths() {
    \Drupal::configFactory()->getEditable('easy_breadcrumb.settings')
      ->set('include_invalid_paths', TRUE)
      ->set('include_title_segment', TRUE)
      ->save();
    \Drupal::configFactory()->getEditable('system.site')
      ->set('page.front', '/path')
      ->save();

    $request_context = new RequestContext();
    $breadcrumb_builder = new EasyBreadcrumbBuilder($request_context,
      \Drupal::service('access_manager'), \Drupal::service('router'),
      \Drupal::service('path_processor_manager'),
      \Drupal::service('config.factory'),
      \Drupal::service('title_resolver'), \Drupal::service('current_user'),
      \Drupal::service('path.current'),
      \Drupal::service('plugin.manager.menu.link')
    );

    $route_match = new RouteMatch('test_front', new Route('/front'));
    $result = $breadcrumb_builder->build($route_match);
    $this->assertCount(0, $result->getLinks());
  }

}
