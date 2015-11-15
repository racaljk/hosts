![](https://lh3.googleusercontent.com/OlK0I-7oGT7TTP2dRhU_cyGgaPsFv9LPLA26-saxcjuUlB2H4xzSpaRj5CROZkg84jeeUeP8zBp3sJ2aZM_4MLfWT1-wri6P8ILsGgU5TQ=s660)

**更多内容请访问[hosts wiki](https://github.com/racaljk/hosts/wiki)**

### Windows
* 用文本编辑器(如Notepad++|记事本)打开`C:\Windows\System32\drivers\etc`中的hosts文件，  
把 -> [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) <- 全部内容复制到hosts文件中，保存后按下述方法令其生效。
<br>**注意：如果遇到无法保存，请右键hosts->属性->安全，然后选择你登陆的用户名，最后点击编辑，勾选"写入"即可。**

###Linux&Mac
如果是用linux系统的基友们，请在`/etc`目录下新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)。

如果是苹果电脑（Mac）则新建或修改`/private/etc/`目录下的[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件。

###iOS&Android
Android：需要root权限。新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)文件并保存在`/system/etc`目录下。

iOS：需越狱。访问设备文件系统，新建或修改[hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts)并保存在`/etc`文件夹下。
###注意！Linux、Mac、Android用户请用Notepad++ 转换文本编码和换行符格式，否则hosts可能会无法正常工作。

### GNU/Linux
* Linux 系统终端下命令：  
使用wget或curl，以wget为例：  
开启终端(快捷键为"Ctrl + Alt + T")输入`wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts_tool/script_tool_for_linux.sh -O - | sudo bash -`
<br>按下述方法令其生效

### 修改hosts后生效的方法
* Windows  
开始 -> 运行 -> 输入cmd -> 在CMD窗口输入`ipconfig /flushdns`
  
* Linux  
终端输入`sudo systemctl restart NetworkManager`
<br>非systemd发行版，终端输入`sudo rcnscd restart`
  
* Mac OS X  
终端输入`sudo killall -HUP mDNSResponder`
  
* Android  
开启飞行模式 -> 关闭飞行模式  
  
* 通用方法  
拔网线(断网) -> 插网线(重新连接网络)  
  
### 其它
* 可使用[getHosts.py](https://github.com/racaljk/hosts/blob/master/getHosts.py)进行跨平台hosts相关操作,简单示例如下
```python
import getHosts
h = getHosts.hosts()
h.printContributors() #输出hosts贡献者名单
h.getReadMeFile()     #获取README.MD文件
h.getHostsFile()      #获取hosts文件
h.reportIssue(usrname='github username',password='github password',\
			title='issue title',body='issue content')
              		  #快捷创建Issue
                      #更多功能亟待补充
```
* 衷心感谢每位参与开源hosts的用户[https://github.com/racaljk/hosts/graphs/contributors](https://github.com/racaljk/hosts/graphs/contributors)

Copyright © 2014-2015 racaljk, All Rights Reserved.
