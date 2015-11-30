![](https://www.google.com.hk/logos/doodles/2015/evidence-of-water-found-on-mars-5652760466817024.2-hp.gif)
<br>**已证实火星上存在液态水啦！！**

**更多内容请访问[hosts wiki](https://github.com/racaljk/hosts/wiki)**

### Windows
* 用文本编辑器(如Notepad++|记事本)，右键以管理员身份打开，按`crtl+字母O`打开 `C:\Windows\System32\drivers\etc`中的hosts文件(文件类型选择`所有文件`，否则可能看不到hosts)，  
把 -> [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) <- 全部内容复制到hosts文件中，保存后按下述方法令其生效。

### OS X
* 打开Finder，按`Shift+Command+G` ，输入 `/etc/hosts` , 将hosts文件拖到桌面，
把 -> [hosts](https://raw.githubusercontent.com/racaljk/hosts/master/hosts) <- 
全部内容复制到hosts文件中，保存。
将hosts文件拖回 `/etc/hosts` 中，会提示相同文件，选择`替换`，输入你Mac的密码即可。

### GNU/Linux
* Linux 系统终端下命令：  
使用wget或curl，以wget为例：  
开启终端(快捷键为"Ctrl + Alt + T")输入`wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts_tool/script_tool_for_linux.sh -O - | sudo bash -`
<br>按下述方法令其生效

### 修改hosts后生效的方法
* Windows  
开始 -> 运行 -> 输入cmd -> 在CMD窗口输入`ipconfig /flushdns`

* Mac OS X  
终端输入`sudo killall -HUP mDNSResponder`

* Linux  
终端输入`sudo rcnscd restart`
<br>(对于systemd发行版，请使用命令`sudo systemctl restart NetworkManager`。如果不懂请都尝试下)
  
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
