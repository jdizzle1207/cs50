<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // search database for places matching $_GET["geo"] and add asterisks before/after for bool complete
    $rows = query("SELECT * FROM places WHERE MATCH(place_name,postal_code,admin_name1,admin_code1) AGAINST(? IN BOOLEAN MODE) ORDER BY place_name;",'*'.$_GET["geo"].'*');

    foreach ($rows as $value)
    {
        array_push($places, $value);
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
