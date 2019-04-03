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

switch ( $_GET[ 'action' ] ) {

    case 'checkWeb':

        $serial->deviceSet( SERIALPORT );
        $serial->confBaudRate(9600); //Baud rate: 9600
        $serial->confParity( 'none' );  //Parity (this is the "N" in "8-N-1")
        $serial->confCharacterLength( 1 );
        $serial->confStopBits( 1 );  //Stop bits (this is the "1" in "8-N-1")
        $serial->confFlowControl( 'none' );
        $serial->deviceOpen();
        if ( $_GET[ 'found' ] == 1 ) {
            $serial->sendMessage( "Y" );
        } else {
            $serial->sendMessage( "N");
        }
        echo '<pre>';
        print_r ( $serial );

        $serial->deviceClose();

//     break;

    default:
        echo 'Select Action<br />';
        echo '<a href="webcheck.php?action=checkWeb&found=1">Check with 1</a><br />';
        echo '<a href="webcheck.php?action=checkWeb&found=0">Check with 0</a><br />';

    break;

}