@echo off
REM ________________________________________________________________
>nul 2>&1 "%SystemRoot%\System32\cacls.exe" "%SystemRoot%\System32\config\system"
if '%errorlevel%' NEQ '0' (
goto UACPrompt
) else ( goto gotAdmin )
:UACPrompt
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
echo UAC.ShellExecute "%~s0", "", "", "runas", 1 >> "%temp%\getadmin.vbs"
"%temp%\getadmin.vbs"
exit /B
:gotAdmin
if exist "%temp%\getadmin.vbs" ( del "%temp%\getadmin.vbs" )
pushd "%CD%"
CD /D "%~dp0"
REM ________________________________________________________________
::start %SystemRoot%\notepad.exe "%SystemRoot%\System32\drivers\etc\hosts"
echo -----------------------------------------------------------
echo https://github.com/racaljk/hosts
echo -----------------------------------------------------------
echo Backup hosts ...
copy "%SystemRoot%\System32\drivers\etc\hosts" "%SystemRoot%\System32\drivers\etc\hosts-%date%-%time::=-%"
echo -----------------------------------------------------------
:: flush DNS before copy or after copy???
:: I think it's same.
ipconfig /flushdns
echo -----------------------------------------------------------
echo Begin to copy hosts ...
copy "%~dp0..\..\hosts" "%SystemRoot%\System32\drivers\etc\hosts"
:: pause for user to see what's going on
:: in case of someone see a black window flash away
:: and report it to Github issues.
pause
