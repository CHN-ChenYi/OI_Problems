while true; do
    ./gen.exeout
    ./correct.exeout
    ./test.exeout
    diff test.out test.ans
    if [ $? -ne 0 ]; then break; fi
done