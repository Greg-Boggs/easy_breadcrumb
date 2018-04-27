<?php

namespace Drupal\easy_breadcrumb;

use Drupal\Component\Render\FormattableMarkup;
use Drupal\Component\Utility\Unicode;
use Drupal\Component\Utility\Xss;
use Drupal\Core\Access\AccessManagerInterface;
use Drupal\Core\Breadcrumb\Breadcrumb;
use Drupal\Core\Breadcrumb\BreadcrumbBuilderInterface;
use Drupal\Core\Cache\CacheableDependencyInterface;
use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Controller\TitleResolverInterface;
use Drupal\Core\Link;
use Drupal\Core\ParamConverter\ParamNotConvertedException;
use Drupal\Core\Path\CurrentPathStack;
use Drupal\Core\PathProcessor\InboundPathProcessorInterface;
use Drupal\Core\Routing\RequestContext;
use Drupal\Core\Routing\RouteMatch;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\StringTranslation\StringTranslationTrait;
use Drupal\Core\StringTranslation\TranslatableMarkup;
use Drupal\Core\Url;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpKernel\Exception\AccessDeniedHttpException;
use Symfony\Component\Routing\Exception\MethodNotAllowedException;
use Symfony\Component\Routing\Exception\ResourceNotFoundException;
use Symfony\Component\Routing\Matcher\RequestMatcherInterface;
use Drupal\Core\Menu\MenuLinkManager;

/**
 * Class to define the menu_link breadcrumb builder.
 */
class EasyBreadcrumbBuilder implements BreadcrumbBuilderInterface {
  use StringTranslationTrait;

  /**
   * The router request context.
   *
   * @var \Drupal\Core\Routing\RequestContext
   */
  protected $context;

  /**
   * The menu link access service.
   *
   * @var \Drupal\Core\Access\AccessManagerInterface
   */
  protected $accessManager;

  /**
   * The dynamic router service.
   *
   * @var \Symfony\Component\Routing\Matcher\RequestMatcherInterface
   */
  protected $router;

  /**
   * The dynamic router service.
   *
   * @var \Drupal\Core\PathProcessor\InboundPathProcessorInterface
   */
  protected $pathProcessor;

  /**
   * Site config object.
   *
   * @var \Drupal\Core\Config\Config
   */
  protected $siteConfig;

  /**
   * Breadcrumb config object.
   *
   * @var \Drupal\Core\Config\Config
   */
  protected $config;

  /**
   * The title resolver.
   *
   * @var \Drupal\Core\Controller\TitleResolverInterface
   */
  protected $titleResolver;

  /**
   * The current user object.
   *
   * @var \Drupal\Core\Session\AccountInterface
   */
  protected $currentUser;

  /**
   * The menu link manager.
   *
   * @var \Drupal\Core\Menu\MenuLinkManager
   */
  protected $menuLinkManager;

  /**
   * Constructs the PathBasedBreadcrumbBuilder.
   *
   * @param \Drupal\Core\Routing\RequestContext $context
   *   The router request context.
   * @param \Drupal\Core\Access\AccessManagerInterface $access_manager
   *   The menu link access service.
   * @param \Symfony\Component\Routing\Matcher\RequestMatcherInterface $router
   *   The dynamic router service.
   * @param \Drupal\Core\PathProcessor\InboundPathProcessorInterface $path_processor
   *   The inbound path processor.
   * @param \Drupal\Core\Config\ConfigFactoryInterface $config_factory
   *   The config factory service.
   * @param \Drupal\Core\Controller\TitleResolverInterface $title_resolver
   *   The title resolver service.
   * @param \Drupal\Core\Session\AccountInterface $current_user
   *   The current user object.
   * @param \Drupal\Core\Path\CurrentPathStack $current_path
   *   The current path.
   * @param \Drupal\Core\Menu\MenuLinkManager $menu_link_manager
   *   The menu link manager.
   */
  public function __construct(RequestContext $context, AccessManagerInterface $access_manager, RequestMatcherInterface $router, InboundPathProcessorInterface $path_processor, ConfigFactoryInterface $config_factory, TitleResolverInterface $title_resolver, AccountInterface $current_user, CurrentPathStack $current_path, MenuLinkManager $menu_link_manager) {
    $this->context = $context;
    $this->accessManager = $access_manager;
    $this->router = $router;
    $this->pathProcessor = $path_processor;
    $this->siteConfig = $config_factory->get('system.site');
    $this->config = $config_factory->get('easy_breadcrumb.settings');
    $this->titleResolver = $title_resolver;
    $this->currentUser = $current_user;
    $this->currentPath = $current_path;
    $this->menuLinkManager = $menu_link_manager;
  }

  /**
   * {@inheritdoc}
   */
  public function applies(RouteMatchInterface $route_match) {
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function build(RouteMatchInterface $route_match) {
    $breadcrumb = new Breadcrumb();
    $links = [];
    $exclude = [];
    $curr_lang = \Drupal::languageManager()->getCurrentLanguage()->getId();
    $replacedTitles = [];
    $mapValues = preg_split('/[\r\n]+/', $this->config->get(EasyBreadcrumbConstants::REPLACED_TITLES));

    foreach ($mapValues as $mapValue) {
      $values = explode("::", $mapValue);
      if (count($values) == 2) {
        $replacedTitles[$values[0]] = $values[1];
      }
    }

    // General path-based breadcrumbs. Use the actual request path, prior to
    // resolving path aliases, so the breadcrumb can be defined by simply
    // creating a hierarchy of path aliases.
    $path = trim($this->context->getPathInfo(), '/');
    $path = urldecode($path);
    $path_elements = explode('/', $path);
    $front = $this->siteConfig->get('page.front');

    // Give the option to keep the breadcrumb on the front page.
    $keep_front = !empty($this->config->get(EasyBreadcrumbConstants::HOME_SEGMENT_TITLE))
                  && $this->config->get(EasyBreadcrumbConstants::HOME_SEGMENT_KEEP);
    $exclude[$front] = !$keep_front;
    $exclude[''] = !$keep_front;
    $exclude['/user'] = TRUE;


    $parameters = $route_match->getParameters();
    foreach ($parameters as $key => $parameter) {
      if ($key === 'view_id') {
        $breadcrumb->addCacheTags(['config:views.view.' . $parameter]);
      }
      // TODO: only consider route parameters that actually are being used below!
      if ($parameter instanceof CacheableDependencyInterface) {
        $breadcrumb->addCacheableDependency($parameter);
      }
    }

    // Because this breadcrumb builder is path and config based, vary cache
    // by the 'url.path' cache context and config changes.
    $breadcrumb->addCacheContexts(['url.path']);
    $breadcrumb->addCacheableDependency($this->config);
    $i = 0;
    $add_langcode = FALSE;

    // Remove the current page if it's not wanted.
    if (!$this->config->get(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT)) {
      array_pop($path_elements);
    }

    if (isset($path_elements[0])) {

      // Remove the first parameter if it matches the current language.
      if (!($this->config->get(EasyBreadcrumbConstants::LANGUAGE_PATH_PREFIX_AS_SEGMENT))) {
        if (Unicode::strtolower($path_elements[0]) == $curr_lang) {
          array_shift($path_elements);
          $add_langcode = TRUE;
        }
      }
    }
    while (count($path_elements) > 0) {
      $check_path = '/' . implode('/', $path_elements);
      if ($add_langcode) {
        $check_path = '/' . $curr_lang . $check_path;
      }

      // Copy the path elements for up-casting.
      $route_request = $this->getRequestForPath($check_path, $exclude);
      if ($this->config->get(EasyBreadcrumbConstants::EXCLUDED_PATHS)) {
        $config_textarea = $this->config->get(EasyBreadcrumbConstants::EXCLUDED_PATHS);
        $excludes = preg_split('/[\r\n]+/', $config_textarea, -1, PREG_SPLIT_NO_EMPTY);
        if (in_array(end($path_elements), $excludes)) {
          break;
        }
      }

      if ($route_request) {
        $route_match = RouteMatch::createFromRequest($route_request);
        $access = $this->accessManager->check($route_match, $this->currentUser, NULL, TRUE);
        $breadcrumb = $breadcrumb->addCacheableDependency($access);
        // The set of breadcrumb links depends on the access result, so merge
        // the access result's cacheability metadata.
        if ($access->isAllowed()) {
          if ($this->config->get(EasyBreadcrumbConstants::TITLE_FROM_PAGE_WHEN_AVAILABLE)) {
            $title = $this->getTitleString($route_request, $route_match, $replacedTitles);

            // If the title is to be replaced...
            if ($title && array_key_exists($title, $replacedTitles)) {
              // Replaces the title.
              $title = $replacedTitles[$title];
            }
          }
          if (!isset($title)) {

            if ($this->config->get(EasyBreadcrumbConstants::USE_MENU_TITLE_AS_FALLBACK)) {
              // Try resolve the menu title from the route.
              $route_name = $route_match->getRouteName();
              $route_parameters = $route_match->getRawParameters()->all();
              $menu_links = $this->menuLinkManager->loadLinksByRoute($route_name, $route_parameters);

              if (!empty($menu_links)) {
                $menu_link = reset($menu_links);
                $title = $menu_link->getTitle();
                if (array_key_exists($title, $replacedTitles)) {
                  $title = $replacedTitles[$title];
                }
              }
            }

            // Fallback to using the raw path component as the title if the
            // route is missing a _title or _title_callback attribute.
            if (!isset($title)) {
              $title = str_replace(['-', '_'], ' ', Unicode::ucfirst(end($path_elements)));
              if (array_key_exists($title, $replacedTitles)) {
                $title = $replacedTitles[$title];
              }
            }
          }

          // Add a linked breadcrumb unless it's the current page.
          if ($i == 0
              && $this->config->get(EasyBreadcrumbConstants::INCLUDE_TITLE_SEGMENT)
              && !$this->config->get(EasyBreadcrumbConstants::TITLE_SEGMENT_AS_LINK)) {
            $links[] = Link::createFromRoute($title, '<none>');
          }
          else {
            $url = Url::fromRouteMatch($route_match);
            if ($this->config->get(EasyBreadcrumbConstants::ABSOLUTE_PATHS)) {
              $url->setOption('absolute', TRUE);
            }
            $links[] = new Link($title, $url);
          }
          unset($title);
          $i++;
        }
      }
      elseif ($this->config->get(EasyBreadcrumbConstants::INCLUDE_INVALID_PATHS) && empty($exclude[implode('/', $path_elements)])) {
        // TODO: exclude the 404 page and other's with a system path.
        $title = str_replace(['-', '_'], ' ', Unicode::ucfirst(end($path_elements)));
        $this->applyTitleReplacement($title, $replacedTitles);
        $links[] = Link::createFromRoute($title, '<none>');
        unset($title);
      }
      array_pop($path_elements);
    }

    // Add the home link, if desired.
    if ($this->config->get(EasyBreadcrumbConstants::INCLUDE_HOME_SEGMENT)) {
      if ($path && '/' . $path != $front && $path != $curr_lang) {
        $links[] = Link::createFromRoute($this->config->get(EasyBreadcrumbConstants::HOME_SEGMENT_TITLE), '<front>');
      }
      if ($this->config->get(EasyBreadcrumbConstants::HIDE_SINGLE_HOME_ITEM) && count($links) === 1) {
        return $breadcrumb->setLinks([]);
      }
    }
    $links = array_reverse($links);

    if ($this->config->get(EasyBreadcrumbConstants::REMOVE_REPEATED_SEGMENTS)) {
      $links = $this->removeRepeatedSegments($links);
    }

    return $breadcrumb->setLinks($links);
  }

  /**
   * Apply title replacements.
   *
   * @param string $title
   *   Page title.
   * @param array $replacements
   *   Replacement rules map.
   */
  public function applyTitleReplacement(&$title, array $replacements) {
    if (!is_string($title)) {

      return;
    }

    if (array_key_exists($title, $replacements)) {
      $title = $replacements[$title];
    }
  }

  /**
   * Get string title for route.
   *
   * @param \Symfony\Component\HttpFoundation\Request $route_request
   *   A request object.
   * @param \Drupal\Core\Routing\RouteMatchInterface $route_match
   * @param array $replacedTitles
   *
   *
   * @return string | FALSE
   *   Either the current title string or FALSE if unable to determine it.
   */
  public function getTitleString(Request $route_request, RouteMatchInterface $route_match, array $replacedTitles) {
    $title = $this->titleResolver->getTitle($route_request, $route_match->getRouteObject());
    $this->applyTitleReplacement($title, $replacedTitles);
    // Get string from title. Different routes return different objects.
    // Many routes return a translatable markup object.
    if ($title instanceof TranslatableMarkup) {
      $title = $title->render();
    }
    elseif ($title instanceof FormattableMarkup) {
      $title = (string) $title;
    }

    // Other paths, such as admin/structure/menu/manage/main, will
    // return a render array suitable to render using core's XSS filter.
    elseif (is_array($title) && array_key_exists('#markup', $title)) {
      // If this render array has #allowed tags use that instead of default.
      $tags = array_key_exists('#allowed_tags', $title) ? $title['#allowed_tags'] : NULL;
      $title = Xss::filter($title['#markup'], $tags);
    }

    // If a route declares the title in an unexpected way log and return FALSE.
    if (!is_string($title)) {
      \Drupal::logger('easy_breadcrumb')->notice('Easy Breadcrumb could not determine the title to use for @path', ['@path' => $route_match->getRouteObject()->getPath()]);
      return FALSE;
    }
    return $title;
  }

  /**
   * Remove duplicate repeated segments.
   *
   * @param \Drupal\Core\Link[] $links
   *   The links.
   *
   * @return \Drupal\Core\Link[]
   *   The new links.
   */
  protected function removeRepeatedSegments(array $links) {
    $newLinks = [];

    /** @var \Drupal\Core\Link $last */
    $last = NULL;

    foreach ($links as $link) {
      if (empty($last) || (!$this->linksAreEqual($last, $link))) {
        $newLinks[] = $link;
      }

      $last = $link;
    }

    return $newLinks;
  }

  /**
   * Compares two breadcrumb links for equality.
   *
   * @param \Drupal\Core\Link $link1
   *   The first link.
   * @param \Drupal\Core\Link $link2
   *   The second link.
   *
   * @return bool
   *   TRUE if equal, FALSE otherwise.
   */
  protected function linksAreEqual(Link $link1, Link $link2) {
    $links_equal = TRUE;

    if ($link1->getText() instanceof TranslatableMarkup) {
      $link_one_text = (string) $link1->getText();
    }
    else {
      $link_one_text = $link1->getText();
    }

    if ($link2->getText() instanceof TranslatableMarkup) {
      $link_two_text = (string) $link2->getText();
    }
    else {
      $link_two_text = $link2->getText();
    }

    if ($link_one_text != $link_two_text) {
      $links_equal = FALSE;
    }

    if ($link1->getUrl()->getInternalPath() != $link2->getUrl()->getInternalPath()) {
      $links_equal = FALSE;
    }

    return $links_equal;
  }

  /**
   * Matches a path in the router.
   *
   * @param string $path
   *   The request path with a leading slash.
   * @param array $exclude
   *   An array of paths or system paths to skip.
   *
   * @return \Symfony\Component\HttpFoundation\Request
   *   A populated request object or NULL if the path couldn't be matched.
   */
  protected function getRequestForPath($path, array $exclude) {
    if (!empty($exclude[$path])) {
      return NULL;
    }
    // @todo Use the RequestHelper once https://www.drupal.org/node/2090293 is
    //   fixed.
    $request = Request::create($path);
    // Performance optimization: set a short accept header to reduce overhead in
    // AcceptHeaderMatcher when matching the request.
    $request->headers->set('Accept', 'text/html');
    // Find the system path by resolving aliases, language prefix, etc.
    $processed = $this->pathProcessor->processInbound($path, $request);
    if (empty($processed) || !empty($exclude[$processed])) {
      // This resolves to the front page, which we already add.
      return NULL;
    }
    $this->currentPath->setPath($processed, $request);
    // Attempt to match this path to provide a fully built request.
    try {
      $request->attributes->add($this->router->matchRequest($request));
      return $request;
    }
    catch (ParamNotConvertedException $e) {
      return NULL;
    }
    catch (ResourceNotFoundException $e) {
      return NULL;
    }
    catch (MethodNotAllowedException $e) {
      return NULL;
    }
    catch (AccessDeniedHttpException $e) {
      return NULL;
    }
  }

}
