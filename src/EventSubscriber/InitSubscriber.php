<?php /**
 * @file
 * Contains \Drupal\easy_breadcrumb\EventSubscriber\InitSubscriber.
 */

namespace Drupal\easy_breadcrumb\EventSubscriber;

use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Drupal\easy_breadcrumb\EasyBreadcrumbConstants;

class InitSubscriber implements EventSubscriberInterface {

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    return [KernelEvents::REQUEST => ['onEvent', 0]];
  }

  public function onEvent() {
    $config = \Drupal::config('easy_breadcrumb.settings');
    $disable_drupal_default_breadcrumb = $config->get(EasyBreadcrumbConstants::DISABLE_DEFAULT_DRUPAL_BREADCRUMB);
    if ($disable_drupal_default_breadcrumb) {
      // Sets the Drupal's default breadcrumb as an empty array to disable it.
      //drupal_set_breadcrumb([]);
    }
  }

}
