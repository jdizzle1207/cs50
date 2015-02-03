<!DOCTYPE html>

<html>

    <head>

        <link href="css/bootstrap.min.css" rel="stylesheet"/>
        <link href="css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="js/jquery-1.10.2.min.js"></script>
        <script src="js/bootstrap.min.js"></script>
        <script src="js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="top">
                <a href="index.php"><img alt="C$50 Finance" src="img/logo.gif"/></a>
				<div id="navigation">
                	<a href="quote.php">Quote</a>
                	<a href="buy.php">Buy</a>
                	<a href="sell.php">Sell</a>
                	<a href="history.php">History</a>

                </div>
            </div>

            <div id="middle">
