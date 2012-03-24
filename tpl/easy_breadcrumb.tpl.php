<?php
/**
 * @file
 * Tpl for breadcrumb.
 */
?>

<?php
if($segments_quantity > 0):
?>

<div class="easy-breadcrumb">

  <?php
  for ($i = 0, $s = $segments_quantity - 1; $i < $segments_quantity; ++$i):
  ?>

    <span class="easy-breadcrumb_segment-wrapper">
      <?php print $breadcrumb[$i]; ?>
    </span>

    <?php if ($i < $s): ?>
      <span class="easy-breadcrumb_segment-separator">
        <?php print $separator; ?>
      </span>
    <?php endif; ?>

  <?php
  endfor;
  ?>

</div>

<?php
endif;
?>
