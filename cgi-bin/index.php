<?php
        echo "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n";
        
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h1>Get cookie</h1>
    <form method="GET" action="/cgi-bin/index.php">
        cookie name: <input type="text" name="cookie">
        <input type="submit" value="Get cookie" name="get">
    </form>
    
    <h1>Set cookie</h1>
    <form method="GET" action="/cgi-bin/set_cookie.php">
        cookie name: <input type="text" name="name">
        cookie value: <input type="text" name="value">
        <input type="submit" value="Set cookie" name="set">
    </form>
</body>
</html>