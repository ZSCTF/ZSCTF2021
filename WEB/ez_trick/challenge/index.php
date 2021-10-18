<?php
if (!isset($_POST['a'])&!isset($_POST['b'])&!isset($_GET['cmd']))
{
   show_source("index.php");
}
$a=$_POST['a'];
$b=$_POST['b'];
if($b!==$a&sha1($a)===sha1($b)){
        $cmd = $_GET['cmd'];
        if (!preg_match('/flag/i',$cmd))
        {
            $cmd = escapeshellarg($cmd);
            system('cat '.$cmd);
        }
}
?>
