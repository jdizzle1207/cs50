<h3>Specify share(s) to sell:</h3>
<form action="sell.php" method="post">
	<fieldset>
		<div class="form-group">
		<select autofocus class="form-control" name="ticker">
			<?php
				foreach ($data as $element): ?>
					<option value="<?= $element["ticker"] ?>"><?= $element["ticker"] ?> -- You have <?= $element["shares"] ?> shares of <?= $element["name"] ?> to sell at $<?= $element["price"] ?> per share</option>
			<?php endforeach ?>
		</select>
		<input type="number" name="qty" min="1" max="99999999"/>
		<button type="submit" class="btn btn-default">SELL</button>
		</div>
	</fieldset>
</form>