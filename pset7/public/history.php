<?php

	// configuration
	require("../includes/config.php");
	
	$rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
	if ($rows === false)
	{
		apologize("Could not access transaction record.");
	}
	
	render("display_history.php", ["title" => "Transaction Record", "rows" => $rows]);

?>