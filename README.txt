The Easy Breadcrumb module provides a plug-and-play block to be embedded in your
pages, typically at some place near the page's header. Easy Breadcrumb takes
advantage of the work you've already done for generating your paths' alias,
while it naturally encourages the creation of semantic and consistent paths.
This modules is currently available for Drupal 7.x.

Easy Breadcrumb uses the current URL (path alias) and the current page's title
to automatically extract the breadcrumb's segments and its respective links.
Easy Breadcrumb is really a plug and play module, it auto-generates the
breadcrumb by using the current URL, the user needs to do anything to get it
working.

For example, having an URL like "gallery/videos/once-a-time-in-cartagena",
EasyBreadcrumb will automatically produces the breadcrumb
"Home >> Gallery >> Videos >> Once a time in Cartagena" or
"Home >> Videos >> Once a Time in Cartagena". Again, the breadcrumb presentation
will vary depending on your module's settings.

Requirements
  * Pathauto

Recommended modules:
  * Transliteration
      is useful if your site is likely contain characters beyond ASCII
      128. Like: ñ, ó, among others. After activate it, go to
      admin/config/search/path/settings and check the option Transliterate
      prior to creating alias.

Configuration:

  To start using it, just go to the admin modules page
  (URL "admin/modules/list"), locate it under the category "others" and activate
  it, then go to the blocks list page (URL "admin/structure/block") and locate
  the block named "Easy Breadcrumb", and configure it like any other block
  (region, URLs, etc.).

  The configuration page of this module is under
  "Admin > Configuration > User Interface > Easy Breadcrumb"
  (URL "admin/config/user-interface/easy-breadcrumb").

  The provided options for this module are the following.

  * To disable the Drupal default breadcrumb: mark / unmark the checkbox
    "Disable the default Drupal's breadcrumb".
  * To include / exclude the front page from the breadcrumb: mark / unmark
    the checkbox "Include the front page as the first segment in the
    breadcrumb".
  * To include / exclude the current page's title from the breadcrumb:
    mark / unmark
    the checkbox "Include the current page's title as a segment in the
    breadcrumb".
  * To decide if the module should use the page's title when it is available
    instead of it always trying to deduce it from the URL: mark / unmark the
    checkbox "Use the page's title when available".
  * To decide if the module should print the title as a link then mark / unmark
    the checkbox "Make the page's title segment a link".
  * To use a custom separator between the breadcrumb's segments: just enter
    the string (default to ">>") to be used as the segments separator in the
    textfield "Segments separator".
  * The module allows to choose a transformation mode for the segments' title:
    for this, choose one of the provided options in the combobox
    "Transformation mode for the segments' titles".
  * You might want some words to be ignored (not to be capitalized) by the
    'capitalizator'. For this, enter the desired words to be ignored by the
    'capitalizator' separating them with a space. There is a 'textarea' named
    "Words to be ignored by the 'capitalizator'" for this purpose.
  * For excluding some paths from the segments to be generated, enter a
    line-separated list of paths (relatives to root) in the 'textarea' named
    "Paths to be excluded while generating the breadcrumb's segments".
    E.g.: blog/article.

Module Page: http://drupal.org/project/easy_breadcrumb
