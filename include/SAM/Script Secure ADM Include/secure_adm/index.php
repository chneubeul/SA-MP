<?php
	$ANTI_FLOOD = 	'123';
	$ACK_TRUE =  	'{BOBO_HAHA,ACCESSCONTROL,TRUE}';
	$ACK_FALSE = 	'Fuck you thief :P';

	if(isset($_GET['code'])){
		if($_GET['code'] == $ANTI_FLOOD){
			if(isset($_GET['port'])){
				if(isset($_GET['bind'])){
					$fdata = $_GET['bind'].":".$_GET['port'];
					$file = fopen("Server.txt","r");
					$ch = 0;
					while(!feof($file)){
						$line = fgets($file,64);
						$line = trim($line," \t\n\r\0\x0B");
						if($fdata == $line){
							$ch = 1;
							break;
						}
					}
					fclose($file);
					
					if($ch == 1){
						echo $ACK_TRUE;
					} else {
						echo $ACK_FALSE;
					}
				}
			}
		}
	}
?>
