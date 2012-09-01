<?php
error_reporting(E_ALL);
// domain search example.
$tld="oz";
$domain="example";
$user="OZTLD";
$userkey="1234567890abcdef";
$name="John Smith";
$email="john@smith.com";
$ns1="ns1.fancydns.net";
$ns2="ns2.fancydns.net";

$name=rawurlencode($name);
$email=rawurlencode($email);

// change this to the TLD manager server
$URL="http://127.0.0.1/rm_api.cgi?cmd=register&user=".$user."&userkey=".$userkey."&tld=".$tld."&domain=".$domain."&name=".$name."&email=".$email."&ns1=".$ns1."&ns2=".$ns2;
$handle=fopen($URL, "r");
$ret_data=fread($handle, 1024);
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
		echo "An unknown problem has occured. Please try again later.";
		break;
}
echo "<h2>Debug</h2>";
echo $URL."-";
echo "[".$ret_data."]";
?>
