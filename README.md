![](https://www.google.com/logos/doodles/2016/41st-anniversary-of-the-discovery-of-the-mountain-of-the-butterflies-5704071614824448.2-hp2x.jpg)

**更多内容请访问[hosts wiki](https://github.com/racaljk/hosts/wiki)**

-----------------

> **请注意：下述命令或指导均可能覆盖现有hosts，如现有hosts内容重要的话请备份后再尝试下述方法。**
> **如果不想手动备份的话，请尝试[HostsTool](https://github.com/ppoffice/Hozz)和[一些方便的scripts](https://github.com/racaljk/hosts/tree/master/scripts)。**

------------------

## Windows
用文本编辑器（如记事本等）打开文件：

    C:\Windows\System32\drivers\etc\hosts
    
并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。

然后请重置网络以便让更改生效。

> 注意：如果遇到无法保存，请右键文件hosts并找到“属性” -> “安全”，然后选择你登陆的用户名，最后点击编辑，勾选“写入”即可。

## Mac OS
请 新建/修改 `/private/etc/hosts` 文件，并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。

然后请重置网络以便让更改生效。

> 也可以使用[Gas Mask](http://www.macupdate.com/app/mac/29949/gas-mask/)工具。


## Android
请 新建/修改 `/system/etc/hosts` 文件，并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。

然后请重置网络以便让更改生效。

## iOS
请 新建/修改 `/etc/hosts` 文件，并将我们的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件中的内容全部内容复制到该文件中并保存。

然后请重置网络以便让更改生效。

## Linux
开启终端（快捷键为<kbd>Ctrl + Alt + T</kbd>）并在终端内输入下述命令：

    bash -c 'wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts -qO /tmp/hosts && sudo mv /tmp/hosts /etc/hosts'
    
并重置网络以便让更改生效。

## Annoucement
* 重置网络方法：断网/开启飞行模式（如果有的话） 并重新连接。
* Linux、Mac、Android用户请用Notepad++ 转换文本编码和换行符格式，否则hosts可能会无法正常工作。对此你可以参考这个[解决方案](http://www.zhihu.com/question/29064201/answer/63612656)。
* Android和iOS需要root权限和越狱后才能访问hosts文件。
* 由于部分App不支持[SNI](https://en.wikipedia.org/wiki/Server_Name_Indication)，故[不推荐在移动设备上使用](https://github.com/racaljk/hosts/wiki/%E4%B8%BA%E4%BB%80%E4%B9%88%E4%B8%8D%E6%8E%A8%E8%8D%90%E5%9C%A8%E7%A7%BB%E5%8A%A8%E8%AE%BE%E5%A4%87%E4%B8%8A%E4%BD%BF%E7%94%A8hosts%EF%BC%9F)
* 转载和使用过程中请保留hosts文件注释以及任何能体现版权的信息。
* 衷心感谢每位参与开源hosts的用户[Contributors](https://github.com/racaljk/hosts/graphs/contributors)

## License
* Code of this project is licensed under the [MIT License](https://github.com/racaljk/hosts/blob/master/LICENSE)
* Content of this project (including hosts , wiki and Readme) is licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)
![img-source-from-https://github.com/docker/dockercraft](https://github.com/docker/dockercraft/raw/master/docs/img/contribute.png?raw=true)
