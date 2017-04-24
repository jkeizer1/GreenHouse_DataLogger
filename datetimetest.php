<Head>
	 <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

    <meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate"/>
    <meta http-equiv="Pragma" content="no-cache"/>
    <meta http-equiv="Expires" content="0"/>
</Head>
<body>
<?php
$xmlout = "<RECORD>".PHP_EOL;
$xmlout .= "<DATE>". date('Y-m-d'). "</DATE>". PHP_EOL;
if (date('I') == 1) {
	echo ("ok 7");
	$dst_hour = date('H') + 1;
	$xmlout .= "<TIME>". $dst_hour . ':' . date('i'). "</TIME>". PHP_EOL;
}
else $xmlout .= "<TIME>". date('i'). "</TIME>". PHP_EOL;
$xmlout .= "<TEMPC>25.2</TEMPC>". PHP_EOL;
$xmlout .= "</RECORD>". PHP_EOL;

echo ($xmlout);

?>
</body>
