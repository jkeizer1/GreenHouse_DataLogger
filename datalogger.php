<?php
$file = "./data/datalog.txt";
$xmlout = "<RECORD>".PHP_EOL;
$xmlout .= "<DATE>". date('Y-m-d'). "</DATE>". PHP_EOL;


//$xmlout .= "<TIME>". date('H:i'). "</TIME>". PHP_EOL;
if (date('I') == 1) {
	$dst_hour = date('H') + 1;
	$xmlout .= "<TIME>". $dst_hour . ':' . date('i'). "</TIME>". PHP_EOL;
}
else $xmlout .= "<TIME>". date('H:i'). "</TIME>". PHP_EOL;

$xmlout .= "<TEMPC>". $_GET["TEMPC"]. "</TEMPC>". PHP_EOL;
$xmlout .= "</RECORD>". PHP_EOL;
$f = file_put_contents($file, $xmlout, FILE_APPEND);
?>
