# Download Executable File

#### Download address:
- [hosts_tool.exe](https://git.io/vVSwE)
- [Mirror address](https://yunpan.cn/cq4amgJfUZwTM)(code:b9b1)

OS type | Minimun Supported Version
--------|-------------------
WorkStation | Microsoft Windows XP Family
Server | Microsoft Windows Server 2003 Family

>If you choose `Download`, It means you agreed the MIT license(redefined).

# Hosts Tool

这个工具可以帮助你全自动的更换 备份原来的hosts文件 所有麻烦的事情只需要打开一个程序就能搞定 如果你愿意，程序还可以作为服务安装随系统启动 每次开机后每隔30分钟会自动检测hosts文件的更新噢

**在此特别感谢[@qwerty258](https://github.com/qwerty258)为本程序提供了Visual Studio的工程文件**

## How to use?

main program file: `hosts_tool.exe`

 - 无参数运行`hosts_tool.exe` 用来更新hosts文件 如有更新 程序会备份原有的hosts文件
 - 带参数 `-fi` 运行`hosts_tool.exe` 安装一个名为`racaljk-hoststool`的服务
 - 带参数 `-fu` 运行`hosts_tool.exe` 卸载已经安装的`racaljk-hoststool`服务

 (如有安全软件请放行通过)

## 注意事项

1.如果安装服务 程序会往`%SystemRoot%`下复制一个`hosts_tool.exe`文件用来作为服务启动的主程序

2.安装服务后 日志文件会保存在`C:\Hosts_Tool_log.log`下 您可以通过查看日志观察服务的工作状态

3.卸载服务请使用原来的`hosts_tool.exe`文件 请不要在命令行中直接执行`hosts_tool -fu`(如执行 需要手动删除`%SystemRoot%`目录下的`hoststools.exe`)

4.请间隔一段时间后清理`%SystemRoot%\system32\drivers\etc\`文件夹 (因为可能堆满了备份的文件)

5.Bug Report: 请开新的issue并`@Too-Naive`或者发邮件给 sweheartiii[at]hotmail.com (请记得带上日志文件)

## for Developer

### Code license:

>The MIT License(MIT)(redefined)

>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, and to permit persons to  whom the Software is furnished to do so, BUT DO NOT SUBLICENSE, AND / OR SELL OF THE SOFTWARE,subject to the following conditions :

>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

>If you use the project's source code or its derivative products (including but not limited to the executable file), it means that you have agreed to the terms of this license and comply with the terms of the license. If you do not agree to this license agreement, please do not use this project's source code and its derivatives (including but not limited to the executable file).

### Service Debug Mode :

If you want to enter debug mode, follow the steps blow.

1. Open the console.
2. Change the working directory where is the `hosts_tools.exe` position.
3. Input `hosts_tools.exe --debug-pipe` and press enter.
4. Now you can see the current working status of service.
5. Press **Ctrl+C** to Exit debug mode.
6. Exit debug mode will cause service uninstall.

**WARNING: IN DEBUG MODE, DO NOT CLOSE THE CONSOLE DIRECT**

	_Notice:In debug mode, service run cycle is very sort_

### How to Compile?

**Save `hosts_tool.exe.manifest` to directory first**

Compile commandline:

```
windres hosts_tool.rc -o hosts_toolr.o
g++ -o hosts_tool.exe hosts_tool.cpp hosts_toolr.o -lwininet -O2 -s
```

File `hosts_tool.exe.manifest`:

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    <assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
    <trustInfo xmlns="urn:schemas-microsoft-com:asm.v3">
        <security>
            <requestedPrivileges>
                <requestedExecutionLevel level="requireAdministrator" uiAccess="false"/>
            </requestedPrivileges>
        </security>
    </trustInfo>
</assembly>
```

Sorry for my poor English.
