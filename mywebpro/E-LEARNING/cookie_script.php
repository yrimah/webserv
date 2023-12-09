<?php 
        if (isset($_GET["btn"]))
        {
            $name = $_GET["cookie"];
            $value = $_GET["value"];
            setcookie($name, $value);
            echo "</p style=\"background-color:green;font-size:50px;\">Cookie seted</p>";
        }
        else if (isset($_GET["btnget"]))
        {
            if ($_COOKIE[$_GET["cookiename"]])
            {
                $val = $_COOKIE[$_GET["cookiename"]];
                echo "<p style=\"color:white;background-color:black;font-size:50px;\">" . $val ."</p>";
            }
            else
                echo "<p style=\"background-color:red;font-size:50px;\"> Cookie not set </p>";
        }
        else if (isset($_GET["delete"]))
        {
            if ($_COOKIE[$_GET["cookiename"]])
            {
                setcookie($_GET["cookiename"], "", time() - 3600);
                echo "</p style=\"background-color:green;font-size:50px;\">Cookie deleted</p>";
            }
            else
                echo "<p style=\"background-color:red;font-size:50px;\"> Cookie not set </p>";
        } 
        sleep(3);
        echo '<script type="text/javascript"> 
        window.location.href="cookie.html" 
        </script> ';
    ?>