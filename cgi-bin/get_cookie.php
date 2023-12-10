<?php
    if (isset($_GET["get"]))
    {
        if ($_COOKIE["cookie"])
            echo "<p>Cookie value is : " . $_COOKIE["cookie"] ."</p>";
        else
            echo "<p>Cookie not set</p>";
        // header("");
        header("refresh: 3; url = /cgi-bin/index.php");
    }
?>