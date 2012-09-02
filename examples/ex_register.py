import urllib

apiUrl = "http://127.0.0.1/rm_api.cgi"

def request(url,command,data):
    qryCmd = urllib.quote_plus(command)
    query = urllib.urlencode(data)
    socket = urllib.urlopen(url + "?cmd=%s&%s" % (qryCmd, query))
    if socket:
        return socket.read(1024);
    else:
        return false;
 
requestData = {
    "tld": "oz",
    "domain": "example",
    "user": "OZTLD",
    "userkey": "1234567890abcdef",
    "name": "John Smith",
    "email": "john@smith.com",
    "ns1": "ns1.fancydns.net",
    "ns2": "ns2.fancydns.net"}

apiResponse = request(url = apiUrl, command = 'register', data = requestData);

if apiResponse:
    print apiResponse
else:
    print "Oh no! Something went wrong..."