<?php
// domain search example.
error_reporting(E_ALL);
$domain="opennic.oz";
$user="TEST01";
$userkey="1234567890abcdef";
$name="John Smith";
$email="john@smith.com";
$ns1="ns1.fancydns.net";
$ns2="ns2.fancydns.net";

$name=urlencode($name);
$email=urlencode($email);

$URL="http://127.0.0.1/rm_api.cgi?cmd=register&user=".$user."&userkey=".$userkey."&domain=".$domain."&name=".$name."&email=".$email."&ns1=".$ns1."&ns2=".$ns2."";
$handle=fopen($URL, "r");
$ret_data=fread($handle, 10);
fclose($handle);
switch($ret_data)
{
	case "0":
		echo "Error: Something went wrong during the domain registration process.";
		break;
	case "1":
		echo "Success: Domain Registered";
		break;
	case "255":
		echo "Server error occured.";
		break;
	default:
		echo "An unknown problem as occured. Please try again later.";
		break;
}
?>