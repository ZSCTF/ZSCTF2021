<?php

error_reporting(0);

class superGate{
    public $gay = true;

    function __destruct(){
        echo file_get_contents("/flag");
        die();
    }
}

$p = $_GET['p'];
$honey = unserialize($p);
if(preg_match("/superGate/i", serialize($honey))){
    echo "no";
    throw Exception();
}

show_source(__FILE__);
  