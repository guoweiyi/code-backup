<?php
error_reporting(0);
class Start
{
    public $name='cmcc';
    public $flag='/flag';

    public function __wakeup(){
        echo "hello";
        echo $this->name;
    }

    public function __get($cc){
        echo "your flag : ".$this->flag;
        return ;
    }
}

class Grant{
    private $phone_number=10086;
    public $file;

    public function __construct(){
        echo "I want to get flag!";
    }

    public function __toString(){
        return $this->file->fii1lennnaammee['filllennname'];
    }
}

class Bill{
    public $number='';
    public $card='';

    public function __get($name){
        $function = $this->card;
        return $function();
    }

    public function Get_bill($file){
        include($file);
    }

    public function __invoke(){
        $content = $this->Get_bill($this->number);
        echo $content;
    }
}


if (isset($_POST['cmd'])) {
    unserialize($_POST['cmd']);
} else {
    highlight_file(__FILE__);
}
?>