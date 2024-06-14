# Generic Minecraft Server Authentication Web Portal

## Intro

This is a generic solution for a basic XAMP stack Authentication Portal for a Minecraft Server. It utilizes the Discord Server roles and authentication to manage access and Minecraft's built in RCON functionality to automatically manage the whitelist and banlist for the server(s). Users do not need to create any accounts in order to interact with the portal and their access is limited by the roles that are setup in the associated Discord Server.

This web application features:
- Independent public portal to allow for convienence: users can submit applications for the server and privileged users can approve or deny those applications
- View Applications, Whitelists, and Banlists with each users' Discord Id and Minecraft Account so there's no confusion over who's who
- Automatically add users to the servers' whitelists and banlists without accessing the server or logging in
- Automatically verifies users are in the associated Discord server and has appropriate roles before application submission and validates that the provided Minecraft Account exists
- Automatically posts when submissions have been approved or denied into a channel in the Discord server

## Setup Overview

The files listed in the `sitefiles` directory are almost ready to go out of the box. There are a few pieces that need the be configured in order for the site to function properly (outside of updating for content):

1. Web Server Setup:
    1. OS: choice of Linux distro (recommended), Windows, etc
    2. Web Server: Apache
    3. Database: MariaDB / MySQL
        * Update `scripts/db.inc` with the database connection information
        * Run `schema.sql` to load the default database table schema
    4. Scripting Language: PHP
2. Discord Server Information (enable developer mode in Discord and update `scripts/globals.priv`):
    1. Roles and their Ids
        * User roles
        * Admin/Mod roles
    2. Discord Server Id
3. [Create Discord Application](https://discord.com/developers/docs/quick-start/getting-started#step-1-creating-an-app)
    1. Update `scripts/client-info.priv` with the required information
    2. Update `scripts/redirecturl.priv` with the appropriate redirect url
    3. Invite the Discord application to the server that is intended to be used and attach a webhook with the app to a channel
    4. Update `scripts/globals.priv` `$onboarding_webhook_url` with the webhook url taken from the channel so the application can post to it
4. Minecraft Server Setup
    1. Enable RCON in `server.properties`
    2. Update `scripts/globals.priv` with the appropriate RCON information
5. Update the HTML pages to fit your server, if necessary
6. Update other items throughout the codebase as necessary

## License

