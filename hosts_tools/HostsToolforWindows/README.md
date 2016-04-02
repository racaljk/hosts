## Hosts Tool

这个工具可以帮助你全自动的更换 备份原来的hosts文件 所有麻烦的事情只需要打开一个程序就能搞定 并且程序还可以作为服务安装随系统启动 每次开机后都每30分钟会自动检测hosts文件的更新噢

### How to use?

main program file: `hosts_tool.exe`

Compile `hosts_tool.cpp` or Download[hosts_tool.exe](https://git.io/vVCFE)

Compile commandline:`g++ -o hosts_tool.exe hosts_tool.cpp -s -O2 -lwininet`

 - 无参数运行`hosts_tool.exe` 用来更新hosts文件 如有更新 程序会备份原有的hosts文件
 - 带参数 `-i` 运行`hosts_tool.exe` 安装一个名为`racaljk-hoststool`的服务
 - 带参数 `-u` 运行`hosts_tool.exe` 卸载已经安装的`racaljk-hoststool`服务

如果安装服务 则会往`%SystemRoot%`下复制一个`hosts_tool.exe`文件用来服务启动(如有安全软件请放行通过)

安装服务后 日志文件会保存在`c:\Hosts_Tool_log.log`下 您可以通过查看日志在观察服务的工作状态

卸载服务请使用原来的`hosts_tool.exe`文件 请不要在命令行中直接执行`hosts_tool -u`

请间隔一段时间后清理`%SystemRoot%\system32\drivers\etc\`文件夹 (因为可能堆满了备份的文件)

Bug Report: 请开新的issue并`@Too-Naive` 或者发邮件给 sweheartiii[at]hotmail.com (请记得带上日志文件)


