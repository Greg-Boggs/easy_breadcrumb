<?php if ($segments_quantity > 0): ?>
  <div class="easy-breadcrumb">
    <?php foreach ($breadcrumb as $i => $item): ?>
      <?php print $item; ?>
      <?php if ($i < $segments_quantity - 1): ?>
         <span class="easy-breadcrumb_segment-separator"><?php print $separator; ?></span>
      <?php endif; ?>
    <?php endforeach; ?>
  </div>
<?php endif; ?>