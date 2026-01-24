<?php

class you {
    private $body;
    private $pro;

    public function __construct($props = []) {
        foreach($props as $k => $v) {
            $this->$k = $v;
        }
    }
    public function linkReference($p1, $p2) {
        $this->$p2 = &$this->$p1;
    }
}

// Setting private $body
// Setting private $pro
$props = array(
    'body' => 'test',
    'pro' => 'test',
);
$obj = new you($props);
echo urlencode(serialize($obj));

// POC Segment 
class my {
    public $name;

    public function __construct($props = []) {
        foreach($props as $k => $v) {
            $this->$k = $v;
        }
    }
    public function linkReference($p1, $p2) {
        $this->$p2 = &$this->$p1;
    }
}

// Setting public $name
$props = array(
    'name' => 'myname',
);
$obj = new my($props);
echo urlencode(serialize($obj));

?>