<h3>Transaction Record:</h3>
<table>
	<thead>
		<tr>
			<th class="center">Buy/Sell</th>
			<th class="left">Ticker</th>
			<th class="center"># Shares</th>
			<th class="right">Price</th>
			<th class="right">Date/Time</th>
		</tr>
	</thead>
	<tbody>
		<?php $i=0; foreach ($rows as $row): ?>
			<tr <?php if ($i % 2 == 0) echo 'class="shade"'?>>
				<td class="
					<?php
						if ($row["buy"] == 1)
						{
							echo 'buy">Buy';
						}
						else 
						{
							echo 'sell">Sell';
						}
					?>
				</td>
				<td class="left"><?= $row["ticker"] ?></td>
				<td><?= $row["shares"] ?></td>
				<td class="right">$<?= $row["shareprice"] ?></td>
				<td class="right"><?= $row["timestamp"] ?></td>
			</tr>
		<?php $i++; endforeach; ?>
	</tbody>
</table>