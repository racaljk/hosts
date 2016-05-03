/*
 * The MIT License(MIT)(redefined)
 *
 * Copyright (C) 2016 Too-Naive E-mail:sometimes.naive@hotmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, and to permit persons to
 * whom the Software is furnished to do so, BUT DO NOT SUBLICENSE, AND / OR SELL
 * OF THE SOFTWARE,subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * If you use the project's source code or its derivative products (including
 * but not limited to the executable file), it means that you have agreed to the
 * terms of this license and comply with the terms of the license. If you do not
 * agree to this license agreement, please do not use this project's source
 * code and its derivatives (including but not limited to the executable
 * file).
 */
//download.hpp(Re-edit)
//Code:https://raw.githubusercontent.com/Too-Naive/Tools/master/download.hpp

#pragma once

#include <windows.h>
#include <wininet.h>
#include "ptrerr.hpp"

//need wininet.lib

#pragma comment(lib,"wininet.lib")

#define ___userAgent TEXT("Mozilla/4.0 (compatible; Windows NT 6.1)")

bool Func_DownloadEx(const TCHAR * url,const TCHAR * file,const DWORD FileAttributes){
	const size_t dwBuffer=2048;		//buffer size
	HINTERNET hWeb,hRequest;		//Internet request handle
	DWORD dwReadByte=0,dwReserved;		//read byte count
	char szBuffer[dwBuffer]="";		//read buff
	HANDLE hdFile=INVALID_HANDLE_VALUE;	//file handle
	//bug check begin
	if (!(hWeb=InternetOpen(___userAgent,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0))) return false;
	if (!(hRequest=InternetOpenUrl(hWeb,url,NULL,0,INTERNET_FLAG_DONT_CACHE,0))){
		InternetCloseHandle(hWeb);
		return false;
	}
	if ((hdFile=CreateFile(file,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FileAttributes,NULL))==INVALID_HANDLE_VALUE){
		InternetCloseHandle(hWeb);
		InternetCloseHandle(hRequest);
		return false;
	}
	//end.
	while (InternetReadFile(hRequest,(PVOID)szBuffer,dwBuffer,&dwReadByte) && dwReadByte)
		WriteFile(hdFile,szBuffer,dwReadByte,&dwReserved,NULL);
	CloseHandle(hdFile);
	InternetCloseHandle(hRequest);
	InternetCloseHandle(hWeb);
	return true;
}

inline bool __fastcall Func_Download(const TCHAR *url,const TCHAR *file){//for backward compatibility
	return Func_DownloadEx(url,file,FILE_ATTRIBUTE_NORMAL);
}
