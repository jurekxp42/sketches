<?php

define ( 'SERIALPORT' , 'USB1' );


require( 'php_serial.class.php' );

$serial = new phpSerial();
$serial->deviceSet( SERIALPORT );
$serial->confBaudRate(9600);
$serial->confParity( 'none' );
$serial->confCharacterLength( 8 );
$serial->confStopBits( 1 );
$serial->confFlowControl( 'none' );
$serial->deviceOpen();


while ( true ) {

    ob_start();
    passthru ( 'free' , $res );
    $result = ob_get_contents();
    ob_end_clean();

    $lines = explode ( "\n" , $result );
    $values = explode ( " " , $lines[1] );

    $pos = 0;
    foreach ( $values AS $val ) {
        if ( empty ( $val ) === FALSE ) {
            $pos++;
            if ( $pos == 2 ) {
                $all = $val;
            }
            if ( $pos == 4 ) {
                $free = $val;
            }
        }

    }
    $all = round ( ( $all / 1024 ) );
    $free = round ( ( $free / 1024 ) );
    $percent = round ( ( $free * 100 / $all  ) );

    switch ( $percent ) {
        case $percent > 50:
            $message = 'c';
        break;
        case $percent > 30:
            $message = 'b';
        break;
        case $percent > 10:
            $message = 'a';
        break;
        default:
            $message = 'd';
        break;
    }

    $serial->sendMessage( $message );
    sleep ( 1 );

}

$serial->deviceClose();
