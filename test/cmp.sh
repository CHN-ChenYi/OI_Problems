declare -i cnt=0
for ((;;)) do
    ./gen.exeout
    ./correct.exeout
    ./test.exeout
    diff test.out test.ans -wbZB
    if [ $? -ne 0 ];
    then break; fi
    echo $((++cnt))
done