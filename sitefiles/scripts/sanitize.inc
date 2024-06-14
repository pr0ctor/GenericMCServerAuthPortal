<?php

    function sanitizeInput($text) {
        return htmlspecialchars(strip_tags(filter_var(trim($text), FILTER_SANITIZE_STRING)));
    }
    
?>