<!DOCTYPE html>
<html lang="pl">
	
	<head>
		<title>ADM Key Generator</title>
	</head>
	
	<body>
		<script type="text/javascript">
			function getRandomInt(min, max) {
				return Math.floor(Math.random() * (max - min + 1)) + min;
			}

			function CreateKey(value){
				switch(value){
				
					//HexNegative
					case 1: {
						var a0, b0;
						
						a0 = getRandomInt(1,15);
						b0 = 16-a0;
						document.write("HexNegative</br></br>");
						document.write("Encrypt Key:</br>",a0,"</br></br>");
						document.write("Decrypt Key:</br>",b0,"</br>");
						break;
					}
					
					//RollX
					case 2: {
						var a0, b0;
						
						a0 = getRandomInt(1,255);
						b0 = 256-a0;
						document.write("RollX</br></br>");
						document.write("Encrypt Key:</br>",a0,"</br></br>");
						document.write("Decrypt Key:</br>",b0,"</br>");
						break;
					}
					
					//ADM (ADMx32)
					case 3: {
					
						var a = {}, b = {}, c;
						c = 4;
						
						for(i = 0; i < c; i++){
							a[i] = getRandomInt(1,255);
							b[i] = 256-a[i];
						}
						document.write("ADM (ADMx32)</br></br>");
						document.write("Encrypt Key:</br>");
						for(i = 0; i < c; i++){
							document.write(a[i]," ");
						}
						document.write("</br></br>");
						
						document.write("Decrypt Key:</br>");
						for(i = 0; i < c; i++){
							document.write(b[i]," ");
						}
						document.write("</br>");
						
						break;
					}
					
					//ADMx64
					case 4: {
						var a = {}, b = {}, c;
						c = 8;
						
						for(i = 0; i < c; i++){
							a[i] = getRandomInt(1,255);
							b[i] = 256-a[i];
						}
						document.write("ADMx64</br></br>");
						document.write("Encrypt Key:</br>");
						for(i = 0; i < c; i++){
							document.write(a[i]," ");
						}
						document.write("</br></br>");
						
						document.write("Decrypt Key:</br>");
						for(i = 0; i < c; i++){
							document.write(b[i]," ");
						}
						document.write("</br>");
						break;
					}
					
					//ADMx128
					case 5: {
						var a = {}, b = {}, c;
						c = 16;
						
						for(i = 0; i < c; i++){
							a[i] = getRandomInt(1,255);
							b[i] = 256-a[i];
						}
						document.write("ADMx128</br></br>");
						document.write("Encrypt Key:</br>");
						for(i = 0; i < c; i++){
							document.write(a[i]," ");
						}
						document.write("</br></br>");
						
						document.write("Decrypt Key:</br>");
						for(i = 0; i < c; i++){
							document.write(b[i]," ");
						}
						document.write("</br>");
						break;
					}
					
					//ADMx256
					case 6: {
						var a = {}, b = {}, c;
						c = 32;
						
						for(i = 0; i < c; i++){
							a[i] = getRandomInt(1,255);
							b[i] = 256-a[i];
						}
						document.write("ADMx256</br></br>");
						document.write("Encrypt Key:</br>");
						for(i = 0; i < c; i++){
							document.write(a[i]," ");
						}
						document.write("</br></br>");
						
						document.write("Decrypt Key:</br>");
						for(i = 0; i < c; i++){
							document.write(b[i]," ");
						}
						document.write("</br>");
						break;
					}
				}
			}
		</script>
	</body>
</html>

<?php

$APPType = $_GET['APPType'];

if($APPType >= 1 && $APPType <= 6){
	echo '
	<script>
		CreateKey('.$APPType.');
	</script>
	<br/><br/>
	<a href = "" style="text-decoration: none">Generate new key</a>
	<br/><br/>
	<a href = "index.php" style="text-decoration: none">Select a different algorithm</a>
	';
} else {

	echo '
		<form enctype="multipart/form-data" action="index.php" method="GET">
			<div>
				<p>Select algorithm</p>
				<input type="radio" name="APPType" value="1" />HexNegative<br />
				<input type="radio" name="APPType" value="2" />RollX<br />
				<input type="radio" name="APPType" value="3" />ADM (ADMx32)<br />
				<input type="radio" name="APPType" value="4" />ADMx64<br />
				<input type="radio" name="APPType" value="5" />ADMx128<br />
				<input type="radio" name="APPType" value="6" />ADMx256<br />
				<br />
				<input type="submit" value="Generate keys" />
			</div>
		</form>
	';
}
?>