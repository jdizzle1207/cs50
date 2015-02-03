<?php

	// configuration
	require("../includes/config.php"); 

	$rows = query("SELECT * FROM shares WHERE id = ?", $_SESSION["id"]);
	$balance = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
	$balance = $balance[0]["cash"];	
	
	$cash = '$' . number_format($balance, 2, '.', ',');
	
	$data = [];
	foreach ($rows as $row)
	{
		$stock = lookup($row["ticker"]);
		if ($stock !== false)
		{
			$price = $stock["price"];
			$data[] = [
			    "name" => $stock["name"],
			    "price" => $price,
			    "shares" => $row["shares"],
			    "ticker" => $row["ticker"],
			];
		}
	}
	
	// render portfolio
	render("portfolio.php", ["title" => "Portfolio", "data" => $data, "cash" => $cash]);

?>
