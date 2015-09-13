#requirement:python2.7
#more functions will be added in next version

import urllib2

class hosts(object):
    def __init__(self):
        self.reposUrl = 'https://github.com/racaljk/hosts'

    def getRaw(url):
        header ={
                'User-Agent':'Mozilla/5.0 (Windows NT 6.2; rv:16.0) Gecko/20100101 Firefox/16.0'
        }
        request = urllib2.Request(url,headers=header)
        response = urllib2.urlopen(request)
        return response.read()

    def getReadMeFile(self):
        url = 'https://raw.githubusercontent.com/racaljk/hosts/master/README.md'
        content = self.getRaw(url)
        with open('README.MD','wb') as f:
            f.write(content)

    def getHostsFile(self):
        url = 'https://raw.githubusercontent.com/racaljk/hosts/master/hosts'
        content = self.getRaw(url)
        with open('hosts','wb') as f:
            f.write(content)

    def printContributors(self):
        c = [
            {
                'author'     : 'racaljk',
                'githubpage' :'https://github.com/racaljk'
            },
            {
                'author'     : 'andytimes',
                'githubpage' : 'https://github.com/andytimes'
            },
            {
                'author'     : 'smounives',
                'githubpage' : 'https://github.com/smounives'
            },
            {
                'author'     : 'cw881014',
                'githubpage' : 'https://github.com/cw881014'
            },
            {
                'author'     : 'TimothyGu',
                'githubpage' : 'https://github.com/TimothyGu'
            },
            {
                'author'     : 'RellyVadd',
                'githubpage' : 'https://github.com/RellyVadd'
            },
            {
                'author'     : 'LyricTian',
                'githubpage' : 'https://github.com/LyricTian'
            }
        ]
        print ':D thanks for all contributors:'
        for x in xrange(len(c)):
            for (k,v) in c[x].items():
                print k+':'+v



