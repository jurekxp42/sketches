<?php

function myErrorHandler($fehlercode, $fehlertext, $fehlerdatei, $fehlerzeile){
    echo $fehlercode.' <br />';
    echo $fehlertext.' <br />';
    echo $fehlerdatei.' <br />';
    echo $fehlerzeile.' <br />';
}

define ( 'SERIALPORT' , '/dev/ttyUSB0' );

$alter_error_handler = set_error_handler("myErrorHandler");

require( 'php_serial.class.php' );
$serial = new phpSerial();


$serial->deviceSet( SERIALPORT );
$serial->confBaudRate(9600); //Baud rate: 9600
$serial->confParity( 'none' );  //Parity (this is the "N" in "8-N-1")
$serial->confCharacterLength( 8 );
$serial->confStopBits( 1 );  //Stop bits (this is the "1" in "8-N-1")
$serial->confFlowControl( 'none' );
$serial->deviceOpen();

// echo '<pre>';
$string = '';
$count = getPing();
$wert =  str_pad ( $string , $count , 'f' );
echo $wert."\n";
$serial->sendMessage( $wert );
sleep ( 1 );

for ( $i = 1 ; $i <= 150 ; $i++ ) {
    
    $count2 = getPing();
    $step = ( $count2 - $count );
    $count = $count2;
    if ( $step < 0 ) {
        $wert =  str_pad ( $string , ( $step * - 1 ) , 'g' );
    } else {
        $wert =  str_pad ( $string , $step , 'f' );
    }
    echo $wert."\n";
    $serial->sendMessage( $wert );
    sleep ( 1 );


}

$serial->deviceClose();

function getPing() {
    ob_start();
    passthru ( 'ping -qc 1 i-base.net' , $res );
    $result = ob_get_contents();
    ob_end_clean();
    preg_match( "#\/[0-9]{1,3}\.[0-9]{1,3}\/#sim" , $result , $stat );
    $count = str_replace ( '/' , '' , $stat[ 0 ] );
    return round($count);
}