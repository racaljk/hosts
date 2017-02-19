## Hosts Tools

这个工具可以帮助你全自动的更换 备份原来的hosts文件 所有麻烦的事情只需要打开一个程序就能搞定 并且程序还可以作为服务随系统启动 每次开机都可以自动检测hosts文件的更新噢

### How to use?

主程序`hosts_tool.exe`

 - 无参数运行 用来更新hosts文件 以及备份原有的hosts文件
 - 参数 -i 安装一个名为`racaljk-hoststool`的服务
 - 参数 -u 卸载安装的服务

如果安装服务 则会往`%SystemRoot%`下复制一个`hosts_tool.exe`文件用来服务启动

安装服务后 日志文件会保存在`c:\Hosts_Tool_log.log`下 您可以通过查看日志在观察服务的工作状态

Bug Report: 请开新的issue 或者发邮件给sweheartiii[at]hotmail.com

## 开放源代码许可

本项目源代码遵循[GNU General Public License v3.0协议](http://www.gnu.org/licenses/gpl.html)

有关协议的详细内容 请参阅上一行的[链接](http://www.gnu.org/licenses/gpl.html)


