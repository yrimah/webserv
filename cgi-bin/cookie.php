<?php
        echo "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n";
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
		<title>Coooookies</title>
	</head>

	<body>
		<div class="pass__block">
		<h1> Set Cookie: </h1> <br />
    <form action = "/cgi-bin/set_cookie.py" method = "get">
        Cookie Name: <input type = "text" name = "key">  <br />
        <br>
        Cookie Value: <input type = "text" name = "value" />
        <input type = "submit" value = "Submit" /> <br />
    </form>

    <br />
    <br />
    <br />
    <br />
    <h1> Get Cookie: </h1> <br />
    <form action = "/cgi-bin/get_cookie.py" method = "get">
        Cookie Name: <input type = "text" name = "key">  <br />
        <br>
        <input type = "submit" value = "Submit" /> <br />
    </form>
</div>
</body>
</html>