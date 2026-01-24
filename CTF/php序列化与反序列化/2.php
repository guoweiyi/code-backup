<?php
class mylogin{
    var $user;
    var $pass;
    function __construct($user,$pass){
        $this->user=$user;
        $this->pass=$pass;
    }
    function login(){
        if ($this->user=="daydream" and $this->pass=="ok"){
            return 1;
        }
    }
}
$a=new mylogin('daydream','ok');
echo serialize($a);
?>