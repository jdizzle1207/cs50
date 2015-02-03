<?php

// configuration (require login, etc.)
require("../includes/config.php");

// check if user submitted ticker symbol
if ($_SERVER["REQUEST_METHOD"] == "POST")
{

	if(empty($_POST["ticker"]))
	{
		apologize("Ticker symbol REQUIRED!");
	}
	
	else 
	{
		$stock = lookup($_POST["ticker"]); 

		if ($stock === false)
		{
			apologize("ERROR, please check ticker and try again.");
		}
		
		else 
		{
			$ticker = $_POST["ticker"];
			render("display_quote.php", ["Title" => ("Stock Quote for " + $ticker), "name" => $stock["name"], "symbol" => $stock["symbol"], "price" => $stock["price"]]);
		}
	}

}

else 
{
	render("get_ticker.php", ["title" => "Get Quote"]);
}
?>