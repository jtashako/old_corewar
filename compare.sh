#! /bin/sh
./corewar -d $1 $2 $3 $4 $5 | sed '/^Fighter.*$/d' > ONE.txt
./debug/42corewar -d $1 $2 $3 $4 $5 | sed '/^Introducing.*$/d' | sed '/^* Player.*$/d' > TWO.txt
diff -wB ONE.txt TWO.txt > /dev/null
if [[ $? == 1 ]]; then
	echo "                                                                                     Ours                                                                                                             vs                                                                                                                          Theirs"
	diff -wBy -W 350 ONE.txt TWO.txt
else
	echo "Memory Dumps Match"
fi
rm ONE.txt TWO.txt
