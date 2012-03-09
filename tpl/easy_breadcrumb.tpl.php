<?php
/**
 * @file
 * Tpl for breadcrumb
 */
?>
<div class="easy-breadcrumb">

  <?php
  $n = count($breadcrumb);
  $s = $n - 1;

  for ($i = 0; $i < $n; ++$i):
    ?>

    <span class="easy-breadcrumb_segment-wrapper">
      <?php echo $breadcrumb[$i]; ?>
    </span>

    <?php if ($i < $s): ?>
      <span class="easy-breadcrumb_segment-separator">
        <?php echo $separator; ?>
      </span>
    <?php endif; ?>

  <?php endfor ?>

</div>
