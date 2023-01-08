#!/bin/bash
id=`xinput|grep TouchPad|awk '{x=$6;split(x,arr,"=");print arr[2];}'`
flag=`xinput list-props $id|grep 'Device Enabled'|awk '{
	echo $id
	if($4=="0"){
		print 0;
	}
	else{
		print 1;
	}
}'`
if [ $flag == 0 ]
then
	xinput enable $id
else
	xinput disable $id
fi

#xinput list-props $id|grep 'Device Enabled'|awk '{
#	  echo $id
#	  if($4=="0"){
#		  cmd="xinput enable "$id;
#	  }
#	  else{
#		  cmd="xinput disable "$id;
#	  }
#	  system(cmd);
#}'
#awk内语法不会
