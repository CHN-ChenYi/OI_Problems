:loop
gen
correct
test
fc test.out test.ans
if errorlevel 1 pause
goto loop