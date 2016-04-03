//download.hpp
//Author:qdxllecrn
//E-mail:sweheartiii[at]hotmail.com
//Code:https://raw.githubusercontent.com/Too-Naive/Tools/master/download.hpp

#pragma once

#include <windows.h>
#include <wininet.h>

//need wininet.lib

#pragma comment(lib,"wininet.lib")

#define ___userAgent TEXT("Mozilla/4.0 (compatible; Windows NT 5.1)")


bool Func_DownloadEx(const TCHAR * url,const TCHAR * file,const DWORD FileAttributes){
	const size_t dwBuffer=2048;	//buffer size
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


