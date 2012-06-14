<?php
// domain search example.
error_reporting(E_ALL);
$domain="opennic.oz";
$user="TEST01";
$userkey="1234567890abcdef";

$URL="http://127.0.0.1/rm_api.cgi?cmd=check&user=".$user."&userkey=".$userkey."&domain=".$domain;
$handle=fopen($URL, "r");
$ret_data=fread($handle, 1024);
fclose($handle);
switch($ret_data)
{
	case "0":
		echo "Congratulations! ".$domain." is available for registration!";
		break;
	case "1":
		echo "Sorry, ".$domain." has already been registered.";
		break;
	case "255":
		echo "Server error occured.";
		break;
	default:
		echo "An unknown problem as occured. Please try again later.";
		break;
}
?>