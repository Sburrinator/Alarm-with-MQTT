<?php
session_start();

// Method that verifies if the session is still on
if(!isset($_SESSION['logout'])){
    header("Location: errore.php");
    exit;
}

// Method that verifies if the form got sent correctly
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // If the alarm is going to be turned on, it will insert in the database true, otherwise it'll insert false. 'Accendi' means turn on and 'Spegni' turned off
    if(isset($_POST['accendi1'])){
        $con = new mysqli("localhost","username","password","dbname");
        if (mysqli_connect_errno()) {
            echo("Connessione non effettuata: ".mysqli_connect_error()."<BR>");                         
            exit();
        }
        $conta=0;
        //Insert query creation. In this case I created the query that inserts the ip and mail of who made the action, time and the status of the alarm (stato_allarme)
        $email=$_SESSION['email'];
        $sql = "INSERT INTO iot(ID_ultimostato, stato_allarme, utente_richiesta, log, ip) VALUES (null, true, '".$email."', '".date('Y-m-d h:i:s', time())."', '".$_SESSION['ip']."')";
        //Execution query that returns $ris
        $ris = $con->query($sql) or die ("Query fallita!");
        //End of db connection
        $con->close();
        header("Location: webapp.php");
    }
    //This if makes the same thing of the one before but it'll insert false when you want to turn off the alarm (it takes datas from the form in webbapp.php)
    if(isset($_POST['spegni1'])){
        $con = new mysqli("localhost","username","password","dbname");
        if (mysqli_connect_errno()) {
            echo("Connessione non effettuata: ".mysqli_connect_error()."<BR>");                         
            exit();
        }
        $conta=0;
        //Insert query creation (false state so it will turn off the alarm)
        $email=$_SESSION['email'];
        $sql = "INSERT INTO iot(stato_allarme, utente_richiesta, log, ip) VALUES (false, '".$email."', '".date('Y-m-d h:i:s', time())."', '".$_SESSION['ip']."')";
        $ris = $con->query($sql) or die ("Query fallita!");
        $con->close();
        header("Location: webapp.php");
    }
}
?>