<?php
//=======================================================================================================
// Compose message. You can use Markdown
// Message Formatting -- https://discordapp.com/developers/docs/reference#message-formatting
//========================================================================================================

function generateWebhookContent($content, $embeds) {

    require($_SERVER["DOCUMENT_ROOT"]."/scripts/globals.priv");

    $json_data = json_encode([
        //"content" => "test",
        // Username
        "username" => "$webhook_username",

        "allowed_mentions" => [
            "parse" => []
        ],
    
        // Avatar URL.
        // Uncoment to replace image set in webhook
        //"avatar_url" => "URL",
    
        // Text-to-speech
        "tts" => false,
    
        // File upload
        // "file" => "",
    
        // Embeds Array
        "embeds" => $embeds
    
    ], JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE );

    return $json_data;
}

function sendWebhookRequest($json) {

    require($_SERVER["DOCUMENT_ROOT"]."/scripts/globals.priv");

    $webhookurl = $onboarding_webhook_url;

    $ch = curl_init( $webhookurl );
    curl_setopt( $ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json; charset=utf-8'));
    curl_setopt( $ch, CURLOPT_POST, true);
    curl_setopt( $ch, CURLOPT_POSTFIELDS, $json);
    curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, true);
    curl_setopt( $ch, CURLOPT_HEADER, false);
    curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true);

    $response = curl_exec( $ch );
    // If you need to debug, or find out why you can't send message uncomment line below, and execute script.
    //echo $response;
    curl_close( $ch );
}

    /*

[
            [
                // Embed Title
                "title" => "Minecraft Server Approval",
    
                // Embed Type
                "type" => "rich",
    
                // Embed Description
                "description" => "Description will be here, someday, you can mention users here also by calling userID <@12341234123412341>",
    
                // URL of title link
                "url" => "https://gist.github.com/Mo45/cb0813cb8a6ebcd6524f6a36d4f8862c",
    
                // Timestamp of embed must be formatted as ISO8601
                "timestamp" => date("c", strtotime("now")),
    
                // Embed left border color in HEX
                "color" => hexdec( "3366ff" ),
    
                // Footer
                "footer" => [
                    "text" => "GitHub.com/Mo45",
                    "icon_url" => "https://ru.gravatar.com/userimage/28503754/1168e2bddca84fec2a63addb348c571d.jpg?size=375"
                ],
    
                // Image to send
                "image" => [
                    "url" => "https://ru.gravatar.com/userimage/28503754/1168e2bddca84fec2a63addb348c571d.jpg?size=600"
                ],
    
                // Thumbnail
                //"thumbnail" => [
                //    "url" => "https://ru.gravatar.com/userimage/28503754/1168e2bddca84fec2a63addb348c571d.jpg?size=400"
                //],
    
                // Author
                "author" => [
                    "name" => "krasin.space",
                    "url" => "https://krasin.space/"
                ],
    
                // Additional Fields array
                "fields" => [
                    // Field 1
                    [
                        "name" => "Field #1 Name",
                        "value" => "Field #1 Value",
                        "inline" => false
                    ],
                    // Field 2
                    [
                        "name" => "Field #2 Name",
                        "value" => "Field #2 Value",
                        "inline" => true
                    ]
                    // Etc..
                ]
            ]
        ]

    */

?>