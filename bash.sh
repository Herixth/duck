#########################################################################
# File Name: bash.sh
# Author: Herithx
# mail: 17361019875@163.com
# Created Time: 2018年09月09日 星期日 10时52分50秒
#########################################################################
#!/bin/bash

while true; do
	./rand > inputs.in
	./201412_3 < inputs.in > 201412_3.out
	./std < inputs.in > std.out
	#diff 201412_3.out std.out
	if [ $? -ne 0 ]; then break; fi
	if diff 201412_3.out std.out;then
		printf "AC!\n"
	else
		printf "WA!\n"
		exit 0;
	fi
done

