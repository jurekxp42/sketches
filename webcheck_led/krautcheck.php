<?php

function myErrorHandler($fehlercode, $fehlertext, $fehlerdatei, $fehlerzeile){
    echo $fehlercode.' <br />';
    echo $fehlertext.' <br />';
    echo $fehlerdatei.' <br />';
    echo $fehlerzeile.' <br />';
}

define ( 'SERIALPORT' , 'COM1' );

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

for ( $i = 1 ; $i <= 5 ; $i++ ) {
    $serial->sendMessage( "d");
    $count  = file_get_contents ( 'http://www.kraeuterhaus.de/makemyled.php' );
//     var_dump ( $count );

    echo $count."\n";

    switch ( $count ) {
        case '0':
            $serial->sendMessage( "d");
        break;
        case '1':
            $serial->sendMessage( "a");
        break;
        case '2':
            $serial->sendMessage( "b");
        break;
        default:
            $serial->sendMessage( "c");
        break;
    }
    sleep ( 5 );

}

$serial->deviceClose();
