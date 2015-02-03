<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
			// check for validity
        if (empty($_POST["username"]) || empty($_POST["password"]))
        {
			apologize("Username and Password are REQUIRED!");        
        }
        
        if ($_POST["password"] != $_POST["confirmation"])
        {
        	apologize("Passwords do not match!");
        }
        
        // insert user if previous checks passed, if returns false, tell user name taken
        if (query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"])) === false)
        {
			apologize("Username already taken :(");
        }
        
        // remember new userid in session cookie so user won't have to login after registration
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        
        $_SESSION = ["id" => $id];
        
        redirect("index.php");
        
	  }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
?>