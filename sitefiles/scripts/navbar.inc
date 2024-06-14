<nav class="navbar navbar-expand-lg navbar-light bg-light" role="navigation">
	<div class="container-fluid">
		<button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		</button>
		<div class="collapse navbar-collapse justify-content-center" id="#navbarSupportedContent">
			<span class="navbar-brand"><img src="<?php echo (rand(0, 1) == 1) ? "../images/generic-ms-logo.png" : "../images/generic-ms-logo-2.png" ?>" width="30px" height="30px" class="d-inline-block align-top" id="navbar-logo"> <a href="<some_url>" id="navbar-brand-link">Minecraft Server</a></span>
			<ul class="navbar-nav">

				<li class="nav-item">
					<a class="nav-link" href="/index.html">Home</a>
				</li>

				<?php

					if(!isset($_SESSION["isBanned"]) && isset($_SESSION["user"]))
					{
				?>
				
				<li class="nav-item">
					<a class="nav-link" href="/dashboard.html">My Applications</a>
				</li>

				<?php
					}

					if(!isset($_SESSION["isBanned"]) && isset($_SESSION["user"]) && (isset($_SESSION['isAdmin']) && $_SESSION['isAdmin'] == true))
					{
				?>
				
				<li class="nav-item">
					<a class="nav-link" href="/memberlist.html">Members</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="/applications.html">All Applications</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="/whitelist.html">Whitelist</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="/banlist.html">Ban List</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="/approvals.html">Approvals</a>
				</li>
				<?php
					}
					
					if(isset($_SESSION["user"]))
					{
					
				?>
				<li class="nav-item">
					<a class="nav-link" href="/logout.html">Logout</a>
				</li>
				<?php
					}
					else {
				?>	
					<div class="nav-item h-screen bg-discord-gray">
						<a href="/init-discord-oauth.html" class="nav-link discord-login-link">
						<span class="text-white font-semibold text-xl"><i class="fa-brands fa-discord mr-2"></i> Login with Discord</span>
					</a>
				</div>
				<?php
					}
				?>	
				
			</ul>
		</div>
	</div>
</nav>