

%1 %2
ver|find "5.">nul&&goto :st
mshta vbscript:createobject("shell.application").shellexecute("%~s0","goto :st","","runas",1)(window.close)&goto :eof
:st

copy "%~0" "%windir%\system32\"
cls
@REM HostsGet Version0.3.1

@echo off
del %temp%\download.vbs > nul
cd /d %~dp0
echo 初始化中...

echo iLocal=LCase("c:\hosts") >> %temp%\download.vbs
echo iRemote=LCase("https://raw.githubusercontent.com/racaljk/hosts/master/hosts") >> %temp%\download.vbs

echo Set xPost=createObject("Microsoft.XMLHTTP") 'Set Post = CreateObject("Msxml2.XMLHTTP") >> %temp%\download.vbs
echo xPost.Open "GET",iRemote,0 >> %temp%\download.vbs
echo xPost.Send() >> %temp%\download.vbs
echo set sGet=createObject("ADODB.Stream") >> %temp%\download.vbs
echo sGet.Mode=3 >> %temp%\download.vbs
echo sGet.Type=1 >> %temp%\download.vbs
echo sGet.Open() >> %temp%\download.vbs
echo sGet.Write xPost.ResponseBody >> %temp%\download.vbs
echo sGet.SaveToFile iLocal,2 >> %temp%\download.vbs

echo 初始化完成...请稍后...
ping 127.0.0.1 > nul
echo 开始从github中下载hosts
%temp%\download.vbs
echo 请稍后...
del %temp%\download.vbs /s /q
ping 127.0.0.1 > nul
echo 正在备份原hosts...
move %windir%\system32\drivers\etc\hosts %windir%\
set filename=%date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%%time:~6,2%
ren %windir%\hosts %filename%.bak


echo hosts文件已经备份到%windir%，名字为%filename% ，路径为：%windir%\%filename%  .

move c:\hosts %windir%\system32\drivers\etc\
echo hosts替换完成.
ipconfig /flushdns
echo 按任意键访问google.com.hk进行测试，如取消，请直接关闭本窗口
pause >nul
start https://www.google.com.hk
echo 已经帮你访问google.com.hk 如可以访问则替换成功.

echo 按任意键关闭
pause >nul
