The Easy Breadcrumb module provides a plug-and-play breadcrumb block to be
embedded in your pages, typically at some place near the page's header.

Easy Breadcrumb uses the current URL (path alias) and the current page's title
to automatically extract the breadcrumb's segments and its respective links.
Easy Breadcrumb is really a plug and play module, it auto-generates the
breadcrumb by using the current URL, the user needs dont's need to configure
anything to get it working.

The resulting block will display something like: "Home >> Contact Us" or
"Home / Contact us". The breadcrumb presentation could vary depending on your
module's settings.


*** Module's Configuration ***

  To start using it, just go to the admin modules page (URL "admin/modules/list"),
  locate it under the category "others" and activate it, then go to the blocks list page
  (URL "admin/structure/block") and locate the block named "Easy Breadcrumb",
  and configure it like any other block (region, URLs, etc.).

  The configuration page of this module is under "Admin > Configuration > Easy Breadcrumb"
  (URL "admin/config/easy-breadcrumb").

  The provided options for this module are the following.

  * To disable the Drupal default breadcrumb: mark / unmark the checkbox
    "Disable the Drupal's default breadcrumb".
  * To include / exclude the front page from the breadcrumb: mark / unmark
    the checkbox "Display the front page as a segment in the breadcrumb".
  * To include / exclude the current page's title from the breadcrumb: mark / unmark
    the checkbox "Display the current page's title in the breadcrumb".
  * To decide if the module should use the page's title when it is available
    instead of it always trying to deduce it from the URL: mark / unmark the
    checkbox "Use the page's title when available".
  * To use a custom separator between the breadcrumb's segments: just enter
    the string (default to ">>") or the HTML code to be used as the segments
    separator in the textfield "Segments separator".
  * The module allows to choose a transformation mode for to the segments's
    title: for this, choose one of the provided options in the combobox
    "Segments title's transformation mode".
  * You might want some words to be ignored (not to be capitalized) by the
    'capitalizator': for this, enter the desired words to be ignored by the
    'capitalizator' separating them with commas. There is a 'textarea' named
    "Words to be ignored by the 'capitalizator'" for this purpose.

*** end Module's Configuration ***
