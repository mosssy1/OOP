@echo off
set PROGRAM="%~1"

rem ������� �������
%PROGRAM% matrix01.txt > %TEMP%\invert01.txt
if ERRORLEVEL 1 goto err
fc invert01.txt %TEMP%\invert01.txt
if ERRORLEVEL 1 goto err

rem ������� � �������� ������� 
%PROGRAM% matrix02.txt > %TEMP%\invert02.txt
if ERRORLEVEL 1 goto err
fc invert02.txt %TEMP%\invert02.txt
if ERRORLEVEL 1 goto err

rem ������������ = 0
%PROGRAM% matrix03.txt > %TEMP%\invert03.txt
fc invert03.txt %TEMP%\invert03.txt
if ERRORLEVEL 1 goto err

rem � ������������ ����������
%PROGRAM% matrix04.txt > %TEMP%\invert04.txt
fc invert04.txt %TEMP%\invert04.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1