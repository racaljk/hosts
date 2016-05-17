![doodles](https://www.google.com/logos/doodles/2016/teachers-day-2016-us-6296626244091904.2-hp2x.gif)

[English version](https://github.com/racaljk/hosts/wiki/README(en))

**使用本项目之前，请先阅读此 README 及下方的许可协议**

**目前通过修改 hosts 无法观看 YouTube 视频 详情: [Issue #297](https://github.com/racaljk/hosts/issues/297)**

**使用镜像地址获取** [**hosts**](https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts)

**进入聊天室:** [![Join the chat at https://gitter.im/racaljk/hosts](https://badges.gitter.im/racaljk/hosts.svg)](https://gitter.im/racaljk/hosts?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## 更新 hosts
* 下面介绍的操作均可能覆盖现有 hosts ，进行操作前请先确认是否需要备份。
* 推荐使用本项目的 [**Host Tools**](https://github.com/racaljk/hosts/tree/master/tools) 来自动化 备份/配置 工作。

* 若更新 hosts 未立即生效，请重置网络：
  - 在系统设置内开关网络
  - 启用禁用飞行模式
  - 重启系统

### Windows
用文本编辑器（如 [Notepad++](https://notepad-plus-plus.org/)）打开文件：

    C:\Windows\System32\drivers\etc\hosts

将 [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) 全部内容复制到上述文件内并保存

> 注意：如果遇到无法保存，请右键文件hosts并找到“属性” -> “安全”，然后选择你登陆的用户名，最后点击编辑，勾选“写入”即可。

### Linux
将 [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) 全部内容复制到`/etc/hosts`中并保存。

或开启终端（快捷键为<kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>T</kbd>）输入命令：

    wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts -qO /tmp/hosts && sudo sh -c 'cat /tmp/hosts > /etc/hosts'

### Mac OS
将 [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) 全部内容复制到 `/etc/hosts`中并保存。

### Android
将 [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) 全部内容复制到 `/etc/hosts`中并保存。

### iOS
将 [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) 全部内容复制到 `/etc/hosts`中并保存。


## 更多
**获取更多信息，请访问 [Wiki 页面](https://github.com/racaljk/hosts/wiki) 。如有问题，请开 [Issue](https://github.com/racaljk/hosts/issues) 反馈。**

## License
- 本项目的所有代码除另有说明外,均按照 [MIT License](https://github.com/racaljk/hosts/blob/master/LICENSE) 发布。
- 本项目的hosts，README.MD，wiki等资源基于[CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)
这意味着你可以拷贝、并再发行本项目的内容，但是你将必须同样**提供原作者信息以及协议声明**。同时你也**不能将本项目用于商业用途**，
按照我们狭义的理解（增加附属条款），凡是**任何盈利的活动皆属于商业用途**。
- 请在遵守当地相关法律法规的前提下使用本项目。

![img-source-from-https://github.com/docker/dockercraft](https://github.com/docker/dockercraft/raw/master/docs/img/contribute.png?raw=true)
