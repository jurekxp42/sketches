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

for ( $i = 1 ; $i <= 15 ; $i++ ) {

    ob_start();
    passthru ( 'ping -qc 1 i-base.net' , $res );
    $result = ob_get_contents();
    ob_end_clean();
    preg_match( "#\/[0-9]{1,3}\.[0-9]{1,3}\/#sim" , $result , $stat );
    $count = str_replace ( '/' , '' , $stat[ 0 ] );

    echo $count."\n";

    switch ( $count ) {
        case $count > 30:
            $serial->sendMessage( "d");
        break;
        case $count > 26:
            $serial->sendMessage( "a");
        break;
        case $count > 25:
            $serial->sendMessage( "b");
        break;
        default:
            $serial->sendMessage( "c");
        break;
    }
    sleep ( 1 );

}

$serial->deviceClose();
