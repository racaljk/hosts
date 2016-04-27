 **目前通过修改hosts无法实现观看YouTube视频 详情:[#297](https://github.com/racaljk/hosts/issues/297)**
 
![](https://www.google.com.sg/logos/doodles/2016/lantern-festival-2016-4824959689949184.2-hp.jpg)

**使用镜像地址获取** [hosts](https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts) 

# 欢迎使用hosts！[![Join the chat at https://gitter.im/racaljk/hosts](https://badges.gitter.im/racaljk/hosts.svg)](https://gitter.im/racaljk/hosts?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

1. 下述使用指导均可能覆盖现有 hosts ，如现有 hosts 内容重要的话请事先备份。您也可以使用我们的 [**Host Tools**](https://github.com/racaljk/hosts/tree/master/tools) 来自动化 备份/配置 的工作。
2. 根据下述使用指导配置完成后，您将需要“重置网络”：

- 重启系统
- 拔插网线
- 启用禁用飞行模式
- 在系统设置内开关网络

如果不先重置网络， hosts 不一定会立即生效。

> **如有其他问题，请访问 [我们的 Wiki 页面](https://github.com/racaljk/hosts/wiki) 。**    
>**使用本项目之前，请先阅读下方的用户协议**

## Windows
用文本编辑器（如记事本等）打开文件：

    C:\Windows\System32\drivers\etc\hosts

并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。

> 注意：如果遇到无法保存，请右键文件hosts并找到“属性” -> “安全”，然后选择你登陆的用户名，最后点击编辑，勾选“写入”即可。

## Mac OS
请 新建/修改 `/private/etc/hosts` 文件，并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。


> 也可以使用[Gas Mask](http://www.macupdate.com/app/mac/29949/gas-mask/)工具。


## Android
请 新建/修改 `/system/etc/hosts` 文件，并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。


## iOS
请 新建/修改 `/etc/hosts` 文件，并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。


## Linux
请 新建/修改 `/etc/hosts` 文件，并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。

或是开启终端（快捷键为<kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>T</kbd>）并直接使用下述命令：

    bash -c 'wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts -qO /tmp/hosts && sudo mv /tmp/hosts /etc/hosts'
    

## License
- 本项目的所有代码除另有说明外,均按照 [MIT License](https://github.com/racaljk/hosts/blob/master/LICENSE) 发布。
- 本项目的hosts，README.MD，wiki等资源基于[CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)
这意味着你可以拷贝、并再发行本项目的内容，但是你将必须同样**提供原作者信息以及协议声明**。同时你也**不能将本项目用于商业用途**，按照我们狭义的理解（增加附属条款），凡是**任何盈利的活动皆属于商业用途**。
- 如果您使用了本项目，则您在使用本项目的产品(包括但不限于其衍生产品)过程中产生的法律问题和安全问题，**与本项目无关**。同样，本项目也不承担任何连带法律责任。
- 项目中有规定其他协议的，也适用于本用户协议的最后一条协议。
- **使用/下载本项目中的产品(包括但不限于其衍生产品)则意味着您已经阅读了本协议并愿意遵守本协议规定的有关事项；若你无法遵守上述的责任和义务，请不要拷贝、并再发行本项目；如果您违反本协议使用/下载项目中的产品(包括但不限于其衍生产品)，我们将最大限度地追究您的违约责任。**

![img-source-from-https://github.com/docker/dockercraft](https://github.com/docker/dockercraft/raw/master/docs/img/contribute.png?raw=true)
