<?php
    session_start();
    if (isset($_SESSION["name"]))
        header("location: account.php");
    // {
    //     session_start();
    //     // echo $_POST["signname"];
    //     // echo "TSTE";
    //     $_SESSION["name"] = $_POST["logemail"];
    // }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="shortcut icon" href="img/icon.png">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">
    <link rel="stylesheet" href="css/style.css">
    <title>E-LEARNING-PLATFORME</title>
</head>
<body>
    <!--Start header-->
    <div class="header">
        <div class="container">
            <div class="row">
                <div class="col">
                    E-learning@platforme.ma - <a href="" class="btn btn-outline-primary"  data-toggle="modal" data-target="#staticBackdrop" style="margin: 5px;">Login</a>
                    <a href="" class="btn btn-outline-primary"  data-toggle="modal" data-target="#staticBackdrop1" style="margin: 5px;">Sign-Up</a>
                </div>
                <div class="col">
                    <ul>
                        <li><a href="https://www.facebook.com/E-learning-platforme" target="_blank"><i class="fa fa-facebook-square"></i></a></li>
                        <li><a href="https://www.instagram.com/E-learning-platforme" target="_blank"><i class="fa fa-instagram"></i></a></li>
                        <li><a href="https://www.twitter.com/E-learning-platforme" target="_blank"><i class="fa fa-twitter"></i></a></li>
                        <li><a href="https://www.pinterest.com/E-learning-platforme" target="_blank"><i class="fa fa-pinterest-p"></i></a></li>
                    </ul>
                </div>
            </div>
        </div>
    </div>
    <!--End header-->
        <!--Start navbar-->
        <nav class="navbar navbar-expand-lg navbar-light">
            <div class="container">
                <a class="navbar-brand" href="index.php">
                    <img src="img/logo.png" width="180" alt="Logo">
                </a>
                <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
                    <span class="navbar-toggler-icon"></span>
                    </button>
                    <div class="collapse navbar-collapse" id="navbarSupportedContent">
                    <ul class="navbar-nav ml-auto">
                        <li class="nav-item active">
                        <a class="nav-link" href="index.html">HOME<span class="sr-only">(current)</span></a>
                        </li>
                        <li class="nav-item">
                        <a class="nav-link" href="#teachers">TEACHERS</a>
                        </li>
                        <li class="nav-item dropdown">
                        <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                            COURSES
                        </a>
                        <div class="dropdown-menu" aria-labelledby="navbarDropdown">
                            <a class="dropdown-item" href="courses.html#html_css">HTML/CSS</a>
                            <a class="dropdown-item" href="courses.html#js_jquery">JAVASCRIPT/JQUERY</a>
                            <a class="dropdown-item" href="courses.html#angular_vue">ANGULAR/VUE</a>
                            <a class="dropdown-item" href="courses.html#php_laravel">PHP/LARAVEL</a>
                            <a class="dropdown-item" href="courses.html#python_django">PYTHON/DJANGO</a>
                            <a class="dropdown-item" href="courses.html#sql">SQL/POSTGRESQL</a>
                            <a class="dropdown-item" href="courses.html#c_cpp">C/C++</a>
                            <a class="dropdown-item" href="courses.html#java_c#">JAVA/C#</a>
                        </div>
                        </li>
                        <li class="nav-item">
                            <a class="nav-link" href="contact.html">CONTACT</a>
                        </li>
                        <li class="nav-item">
                            <a class="nav-link" href="cookie.html">COOKIE</a>
                        </li>
                    </ul>
                    </div>
            </div>
        </nav>
        <!--End navbar-->
        <!--Start slider-->
    <div id="carouselExampleCaptions" class="carousel slide" data-ride="carousel">
        <ol class="carousel-indicators">
            <li data-target="#carouselExampleCaptions" data-slide-to="0" class="active"></li>
            <li data-target="#carouselExampleCaptions" data-slide-to="1"></li>
            <li data-target="#carouselExampleCaptions" data-slide-to="2"></li>
        </ol>
        <div class="carousel-inner">
            <div class="carousel-item">
                <img src="img/slider/slider1.png" class="d-block w-100" alt="Img1" style="height: 500px;">
        </div>
        <div class="carousel-item active">
                <img src="IMG/slider/slider2.png" class="d-block w-100" alt="Img2" style="height: 500px;">
        </div>
        <div class="carousel-item">
                <img src="IMG/slider/slider3.png" class="d-block w-100" alt="Img3" style="height: 500px;">
        </div>
        </div>
        <a class="carousel-control-prev" href="#carouselExampleCaptions" role="button" data-slide="prev">
            <span class="carousel-control-prev-icon" aria-hidden="true"></span>
            <span class="sr-only">Previous</span>
        </a>
        <a class="carousel-control-next" href="#carouselExampleCaptions" role="button" data-slide="next">
            <span class="carousel-control-next-icon" aria-hidden="true"></span>
            <span class="sr-only">Next</span>
        </a>
    </div>
    <!--End slider-->
    <!--start pCourses-->
    <div class="pCourses text-center">
        <h2>POPULAR COURSES</h2>
        <div class="container">
            <div class="row">
                <div class="col-lg-3 col-sm-6 features-items">
                    <i class="fab fa-php rounded-circle"></i>
                    <h3>PHP</h3>
                    <p>Server-side scripting language.</p>
                </div>

                <div class="col-lg-3 col-sm-6 features-items">
                    <i class="fab fa-python rounded-circle"></i>
                    <h3>PYTHON</h3>
                    <p>High-level programming language.</p>
                </div>

                <div class="col-lg-3 col-sm-6 features-items">
                    <i class="fab fa-java rounded-circle"></i>
                    <h3>JAVA</h3>
                    <p>Japan Anti-Vivisection Association.</p>
                </div>

                <div class="col-lg-3 col-sm-6 features-items">
                    <i class="fab fa-js rounded-circle"></i>
                    <h3>JAVASCRIPT</h3>
                    <p>Client-side scripting language.</p>
                </div>
            </div>
        </div>
    </div>
    <!--End pCourses-->
    <!--start teachers-->
    <div class="teachers text-center" id="teachers">
        <h2>TEACHERS</h2>
        <div class="container">
            <div class="row">
                <div class="col-lg-3 col-sm-6 teachers-items">
                    <div class="teacher_img">
                        <img src="img/teachers/teacher1.png" alt="teacher">
                    </div>
                    <div class="teacher_name">
                        <h3>MITCHELL BRADBURY</h3>
                    </div>
                </div>

                <div class="col-lg-3 col-sm-6 teachers-items">
                    <div class="teacher_img">
                        <img src="img/teachers/teacher2.png" alt="teacher">
                    </div>
                    <div class="teacher_name">
                        <h3>JOHN ROBERSON</h3>
                    </div>
                </div>

                <div class="col-lg-3 col-sm-6 teachers-items">
                    <div class="teacher_img">
                        <img src="img/teachers/teacher3.png" alt="teacher">
                    </div>
                    <div class="teacher_name">
                        <h3>SARAH CHESNEY</h3>
                    </div>
                </div>

                <div class="col-lg-3 col-sm-6 teachers-items">
                    <div class="teacher_img">
                        <img src="img/teachers/teacher4.png" alt="teacher">
                    </div>
                    <div class="teacher_name">
                        <h3>STEVEN BOSE</h3>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <!--End teachers-->
    <!--start statistic/recognized_by-->
    <div class="statistic recognized_by text-center">
        <div class="container">
            <div class="row">
                <div class="col-lg-3 col-sm-6">
                    <h3>CERTIFICATE</h3>
                    <P>3767</P>
                </div>

                <div class="col-lg-3 col-sm-6">
                    <h3>COURSES</h3>
                    <P>840</P>
                </div>

                <div class="col-lg-3 col-sm-6">
                    <h3>APPLICATION</h3>
                    <P>977</P>
                </div>

                <div class="col-lg-3 col-sm-6">
                    <h3>MEMBERS</h3>
                    <P>7504</P>
                </div>
            </div>
        </div>
        <div class="recognized">
            <div class="container">
                <h2>RECOGNIZED BY</h2>
                <div class="row">
                    <div class="col-sm-4">
                        <img src="img/recognized/google.png" alt="google">
                    </div>
    
                    <div class="col-sm-4">
                        <img src="img/recognized/facebook.png" alt="google">
                    </div>
    
                    <div class="col-sm-4">
                        <img src="img/recognized/productH.png" alt="google">
                    </div>
                </div>
            </div>
        </div>
    </div>
    <!--End statistic/recognized_by-->
    <!--start login-->
    <!-- Modal -->
    <div class="modal fade" id="staticBackdrop" data-backdrop="static" data-keyboard="false" tabindex="-1" aria-labelledby="staticBackdropLabel" aria-hidden="true">
        <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
            <h5 class="modal-title" id="staticBackdropLabel">LOGIN</h5>
            <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                <span aria-hidden="true">&times;</span>
            </button>
            </div>
            <div class="modal-body">
                <form method="post" action="access.php">
                    <div class="form-group">
                        <label for="exampleInputEmail1">Email address</label>
                        <input type="email" name="logemail" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp" required>
                    </div>
                    <div class="form-group">
                        <label for="exampleInputPassword1">Password</label>
                        <input type="password" name="logpasswd" class="form-control" id="exampleInputPassword1" required>
                    </div>
                    <!-- <div class="form-group form-check">
                        <input type="checkbox" class="form-check-input" id="exampleCheck1">
                        <label class="form-check-label" for="exampleCheck1">I'm not a Robot</label>
                    </div> -->
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">CLOSE</button>
                        <button type="submit" name="logbtn" class="btn btn-primary">LOGIN</button>
                    </div>
                </form>
            </div>
        </div>
        </div>
    </div>
    <div class="modal fade" id="staticBackdrop1" data-backdrop="static" data-keyboard="false" tabindex="-1" aria-labelledby="staticBackdropLabel" aria-hidden="true">
        <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
            <h5 class="modal-title" id="staticBackdropLabel">Sign-Up</h5>
            <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                <span aria-hidden="true">&times;</span>
            </button>
            </div>
            <div class="modal-body">
                <form method="post" action="access.php">
                    <div class="form-group">
                        <label for="exampleInputEmail1">Username</label>
                        <input type="text" name="signname" class="form-control" id="exampleInputUsername" aria-describedby="username" required>
                    </div>
                    <div class="form-group">
                        <label for="exampleInputEmail1">Email address</label>
                        <input type="email" name="signemail" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp" required>
                        <small id="emailHelp" class="form-text text-muted">We'll never share your email with anyone else.</small>
                    </div>
                    <div class="form-group">
                        <label for="exampleInputPassword1">Password</label>
                        <input type="password" name="signpasswd" class="form-control" id="exampleInputPassword1" required>
                    </div>
                    <!-- <div class="form-group form-check">
                        <input type="checkbox" class="form-check-input" id="exampleCheck1">
                        <label class="form-check-label" for="exampleCheck1">I'm not a Robot</label>
                    </div> -->
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
                        <button type="submit" name="signbtn" class="btn btn-primary">Sign-Up</button>
                    </div>
                </form>
            </div>
        </div>
        </div>
    </div>
    <!--end login-->
    <!--start footer-->
    <footer>
        <div class="container">
            <div class="row">
                <div class="col-sm-4 Ilink">
                    <ul>
                        <li><a href="courses.html">- Courses</a></li>
                        <li><a href="#">- Certificates</a></li>
                        <li><a href="#">- Blog</a></li>
                        <li><a href="#">- About us</a></li>
                        <li><a href="#">- Community</a></li>
                        <li><a href="#">- Support</a></li>
                    </ul>
                </div>

                <div class="col-sm-4 Ilink">
                    <ul>
                        <li><a href="#">- FAQ’s</a></li>
                        <li><a href="#">- Press Kit</a></li>
                        <li><a href="#">- Privacy</a></li>
                        <li><a href="#">- Terms</a></li>
                        <li><a href="#">- College</a></li>
                        <li><a href="#">- Help</a></li>
                    </ul>
                </div>

                <div class="col-sm-4 Ilink">
                    <h2>Download for Free</h2>
                    <div class="download">
                        <a href="#"><i class="fab fa-google-play"></i></a>
                        <a href="#"><i class="fab fa-app-store"></i></a>
                    </div>
                </div>
            </div>
        </div>
    </footer>
    <div class="footer1 text-center" style="background-color: #000;">
        <div class="container">
            <div class="row">
                <div class="col">
                    <a href="#" style="text-decoration: none;"><p style="color: #fff;padding-top: 15px;">ALL-RIGHT-RESERVED-E-LEARNING-PLATFOME-2022</p></a>
                </div>
            </div>
        </div>
    </div>
    <!--End footer-->
    <script src="https://kit.fontawesome.com/f641f87c42.js" crossorigin="anonymous"></script>
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js" integrity="sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/js/bootstrap.min.js" integrity="sha384-+YQ4JLhjyBLPDQt//I+STsc9iw4uQqACwlvpslubQzn4u2UU2UFM80nGisd026JF" crossorigin="anonymous"></script>
</body>
</html>