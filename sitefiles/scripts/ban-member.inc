<?php   session_start();
    require_once($_SERVER["DOCUMENT_ROOT"]."/scripts/authenticate.inc");
    require_once($_SERVER["DOCUMENT_ROOT"]."/scripts/rcon.class.inc");
    require_once($_SERVER["DOCUMENT_ROOT"]."/scripts/db.inc");
    require_once($_SERVER["DOCUMENT_ROOT"]."/scripts/globals.priv");
    include($_SERVER["DOCUMENT_ROOT"]."/scripts/webhook-helper.inc");

    if(!isset($_POST['operation'])) {
        header("Location: ../dashboard.html");
        exit();
    }

    if(empty($_POST['operation'])) {
        header("Location: ../dashboard.html");
        exit();
    }

    if($_POST["operation"] == "ban-member") {

        if(!empty($_POST["recordid"])) {

            include($_SERVER["DOCUMENT_ROOT"]."/scripts/sanitize.inc");

            $parsedMemberId = intval(sanitizeInput($_POST["recordid"]));
            $parsedReason = sanitizeInput($_POST["reason"]);

            if($parsedMemberId <= 0) {
                header("Location: ../dashboard.html");
                exit();
            }

            // Member to ban

            $getMemberInfo = $db->prepare("
                select m.id as memid, m.discord_id as did, mca.id as mcaid, mca.name as mcname
                from members m
                inner join mcaccounts mca on m.mcaccount = mca.id
                where m.id = ? 
                limit 1
            ");
            $getMemberInfo->bind_param("i", $parsedMemberId);
            $getMemberInfo->execute();

            $member = $getMemberInfo->get_result();

            $m = $member->fetch_assoc();

            // Create the ban in 'Bans'

            $addBans = $db->prepare("insert into bans(member, mcaccount, reason) values( ? , ? , ? )");
            $addBans->bind_param("iis", $m["memid"], $m["mcaid"], $parsedReason);
            $addBans->execute();
            $addBans->close();

            // Remove any Whitelist records

            $deleteWhitelists = $db->prepare("delete from whitelist where member = ? ");
            $deleteWhitelists->bind_param("i", $m["memid"]);
            $deleteWhitelists->execute();
            $deleteWhitelists->close();

            // Ban on servers
            $servers = $minecraft_server_types;

            foreach($servers as $s) {

                $rcon_port = ($s == "Vanilla") ? $vanilla_server_rcon_port : $modded_server_rcon_port;
                $r = new RCon($rcon_server_ip, $rcon_port, $rcon_port_password); //create rcon object for server on the rcon port with a specific password

                if($r->Auth()) //Connect and attempt to authenticate
                {
                    $r->rconCommand("whitelist remove ".$m["name"]); //send a command
                    $r->rconCommand("ban ".$m["name"]); //send a command
                }

                $embeds = [
                    [
                        // Embed Title
                        "title" => "Minecraft Server Ban",
            
                        // Embed Type
                        "type" => "rich",
            
                        // Embed Description
                        "description" => "<@".$_SESSION["user"]["userData"]["id"]."> banned <@".$m["did"]."> (`".$m["mcname"]."`) from the ".$s." server. Reason: ".$parsedReason,
            
                        // Timestamp of embed must be formatted as ISO8601
                        "timestamp" => date("c", strtotime("now")),
            
                        // Embed left border color in HEX
                        "color" => hexdec( "ff0000" ),
            
                        // Image to send
                        "thumbnail" => [
                            "url" => ($s == "Vanilla") ? "<url_to>/images/generic-ms-logo.png" : "<url_to>/images/generic-ms-logo-2.png"
                        ]
                    ]
                ];

                $content = generateWebhookContent("", $embeds);
                    
                sendWebhookRequest($content);
            }

            $getMemberInfo->close();

        }
    }

    header("Location: ../applications.html");
    exit();
?>