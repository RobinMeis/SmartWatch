<?php
function generate_array($filename) {
  $image = imagecreatefrompng ($filename);
  for ($y=0; $y<16; ++$y) {
    $short = 0;
    for ($x=0; $x<16; ++$x) {
      if (imagecolorat ($image, $x, $y)>0)
        $short |= (1<<$x);
    }
    echo "$short, ";
  }
  echo "\n";
}

generate_array("icon.png");
?>
