![undefine](http://www.google.cn/landing/cnexp/google-search.png)

[README.md for English](https://github.com/racaljk/hosts/blob/master/README.eng.md)
## Windows
* 用记事本打开`C:\Windows\System32\drivers\etc`中的hosts文件，把[hosts](https://github.com/racaljk/hosts_for_google_service/blob/master/hosts)中的代码复制到hosts文件中覆盖里面的内容，保存即可。
<br>注意：如果遇到无法保存，请右键hosts->属性->安全，然后选择你登陆的用户名，最后点击编辑，勾选"写入"即可。

* 如果觉得上述方法过于繁琐,可以使用hosts_tool文件夹里的edit hosts.bat批处理一键编辑hosts文件，或者使用Hosts自动配置工具一键完成<br>**下载地址:[http://pan.baidu.com/s/1bnrPn1l](http://pan.baidu.com/s/1bnrPn1l)**

## GNU/Linux 
* 以Ubuntu为例,终端输入`gksudo gedit /etc/hosts`,然后把[hosts](https://github.com/racaljk/hosts_for_google_service/blob/master/hosts) 中的代码复制到hosts文件中覆盖里面的内容，保存即可。

## Others
* hosts自动配置工具使用C++构建,GUI基于Qt,源码遵守GPL协议发布
* 如果项目中某些分类IP失效但未更新,请及时通过Issue反馈或者Pull Request你的有效IP List到本项目
* 谷歌IP不一定有用,如果上述hosts还是无法登陆谷歌请使用[GoGo Tester](https://raw.githubusercontent.com/azzvx/gogotester/2.3/GoGo%20Tester/bin/Release/GoGo%20Tester.exe)寻找IP作为最后解决方案

Copyright © 2015 racallinux.cn, All Rights Reserved.
