[![doodle]][doodle-story]

[doodle]: https://www.google.com/logos/doodles/2016/googles-18th-birthday-5661535679545344-hp2x.gif "Google 18岁啦"
[doodle-story]: https://www.google.com.hk/search?q=Google

**使用本项目之前，请先阅读此 [README](README.md) 及下方的许可协议**

**注意: Google 等网站请通过 https 方式访问，如** https://www.google.com/ncr

|      [聊天室][chat-room]       |    [hosts 格式检测][travis-status]    |  [镜像hosts][mirror_of_hosts]  |  [常见问题解答][faq] |
| :----------------------------: | :-----------------------------------: |  :---------------------------: |  :-----------------: |
|  [![chat-metadata]][chat-room] |  [![travis-metadata]][travis-status]  |  [![coding.net]][coding-link]  |  [![faq-icon]][faq]  |

[chat-metadata]: https://github.com/racaljk/hosts/releases/download/img-bak/gitter-metadata.png "Join the chat"
[chat-room]: https://gitter.im/racaljk/hosts?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge "Gitter chat room"
[travis-metadata]: https://travis-ci.org/racaljk/hosts.svg "Travis CI Metadata"
[travis-status]: https://travis-ci.org/racaljk/hosts "Travis CI Status"
[coding.net]: https://github.com/racaljk/hosts/releases/download/img-bak/coding-icon.png
[coding-link]: https://coding.net/u/scaffrey/p/hosts/git "Coding"
[mirror_of_hosts]: https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts
[faq-icon]: http://www.easyicon.net/api/resizeApi.php?id=1190784&size=48
[faq]: https://github.com/racaljk/hosts/wiki/The-hosts-FAQ

## 更新 hosts
#### 推荐使用项目内的 [应用/工具](tools) 来自动备份/更新 hosts 文件

* **Windows**
   1. 用文本编辑器（如 [Notepad++](https://notepad-plus-plus.org/)）打开：`
  %SystemRoot%\System32\drivers\etc\hosts`
  > ![](https://i.imgur.com/BwW2cft.jpg)

   2. 将 [hosts][github-hosts] 全部内容复制到上面的文件内并保存。
   > 注意：如果遇到无法保存，请右键文件hosts并找到“属性” -> “安全”，然后选择你登陆的用户名，最后点击编辑，勾选“写入”即可。

* **其他平台**请将 [hosts][github-hosts] 全部内容复制到`/etc/hosts`中并保存。
> 附：[各平台 hosts 位置](https://github.com/racaljk/hosts/wiki/各平台-hosts-文件位置)

**注意**： 若更新后，hosts 没有立即生效，请重置网络：

- 在系统设置内开关网络，或启用禁用飞行模式

## 更多
- [关于中国的互联网](https://github.com/racaljk/hosts/wiki/关于中国的互联网)
- 获取更多信息，请访问 [Wiki 页面](https://github.com/racaljk/hosts/wiki) 。如有问题，请开 [Issue](https://github.com/racaljk/hosts/issues) 反馈。


## License
- 本项目的所有代码除另有说明外,均按照 [MIT License](LICENSE) 发布。
- 本项目的hosts，README.MD，wiki等资源基于[CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)
这意味着你可以拷贝、并再发行本项目的内容，但是你将必须同样**提供原作者信息以及协议声明**。同时你也**不能将本项目用于商业用途**，
按照我们狭义的理解（增加附属条款），凡是**任何盈利的活动皆属于商业用途**。
- 请在遵守当地相关法律法规的前提下使用本项目。

![img-source-from-https://github.com/docker/dockercraft](https://github.com/docker/dockercraft/raw/master/docs/img/contribute.png?raw=true)

[github-hosts]: https://raw.githubusercontent.com/racaljk/hosts/master/hosts "hosts on Github"
