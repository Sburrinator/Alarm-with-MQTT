
<?php
    // this page is where you can controll your alarm 
    session_start(); 
    if(!isset($_SESSION['logout'])){
        header("Location: errore.php");
    }
?>
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Controllo Dispositivi IoT</title>
    <link rel="stylesheet" href="styleapp.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css">
</head>
<body>
    <div class="main-container">
        <div class="menu" id="menu">
            <h2>Menu</h2><?php echo $_SESSION['ip']; ?>
            <a href="logout.php" class="logout-button">
                <i class="fas fa-sign-out-alt"></i> Logout
            </a>
        </div>
        <div class="container">
            <button class="menu-toggle" onclick="toggleMenu()">☰ Menu</button>
            <h1>Controllo Dispositivi IoT</h1>
            <div class="device-control" id="soggiorno">
                <div class="device">
                    <h3>Allarme</h3>
                    <form action="process_device.php" method="post">
                        <input type="hidden" name="device" value="Lampada">
                        <button type="submit" name="accendi1" value="on" class="btn-on">Accendi</button>
                        <button type="submit" name="spegni1" value="off" class="btn-off">Spegni</button>
                    </form>
                </div>
        </div>
    </div>
    <script>
        function toggleMenu() {
            document.getElementById('menu').classList.toggle('open');
        }
    </script>
</body>
</html>
