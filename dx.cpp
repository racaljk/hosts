//dx.cpp
//Author:qdxllecrn
//E-mail:sweheartiii[at]hotmail.com


#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "handle/download.hpp"
#include <string.h>
#define DEFBUF(x,y) x[y]=_T("")
OSVERSIONINFO osif;

void NormalEntry(){
	SYSTEMTIME st={0,0,0,0,0,0,0,0};
	TCHAR DEFBUF(buf1,BUFSIZ),DEFBUF(buf2,BUFSIZ),DEFBUF(buf3,BUFSIZ);
	SetConsoleTitle(_T("racaljk-host tools"));
	if (!Func_DownloadEx(_T("https://raw.githubusercontent.com/racaljk/hosts/master/hosts"),_T(".\\hosts"),FILE_ATTRIBUTE_SYSTEM));
	GetLocalTime(&st);
	if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ));
	_stprintf(buf1,_T("%s\\system32\\drivers\\etc\\hosts"),buf3);
	_stprintf(buf2,_T("%s\\system32\\drivers\\etc\\hosts.back.%04d-%02d-%02d.%2d:%2d:%2d"),
	buf3,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	if (!SetFileAttributes(buf1,FILE_ATTRIBUTE_NORMAL)); //for avoid CopyFile failed.
	if (!CopyFile(buf1,buf2,FALSE));
	if (!CopyFile(_T(".\\hosts"),buf1,FALSE));
	if (!DeleteFile(_T(".\\hosts")));
	MessageBox(NULL,"Hosts File Set Success!","Congratulations!",MB_ICONINFORMATION|MB_SETFOREGROUND);
	return ;
}

int Func_CoreTest(int argc,TCHAR const *argv[]){
	if (argc==1) start:ShellExecute(NULL,osif.dwMajorVersion==5?_T("open"):_T("runas"),argv[0],_T("-run"),NULL,SW_HIDE);
	else if (!_tcscmp(_T("-run"),argv[1])) NormalEntry(); else goto start;
	return 0;
}


int _tmain(int argc,const TCHAR *argv[]){
	GetVersionEx(&osif);
	return Func_CoreTest(argc,argv);
}