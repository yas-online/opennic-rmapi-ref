<?php
// domain search example.
$tld="oz";
$domain="example";
$user="TEST01";
$userkey="1234567890abcdef";

// change this to the TLD manager server
$URL="http://127.0.0.1/rm_api.cgi?cmd=check&user=".$user."&userkey=".$userkey."&tld=".$tld."&domain=".$domain;
$handle=fopen($URL, "r");
$ret_data=fread($handle, 1024);
fclose($handle);
switch($ret_data)
{
	case "0":
		echo "Congratulations! ".$domain.".".$tld." is available for registration!";
		break;
	case "1":
		echo "Sorry, ".$domain.".".$tld." has already been registered.";
		break;
	case "255":
		echo "Server error occured.";
		break;
	default:
		echo "An unknown problem has occured. Please try again later.";
		break;
}
?>