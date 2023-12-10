<?php
    echo "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n";
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>COOOOOOkies</title>
</head>
<body>
    <h1>Teeeest</h1>
    <?php
    // echo "Set-Cookie: " . $_GET["name"] . "=" . $_GET["value"] . "\r\n";
    $test = "testtttt";
    echo "HELoooo ". $_GET["name"];
    echo "HaaaaLoooo ". $_GET["value"];
    echo "Hiiiiiii ". $test;
    // // echo json_encode($_GET);
    // if (isset($_POST["set"]))
    // {
    //     echo "test";
    //     if (isset($_COOKIE["name"]))
    //         echo "<p>Cookie already set.</p>";
    //     else
    //     {
    //         setcookie($_GET["name"], $_GET["value"], time() + (86400 * 30), "/");
    //         echo "Set-Cookie: " . $_GET["name"] . "=" . $_GET["value"] . "\r\n";
    //         echo "<p>Cookie stored</p>";
    //     }
    //     // echo json_encode($_COOKIE);
    // }
?>
</body>
</html>
