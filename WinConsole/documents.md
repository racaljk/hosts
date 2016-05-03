# Code license:

>The MIT License(MIT)(redefined)

>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, and to permit persons to  whom the Software is furnished to do so, BUT DO NOT SUBLICENSE, AND / OR SELL OF THE SOFTWARE,subject to the following conditions :

>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

>If you use the project's source code or its derivative products (including but not limited to the executable file), it means that you have agreed to the terms of this license and comply with the terms of the license. If you do not agree to this license agreement, please do not use this project's source code and its derivatives (including but not limited to the executable file).

# How to Compile?

**Save `tool.exe.manifest` to directory first**

## for Mingw g++

Compile commandline:

```
windres tool.rc -o toolr.o
g++ -o tool.exe tool.cpp toolr.o -lwininet -O2 -s
```

File `tool.exe.manifest`:

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    <assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
    <trustInfo xmlns="urn:schemas-microsoft-com:asm.v3">
        <security>
            <requestedPrivileges>
                <requestedExecutionLevel level="requireAdministrator" uiAccess="false"/>
            </requestedPrivileges>
        </security>
    </trustInfo>
</assembly>
```

## Files description

File Name | Description
----------|-------------
tool.cpp | Main program file
default.hpp | Default hosts file
diff.hpp | Support file check different
download.hpp | Download support
mitlicense.hpp | MIT license string file
make.cmd | Compile script
pipedebug.hpp | Debug tool for service mode
ptrerr.hpp | Log file support
tool.exe.manifest | Executable manifest file
tool.rc | program resource script file
wininet.lib | g++ compile library

## Functions description

Function name | Description
--------------|-------------
`__Check_Parameters` | Function check parameters
`Service_Main` | Service main function
`Service_Control` | Service control function
`Func_Service_Install` | Install service function
`Func_Service_UnInstall` | Uninstall service function
` NormalEntry` | Replace/download hosts function
`___debug_point_reset` | Debug function(reserved)
`__show_str` | Show normal information
`Func_ResetFile` | Reset hosts file function

## Program runtime process(Run without parameters)

1. Check parameters
2. Get system path
3. Download hosts file
4. Check diff between downloaded file and system hosts file
5. If different copy a backup file and replace it
6. Delete temp file


## Hosts Backup file(Windows 7+)

```
# Copyright (c) 1993-2009 Microsoft Corp.
#
# This is a sample HOSTS file used by Microsoft TCP/IP for Windows.
#
# This file contains the mappings of IP addresses to host names. Each
# entry should be kept on an individual line. The IP address should
# be placed in the first column followed by the corresponding host name.
# The IP address and the host name should be separated by at least one
# space.
#
# Additionally, comments (such as these) may be inserted on individual
# lines or following the machine name denoted by a '#' symbol.
#
# For example:
#
#      102.54.94.97     rhino.acme.com          # source server
#       38.25.63.10     x.acme.com              # x client host

# localhost name resolution is handled within DNS itself.
#	127.0.0.1       localhost
#	::1             localhost
```
