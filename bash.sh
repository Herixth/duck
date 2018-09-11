#########################################################################
# File Name: bash.sh
# Author: Herixth
# mail: 17361019875@163.com
# Created Time: 2018年09月11日 星期二 14时49分10秒
#########################################################################
#!/bin/bash

g++ crontab.cpp -o crontab
g++ std.cpp -o std
g++ rand.cpp -o rand

./rand > input.in
time ./crontab < input.in > crontab.out
time ./std < input.in > std.out
diff crontab.out std.out
if [ $? -ne 0 ]; then break; fi
	if diff crontab.out std.out;then
		printf "AC!\n"
    else
        printf "WA!\n"
        exit 0;
    fi

