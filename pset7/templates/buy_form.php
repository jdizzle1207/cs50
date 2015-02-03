<h3>Please specify share(s) to purchase:</h3>
<fieldset>
	<form action="buy.php" method="POST">
	Ticker:
	<input autofocus type="text" maxlength="8" name="ticker"/>
	Shares:
	<input type="number" min="1" max="99999999" name="qty"/>
	<button type="submit" class="btn btn-default">BUY</button>
	</form>
</fieldset>
<h5>NOTE: In the interest of prompt trading, trade will occur in realtime without confirmation.</h5>
