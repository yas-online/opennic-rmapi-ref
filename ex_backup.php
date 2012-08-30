<?php
error_reporting(E_ALL);
// domain search example.
$tld="oz";
$domain="opennic";
$user="OZTLD";
$userkey="1234567890abcdef";

// change this to the TLD manager server
$URL="http://127.0.0.1/rm_api.cgi?cmd=backup&user=".$user."&userkey=".$userkey."&tld=".$tld."&domain=".$domain;
$handle=fopen($URL, "r");
$ret_data=fread($handle, 2048);
fclose($handle);
echo "".$ret_data."";
?>
