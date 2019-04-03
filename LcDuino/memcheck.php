<?php

define ( 'SERIALPORT' , '/dev/ttyACM0' );


require( 'php_serial.class.php' );

$serial = new phpSerial();
$serial->deviceSet( SERIALPORT );
$serial->confBaudRate(9600);
$serial->confParity( 'none' );
$serial->confCharacterLength( 8 );
$serial->confStopBits( 1 );
$serial->confFlowControl( 'none' );
$serial->deviceOpen();

// var_dump ( $serial );
while ( true ) {

//     ob_start();
//     passthru ( 'free' , $res );
//     $result = ob_get_contents();
//     ob_end_clean();

//     $lines = explode ( "\n" , $result );
//     $values = explode ( " " , $lines[1] );
  for ( $i = 97 ; $i <= 122; $i++ ) {
    echo $i.': '.chr( $i )."\n";
  }
  die();
    $message = 'interface';
    $serial->sendMessage( $message );
    sleep ( 1 );

}

$serial->deviceClose();
