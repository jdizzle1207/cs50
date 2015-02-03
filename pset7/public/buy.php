<?php

	// configuration
	require("../includes/config.php");
	
	// common variables
	$id = $_SESSION["id"];
	
	if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		if (empty($_POST["ticker"]) || empty($_POST["qty"]))
		{
			apologize("Please specify both ticker and qty to purchase stock.");
		}
		
		else 
		{
			$balance = query("SELECT cash FROM users where id = ?", $id);
			$balance = $balance[0]["cash"];
			
			$lookup = lookup($_POST["ticker"]);
			if ($lookup === false)
			{
				apologize("Sorry, could not lookup stock quote. ABORT.");
			}

			$cost = $lookup["price"] * $_POST["qty"];
			
			if (($lookup["price"] * $_POST["qty"]) > $balance)
			{
				apologize("INSUFFICIENT FUNDS");
			}
			
			else 
			{
				query("START TRANSACTION");
				query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $id);
				query("INSERT shares (id, ticker, shares) values (?, UPPER(?), ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $id, $_POST["ticker"], $_POST["qty"]);
				query("INSERT INTO history (id, buy, ticker, shares, shareprice) VALUES (?, 1, UPPER(?), ?, ?)", $id, $_POST["ticker"], $_POST["qty"], $lookup["price"]);
				if (query("COMMIT") === false)
				{
					if (query("ROLLBACK"))
					{
						apologize("TRANSACTION ERROR, ROLLED BACK");
					}
					
					else
					{
						apologize("CRITICAL: TRANSACTION ERROR *AND* ROLLBACK FAILED!!!");
					}
				}
				
				else 
				{
					redirect("index.php");
				}
			}
		}
	}
	
	else
	{
		render("buy_form.php", ["title" => "Buy Shares"]);
	}

?>