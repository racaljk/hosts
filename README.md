![](https://lh3.googleusercontent.com/OlK0I-7oGT7TTP2dRhU_cyGgaPsFv9LPLA26-saxcjuUlB2H4xzSpaRj5CROZkg84jeeUeP8zBp3sJ2aZM_4MLfWT1-wri6P8ILsGgU5TQ=s660)

**更多内容请访问[hosts wiki](https://github.com/racaljk/hosts/wiki)**

## Windows
用文本编辑器(如Notepad++|记事本)打开`C:\Windows\System32\drivers\etc`中的hosts文件，  
把 -> [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) <- 全部内容复制到hosts文件中，保存后通过
```开始 -> 运行 -> 输入cmd -> 在CMD窗口输入ipconfig /flushdns```使其生效。
<br>**注意：如果遇到无法保存，请右键hosts->属性->安全，然后选择你登陆的用户名，最后点击编辑，勾选"写入"即可。**

## Linux
Linux 系统终端下命令：  
使用wget或curl，以wget为例：  
开启终端(快捷键为"Ctrl + Alt + T")输入`bash -c 'wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts -qO /tmp/hosts && sudo mv /tmp/hosts /etc/hosts'`
<br>最后在终端输入`sudo systemctl restart NetworkManager`
<br>**注意 : 非systemd发行版，终端输入`sudo rcnscd restart`，如果不清楚请两个都试一次。**

## Mac OS
请在`/private/etc/`目录下新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)，然后终端输入`sudo killall -HUP mDNSResponder`使其生效。

## Android
请在`/system/etc`目录下新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)，然后通过`开启飞行模式 -> 关闭飞行模式 `的方式使其生效。

## iOS 
请在`/etc`目录下新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)使其生效。

## 注意事项！
* Linux、Mac、Android用户请用Notepad++ 转换文本编码和换行符格式，否则hosts可能会无法正常工作。对此你可以参考这个[解决方案](http://www.zhihu.com/question/29064201/answer/63612656)。
* Android和iOS需要root权限和越狱后才能访问hosts文件。
* 由于部分App不支持[SNI](https://en.wikipedia.org/wiki/Server_Name_Indication)，故不推荐在移动设备上使用
 
##  其它
* 转载和使用过程中请保留hosts文件注释以及任何能体现版权的信息。
* 可使用[getHosts.py](https://github.com/racaljk/hosts/blob/master/getHosts.py)进行跨平台hosts相关操作
* 可使用`scripts/`中的脚本进行配置
* 衷心感谢每位参与开源hosts的用户[https://github.com/racaljk/hosts/graphs/contributors](https://github.com/racaljk/hosts/graphs/contributors)

## License
* Code of this project is licensed under the MIT license.
* Content of this project (including hosts , wiki and Readme) is licensed under [CC4.0 BY-NC-SA ](https://creativecommons.org/licenses/by-nc-sa/4.0/)
