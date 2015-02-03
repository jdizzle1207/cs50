<?php

// configuration (require login, etc.)
require("../includes/config.php");

// set some common vars
$id = &$_SESSION["id"];
$ticker = &$_POST["ticker"];
$qty = &$_POST["qty"];

// check if user submitted ticker symbol
if ($_SERVER["REQUEST_METHOD"] == "POST")
{
	if (empty($ticker) || empty($qty))
	{
		apologize("To sell, specify both ticker and qty.");
	}
	
	else 
	{
		$stocksheld = query("SELECT * FROM shares WHERE id = ?", $id);
		
		if ($stocksheld === false)
		{
			apologize("No Stock to Sell");
		}
		
		else 
		{
			$boh = query("SELECT shares FROM shares WHERE id = ? and ticker = UPPER(?)", $id, $ticker);
			if ($qty > $boh[0]["shares"] || $boh === false)
			{
				apologize("You don't have that many shares to sell!!!");
			}
			
			else 
			{
				$lookup = lookup($ticker);
				if ($lookup === false)
				{
					apologize("Could not perform stock lookup!");
				}
				$price = $lookup["price"];
				$saleprice = $price * $qty; 
				
				query("START TRANSACTION");
				query("UPDATE shares SET shares = shares - ? where id = ? AND ticker = UPPER(?)", $qty, $id, $ticker);
				query("UPDATE users SET cash = cash + ? WHERE id = ?", $saleprice, $id);
				query("INSERT into history (id, ticker, shares, shareprice) VALUES (?, UPPER(?), ?, ?)", $id, $ticker, $qty, $price);
				if ($qty == $boh[0]["shares"])
				{
					query("DELETE from shares WHERE id = ? AND ticker = UPPER(?)", $id, $ticker);
				}
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
}

else 
{
	$data = array();
	$stocksheld = query("SELECT * FROM shares WHERE id = ?", $id);
	
	foreach ($stocksheld as $stock)
	{
		$stockticker = $stock["ticker"];
		$shares = $stock["shares"];
		$lookup = lookup($stockticker);
		$price = $lookup["price"];
		$name = $lookup["name"];
		$data[$stockticker] = [
			"ticker" => $stockticker,
			"shares" => $shares,
			"price" => $price,
			"name" => $name
		];
		
		
		
	}

	if ($stocksheld === false)
	{
		apologize("No Stock to Sell");
	}
	
	render("sell_form.php", ["title" => "Sell Shares", "data" => $data]);
}

?>