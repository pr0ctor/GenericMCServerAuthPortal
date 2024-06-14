<?php session_start();

    if(!isset($_SESSION["user"])) {
        header("Location: ../index.html");
        exit();
    }
    
    if(!isset($_SESSION["isAdmin"])) {
        header("Location: ../dashboard.html");
        exit();
    }

    if(isset($_SESSION["isBanned"]) && $_SESSION["isBanned"] == true) {
        header("Location: ../dashboard.html");
        exit();
    }

?>