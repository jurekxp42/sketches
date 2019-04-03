<?php

function myErrorHandler($fehlercode, $fehlertext, $fehlerdatei, $fehlerzeile){
    echo $fehlercode.' <br />';
    echo $fehlertext.' <br />';
    echo $fehlerdatei.' <br />';
    echo $fehlerzeile.' <br />';
}

define ( 'SERIALPORT' , 'USB1' );

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

while ( true ) {

    ob_start();
    passthru ( 'cat /proc/loadavg' , $res );
    $result = ob_get_contents();
    ob_end_clean();
    preg_match( "#^[0-9]\.[0-9]{1,2} #sim" , $result , $stat );
    $count = str_replace ( '/' , '' , $stat[ 0 ] );

//     echo $count." | ";

    switch ( $count ) {
        case $count > 0.75:
            $message = 'c';
        break;
        case $count > 0.50:
            $message = 'b';
        break;
        case $count > 0.25:
            $message = 'a';
        break;
        default:
            $message = 'd';
        break;
    }
//     echo $message."\n";
    $serial->sendMessage( $message );
    sleep ( 1 );

}

$serial->deviceClose();
