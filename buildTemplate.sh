#!/bin/bash
if [ $# -ge 1 ]; then
if [ -e $1 ];then
	TEXT=`cat "$1"`
	OUT_TEXT="$TEXT"
	OUTS=`echo "$TEXT" | grep -oE "\{.*:[0-9]+\}"`
	for pattern in $OUTS;do
		match=${pattern/\{/}
		match=${match/\}/}
		arr=(${match/:/ })
		index="${arr[0]}"
		iter="${arr[1]}"
		((iter=iter+1))
		OUT_TEXT="${OUT_TEXT/$pattern/$iter}"
		TEXT="${TEXT/$pattern/\{$index:$iter\}}"
		echo "$el"
	done
	echo "$TEXT" > "$1"
	OUT_FILE="$1"
	echo "$OUT_TEXT" > "${OUT_FILE/.template/}"
fi
fi
