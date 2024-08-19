#!/bin/bash

STATUS=0
DIFF_OUTPUT=diff.out
diff stdout.txt ref.txt > $DIFF_OUTPUT
DIFF_STATUS=$(cat $DIFF_OUTPUT)
if [ "$DIFF_STATUS" ]; then
	cat $DIFF_STATUS
	STATUS=1
fi
if [ $STATUS -eq 1 ]; then
	echo KO
else
	echo OK
fi
exit $STATUS
