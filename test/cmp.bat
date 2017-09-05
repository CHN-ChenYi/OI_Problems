:loop
gen.exe
correct.exe
test.exe
fc test.out test.ans
if errorlevel 1 pause
goto loop