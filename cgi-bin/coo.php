<?php
    echo "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n";
    if (isset($_GET["get"]))
    {
        echo "GEEEEEEEEt";
        if (isset($_COOKIE["cookie"]))
            echo "<p>Cookie value is : " . $_COOKIE["cookie"] ."</p>";
        else
            echo "<p>Cookie not set</p>";
        // header("refresh: 3; url = /cgi-bin/index.php");
    }
?>