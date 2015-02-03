<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
			// check for validity
        if (empty($_POST["currentpw"]) || empty($_POST["password"]) || empty($_POST["confirm"]))
        {
			apologize("All 3 fields are REQUIRED!");        
        }
        
        if ($_POST["password"] != $_POST["confirm"])
        {
        	apologize("Passwords do not match!");
        }
        
        $hash = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $hash = $hash[0]["hash"];
        
        if (password_verify($_POST["currentpw"], $hash))
        {
        	if (query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["password"]), $_SESSION["id"]) === false)
	        {
				apologize("FAILED, password NOT changed!");
	        }
	    }

		else 
		{
        	apologize("Current Password is INCORRECT!");
        }
        
        redirect("index.php");
        
	  }
    else
    {
        // else render form
        render("password_form.php", ["title" => "Change Password"]);
    }
    
?>