<h3>Your Current Balance:</h3>
<h4><?= $cash ?></h4>
<table>
	<thead>	
		<tr>
			<th class="left">Ticker</th>
			<th></th>
			<th class="right">Shares</th>
			<th class="right">Price ($)</th>
		</tr>
	</thead>
	<tbody>
		<?php $i = 0; foreach ($data as $position): ?>
		    <tr <?php if ($i % 2 == 0) echo 'class="shade"'?>>
		        <td class="left"><?= $position["ticker"] ?></td>
		        <td class="left"><?= $position["name"] ?></td>
		        <td class="right"><?= $position["shares"] ?></td>
		        <td class="right"><?php printf("%0.2f", $position["price"]); $i++; ?></td>
		    </tr>
		<?php endforeach ?>
	</tbody>
</table>