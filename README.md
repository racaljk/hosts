![](http://www.google.com/logos/doodles/2015/holidays-2015-day-3-6399865393250304-hp2x.jpg)

**更多内容请访问[hosts wiki](https://github.com/racaljk/hosts/wiki)**

-----------------

> **请注意：下述命令或指导均可能覆盖现有hosts，如现有hosts内容重要的话请备份后再尝试下述方法。**
> **如果不想手动备份的话，请尝试我们的[HostsTool](https://github.com/racaljk/hosts/tree/master/HostsTool)和[一些方便的script](https://github.com/racaljk/hosts/tree/master/scripts)。**

------------------

## Windows
用文本编辑器(如Notepad++|记事本)打开`C:\Windows\System32\drivers\etc`中的hosts文件，
把 -> [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) <- 全部内容复制到hosts文件中，保存后通过
```开始 -> 运行 -> 输入cmd -> 在CMD窗口输入ipconfig /flushdns```使其生效。
<br>**注意：如果遇到无法保存，请右键hosts->属性->安全，然后选择你登陆的用户名，最后点击编辑，勾选"写入"即可。**

## Linux
开启终端(快捷键为"Ctrl + Alt + T")输入`bash -c 'wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts -qO /tmp/hosts && sudo mv /tmp/hosts /etc/hosts'`
<br>最后在终端输入`sudo systemctl restart NetworkManager`
<br>**注意 : 非systemd发行版，终端输入`sudo rcnscd restart`，如果不清楚请两个都试一次，或者参考[#100](https://github.com/racaljk/hosts/issues/100)**

## Mac OS
可以使用[Gas Mask](http://www.macupdate.com/app/mac/29949/gas-mask/)工具修改

或者在`/private/etc/`目录下新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)，然后终端输入`sudo killall -HUP mDNSResponder`使其生效。

## Android
请在`/system/etc`目录下新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)，然后通过`开启飞行模式 -> 关闭飞行模式 `的方式使其生效。

## iOS
请在`/etc`目录下新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)使其生效。

## Annoucement
* Linux、Mac、Android用户请用Notepad++ 转换文本编码和换行符格式，否则hosts可能会无法正常工作。对此你可以参考这个[解决方案](http://www.zhihu.com/question/29064201/answer/63612656)。
* Android和iOS需要root权限和越狱后才能访问hosts文件。
* 由于部分App不支持[SNI](https://en.wikipedia.org/wiki/Server_Name_Indication)，故[不推荐在移动设备上使用](https://github.com/racaljk/hosts/wiki/%E4%B8%BA%E4%BB%80%E4%B9%88%E4%B8%8D%E6%8E%A8%E8%8D%90%E5%9C%A8%E7%A7%BB%E5%8A%A8%E8%AE%BE%E5%A4%87%E4%B8%8A%E4%BD%BF%E7%94%A8hosts%EF%BC%9F)
* 转载和使用过程中请保留hosts文件注释以及任何能体现版权的信息。
* 衷心感谢每位参与开源hosts的用户[Contributors](https://github.com/racaljk/hosts/graphs/contributors)

## License
* Code of this project is licensed under the [MIT License](https://github.com/racaljk/hosts/blob/master/LICENSE)
* Content of this project (including hosts , wiki and Readme) is licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)
![img-source-from-https://github.com/docker/dockercraft](https://github.com/docker/dockercraft/raw/master/docs/img/contribute.png?raw=true)
