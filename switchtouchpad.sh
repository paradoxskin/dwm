  xinput list-props 15|grep 'Device Enabled'|gawk '{
	  if($4=="0"){
		  system("xinput enable 15")
	  }
	  else{
		  system("xinput disable 15")
	  }
  }'
