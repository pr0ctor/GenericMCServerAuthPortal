<?php

    function username_to_uuid($username) {
        $profile = username_to_profile($username);
        if (is_array($profile) and isset($profile['id'])) {
            return $profile['id'];
        }
        return false;
    }

    function username_to_profile($username) {
        if (is_valid_username($username)) {
            $json = @file_get_contents('https://api.mojang.com/users/profiles/minecraft/' . $username);

            if($json === false) {
                return false;
            }

            if (!empty($json)) {
                $data = json_decode($json, true);
                if (is_array($data) and !empty($data)) {
                    return $data;
                }
            }
        }
        return false;
    }

    function is_valid_username($string) {
        return is_string($string) and strlen($string) >= 2 and strlen($string) <= 16 and ctype_alnum(str_replace('_', '', $string));
    }

    function normalizeUuid($uuid) {
        return preg_replace('#([a-z0-9]{8})([a-z0-9]{4})([a-z0-9]{4})([a-z0-9]{4})([a-z0-9]{12})#', '$1-$2-$3-$4-$5', $uuid);
    }

?>