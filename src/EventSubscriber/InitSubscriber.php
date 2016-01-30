<?php /**
 * @file
 * Contains \Drupal\easy_breadcrumb\EventSubscriber\InitSubscriber.
 */

namespace Drupal\easy_breadcrumb\EventSubscriber;

use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;

class InitSubscriber implements EventSubscriberInterface {

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    return [KernelEvents::REQUEST => ['onEvent', 0]];
  }

  public function onEvent() {
    $disable_drupal_default_breadcrumb = variable_get(EasyBreadcrumbConstants::DB_VAR_DISABLE_DEFAULT_DRUPAL_BREADCRUMB, TRUE);
    if ($disable_drupal_default_breadcrumb) {
      // Sets the Drupal's default breadcrumb as an empty array to disable it.
      drupal_set_breadcrumb([]);
    }
  }

}
