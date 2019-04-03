<?php

while ( TRUE ) {
    ob_start();
    passthru ( 'ping -qc 1 i-base.net' , $res );
    $result = ob_get_contents();
    ob_end_clean();
    preg_match( "#\/[0-9]{1,3}\.[0-9]{1,3}\/#sim" , $result , $stat );
    $count = str_replace ( '/' , '' , $stat[ 0 ] );

    echo round( $count )."\n";
    exec ( "echo -n ".( round( $count ) - 152 )." >/dev/ttyUSB0" );
    sleep ( 1 );


}

