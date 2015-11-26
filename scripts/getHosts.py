"""Simple Guidance for getHosts script
This is a simple guidance,it tell you how to use this script even
I know it's useless..
For running this script,you need install python environment(v2.7).
Now you can use this python script to configure your hosts file 
and do something magically.All of the first you need to import 
this script as a PythonModule by IMPORT statement.
For example,if you want to get hosts file via script from remote
server,you ,you might create a new .py file,type following code:

import getHosts
h = getHosts.hosts() #initial an hosts object
h.getHostsFile()     #output hosts file to your local system

I promise there will be more useful functions in the feature.
"""

class hosts(object):

    HEADER = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.2; rv:16.0) Gecko/20100101 Firefox/16.0'
    }

    def __init__(self, header=None):
        self.header = header or self.HEADER
        self.reposUrl = 'https://github.com/racaljk/hosts'

    def getRaw(self, url):

        request = urllib2.Request(url, headers=self.header)
        response = urllib2.urlopen(request)
        return response.read()

    def getReadMeFile(self):
        url = 'https://raw.githubusercontent.com/racaljk/hosts/master/README.md'
        content = self.getRaw(url)
        with open('README.MD', 'wb') as f:
            f.write(content)

    def getHostsFile(self):
        url = 'https://raw.githubusercontent.com/racaljk/hosts/master/hosts'
        content = self.getRaw(url)
        with open('hosts', 'wb') as f:
            f.write(content)

    def printContributors(self):
        l = ['racaljk', 'andytimes', 'smounives',
             'K-Guan','cw881014','fluviusmagnus',
             'whiteclover','LyricTian','RellyVadd',
             'mklnz','chaosshen','TimothyGu']

        c = [{'author': i,
              'githubpage': 'https://github.com/' + i} for i in l]

        print ':D thanks for all contributors(sort by commits):'
        for x in c:
            for (k, v) in x.items():
                print k + ':' + v

    #you need to provide your github.username&github.password in following next functions
    def reportIssue(self,username,password,title,body):
        if username=='' or password=='' or title==''or body=='':
            raise ValueError('incorrect parameters,try again.')
        gh = github.GitHub(username,password)
        gh.repos('racaljk')('hosts').issues.post(title=title, body=body,label='QuickIssue')
        print 'You have succeed to report a Issue to hosts project via getHost script.'

__version__ = '1.1.1'

try:
    # Python 2
    from urllib2 import build_opener, HTTPSHandler, Request, HTTPError
    from urllib import quote as urlquote
    from StringIO import StringIO
    def bytes(string, encoding=None):
        return str(string)
except:
    # Python 3
    from urllib.request import build_opener, HTTPSHandler, HTTPError, Request
    from urllib.parse import quote as urlquote
    from io import StringIO

import re, os, time, hmac, base64, hashlib, urllib, mimetypes, json
from collections import Iterable
from datetime import datetime, timedelta, tzinfo

TIMEOUT=60

_URL = 'https://api.github.com'
_METHOD_MAP = dict(
        GET=lambda: 'GET',
        PUT=lambda: 'PUT',
        POST=lambda: 'POST',
        PATCH=lambda: 'PATCH',
        DELETE=lambda: 'DELETE')

DEFAULT_SCOPE = None
RW_SCOPE = 'user,public_repo,repo,repo:status,gist'

def _encode_params(kw):
    '''
    Encode parameters.
    '''
    args = []
    for k, v in kw.items():
        try:
            # Python 2
            qv = v.encode('utf-8') if isinstance(v, unicode) else str(v)
        except:
            qv = v
        args.append('%s=%s' % (k, urlquote(qv)))
    return '&'.join(args)

def _encode_json(obj):
    '''
    Encode object as json str.
    '''
    def _dump_obj(obj):
        if isinstance(obj, dict):
            return obj
        d = dict()
        for k in dir(obj):
            if not k.startswith('_'):
                d[k] = getattr(obj, k)
        return d
    return json.dumps(obj, default=_dump_obj)

def _parse_json(jsonstr):
    def _obj_hook(pairs):
        o = JsonObject()
        for k, v in pairs.items():
            o[str(k)] = v
        return o
    return json.loads(jsonstr, object_hook=_obj_hook)

class _Executable(object):

    def __init__(self, _gh, _method, _path):
        self._gh = _gh
        self._method = _method
        self._path = _path

    def __call__(self, **kw):
        return self._gh._http(self._method, self._path, **kw)

    def __str__(self):
        return '_Executable (%s %s)' % (self._method, self._path)

    __repr__ = __str__

class _Callable(object):

    def __init__(self, _gh, _name):
        self._gh = _gh
        self._name = _name

    def __call__(self, *args):
        if len(args)==0:
            return self
        name = '%s/%s' % (self._name, '/'.join([str(arg) for arg in args]))
        return _Callable(self._gh, name)

    def __getattr__(self, attr):
        if attr=='get':
            return _Executable(self._gh, 'GET', self._name)
        if attr=='put':
            return _Executable(self._gh, 'PUT', self._name)
        if attr=='post':
            return _Executable(self._gh, 'POST', self._name)
        if attr=='patch':
            return _Executable(self._gh, 'PATCH', self._name)
        if attr=='delete':
            return _Executable(self._gh, 'DELETE', self._name)
        name = '%s/%s' % (self._name, attr)
        return _Callable(self._gh, name)

    def __str__(self):
        return '_Callable (%s)' % self._name

    __repr__ = __str__

class GitHub(object):

    '''
    GitHub client.
    '''

    def __init__(self, username=None, password=None, access_token=None, client_id=None, client_secret=None, redirect_uri=None, scope=None):
        self.x_ratelimit_remaining = (-1)
        self.x_ratelimit_limit = (-1)
        self.x_ratelimit_reset = (-1)
        self._authorization = None
        if username and password:
            # roundabout hack for Python 3
            userandpass = base64.b64encode(bytes('%s:%s' % (username, password), 'utf-8'))
            userandpass = userandpass.decode('ascii')
            self._authorization = 'Basic %s' % userandpass
        elif access_token:
            self._authorization = 'token %s' % access_token
        self._client_id = client_id
        self._client_secret = client_secret
        self._redirect_uri = redirect_uri
        self._scope = scope

    def authorize_url(self, state=None):
        '''
        Generate authorize_url.

        >>> GitHub(client_id='3ebf94c5776d565bcf75').authorize_url()
        'https://github.com/login/oauth/authorize?client_id=3ebf94c5776d565bcf75'
        '''
        if not self._client_id:
            raise ApiAuthError('No client id.')
        kw = dict(client_id=self._client_id)
        if self._redirect_uri:
            kw['redirect_uri'] = self._redirect_uri
        if self._scope:
            kw['scope'] = self._scope
        if state:
            kw['state'] = state
        return 'https://github.com/login/oauth/authorize?%s' % _encode_params(kw)

    def get_access_token(self, code, state=None):
        '''
        In callback url: http://host/callback?code=123&state=xyz

        use code and state to get an access token.        
        '''
        kw = dict(client_id=self._client_id, client_secret=self._client_secret, code=code)
        if self._redirect_uri:
            kw['redirect_uri'] = self._redirect_uri
        if state:
            kw['state'] = state
        opener = build_opener(HTTPSHandler)
        request = Request('https://github.com/login/oauth/access_token', data=_encode_params(kw))
        request.get_method = _METHOD_MAP['POST']
        request.add_header('Accept', 'application/json')
        try:
            response = opener.open(request, timeout=TIMEOUT)
            r = _parse_json(response.read())
            if 'error' in r:
                raise ApiAuthError(str(r.error))
            return str(r.access_token)
        except HTTPError as e:
            raise ApiAuthError('HTTPError when get access token')

    def __getattr__(self, attr):
        return _Callable(self, '/%s' % attr)

    def _http(self, _method, _path, **kw):
        data = None
        params = None
        if _method=='GET' and kw:
            _path = '%s?%s' % (_path, _encode_params(kw))
        if _method in ['POST', 'PATCH', 'PUT']:
            data = bytes(_encode_json(kw), 'utf-8')
        url = '%s%s' % (_URL, _path)
        opener = build_opener(HTTPSHandler)
        request = Request(url, data=data)
        request.get_method = _METHOD_MAP[_method]
        if self._authorization:
            request.add_header('Authorization', self._authorization)
        if _method in ['POST', 'PATCH', 'PUT']:
            request.add_header('Content-Type', 'application/x-www-form-urlencoded')
        try:
            response = opener.open(request, timeout=TIMEOUT)
            is_json = self._process_resp(response.headers)
            if is_json:
                return _parse_json(response.read().decode('utf-8'))
        except HTTPError as e:
            is_json = self._process_resp(e.headers)
            if is_json:
                json = _parse_json(e.read().decode('utf-8'))
            else:
                json = e.read().decode('utf-8')
            req = JsonObject(method=_method, url=url)
            resp = JsonObject(code=e.code, json=json)
            if resp.code==404:
                raise ApiNotFoundError(url, req, resp)
            raise ApiError(url, req, resp)

    def _process_resp(self, headers):
        is_json = False
        if headers:
            for k in headers:
                h = k.lower()
                if h=='x-ratelimit-remaining':
                    self.x_ratelimit_remaining = int(headers[k])
                elif h=='x-ratelimit-limit':
                    self.x_ratelimit_limit = int(headers[k])
                elif h=='x-ratelimit-reset':
                    self.x_ratelimit_reset = int(headers[k])
                elif h=='content-type':
                    is_json = headers[k].startswith('application/json')
        return is_json

class JsonObject(dict):
    '''
    general json object that can bind any fields but also act as a dict.
    '''
    def __getattr__(self, key):
        try:
            return self[key]
        except KeyError:
            raise AttributeError(r"'Dict' object has no attribute '%s'" % key)

    def __setattr__(self, attr, value):
        self[attr] = value

class ApiError(Exception):

    def __init__(self, url, request, response):
        super(ApiError, self).__init__(url)
        self.request = request
        self.response = response

class ApiAuthError(ApiError):

    def __init__(self, msg):
        super(ApiAuthError, self).__init__(msg, None, None)

class ApiNotFoundError(ApiError):
    pass

if __name__ == '__main__':
    import doctest
    doctest.testmod()
