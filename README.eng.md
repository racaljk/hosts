![undefine](http://www.google.cn/landing/cnexp/google-search.png)

[README.md for Chinese](https://github.com/racaljk/hosts/blob/master/README.md)
## Windows
* Use editor to open the hosts file in the path of `C:\Windows\System32\drivers\etc`.Copy the [hosts file content](https://github.com/racaljk/hosts_for_google_service/blob/master/hosts) to `C:\Windows\System32\drivers\etc`.Finally,save it.
<br>Notification：If you can't save it,you should edit the user permissions and check the 'Write' selection. 

* If operations above are difficult for you ,don't worry!You can download the automatic hosts configuration tool.<br>**Download:[http://pan.baidu.com/s/1bnrPn1l](http://pan.baidu.com/s/1bnrPn1l)**

## GNU/Linux 
* For example,you need to open the terminal on Ubuntu and type `gksudo gedit /etc/hosts`,and you can copy the content in [hosts](https://github.com/racaljk/hosts_for_google_service/blob/master/hosts) to `C:\Windows\System32\drivers\etc`.Finally,save it.

## Others
* Automatic hosts configuration tool was developed by c++,it based on QtGui and it licensed under the GPL license.
* If there are some unavailable ip lists  I haven't updated, you can create an Issue or a Pull Request to remind me.
* If you can not visit google when replaced the hosts file,try to use this software [GoGo Tester](https://raw.githubusercontent.com/azzvx/gogotester/2.3/GoGo%20Tester/bin/Release/GoGo%20Tester.exe) to search an available google ip.

Copyright © 2015 racallinux.cn, All Rights Reserved.
