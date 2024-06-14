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

    if($_POST["operation"] == "approve-application") {

        if(!empty($_POST["recordid"]) && !empty($_POST["ApprovalType"])) {

            include($_SERVER["DOCUMENT_ROOT"]."/scripts/sanitize.inc");

            // Sanitize user data

            $parsedApplicationId = intval(sanitizeInput($_POST["recordid"]));
            $parsedApprovalType = sanitizeInput($_POST["ApprovalType"]);

            if($parsedApplicationId <= 0) {
                header("Location: ../applications.html");
                exit();
            }

            $approvalType = array("Approved", "Denied");

            if(!in_array($parsedApprovalType, $approvalType)) {
                header("Location: ../applications.html");
                exit();
            }

            // Update current application

            $updateApplication = $db->prepare("update applications set application_type = ? where id = ?");
            $updateApplication->bind_param("si", $parsedApprovalType, $parsedApplicationId);
            $updateApplication->execute();
            $updateApplication->close();

            if($parsedApprovalType == "Denied") {
                header("Location: ../applications.html");
                exit();
            }

            // Get person who approved

            $getApprover = $db->prepare("
                select id
                from members
                where discord_id = ?
                limit 1
            ");
            $getApprover->bind_param("s", $_SESSION["user"]["userData"]["id"]);
            $getApprover->execute();
            $approverResult = $getApprover->get_result();

            $approver = $approverResult->fetch_assoc();

            // Create Approval

            $createApproval = $db->prepare("insert into approvals(application_id, approver) values( ? , ? )");
            $createApproval->bind_param("ii", $parsedApplicationId, $approver["id"]);
            $createApproval->execute();
            $createApproval->close();

            $getApprover->close();

            // Get applicant information

            $getApplicant = $db->prepare("
                select m.id as memid, m.discord_id as memdid, mca.id as mcaid, mca.name as mcname, a.server_type
                from applications a
                inner join members m on a.member = m.id
                inner join mcaccounts mca on m.mcaccount = mca.id
                where a.id = ? 
                limit 1
            ");
            $getApplicant->bind_param("i", $parsedApplicationId);
            $getApplicant->execute();

            $applicant = $getApplicant->get_result();

            $a = $applicant->fetch_assoc();

            $servers = array();

            if($a["server_type"] == "Both") {
                $servers = $minecraft_server_types;
            }
            else {
                $servers[] = $a["server_type"];
            }

            $memid = $a["memid"];
            $mcaid = $a["mcaid"];
            $mcaname = $a["mcname"];
            $applicant_discord_id = $a["memdid"];

            // Create whitelist records and whitelist on the various servers

            foreach($servers as $s) {
                $whitelistQuery = $db->prepare("insert into whitelist(member, server_type, mcaccount) values( ? , ? , ? )");
                $whitelistQuery->bind_param("isi", $memid, $s, $mcaid);
                $whitelistQuery->execute();
                $whitelistQuery->close();

                $rcon_port = ($s == "Vanilla") ? $vanilla_server_rcon_port : $modded_server_rcon_port;
                $r = new RCon($rcon_server_ip, $rcon_port, $rcon_port_password); //create rcon object for server on the rcon port with a specific password

                if($r->Auth()) //Connect and attempt to authenticate
                {
                    $r->rconCommand("whitelist add ".$a["mcname"]); //send a command
                }

                $embeds = [
                    [
                        // Embed Title
                        "title" => "Minecraft Server Approval",
            
                        // Embed Type
                        "type" => "rich",
            
                        // Embed Description
                        "description" => "<@".$_SESSION['user']['userData']['id']."> approved <@".$applicant_discord_id."> (`".$mcaname."`) for the ".$s." server.",
            
                        // Timestamp of embed must be formatted as ISO8601
                        "timestamp" => date("c", strtotime("now")),
            
                        // Embed left border color in HEX
                        "color" => hexdec( "00ff00" ),
            
                        // Image to send
                        "thumbnail" => [
                            "url" => ($s == "Vanilla") ? "<url_to>/images/generic-ms-logo.png" : "<url_to>/images/generic-ms-logo-2.png"
                        ]
                    ]
                ];

                $content = generateWebhookContent("", $embeds);
                    
                sendWebhookRequest($content);
            }

            $getApplicant->close();

        }
    }

    header("Location: ../applications.html");
    exit();

?>