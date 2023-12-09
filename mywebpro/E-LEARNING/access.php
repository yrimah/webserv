<?php

    class accounts
    {
        private $email;
        private $name;
        private $passwd;

        function getname()
        {
            return ($this->name);
        }
        function getemail()
        {
            return ($this->email);
        }
        function getpasswd()
        {
            return ($this->passwd);
        }
        function setname($name)
        {
            $this->name = $name;
        }
        function setemail($email)
        {
            $this->email = $email;
        }
        function setpasswd($passwd)
        {
            $this->passwd = $passwd;
        }
    };

    // $log = false;
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if (isset($_POST["signbtn"]))
        // {
        //     $acnts0 = new accounts();
        //     $acnts0->setname($_POST["name"]);
        //     $acnts0->setemail($_POST["email"]);
        //     $acnts0->setpasswd($_POST["passwd"]);
        // }

        $acnts1 = new accounts();
        $acnts1->setname("yrimah");
        $acnts1->setemail("yrimah@1337.ma");
        $acnts1->setpasswd("yrimahPasswd");

        $acnts2 = new accounts();
        $acnts2->setname("test");
        $acnts2->setemail("test@admin.ma");
        $acnts2->setpasswd("test");

        // if (!isset($_POST["signbtn"]))
        $arrayAccounts = array($acnts1, $acnts2);
        // else
        //     $arrayAccounts = array($acnts0, $acnts1, $acnts2);

        if (isset($_POST["logbtn"]))
        {
            // $log = true;
            for ($i = 0; $i < 2; $i++)
            {
                // print_r($arrayAccounts);
                if ($_POST["logemail"] == $arrayAccounts[$i]->getemail())
                {
                    if ($_POST["logpasswd"] == $arrayAccounts[$i]->getpasswd())
                    {
                        session_start();
                        $_SESSION["name"] = $arrayAccounts[$i]->getemail();
                        unset($_POST["logbtn"]);
                        header("location: account.php");
                    }
                }
            }
            unset($_POST["logbtn"]);
        }
        else if (isset($_POST["signbtn"]))
        {
            // print_r($arrayAccounts);
            
            session_start();
            $_SESSION["name"] = $_POST["signname"];
            // unset($_POST["signbtn"]);
            header("location: account.php");
        }
        header("location: index.php");
    }
    else
        header("location: index.php");
?>