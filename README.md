[![doodle]][doodle-story]

[doodle]: https://www.google.com/logos/doodles/2015/holidays-2015-day-3-6399865393250304-hp2x.jpg "春节快乐!"
[doodle-story]: https://www.google.com.hk/search?q=%E6%98%A5%E8%8A%82

> 使用本项目前，请先阅读 [README](README.md) 和 [License](#license)

|      [聊天室][chat-room]       |    [hosts 格式检测][travis-status]    |  [镜像hosts][mirror_of_hosts]  |  [常见问题解答][faq] |
| :----------------------------: | :-----------------------------------: |  :---------------------------: |  :-----------------: |
|  [![chat-metadata]][chat-room] |  [![travis-metadata]][travis-status]  |  [![coding.net]][coding-link]  |  [![faq-icon]][faq]  |

[chat-metadata]: https://badges.gitter.im/racaljk/hosts.svg "Join the chat"
[chat-room]: https://gitter.im/racaljk/hosts?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge "Gitter chat room"
[travis-metadata]: https://travis-ci.org/racaljk/hosts.svg "Travis CI Metadata"
[travis-status]: https://travis-ci.org/racaljk/hosts "Travis CI Status"
[coding.net]: https://cloud.githubusercontent.com/assets/7419875/21286217/c6642eb2-c488-11e6-94b1-8ad01d31ac9d.png
[coding-link]: https://coding.net/u/scaffrey/p/hosts/git "Coding"
[mirror_of_hosts]: https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts
[faq-icon]: http://www.easyicon.net/api/resizeApi.php?id=1190784&size=48
[faq]: https://github.com/racaljk/hosts/wiki/The-hosts-FAQ

## 更新 hosts
#### 推荐使用项目内提供的 [应用/工具](tools) 来自动获取最新 hosts 文件，以下简单介绍手动替换 hosts 的步骤

### Windows

1. 用文本编辑器（如 [Notepad++](https://notepad-plus-plus.org/)）打开 (如下图)：`%SystemRoot%\System32\drivers\etc\hosts`

  > ![](https://i.imgur.com/BwW2cft.jpg)

2. 将 [hosts][github-hosts] 全部内容复制到上面的文件内并保存。

  > 注：如果遇到无法保存，请右键文件hosts并找到 属性 -> 安全，选择你登录的用户名，<br/>
  > 点击 编辑 ，勾选 写入 即可。

### 其他平台

- 请将 [hosts][github-hosts] 全部内容复制到`/etc/hosts`中并保存。

  > 附：[各平台 hosts 位置](https://github.com/racaljk/hosts/wiki/各平台-hosts-文件位置)

**注意**
  >  - 手动替换 hosts 时，建议清空 hosts 原有的内容，再进行复制操作
  >  - 替换 hosts 文件后，相关记录可能不会立即生效，可以关闭开启网络，或启用禁用飞行模式<br/>
  >    让域名解析立即生效

## 如何贡献

`hosts`等文件是由程序自动生成的，如要改变其内容，请修改`hosts-source`分支下的[`hosts.yml`](https://github.com/racaljk/hosts/blob/hosts-source/hosts.yml)，具体说明见该分支下的[README](https://github.com/racaljk/hosts/tree/hosts-source)。

## 更多

- [关于中国的互联网](https://github.com/racaljk/hosts/wiki/关于中国的互联网)
- 获取更多信息，请访问 [Wiki 页面](https://github.com/racaljk/hosts/wiki) 。如有问题，请开 [Issue](https://github.com/racaljk/hosts/issues) 进行反馈。


## License

- 本项目的所有代码除另有说明外,均按照 [MIT License](LICENSE) 发布。
- 本项目的hosts，README.MD，wiki等资源基于 [CC BY-NC-SA 4.0][CC-NC-SA-4.0] 这意味着你可以拷贝、并再发行本项目的内容，<br/>
  但是你将必须同样**提供原作者信息以及协议声明**。同时你也**不能将本项目用于商业用途**，按照我们狭义的理解<br/>
  (增加附属条款)，凡是**任何盈利的活动皆属于商业用途**。
- 请在遵守当地相关法律法规的前提下使用本项目。

![img-source-from-https://github.com/docker/dockercraft](https://github.com/docker/dockercraft/raw/master/docs/img/contribute.png?raw=true)

[github-hosts]: https://raw.githubusercontent.com/racaljk/hosts/master/hosts "hosts on Github"
[CC-NC-SA-4.0]: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh
