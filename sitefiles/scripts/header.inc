<?php session_start();
// ini_set('display_errors', 1);
// ini_set('display_startup_errors', 1);
// error_reporting(E_ALL);
    if(isset($_SESSION['isDiscordServerMember']) && $_SESSION['isDiscordServerMember'] == true) {

        require_once($_SERVER["DOCUMENT_ROOT"]."/scripts/db.inc");
    }
?>
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1.0">

        <title><?php echo (isset($page_title) && !empty($page_title)) ? $page_title." | " : ""; ?>Minecraft Server</title>
        
        <link rel="shortcut icon" href="<?php echo (rand(0, 1) == 1) ? "../images/generic-ms-logo.png" : "../images/generic-ms-logo-2.png" ?>" type="image/png">

        <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.7.0/jquery.min.js" integrity="sha512-3gJwYpMe3QewGELv8k/BX9vcqhryRdzRMxVfq6ngyWXwo03GFEzjsUm8Q7RZcHPHksttq7/GFoxjCVUjkjvPdw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
        
        <?php
            if((isset($_SESSION['isAdmin']) && $_SESSION['isAdmin'] == true) 
            || (isset($_SESSION['isDiscordServerMember']) && $_SESSION['isDiscordServerMember'] == true)) {

        ?>
        <link href="https://cdn.datatables.net/v/dt/dt-1.13.5/datatables.min.css" rel="stylesheet"/>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/datatables/1.10.21/js/jquery.dataTables.min.js" integrity="sha512-BkpSL20WETFylMrcirBahHfSnY++H2O1W+UnEEO4yNIl+jI2+zowyoGJpbtk6bx97fBXf++WJHSSK2MV4ghPcg==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>

        <?php
            }
        ?>

        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.1.1/css/all.min.css" integrity="sha512-KfkfwYDsLkIlwQp6LFnl8zNdLGxu9YAA1QvwINks4PhcElQSvqcyVLLD9aMhXd13uQjoXtEKNosOWaZqXgel0g==" crossorigin="anonymous" referrerpolicy="no-referrer" />
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" integrity="sha384-rbsA2VBKQhggwzxH7pPCaAqO46MgnOM80zW1RWuH61DGLwZJEdK2Kadq2F9CUG65" crossorigin="anonymous">
        <link rel="stylesheet" href="../styles.css" >


    </head>
    <body>