<?php
    //gets the IP address of who uses the alarm
    function getClientIP() {
        $ipaddress = '';
        if (isset($_SERVER['HTTP_CLIENT_IP']))
            $ipaddress = $_SERVER['HTTP_CLIENT_IP'];
        else if(isset($_SERVER['HTTP_X_FORWARDED_FOR']))
            $ipaddress = $_SERVER['HTTP_X_FORWARDED_FOR'];
        else if(isset($_SERVER['HTTP_X_FORWARDED']))
            $ipaddress = $_SERVER['HTTP_X_FORWARDED'];
        else if(isset($_SERVER['HTTP_FORWARDED_FOR']))
            $ipaddress = $_SERVER['HTTP_FORWARDED_FOR'];
        else if(isset($_SERVER['HTTP_FORWARDED']))
            $ipaddress = $_SERVER['HTTP_FORWARDED'];
        else if(isset($_SERVER['REMOTE_ADDR']))
            $ipaddress = $_SERVER['REMOTE_ADDR'];
        else
            $ipaddress = 'UNKNOWN';
        return $ipaddress;
    }

    session_start();


    $array=array(
        "mail1@domain.it"=>"password",
        "mail2@domain.it"=>"password"
    );

    if(isset($_POST['email']) && isset($_POST['password'])){
        $mail=$_POST['email'];
        $psw=$_POST['password'];
        $ip = getClientIP();
        //checks if the credentials are correct
        if(array_key_exists($mail, $array) && $array[$mail]===$psw) {
            $_SESSION['email']=$mail;
            $_SESSION['ip']=$ip;
            $_SESSION['logout']=1;
            header("Location: webapp.php");
            exit();
        }else{
            echo "Uknown user<br>";
            echo "<a href='index.html'>Turn back</a>";
        }
    }
    

    
?> 