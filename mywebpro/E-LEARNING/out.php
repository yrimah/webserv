<?php
    session_start();
    if (isset($_GET["out"]))
    {
        if (isset($_SESSION["name"]))
        {
            unset($_SESSION["name"]);
            session_unset();
            session_destroy();
            header("location: index.php");
        }
    }
    else
        header("location: index.php");
?>