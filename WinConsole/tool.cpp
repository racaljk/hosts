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

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "hander/download.hpp"
#include <tchar.h>
#include <stdlib.h>
#include "hander/ptrerr.hpp"
#include "hander/diff.hpp"
#include "hander/mitlicense.hpp"
#include <signal.h>
#include "hander/pipedebug.hpp"
#include "hander/default.hpp"

#define WIN32_LEAN_AND_MEAN

#define DEFBUF(x,y) x[y]=_T("")
#define THROWERR(x) throw expection(x)

//Hosts file web address set
#ifndef DEBUG
#define hostsfile _T("https://raw.githubusercontent.com/racaljk/hosts/master/hosts")
#define hostsfile1 _T("https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts")
#else
#define hostsfile _T("http://localhost/hosts")
#define hostsfile1 _T("http://localhost/hosts")
#endif
#define objectwebsite _T("https://github.com/racaljk/hosts")
//end.

#define ConsoleTitle _T("racaljk-host tools     Build time:Apr. 30th, '16")

#define CASE(x,y) case x : y; break;
#define pWait _T("\n    \
There seems something wrong in download file, we will retry after 5 seconds.\n")

//tmpfile set
#define DownLocated _T("hosts.tmp")
#define ChangeCTLR _T("hostsq.tmp")
#define ReservedFile _T("hosts_n.tmp")
//end.

#define BAD_EXIT \
		_tprintf(_T("Bad Parameters.\nUsing \"-?\" Parameter to show how to use.\n")),\
		abort();

//debug set
#define LogFileLocate _T("c:\\Hosts_Tool_log.log")
const TCHAR * pipeName=_T("\\\\.\\pipe\\hoststoolnamepipe");
#define szErrMeg _T("\nFatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n")
using namespace __Dpipe;
//end.

//for backward compatibility DO NOT CHANGE IT
TCHAR Sname[]=_T("racaljk-hoststool");
TCHAR const *SzName[]={
	Sname
};
const TCHAR * szServiceShowName=_T("racaljk-hosts Tool");
//end

const size_t localbufsize=1024;

struct expection{
	const TCHAR *Message;
	expection(const TCHAR * _1){
		this->Message=_1;
	}
};

#define SHOW_HELP _T("\
------------------------------------------------------------\n\
Hosts Tool for Windows Console by: Too-Naive\n\
Copyright (C) 2016 @Too-Naive License:MIT LICENSE(redefined)\n\
------------------------------------------------------------\n\n\
Usage: hosts_tool [-? | -r | -fi | -fu | -show | --debug-pipe]\n\n\
Options:\n\
    -?    : Show this help message.\n\
    -r    : Reset system hosts file to default.\n\
    -fi   : Install Auto-Update hosts service(Service Name:%s).\n\
    -fu   : Uninstall service.\n\
    -show : Show the MIT license(redefined)\n\
    --debug-pipe : Debug Mode(reserved)\n\
Example:\n\
    hosts_tool -fi\n\n\
    If you need more imformation about debug mode,\n\
    Please see the page in: https:\x2f\x2fgit.io/vwg0c\n\n")

#define welcomeShow _T("\
    **********************************************\n\
    *                                            *\n\
    *                                            *\n\
    *                                            *\n\
    *        Welcome to use hosts tools!         *\n\
    *                                            *\n\
    *                                            *\n\
    *                    Powered by: @Too-Naive  *\n\
    **********************************************")

//Global variable
SERVICE_STATUS_HANDLE ssh;
SERVICE_STATUS ss;
HANDLE lphdThread[]={
	INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE
};
bool request_client,bReserved;
//end.

//function declaration
int __fastcall __Check_Parameters(int,TCHAR const**);
void WINAPI Service_Main(DWORD, LPTSTR *);
void WINAPI Service_Control(DWORD);
void Func_Service_Install(bool);
void Func_Service_UnInstall(bool);
DWORD __stdcall NormalEntry(LPVOID);
void ___debug_point_reset(int);
inline void __show_str(TCHAR const *,TCHAR const *);
void Func_ResetFile();


SERVICE_TABLE_ENTRY STE[2]={{Sname,Service_Main},{NULL,NULL}};

//define buffer
TCHAR DEFBUF(buf1,localbufsize),DEFBUF(buf2,localbufsize),
	DEFBUF(buf3,localbufsize),DEFBUF(szline,localbufsize);

//define parameters
enum _Parameters{
	EXEC_START_NORMAL		=1<<0x00,
//	EXEC_START_RUNAS		=1<<0x01,
	EXEC_START_SERVICE		=1<<0x02,
	EXEC_START_INSTALL_SERVICE	=1<<0x03,
	EXEC_START_UNINSTALL_SERVICE	=1<<0x04,
	EXEC_START_HELP			=1<<0x05,
	EXEC_DEBUG_RESET		=1<<0x06,
	SHOW_LICENSE			=1<<0x07,
	DEBUG_SERVICE_STOP		=1<<0x08,
	DEBUG_SERVICE_START		=1<<0x09,
	DEBUG_SERVICE_REINSTALL		=1<<0x0a,
	OPEN_LISTEN			=1<<0x0b,
	RESET_FILE		=1<<0x0c,
	PARAMETERS_RESERVED6		=1<<0x0d,
	PARAMETERS_RESERVED7		=1<<0x0e,
	PARAMETERS_RESERVED8		=1<<0x0f,
	PARAMETERS_RESERVED9		=1<<0x10,
	EXEC_BAD_PARAMETERS		=1073741824
};

//define _In_ parameters string
TCHAR const *szParameters[]={
	_T("svc"),//for backward compatibility
	_T("fi"),				//1
	_T("fu"),				//2
	_T("h"),				//3
	_T("-debug-reset"),			//4
	_T("show"),				//5
	_T("?"),				//6
	_T("-debug-stop"),			//7
	_T("-debug-start"),			//8
	_T("-debug-reiu"),			//9
	_T("-debug-pipe"),			//10
	_T("--pipe"),				//11
	_T("r")					//12
};

int __fastcall __Check_Parameters(int argc,TCHAR const **argv){
	if (argc==1) return EXEC_START_NORMAL;
	if (argc>3||!((argv[1][0]==_T('/') ||
		argv[1][0]==_T('-')) && argv[1][1]!=_T('\0'))) BAD_EXIT;
	size_t i=0;
	for (;_tcscmp(&(argv[1][1]),szParameters[i]) &&
		i<sizeof(szParameters)/sizeof(szParameters[0]);i++);
	if (!(i==0 || i==1 ||i==9) && argc>2) BAD_EXIT;
	if (argc==3 && !_tcscmp(argv[2],szParameters[11])) request_client=1;
		else if (argc==3 && _tcscmp(argv[2],szParameters[11])) BAD_EXIT;
	switch (i){
		case  0: bReserved=true;
				 return EXEC_START_SERVICE;
		case  1: return EXEC_START_INSTALL_SERVICE;
		case  2: return EXEC_START_UNINSTALL_SERVICE;
		case  6:
		case  3: return EXEC_START_HELP;
		case  4: return EXEC_DEBUG_RESET;//restart service
		case  5: return SHOW_LICENSE;
		case  7: return DEBUG_SERVICE_STOP;//stop service
		case  8: return DEBUG_SERVICE_START;//start service
		case  9: return DEBUG_SERVICE_REINSTALL;//reinstall service
		case 10: return OPEN_LISTEN;
		case 12: return RESET_FILE;
		default: BAD_EXIT;
	}
	BAD_EXIT
}

//main entry
int _tmain(int argc,TCHAR const ** argv){
	SetConsoleTitle(ConsoleTitle);
	switch (__Check_Parameters(argc,argv)){
		CASE(EXEC_START_NORMAL,NormalEntry(NULL));
		CASE(EXEC_START_INSTALL_SERVICE,Func_Service_Install(true));
		CASE(EXEC_START_UNINSTALL_SERVICE,Func_Service_UnInstall(true));
		CASE(EXEC_START_SERVICE,StartServiceCtrlDispatcher(STE));
		CASE(EXEC_START_HELP,__show_str(SHOW_HELP,Sname));
		CASE(EXEC_DEBUG_RESET,___debug_point_reset(EXEC_DEBUG_RESET));
		CASE(SHOW_LICENSE,__show_str(szMitLicense_Raw,NULL));
		CASE(DEBUG_SERVICE_STOP,___debug_point_reset(DEBUG_SERVICE_STOP));
		CASE(DEBUG_SERVICE_START,___debug_point_reset(DEBUG_SERVICE_START));
		CASE(DEBUG_SERVICE_REINSTALL,___debug_point_reset(DEBUG_SERVICE_REINSTALL));
		CASE(OPEN_LISTEN,___debug_point_reset(OPEN_LISTEN));
		CASE(RESET_FILE,Func_ResetFile());
		default:break;
	}
	return 0;
}

void Func_ResetFile(){
	SYSTEMTIME st={0,0,0,0,0,0,0,0};
	_tprintf(_T("\
------------------------------------------------------------\n\
Hosts Tool for Windows Console by: Too-Naive\n\
Copyright (C) 2016 @Too-Naive License:MIT LICENSE(redefined)\n\
------------------------------------------------------------\n"));
	if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
		_tprintf(_T("    GetEnvironmentVariable() Error!(GetLastError():%ld)\n\
\tCannot get system path!"),GetLastError()),abort();
	GetLocalTime(&st);
	_stprintf(buf1,_T("%s\\system32\\drivers\\etc\\hosts"),buf3);
	_stprintf(buf2,_T("%s\\system32\\drivers\\etc\\hosts.%04d%02d%02d.%02d%02d%02d"),
	buf3,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	if (CopyFile(buf1,buf2,FALSE))
		_tprintf(_T("Backup File success\nFilename:%s\n\n"),buf2);
	FILE *fp=_tfopen(buf1,_T("w"));
	if (!fp) _tprintf(_T("Cannot open file!\n")),abort();
	_ftprintf(fp,_T("%s"),szDefatult_hostsfile);
	fclose(fp);
	_tprintf(_T("    Reset file successfully.\n"));
	system("pause");
	return ;
}

void __abrt(int){
	_tprintf(_T("Received signal SIGINT\n"));
	request_client=0;
	_tprintf(_T("Uninstall service.\n"));
	Func_Service_UnInstall(false);
	TerminateThread(lphdThread[0],0);
	CloseHandle(hdPipe);
	_tprintf(_T("Program will now exit.\n"));
	exit(0);
}

inline void __show_str(TCHAR const* st,TCHAR const * _ingore){
	if (!_ingore) _tprintf(_T("%s"),st);
	else _tprintf(st,_ingore);
	system("pause");
	return ;
}

void Func_Service_UnInstall(bool _quite){
	SC_HANDLE shMang=NULL,shSvc=NULL;
	try{
		if (!GetEnvironmentVariable(_T("SystemRoot"),buf2,BUFSIZ))
			THROWERR(_T("GetEnvironmentVariable() Error in UnInstall Service."));
		_stprintf(buf1,_T("%s\\hoststools.exe"),buf2);
		if (!(shMang=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)))
			THROWERR(_T("OpenSCManager() Error in Uninstall service."));
		if (!(shSvc=OpenService(shMang,Sname,SERVICE_ALL_ACCESS)))
			if (_quite) THROWERR(_T("OpenService() Error in Uninstall service.\nIs service exist?"));
		if (!ControlService(shSvc,SERVICE_CONTROL_STOP,&ss))
			if (_quite) _tprintf(_T("ControlService() Error in Uninstall service.\n%s"),
				_T("Service may not in running.\n"));
		Sleep(2000);//Wait for service stop
		if (!DeleteService(shSvc))
			if (_quite) THROWERR(_T("DeleteService() Error in UnInstall service."));
		if (!DeleteFile(buf1))
			if (_quite) {
				_tprintf(_T("Executable File located:%s\n"),buf1);
				THROWERR(_T("DeleteFile() Error in Uninstall service.\n\
You may should delete it manually."));
		}
	}
	catch (expection _r){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n"),
		_r.Message,GetLastError());
		_tprintf(_T("\n[Debug Message]\n%s\n%s\n"),buf1,buf2);
		CloseServiceHandle(shSvc);
		CloseServiceHandle(shMang);
		if (_quite) abort();
	}
	CloseServiceHandle(shSvc);
	CloseServiceHandle(shMang);
	_tprintf(_T("Service Uninstall Successfully\n"));
	return ;
}

void ___debug_point_reset(int _par){
	SC_HANDLE shMang=NULL,shSvc=NULL;
//	_tprintf(_T("Entry Debug Function.\n"));
	if (_par==DEBUG_SERVICE_REINSTALL){
		Func_Service_UnInstall(false);
		Func_Service_Install(false);
		return ;
	}
	try {
		if (_par!=OPEN_LISTEN) {
			if (!(shMang=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)))
				THROWERR(_T("OpenSCManager() Error in debug_reset."));
			if (!(shSvc=OpenService(shMang,Sname,SERVICE_STOP|SERVICE_START)))
				THROWERR(_T("OpenService() Error in debug_reset."));
		}
		switch(_par){
			case DEBUG_SERVICE_STOP:
			case EXEC_DEBUG_RESET:
				if (!ControlService(shSvc,SERVICE_CONTROL_STOP,&ss))
					THROWERR(_T("ControlService() Error in debug_reset."));
				Sleep(1000);
				if (_par==DEBUG_SERVICE_STOP) break;
			case OPEN_LISTEN:
				if (_par!=EXEC_DEBUG_RESET){
					signal(SIGINT,__abrt);
_tprintf(_T("    Warning:\n    \
You are in debug mode, please press CTRL+C to exit the debug mode.\n\t\t\
DO NOT CLOSE THE CONSOLE DIRECT!!!\n"));
					request_client=1;
					_tprintf(_T("Reinstall service\n"));
					___debug_point_reset(DEBUG_SERVICE_REINSTALL);
					___debug_point_reset(DEBUG_SERVICE_START);
					if ((lphdThread[0]=CreateThread(NULL,0,OpenPipeService,NULL,0,NULL))==INVALID_HANDLE_VALUE)
						THROWERR(_T("CreateThread() Error!"));
					WaitForSingleObject(lphdThread[0],INFINITE);
					CloseHandle(hdPipe);
					return ;
				}
			case DEBUG_SERVICE_START:
				if (!StartService(shSvc,1,SzName))
					THROWERR(_T("StartService() Error in debug_reset."));
			default : break;
		}
	}
	catch (expection _r){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n"),
		_r.Message,GetLastError());
		CloseServiceHandle(shSvc);
		CloseServiceHandle(shMang);
		abort();
	}
	CloseServiceHandle(shSvc);
	CloseServiceHandle(shMang);
//	_tprintf(_T("Exited debug mode.(%d)\n"),_par);
	return ;
}

void Func_Service_Install(bool _q){
	SC_HANDLE shMang=NULL,shSvc=NULL;
	if (_q){
		_tprintf(_T("    LICENSE:MIT LICENSE\n    Copyright (C) 2016 @Too-Naive\n\n"));
		_tprintf(_T("    Bug report:sometimes.naive[at]hotmail.com \n\t       \
Or open new issue\n------------------------------------------------------\n\n"));
	}
	try{
		if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
			THROWERR(_T("GetEnvironmentVariable() Error in Install Service."));
		_stprintf(buf1,_T("%s\\hoststools.exe"),buf3);
		_stprintf(buf2,_T("\"%s\\hoststools.exe\" -svc"),buf3);
		if (request_client)
			_stprintf(szline,_T("%s %s"),buf2,szParameters[11]),
			_tcscpy(buf2,szline),memset(szline,0,sizeof(szline)/sizeof(TCHAR));
		if (!GetModuleFileName(NULL,szline,sizeof(szline)/sizeof(TCHAR)))
			THROWERR(_T("GetModuleFileName() Error in Install Service."));
		if (_q) _tprintf(_T("    Step1:Copy file.\n"));
		if (!CopyFile(szline,buf1,FALSE))
			THROWERR(_T("CopyFile() Error in Install Service.(Is service has been installed?)"));
		if (_q) _tprintf(_T("    Step2:Connect to SCM.\n"));
		if (!(shMang=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)))
			THROWERR(_T("OpenSCManager() failed."));
		if (_q) _tprintf(_T("    Step3:Write service.\n"));
		if (!(shSvc=CreateService(shMang,Sname,szServiceShowName,
		SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,
			buf2,NULL,NULL,NULL,NULL,NULL))){
			if (GetLastError()==ERROR_SERVICE_EXISTS){
				if (!(shSvc=OpenService(shMang,Sname,SERVICE_ALL_ACCESS)))
					THROWERR(_T("OpenService() Error in install service."));/*
				if (!ControlService(shSvc,SERVICE_CONTROL_STOP,&ss))
					_tprintf(_T("ControlService() Error in install service."));*/
				if (!DeleteService(shSvc))
					THROWERR(_T("DeleteService() Error in Install Service."));
				CloseServiceHandle(shSvc);
				if (!(shSvc=CreateService(shMang,Sname,szServiceShowName,
				SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,
				buf2,NULL,NULL,NULL,NULL,NULL)))
					THROWERR(_T("CreateService() failed.(2)")),CloseServiceHandle(shMang);
			}
			else
				THROWERR(_T("CreateService() failed."));
		}
		else //_T("Service installed successfully"),_T("Congratulations!"),MB_SETFOREGROUND|MB_ICONINFORMATION
			_tprintf(_T("Install service successfully.\n"));
		if (!request_client){
			if (!(shSvc=OpenService(shMang,Sname,SERVICE_START)))
				THROWERR(_T("OpenService() Failed"));
			else
				if (!StartService(shSvc,1,SzName))
					THROWERR(_T("StartService() Failed."));
					else
				MessageBox(NULL,_T("Service started successfully"),_T("Congratulations!"),
				MB_SETFOREGROUND|MB_ICONINFORMATION);
		}
	}
	catch (expection _r){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n"),
		_r.Message,GetLastError());
		_tprintf(_T("\n[Debug Message]\n%s\n%s\n%s\n"),buf1,buf2,buf3);
		abort();
	}
	CloseServiceHandle(shMang);
	CloseServiceHandle(shSvc);
	if (_q) system("pause");
	return ;
}

inline void __fastcall ___autocheckmess(const TCHAR * szPstr){
	if (!request_client)
		Func_FastPMNTS(szPstr);
	else
		___pipesentmessage(szPstr);
}

inline void __fastcall ___checkEx(const TCHAR * szPstr,bool space_need){
	if (!request_client)
		if (!space_need) Func_FastPMNSS(szPstr);
		else Func_FastPMNTS(szPstr);
	else
		___pipesentmessage(szPstr);
}

inline void __fastcall _perrtext(const TCHAR * _str,bool _Reserved){
	if (!bReserved)	_tprintf(_str);
	else if (_Reserved) Func_FastPMNTS(_str);
		 else Func_FastPMNSS(_str);
	return ;
}


//TODO: temp string length only 1000(TCHAR)
//is safe for this program? I don't know.

DWORD __stdcall NormalEntry(LPVOID){
	SYSTEMTIME st={0,0,0,0,0,0,0,0};
	FILE * fp=NULL,*_=NULL;
	if (!bReserved){
		_tprintf(_T("    LICENSE:MIT LICENSE\n%s\n    Copyright (C) 2016 @Too-Naive\n"),welcomeShow);
		_tprintf(_T("    Project website:%s\n"),objectwebsite);
		_tprintf(_T("    Bug report:sometimes.naive[at]hotmail.com \n\t       Or open new issue\n\n\n"));
		_tprintf(_T("    Start replace hosts file:\n    Step1:Get System Driver..."));
	}
	else{
		if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
			Func_FastPMNTS(_T("GetEnvironmentVariable() Error!(GetLastError():%ld)\n\
\tCannot get system path!"),GetLastError()),abort();
		_stprintf(buf1,_T("%s\\system32\\drivers\\etc\\hosts"),buf3);
		if (request_client) ___pipeopen(),___pipesentmessage(_T("\nMessage from service:\n\n"));
		Func_FastPMNTS(_T("Open log file.\n"));
		___checkEx(_T("LICENSE:MIT LICENSE\n"),1);
		___checkEx(_T("Copyright (C) 2016 Too-Naive\n"),0);
		___checkEx(_T("Bug report:sometimes.naive[at]hotmail.com\n"),0);
		___checkEx(_T("           Or open new issue.(https://github.com/racaljk/hosts)\n"),0);
	}
	do {
		Sleep(bReserved?(request_client?0:60000):0);//Waiting for network
		GetLocalTime(&st);
		if (bReserved) ___autocheckmess(_T("Start replace hosts file.\n"));
		try {
			if (!bReserved)	if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
				THROWERR(_T("GetEnvironmentVariable() Error!\n\tCannot get system path!"));
			_stprintf(buf1,_T("%s\\system32\\drivers\\etc\\hosts"),buf3);
			_stprintf(buf2,_T("%s\\system32\\drivers\\etc\\hosts.%04d%02d%02d.%02d%02d%02d"),
			buf3,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
			if (!bReserved) _tprintf(_T("\t\tDone.\n    Step2:Download hosts file..."));
			//download
			if (bReserved) if (request_client) ___pipesentmessage(_T("Download files\n"));
			for (int errcunt=0;(!Func_Download(hostsfile,DownLocated)&&
				!Func_Download(hostsfile1,DownLocated));errcunt++)
					if (errcunt>2) THROWERR(_T("DownLoad hosts file Error!"));
					else if (!bReserved) {
						_tprintf(pWait);
						Sleep(bReserved?(request_client?1000:10000):5000);
						if (!bReserved) _tprintf(_T("\tDownload hosts file..."));
					}
			//end.
			if (!bReserved) _tprintf(_T("\tDone.\n    Step3:Change Line Endings..."));
			if (!((fp=_tfopen(DownLocated,_T("r"))) && (_=_tfopen(ChangeCTLR,_T("w")))))
				THROWERR(_T("Open file Error!"));
			while (!feof(fp)){
				memset(szline,0,sizeof(szline));
				_fgetts(szline,1000,fp);
				_fputts(szline,_);
			}
			fclose(fp);fclose(_);
			fp=NULL,_=NULL;
			if (!DeleteFile(DownLocated)){
				if (bReserved)
					Func_FastPMNTS(_T("Delete tmpfile error.(%ld)\n"),GetLastError());
				else
					_tprintf(_T("Delete tmpfile error.(%ld)\n"),GetLastError());
			}
			//new future
			if (!((fp=_tfopen(buf1,_T("r"))) && (_=_tfopen(ReservedFile,_T("w")))));
			while (!feof(fp)){
				memset(szline,0,sizeof(szline));
				_fgetts(szline,1000,fp);
				if (*szline==_T('#')) {
					if (_tcsstr(szline,_T("# Copyright (c) 2014")))
					break; else continue;
				}
				if (*szline==_T('\n')) continue;
				_fputts(szline,_);
			}
			fclose(_);
			if (!feof(fp)){
				if (!(_=_tfopen(DownLocated,_T("w"))));
				_fputts(szline,_);
				while (!feof(fp)) {
					memset(szline,0,sizeof(szline));
					_fgetts(szline,1000,fp);
					_fputts(szline,_);
				}
				fclose(_);
			}
			fclose(fp);
			fp=NULL,_=NULL;
			//end
			if (Func_CheckDiff(ChangeCTLR,DownLocated)){
				if (!bReserved) _tprintf(_T("\tDone.\n\n    \
diff exited with value 0(0x00)\n    \
Finish:Hosts file Not update.\n\n"));
				else ___autocheckmess(_T("Finish:Hosts file Not update.\n\n"));
				DeleteFile(ChangeCTLR);
				DeleteFile(ReservedFile);
				DeleteFile(DownLocated);
				if (!bReserved) {system("pause");return GetLastError();}
			}
			else {
				if (!bReserved) _tprintf(_T("\tDone.\n    Step4:Copy Backup File..."));
				SetFileAttributes(buf1,FILE_ATTRIBUTE_NORMAL); //for avoid CopyFile failed.
				if (!CopyFile(buf1,buf2,FALSE))
					THROWERR(_T("CopyFile() Error on copy a backup file"));
				if (!bReserved) _tprintf(_T("\t\tDone.\n    Step5:Replace Default Hosts File..."));
				if (!CopyFile(ReservedFile,buf1,FALSE))
					THROWERR(_T("CopyFile() Error on copy hosts file to system path"));
				if (!((fp=_tfopen(ChangeCTLR,_T("r"))) && (_=_tfopen(buf1,_T("a+")))))
					THROWERR(_T("_tfopen() Error in copy hosts file."));
				while (!feof(fp)){
					memset(szline,0,sizeof(szline));
					_fgetts(szline,1000,fp);
					_fputts(szline,_);
				}
				fclose(fp);fclose(_);
				Sleep(500);
				DeleteFile(ChangeCTLR);
				DeleteFile(ReservedFile);
				DeleteFile(DownLocated);
				if (!bReserved) _tprintf(_T("Replace File Successfully\n"));
				else ___autocheckmess(_T("Replace File Successfully\n"));
				if (!bReserved) MessageBox(NULL,_T("Hosts File Set Success!"),
					_T("Congratulations!"),MB_ICONINFORMATION|MB_SETFOREGROUND);
			}
		}
		catch(expection runtimeerr){
			if (!bReserved){
				if (!request_client){
					Func_FastPMNTS(_T("Fatal Error:\n"));
					Func_FastPMNSS(_T("%s (GetLastError():%ld)\n"),runtimeerr.Message,GetLastError());
					Func_FastPMNSS(_T("Please contact the application's support team for more information.\n"));
				}
				else {
					_stprintf(szline,szErrMeg,runtimeerr.Message,GetLastError());
					___pipesentmessage(szline);
				}
			}
			else{
				_tprintf(szErrMeg,runtimeerr.Message,GetLastError());
				_tprintf(_T("\n[Debug Message]\n%s\n%s\n%s\n"),buf1,buf2,buf3);
				abort();
			}
		}
		Sleep(bReserved?(request_client?5000:(29*60000)):0);
	} while (bReserved);
	return GetLastError();
}


void WINAPI Service_Main(DWORD,LPTSTR *){
	Func_SetErrorFile(LogFileLocate,_T("a+"));
	if (!(ssh=RegisterServiceCtrlHandler(Sname,Service_Control)))
		Func_FastPMNTS(_T("RegisterServiceCtrlHandler() Error with %ld \n\
Cannot start service!\n"),GetLastError()),abort();
	ss.dwServiceType=SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState=SERVICE_START_PENDING;
	ss.dwControlsAccepted=SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_SHUTDOWN;
	ss.dwServiceSpecificExitCode=0;
	ss.dwWin32ExitCode=0;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=1000;
	SetServiceStatus(ssh,&ss);
	ss.dwCurrentState=SERVICE_RUNNING;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=0;
	SetServiceStatus(ssh,&ss);
	if (!(lphdThread[0]=CreateThread(NULL,0,NormalEntry,NULL,0,NULL))){
		Func_FastPMNTS(_T("CreateThread() Error with %ld \n\
Cannot start main thread to update hosts!\n"),GetLastError());
		ss.dwWin32ExitCode=ERROR_SERVICE_NO_THREAD;
		ss.dwCurrentState=SERVICE_STOPPED;
		ss.dwCheckPoint=1;
		ss.dwWaitHint=0;
		SetServiceStatus(ssh,&ss);
		abort();
	}
	WaitForSingleObject(lphdThread[0],INFINITE);
	ss.dwCurrentState=SERVICE_STOPPED;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=0;
	SetServiceStatus(ssh,&ss);
	return ;
}

void WINAPI Service_Control(DWORD dwControl){
	switch (dwControl)
	{
		case SERVICE_CONTROL_SHUTDOWN:
		case SERVICE_CONTROL_STOP:
			ss.dwCurrentState=SERVICE_STOP_PENDING;
			ss.dwCheckPoint=0;
			ss.dwWaitHint=1000;
			SetServiceStatus(ssh,&ss);
			TerminateThread(lphdThread[0],0);
			if (request_client) CloseHandle(hdPipe);
			ss.dwCurrentState=SERVICE_STOPPED;
			ss.dwCheckPoint=0;
			ss.dwWaitHint=0;
			SetServiceStatus(ssh,&ss);
		default:break;
	}
	return ;
}
