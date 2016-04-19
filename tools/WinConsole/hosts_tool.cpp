<<<<<<< HEAD
<<<<<<< HEAD
//Copyright (C) 2016 Too-Naive 
//E-mail:sweheartiii@hotmail.com

=======
/*
=======
﻿/*
>>>>>>> racaljk/master
 * The MIT License(MIT)(redefined)
 *
 * Copyright(c) 2016 Too-Naive E-mail:sweheartiii@hotmail.com
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
 */
>>>>>>> racaljk/master

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "download.hpp"
#include <tchar.h>
#include <stdlib.h>
#include "ptrerr.hpp"
<<<<<<< HEAD

=======
#include "mitlicense.hpp"
#include "diff.hpp"
<<<<<<< HEAD
>>>>>>> racaljk/master
=======
#include <signal.h>
>>>>>>> racaljk/master

#define WIN32_LEAN_AND_MEAN

#define DEFBUF(x,y) x[y]=_T("")
#define THROWERR(x) throw expection(x)
#define hostsfile _T("https://raw.githubusercontent.com/racaljk/hosts/master/hosts")
<<<<<<< HEAD
#define Shell(x) ShellExecute(NULL,(_os_.dwMajorVersion<=5)?_T("open"):_T("runas"),argv[0],_T(x),NULL,SW_SHOWNORMAL)

#define CASE(x,y) case x : y; break;

#define DownLocated _T(".\\hosts")
#define ChangeCTLR _T(".\\hostsq")

=======
#define hostsfile1 _T("https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts")
#define objectwebsite _T("https://github.com/racaljk/hosts")
#define ConsoleTitle _T("racaljk-host tools     Build time:Apr. 13th, '16")

#define CASE(x,y) case x : y; break;
#define pWait _T("\n    \
There seems something wrong in download file, we will retry after 5 seconds.\n")

#define DownLocated _T("hosts.tmp")
#define ChangeCTLR _T("hostsq.tmp")
#define BAD_EXIT \
		_tprintf(_T("Bad Parameters.\nUsing \"-?\" Parameter to show how to use.\n")),\
		abort();
#define LogFileLocate _T("c:\\Hosts_Tool_log.log")
#define pipeName _T("\\\\.\\pipe\\hoststoolnamepipe")
const size_t localbufsize=1024;
>>>>>>> racaljk/master

struct expection{
	const TCHAR *Message;
	expection(const TCHAR * _1){
		this->Message=_1;
	}
};

<<<<<<< HEAD
<<<<<<< HEAD
#define SHOW_HELP "\n\
Usage: hosts_tool [-fi | -fu | -h]\n\n\n\
Options:\n\
    -h  : Show this help message.\n\
    -fi : Install Auto-Update hosts service(Service Name:%s).\n\
    -fu : uninstall service.\n\n\n\
    Copyright (C) 2016 @Too-Naive\n\
    License:MIT LICENSE\n\n\n"

=======
=======
//for pipe
#define PIPE_TIMEOUT 5000
#define BUFSIZE 4096

typedef struct
{
	OVERLAPPED oOverlap;
	HANDLE hPipeInst;
	TCHAR chRequest[BUFSIZE];
	DWORD cbRead;
	TCHAR chReply[BUFSIZE];
	DWORD cbToWrite;
} PIPEINST, *LPPIPEINST;
//end

>>>>>>> racaljk/master
#define SHOW_HELP _T("\
------------------------------------------------------------\n\
Hosts Tool for Windows Console by: Too-Naive\n\
Copyright (C) 2016 @Too-Naive License:MIT LICENSE(redefined)\n\
------------------------------------------------------------\n\n\
Usage: hosts_tool [-fi | -fu | -h | -? | -show | --debug-pipe]\n\n\
Options:\n\
    -h    : Show this help message.\n\
    -?    : Show this help message.\n\
    -fi   : Install Auto-Update hosts service(Service Name:%s).\n\
    -fu   : Uninstall service.\n\
    -show : Show the MIT license(redefined)\n\
	--debug-pipe : Debug Mode(reserved)\n\
Example:\n\
<<<<<<< HEAD
    hosts_tool -fi\n\n")
>>>>>>> racaljk/master
=======
    hosts_tool -fi\n\n\
    If you need more imformation about debug mode,\n\
    Please see the page in: https:\x2f\x2fgit.io/vVp2k\n\n")
>>>>>>> racaljk/master

#define welcomeShow _T("\
    **********************************************\n\
    *                                            *\n\
    *                                            *\n\
    *                                            *\n\
    *          Welcome use hosts tools!          *\n\
    *                                            *\n\
    *                                            *\n\
    *                    Powered by: @Too-Naive  *\n\
    **********************************************")
//for backward compatibility DO NOT CHANGE IT
TCHAR Sname[]=_T("racaljk-hoststool");
TCHAR const *SzName[]={
	Sname
};
//end


SERVICE_STATUS_HANDLE ssh;
SERVICE_STATUS ss;
HANDLE lphdThread[]={
	INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE
};
HANDLE hdPipe=INVALID_HANDLE_VALUE;
bool request_client;

int __fastcall __Check_Parameters(int,TCHAR const**);
void WINAPI Service_Main(DWORD, LPTSTR *);
void WINAPI Service_Control(DWORD);
DWORD CALLBACK Main_Thread(LPVOID);
<<<<<<< HEAD
<<<<<<< HEAD
void Func_Service_Install(const TCHAR *);
void Func_Service_UnInstall();
void NormalEntry();
bool Func_CheckDiff(const TCHAR*,const TCHAR*) throw(expection);
DWORD __stdcall HostThread(LPVOID);

SERVICE_TABLE_ENTRY STE[2]={{Sname,Service_Main},{NULL,NULL}};
OSVERSIONINFO _os_={sizeof(OSVERSIONINFO),0,0,0,0,_T("")};


enum _Parameters{
	EXEC_START_NORMAL			=1,
	EXEC_START_RUNAS			=2,
	EXEC_START_SERVICE			=4,
	EXEC_START_INSTALL_SERVICE	=8,
	EXEC_START_UNINSTALL_SERVICE=16,
	EXEC_START_HELP				=32,
	EXEC_BAD_PARAMETERS			=65536
};


TCHAR const *__const_Parameters[]={
	_T("rinstall"),
	_T("runinstall"),
	_T("rrun"),
	_T("svc"),//for backward compatibility
	_T("fi"),
	_T("fu"),
	_T("h")
=======
void Func_Service_Install();
void Func_Service_UnInstall();
=======
void Func_Service_Install(bool);
void Func_Service_UnInstall(bool);
>>>>>>> racaljk/master
void NormalEntry();
DWORD __stdcall HostThread(LPVOID);
void ___debug_point_reset(int);
inline void __show_str(TCHAR const *,TCHAR const *);
HANDLE ___pipeopen();
inline DWORD ___pipeclose();
DWORD __stdcall OpenPipeService(LPVOID);
DWORD ___pipesentmessage(const TCHAR *);

void DisconnectAndClose(LPPIPEINST);
BOOL CreateAndConnectInstance(LPOVERLAPPED);
BOOL ConnectToNewClient(HANDLE, LPOVERLAPPED);
inline void GetAnswerToRequest(LPPIPEINST);
void WINAPI CompletedWriteRoutine(DWORD, DWORD, LPOVERLAPPED);
void WINAPI CompletedReadRoutine(DWORD, DWORD, LPOVERLAPPED);


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
	PARAMETERS_RESERVED5		=1<<0x0c,
	PARAMETERS_RESERVED6		=1<<0x0d,
	PARAMETERS_RESERVED7		=1<<0x0e,
	PARAMETERS_RESERVED8		=1<<0x0f,
	PARAMETERS_RESERVED9		=1<<0x10,
	EXEC_BAD_PARAMETERS		=1073741824
};

//define _In_ parameters string
TCHAR const *szParameters[]={
	_T("svc"),//for backward compatibility
<<<<<<< HEAD
	_T("fi"),
	_T("fu"),
	_T("h"),
	_T("-debug-reset"),
	_T("show"),
	_T("?"),
	_T("-debug-stop"),
	_T("-debug-start"),
	_T("-debug-reinstall")
>>>>>>> racaljk/master
=======
	_T("fi"),				//1
	_T("fu"),				//2
	_T("h"),				//3
	_T("-debug-reset"),			//4
	_T("show"),				//5
	_T("?"),				//6
	_T("-debug-stop"),			//7
	_T("-debug-start"),			//8
	_T("-debug-reiu"),			//9
	_T("-debug-pipe"),		//10
	_T("--pipe")			//11
>>>>>>> racaljk/master
};

int __fastcall __Check_Parameters(int argc,TCHAR const **argv){
	if (argc==1) return EXEC_START_NORMAL;
<<<<<<< HEAD
<<<<<<< HEAD
	if (argc>2 || !((argv[1][0]==_T('/') || 
		argv[1][0]==_T('-')) && argv[1][1]!='\0')) return EXEC_BAD_PARAMETERS;
	size_t i=0;
	for (;_tcscmp(&(argv[1][1]),__const_Parameters[i]) && 
		i<sizeof(__const_Parameters)/sizeof(__const_Parameters[0]);i++);
	switch (i){
		case 0: return EXEC_START_RUNAS|EXEC_START_INSTALL_SERVICE;
		case 1: return EXEC_START_RUNAS|EXEC_START_UNINSTALL_SERVICE;
		case 2: return EXEC_START_RUNAS|EXEC_START_NORMAL;
		case 3: return EXEC_START_SERVICE;
		case 4: return EXEC_START_INSTALL_SERVICE;
		case 5: return EXEC_START_UNINSTALL_SERVICE;
		case 6: return EXEC_START_HELP;
		default: break;
	}
	return EXEC_BAD_PARAMETERS;
}



int _tmain(int argc,TCHAR const ** argv){
	SetConsoleTitle(_T("racaljk-host tools"));
	GetVersionEx(&_os_);
	switch (__Check_Parameters(argc,argv)){
		CASE(EXEC_START_NORMAL,Shell("-rrun"));
		CASE(EXEC_START_RUNAS|EXEC_START_NORMAL,NormalEntry());
		CASE(EXEC_START_RUNAS|EXEC_START_INSTALL_SERVICE,Func_Service_Install(argv[0]));
		CASE(EXEC_START_RUNAS|EXEC_START_UNINSTALL_SERVICE,Func_Service_UnInstall());
		CASE(EXEC_START_INSTALL_SERVICE,Shell("-rinstall"));
		CASE(EXEC_START_UNINSTALL_SERVICE,Shell("-runinstall"));
		CASE(EXEC_START_SERVICE,StartServiceCtrlDispatcher(STE));
		CASE(EXEC_START_HELP,_tprintf(SHOW_HELP,Sname));
		case EXEC_BAD_PARAMETERS:
		_tprintf(_T("Bad Parameters."));
		abort();
=======
	if (argc>2 || !((argv[1][0]==_T('/') ||
=======
	if (argc>3||!((argv[1][0]==_T('/') ||
>>>>>>> racaljk/master
		argv[1][0]==_T('-')) && argv[1][1]!=_T('\0'))) BAD_EXIT;
	size_t i=0;
	for (;_tcscmp(&(argv[1][1]),szParameters[i]) &&
		i<sizeof(szParameters)/sizeof(szParameters[0]);i++);
	if (!(i==0 || i==1 ||i==9) && argc>2) BAD_EXIT;
	if (argc==3 && !_tcscmp(argv[2],szParameters[11])) request_client=1;
		else if (argc==3 && _tcscmp(argv[2],szParameters[11])) BAD_EXIT;
	switch (i){
		case  0: return EXEC_START_SERVICE;
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
		default: BAD_EXIT;
	}
	BAD_EXIT
}

//main entry
int _tmain(int argc,TCHAR const ** argv){
	SetConsoleTitle(ConsoleTitle);
	switch (__Check_Parameters(argc,argv)){
		CASE(EXEC_START_NORMAL,NormalEntry());
		CASE(EXEC_START_INSTALL_SERVICE,Func_Service_Install(true));
		CASE(EXEC_START_UNINSTALL_SERVICE,Func_Service_UnInstall(true));
		CASE(EXEC_START_SERVICE,StartServiceCtrlDispatcher(STE));
		CASE(EXEC_START_HELP,__show_str(SHOW_HELP,Sname));
		CASE(EXEC_DEBUG_RESET,___debug_point_reset(EXEC_DEBUG_RESET));
		CASE(SHOW_LICENSE,__show_str(szMitLicenseRaw,NULL));
<<<<<<< HEAD
		CASE(DEBUG_1,___debug_point_reset(DEBUG_1));
		CASE(DEBUG_2,___debug_point_reset(DEBUG_2));
		CASE(DEBUG_3,___debug_point_reset(DEBUG_3));
>>>>>>> racaljk/master
=======
		CASE(DEBUG_SERVICE_STOP,___debug_point_reset(DEBUG_SERVICE_STOP));
		CASE(DEBUG_SERVICE_START,___debug_point_reset(DEBUG_SERVICE_START));
		CASE(DEBUG_SERVICE_REINSTALL,___debug_point_reset(DEBUG_SERVICE_REINSTALL));
		CASE(OPEN_LISTEN,___debug_point_reset(OPEN_LISTEN));
>>>>>>> racaljk/master
		default:break;
	}
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
void __abrt(int _sig){
//	TerminateThread(lphdThread[0],0);
	if (_sig==SIGINT) _tprintf(_T("Received signal SIGINT\n"));
//	___debug_point_reset(DEBUG_SERVICE_STOP);
	request_client=0;
	_tprintf(_T("Uninstall service.\n"));
	Func_Service_UnInstall(false);
	TerminateThread(lphdThread[0],0);
	CloseHandle(hdPipe);
	_tprintf(_T("Program is ready to exit.\n"));
	exit(0);
}

>>>>>>> racaljk/master
inline void __show_str(TCHAR const* st,TCHAR const * _ingore){
	if (!_ingore) _tprintf(_T("%s"),st);
	else _tprintf(st,_ingore);
	system("pause");
	return ;
}
>>>>>>> racaljk/master

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

void NormalEntry(){
	SYSTEMTIME st={0,0,0,0,0,0,0,0};
	FILE * fp=NULL,*_=NULL;
<<<<<<< HEAD
	TCHAR DEFBUF(buf1,32000),DEFBUF(buf2,32000),DEFBUF(buf3,32000),DEFBUF(szline,1000);
	GetLocalTime(&st);
	_tprintf(_T("    LICENSE:MIT LICENSE\n%s\n    Copyright (C) 2016 @Too-Naive\n\n"),welcomeShow);
=======
	GetLocalTime(&st);
	_tprintf(_T("    LICENSE:MIT LICENSE\n%s\n    Copyright (C) 2016 @Too-Naive\n"),welcomeShow);
	_tprintf(_T("    Project website:%s\n"),objectwebsite);
>>>>>>> racaljk/master
	_tprintf(_T("    Bug report:sweheartiii[at]hotmail.com \n\t       Or open new issue\n\n\n"));
	_tprintf(_T("    Start replace hosts file:\n    Step1:Get System Driver..."));
	try {
		if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
			THROWERR(_T("GetEnvironmentVariable() Error!\n\tCannot get system path!"));
		_stprintf(buf1,_T("%s\\system32\\drivers\\etc\\hosts"),buf3);
		_stprintf(buf2,_T("%s\\system32\\drivers\\etc\\hosts.%04d%02d%02d.%02d%02d%02d"),
		buf3,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
		_tprintf(_T("\t\tDone.\n    Step2:Download hosts file..."));
<<<<<<< HEAD
		for (int _count=0;!Func_Download(hostsfile,DownLocated);_count++)
			if (_count>2) THROWERR(_T("DownLoad hosts file Error!"));
=======
		//download
		for (int errcunt=0;!Func_Download(hostsfile,DownLocated)&&
			!Func_Download(hostsfile1,DownLocated);errcunt++,_tprintf(pWait),
			Sleep(5000),_tprintf(_T("\tDownload hosts file...")))
					if (errcunt>2) THROWERR(_T("DownLoad hosts file Error!"));
		//end.
>>>>>>> racaljk/master
		_tprintf(_T("\t100%%\n    Step3:Change Line Endings..."));
		if (!((fp=_tfopen(DownLocated,_T("r"))) && (_=_tfopen(ChangeCTLR,_T("w")))))
			THROWERR(_T("Open file Error!"));
		while (!feof(fp)){
			_fgetts(szline,1000,fp);
			_fputts(szline,_);
		}
		fclose(fp);fclose(_);
		fp=NULL,_=NULL;
		if (!DeleteFile(DownLocated));
		if (Func_CheckDiff(ChangeCTLR,buf1)){
			_tprintf(_T("\t100%%\n\n    diff exited with value 0(0x00)\n    Finish:Hosts file Not update.\n\n"));
			DeleteFile(ChangeCTLR);
			system("pause");
			return ;
		}
		else {
			_tprintf(_T("\t100%%\n    Step4:Copy Backup File..."));
			if (!SetFileAttributes(buf1,FILE_ATTRIBUTE_NORMAL)); //for avoid CopyFile failed.
			if (!CopyFile(buf1,buf2,FALSE))
				THROWERR(_T("CopyFile() Error on copy a backup file"));
			_tprintf(_T("\t\t100%%\n    Step5:Replace Default Hosts File..."));
			if (!CopyFile(ChangeCTLR,buf1,FALSE))
				THROWERR(_T("CopyFile() Error on copy hosts file to system path"));
			if (!DeleteFile(ChangeCTLR));
			_tprintf(_T("Replace File Successfully\n"));
<<<<<<< HEAD
			
=======

>>>>>>> racaljk/master
		}
	}
	catch(expection runtimeerr){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n"),runtimeerr.Message,GetLastError());
		_tprintf(_T("\n[Debug Message]\n%s\n%s\n%s\n"),buf1,buf2,buf3);
		abort();
	}
	MessageBox(NULL,_T("Hosts File Set Success!"),_T("Congratulations!"),MB_ICONINFORMATION|MB_SETFOREGROUND);
	return ;
}

void Func_Service_UnInstall(bool _quite){
	SC_HANDLE shMang=NULL,shSvc=NULL;
<<<<<<< HEAD
	TCHAR DEFBUF(buf1,32000),DEFBUF(buf2,32000);
	try{
		if (!GetEnvironmentVariable(_T("SystemRoot"),buf2,BUFSIZ))
			THROWERR(_T("GetEnvironmentVariable() Error in UnInstall Service."));
		_stprintf(buf1,_T("%s\\hoststools.exe"),buf2);
		if (!(shMang=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)))
			THROWERR(_T("OpenSCManager() Error in Uninstall service."));
		if (!(shSvc=OpenService(shMang,Sname,SERVICE_ALL_ACCESS)))
			THROWERR(_T("OpenService() Error in Uninstall service."));
		if (!ControlService(shSvc,SERVICE_CONTROL_STOP,&ss))
			THROWERR(_T("ControlService() Error in Uninstall service."));
		Sleep(1000);//Wait for service stop
		if (!DeleteService(shSvc))
			THROWERR(_T("DeleteService() Error in UnInstall service."));
		if (!DeleteFile(buf1))
			THROWERR(_T("DeleteFile() Error in Uninstall service."));
=======
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
>>>>>>> racaljk/master
	}
	catch (expection re){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n"),
		re.Message,GetLastError());
		_tprintf(_T("\n[Debug Message]\n%s\n%s\n"),buf1,buf2);
		CloseServiceHandle(shSvc);
		CloseServiceHandle(shMang);
		if (_quite) abort();
	}
<<<<<<< HEAD
	_tprintf(_T("Service Uninstall Successfully\n"));
	CloseServiceHandle(shSvc);
	CloseServiceHandle(shMang);
=======
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
	catch (expection re){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n"),
		re.Message,GetLastError());
		CloseServiceHandle(shSvc);
		CloseServiceHandle(shMang);
		abort();
	}
	CloseServiceHandle(shSvc);
	CloseServiceHandle(shMang);
<<<<<<< HEAD
	_tprintf(_T("Exited debug mode.\n"));
>>>>>>> racaljk/master
=======
//	_tprintf(_T("Exited debug mode.(%d)\n"),_par);
>>>>>>> racaljk/master
	return ;
}


<<<<<<< HEAD
<<<<<<< HEAD
void Func_Service_Install(const TCHAR * st){
	SC_HANDLE shMang=NULL,shSvc=NULL;
	TCHAR DEFBUF(buf1,32000),DEFBUF(buf2,32000),DEFBUF(buf3,32000);
	_tprintf(_T("    LICENSE:MIT LICENSE\n    Copyright (C) 2016 @Too-Naive\n\n"));
	_tprintf(_T("    Bug report:sweheartiii[at]hotmail.com \n\t       Or open new issue\n------------------------------------------------------\n\n"));
=======
void Func_Service_Install(){
=======
void Func_Service_Install(bool _q){
>>>>>>> racaljk/master
	SC_HANDLE shMang=NULL,shSvc=NULL;
	if (_q){
		_tprintf(_T("    LICENSE:MIT LICENSE\n    Copyright (C) 2016 @Too-Naive\n\n"));
		_tprintf(_T("    Bug report:sweheartiii[at]hotmail.com \n\t       Or open new issue\n\
------------------------------------------------------\n\n"));
<<<<<<< HEAD
>>>>>>> racaljk/master
=======
	}
>>>>>>> racaljk/master
	try{
		if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
			THROWERR(_T("GetEnvironmentVariable() Error in Install Service."));
		_stprintf(buf1,_T("%s\\hoststools.exe"),buf3);
<<<<<<< HEAD
		_stprintf(buf2,_T("%s\\hoststools.exe -svc"),buf3);
<<<<<<< HEAD
		_tprintf(_T("    Step1:Copy file.\n"));
		if (!CopyFile(st,buf1,FALSE))
=======
=======
		_stprintf(buf2,_T("\"%s\\hoststools.exe\" -svc"),buf3);
		if (request_client)
			_stprintf(szline,_T("%s %s"),buf2,szParameters[11]),
			_tcscpy(buf2,szline),memset(szline,0,sizeof(szline)/sizeof(TCHAR));
>>>>>>> racaljk/master
		if (!GetModuleFileName(NULL,szline,sizeof(szline)/sizeof(TCHAR)))
			THROWERR(_T("GetModuleFileName() Error in Install Service."));
		if (_q) _tprintf(_T("    Step1:Copy file.\n"));
		if (!CopyFile(szline,buf1,FALSE))
>>>>>>> racaljk/master
			THROWERR(_T("CopyFile() Error in Install Service.(Is service has been installed?)"));
		if (_q) _tprintf(_T("    Step2:Connect to SCM.\n"));
		if (!(shMang=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)))
			THROWERR(_T("OpenSCManager() failed."));
		if (_q) _tprintf(_T("    Step3:Write service.\n"));
		if (!(shSvc=CreateService(shMang,Sname,_T("racaljk-hosts Tool"),
		SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,
			buf2,NULL,NULL,NULL,NULL,NULL))){
<<<<<<< HEAD
//			_tprintf("%ld ---\n",GetLastError());
=======
>>>>>>> racaljk/master
			if (GetLastError()==ERROR_SERVICE_EXISTS){
				if (!(shSvc=OpenService(shMang,Sname,SERVICE_ALL_ACCESS)))
					THROWERR(_T("OpenService() Error in install service."));/*
				if (!ControlService(shSvc,SERVICE_CONTROL_STOP,&ss))
					_tprintf(_T("ControlService() Error in install service."));*/
				if (!DeleteService(shSvc))
					THROWERR(_T("DeleteService() Error in Install Service."));
				CloseServiceHandle(shSvc);
				if (!(shSvc=CreateService(shMang,Sname,_T("racaljk-hosts Tool"),
				SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,
				buf2,NULL,NULL,NULL,NULL,NULL)))
<<<<<<< HEAD
						THROWERR(_T("CreateService() failed.(2)")),CloseServiceHandle(shMang);
			}
			else 
			THROWERR(_T("CreateService() failed."));
		}
		else MessageBox(NULL,_T("Service installed successfully"),_T("Congratulations!"),MB_SETFOREGROUND|MB_ICONINFORMATION);
=======
					THROWERR(_T("CreateService() failed.(2)")),CloseServiceHandle(shMang);
			}
			else
				THROWERR(_T("CreateService() failed."));
		}
		else //_T("Service installed successfully"),_T("Congratulations!"),MB_SETFOREGROUND|MB_ICONINFORMATION
			_tprintf(_T("Install service successfully.\n"));
<<<<<<< HEAD
>>>>>>> racaljk/master
		if (!(shSvc=OpenService(shMang,Sname,SERVICE_START)))
			THROWERR(_T("OpenService() Failed"));
		else
			if (!StartService(shSvc,1,SzName))
				THROWERR(_T("StartService() Failed."));
=======
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
>>>>>>> racaljk/master
	}
	catch (expection runtimeError){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
<<<<<<< HEAD
Please contact the application's support team for more information.\n"),runtimeError.Message,GetLastError());
		_tprintf(_T("\n[Debug Message]\n%s\n%s\n%s\n"),buf1,buf2,buf3);
		abort();
	}
	MessageBox(NULL,_T("Service started successfully"),_T("Congratulations!"),MB_SETFOREGROUND|MB_ICONINFORMATION);
	CloseServiceHandle(shMang);
	CloseServiceHandle(shSvc);
	return ;
}

bool Func_CheckDiff(const TCHAR *lFilePath, const TCHAR * rFilePath) throw(expection) {
	const size_t BUFFER_SIZE=2048; 
	FILE * lFile=_tfopen(lFilePath,_T("rb")),*rFile=_tfopen(rFilePath,_T("rb"));
    if(!(lFile && rFile))
        return false;
    char *lBuffer = new char[BUFFER_SIZE];
    char *rBuffer = new char[BUFFER_SIZE];
    if (!lBuffer||!rBuffer) THROWERR(_T("Can't allocate memory to buffer in diff"));
    do {
    	fread(lBuffer,sizeof(char),BUFFER_SIZE,lFile);
    	fread(rBuffer,sizeof(char),BUFFER_SIZE,rFile);
        if (memcmp(lBuffer, rBuffer, BUFFER_SIZE)||
			((!feof(lFile)&&feof(rFile))||(feof(lFile)&&!(feof(rFile))))){
            delete[] lBuffer;
            delete[] rBuffer;
		    fclose(lFile);
		    fclose(rFile);
            return false;
        }
    } while ((!feof(lFile))&&(!feof(rFile)));
    delete[] lBuffer;
    delete[] rBuffer;
    fclose(lFile);
    fclose(rFile);
    return true;
}


DWORD __stdcall HostThread(LPVOID){
	SYSTEMTIME st={0,0,0,0,0,0,0,0};
	FILE * fp=NULL,*_=NULL;
	TCHAR DEFBUF(buf1,32000),DEFBUF(buf2,32000),DEFBUF(buf3,32000),DEFBUF(szline,1000);
	Func_SetErrorFile(_T("c:\\Hosts_Tool_log.log"),_T("a+"));
	if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
		THROWERR(_T("GetEnvironmentVariable() Error!\n\tCannot get system path!"));
	_stprintf(buf1,_T("%s\\system32\\drivers\\etc\\hosts"),buf3);
=======
Please contact the application's support team for more information.\n"),
		runtimeError.Message,GetLastError());
		_tprintf(_T("\n[Debug Message]\n%s\n%s\n%s\n"),buf1,buf2,buf3);
		abort();
	}
	CloseServiceHandle(shMang);
	CloseServiceHandle(shSvc);
	if (_q) system("pause");
	return ;
}

HANDLE ___pipeopen(){
	while (1){
		if ((hdPipe = CreateFile(pipeName,GENERIC_READ|GENERIC_WRITE,0,
			NULL,OPEN_EXISTING,0,NULL))!=INVALID_HANDLE_VALUE)
			break;
		if (GetLastError()!=ERROR_PIPE_BUSY) return INVALID_HANDLE_VALUE;
		WaitNamedPipe(pipeName, 2000);
	}
	return hdPipe;
}

DWORD ___pipesentmessage(const TCHAR * szSent){
	DWORD dwReserved=PIPE_READMODE_MESSAGE;
    if (!SetNamedPipeHandleState(hdPipe,&dwReserved,NULL,NULL));
    if (!WriteFile(hdPipe,szSent,(lstrlen(szSent)+1)*sizeof(TCHAR),&dwReserved,NULL));
    return GetLastError();
}

inline DWORD ___pipeclose(){
    CloseHandle(hdPipe);
	return GetLastError();
}

DWORD __stdcall HostThread(LPVOID){
	SYSTEMTIME st={0,0,0,0,0,0,0,0};
	FILE * fp=NULL,*_=NULL;
	Func_SetErrorFile(LogFileLocate,_T("a+"));
	if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
		Func_PMNTTS(_T("GetEnvironmentVariable() Error!(GetLastError():%ld)\n\
\tCannot get system path!"),GetLastError()),abort();
	_stprintf(buf1,_T("%s\\system32\\drivers\\etc\\hosts"),buf3);
<<<<<<< HEAD
	Func_FastPMNTS(_T("Open log file.\n"));
	Func_FastPMNTS(_T("LICENSE:MIT LICENSE\n"));
	Func_FastPMNSS(_T("Copyright (C) 2016 Too-Naive\n"));
	Func_FastPMNSS(_T("Bug report:sweheartiii[at]hotmail.com\n"));
	Func_FastPMNSS(_T("           Or open new issue.(https://github.com/racaljk/hosts)\n"));
>>>>>>> racaljk/master
=======
	Func_PMNTTS(_T("[Debug Message]:%d\n"),request_client);
	if (request_client) ___pipeopen(),___pipesentmessage(_T("\nMessage from service:\n\n"));
	Func_PMNTTS(_T("Open log file.\n"));
	___checkEx(_T("LICENSE:MIT LICENSE\n"),1);
	___checkEx(_T("Copyright (C) 2016 Too-Naive\n"),0);
	___checkEx(_T("Bug report:sweheartiii[at]hotmail.com\n"),0);
	___checkEx(_T("           Or open new issue.(https://github.com/racaljk/hosts)\n"),0);
>>>>>>> racaljk/master
	while (1){
		Sleep(request_client?0:60000);//Waiting for network
		GetLocalTime(&st);
		_stprintf(buf2,_T("%s\\system32\\drivers\\etc\\hosts.%04d%02d%02d.%02d%02d%02d"),
		buf3,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
<<<<<<< HEAD
<<<<<<< HEAD
		Func_FastPMNTS(_T("Open log file.\n"));
		Func_FastPMNTS(_T("LICENSE:MIT LICENSE\n"));
		Func_FastPMNSS(_T("Copyright (C) 2016 Too-Naive\n"));
		Func_FastPMNSS(_T("Bug report:sweheartiii[at]hotmail.com\n"));
		Func_FastPMNSS(_T("           Or open new issue.(https://github.com/racaljk/hosts)\n"));
		Func_FastPMNTS(_T("Start replace hosts file.\n"));
		try {
			for (int _count=0;!Func_Download(hostsfile,DownLocated);_count++)
				if (_count>2) THROWERR(_T("DownLoad hosts file Error!"));
=======
		Func_FastPMNTS(_T("Start replace hosts file.\n"));
=======
		___autocheckmess(_T("Start replace hosts file.\n"));
>>>>>>> racaljk/master
		try {
			for (int errcunt=0;!Func_Download(hostsfile1,DownLocated)&&
				!Func_Download(hostsfile,DownLocated);errcunt++,Sleep(request_client?1000:10000))
				if (errcunt>1) THROWERR(_T("DownLoad hosts file Error!"));
<<<<<<< HEAD:hosts_tools/HostsToolforWindows/hosts_tool.cpp
		
>>>>>>> racaljk/master
=======

>>>>>>> racaljk/master:tools/WinConsole/hosts_tool.cpp
			if (!((fp=_tfopen(DownLocated,_T("r"))) && (_=_tfopen(ChangeCTLR,_T("w")))))
				THROWERR(_T("Open file Error!"));
			while (!feof(fp)){
				_fgetts(szline,1000,fp);
				_fputts(szline,_);
			}
			fclose(fp);fclose(_);
			fp=NULL,_=NULL;
			if (!DeleteFile(DownLocated));
			if (Func_CheckDiff(ChangeCTLR,buf1)){
				___autocheckmess(_T("Finish:Hosts file Not update.\n"));
				DeleteFile(ChangeCTLR);
<<<<<<< HEAD
//				return GetLastError();
=======
>>>>>>> racaljk/master
			}
			else {
				if (!SetFileAttributes(buf1,FILE_ATTRIBUTE_NORMAL));//for avoid CopyFile failed.
				if (!CopyFile(buf1,buf2,FALSE))
					THROWERR(_T("CopyFile() Error on copy a backup file"));
				if (!CopyFile(ChangeCTLR,buf1,FALSE))
					THROWERR(_T("CopyFile() Error on copy hosts file to system path"));
				if (!DeleteFile(ChangeCTLR));
				___autocheckmess(_T("Replace File Successfully\n"));
			}
<<<<<<< HEAD
<<<<<<< HEAD
		}
		catch(expection runtimeerr){
			Func_FastPMNTS(_T("\nFatal Error:\n"));
=======
//			Func_FastPMNTS(_T("heiheihei\n"));
		}
		catch(expection runtimeerr){
			Func_FastPMNTS(_T("Fatal Error:\n"));
>>>>>>> racaljk/master
			Func_FastPMNSS(_T("%s (GetLastError():%ld)\n"),runtimeerr.Message,GetLastError());
			Func_FastPMNSS(_T("Please contact the application's support team for more information.\n"));
=======
		}
		catch(expection runtimeerr){
			if (!request_client){
				Func_FastPMNTS(_T("Fatal Error:\n"));
				Func_FastPMNSS(_T("%s (GetLastError():%ld)\n"),runtimeerr.Message,GetLastError());
				Func_FastPMNSS(_T("Please contact the application's support team for more information.\n"));
			}
			else {
				_stprintf(szline,_T("Fatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n"),runtimeerr.Message,GetLastError());
				___pipesentmessage(szline);
			}
>>>>>>> racaljk/master
		}
		Sleep(request_client?5000:(29*60000));
	}
	return GetLastError();
}

void WINAPI Service_Main(DWORD,LPTSTR *){
<<<<<<< HEAD
	if ((ssh=RegisterServiceCtrlHandler(Sname,Service_Control)));
=======
	if (!(ssh=RegisterServiceCtrlHandler(Sname,Service_Control)));
>>>>>>> racaljk/master
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
<<<<<<< HEAD
<<<<<<< HEAD
	if ((hdThread=CreateThread(NULL,0,HostThread,NULL,0,NULL)));
=======
	if (!(hdThread=CreateThread(NULL,0,HostThread,NULL,0,NULL)));
>>>>>>> racaljk/master
	WaitForSingleObject(hdThread,INFINITE);
=======
	if (!(lphdThread[0]=CreateThread(NULL,0,HostThread,NULL,0,NULL)));
	WaitForSingleObject(lphdThread[0],INFINITE);
>>>>>>> racaljk/master
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
<<<<<<< HEAD
}

=======
	return ;
}
<<<<<<< HEAD
>>>>>>> racaljk/master
=======

DWORD __stdcall OpenPipeService(LPVOID){
	HANDLE hConnectEvent;
	OVERLAPPED oConnect;
	LPPIPEINST lpPipeInst;
	DWORD dwWait, cbRet;
	BOOL fSuccess, fPendingIO;
	if (!(hConnectEvent = CreateEvent(NULL,TRUE,TRUE,NULL)))
		return _tprintf(_T("CreateEvent failed with %ld.\n"), GetLastError());
	oConnect.hEvent = hConnectEvent;
	fPendingIO = CreateAndConnectInstance(&oConnect);
	while (1){
		dwWait = WaitForSingleObjectEx(hConnectEvent,INFINITE,TRUE);
		switch (dwWait){
		case 0:
			if (fPendingIO)
				if (!(fSuccess = GetOverlappedResult(hdPipe,&oConnect,&cbRet,FALSE)))
					return printf("ConnectNamedPipe (%ld)\n", GetLastError());
			if (!(lpPipeInst=(LPPIPEINST) HeapAlloc(GetProcessHeap(),0,sizeof(PIPEINST))))
				return printf("GlobalAlloc failed (%ld)\n", GetLastError());
			lpPipeInst->hPipeInst = hdPipe;
			lpPipeInst->cbToWrite = 0;
			CompletedWriteRoutine(0, 0, (LPOVERLAPPED) lpPipeInst);
			fPendingIO = CreateAndConnectInstance(&oConnect);
			break;
		case WAIT_IO_COMPLETION:
			break;
		default:
			return printf("WaitForSingleObjectEx (%ld)\n", GetLastError());
		}
	}
	return 0;
}
void WINAPI CompletedWriteRoutine(DWORD dwErr,DWORD cbWritten,LPOVERLAPPED lpOverLap){
	LPPIPEINST lpPipeInst;
	BOOL fRead = FALSE;
	lpPipeInst = (LPPIPEINST) lpOverLap;
	if ((dwErr == 0) && (cbWritten == lpPipeInst->cbToWrite)){
		fRead = ReadFileEx(lpPipeInst->hPipeInst,lpPipeInst->chRequest,
		BUFSIZE*sizeof(TCHAR),(LPOVERLAPPED) lpPipeInst,
		(LPOVERLAPPED_COMPLETION_ROUTINE) CompletedReadRoutine);
	}
	if (!fRead) DisconnectAndClose(lpPipeInst);
}

void WINAPI CompletedReadRoutine(DWORD dwErr,DWORD cbBytesRead,LPOVERLAPPED lpOverLap){
	LPPIPEINST lpPipeInst;
	BOOL fWrite = FALSE;
	lpPipeInst = (LPPIPEINST) lpOverLap;
	if ((dwErr == 0) && (cbBytesRead != 0)){
		GetAnswerToRequest(lpPipeInst);
		fWrite = WriteFileEx(lpPipeInst->hPipeInst,lpPipeInst->chReply,
			lpPipeInst->cbToWrite,(LPOVERLAPPED) lpPipeInst,
			(LPOVERLAPPED_COMPLETION_ROUTINE) CompletedWriteRoutine);
	}
	if (!fWrite) DisconnectAndClose(lpPipeInst);
}

void DisconnectAndClose(LPPIPEINST lpPipeInst){
	if (! DisconnectNamedPipe(lpPipeInst->hPipeInst))
		printf("DisconnectNamedPipe failed with %ld.\n", GetLastError());
	CloseHandle(lpPipeInst->hPipeInst);
	if (lpPipeInst != NULL)
		HeapFree(GetProcessHeap(),0, lpPipeInst);
}

BOOL CreateAndConnectInstance(LPOVERLAPPED lpoOverlap)
{
	if (!(hdPipe = CreateNamedPipe(pipeName,PIPE_ACCESS_DUPLEX |FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_MESSAGE |	PIPE_READMODE_MESSAGE |	PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,BUFSIZE*sizeof(TCHAR),BUFSIZE*sizeof(TCHAR),
		PIPE_TIMEOUT,NULL)))
		return 0*(printf("CreateNamedPipe failed with %ld.\n", GetLastError()));
	return ConnectToNewClient(hdPipe, lpoOverlap);
}

BOOL ConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo)
{
	BOOL fConnected, fPendingIO = FALSE;
	if ((fConnected = ConnectNamedPipe(hPipe, lpo)))
		return 0*printf("ConnectNamedPipe failed with %ld.\n", GetLastError());
	switch (GetLastError()){
	case ERROR_IO_PENDING:
		fPendingIO = TRUE;
		break;
	case ERROR_PIPE_CONNECTED:
		if (SetEvent(lpo->hEvent))
			break;
	default:
			return 0*printf("ConnectNamedPipe failed with %ld.\n", GetLastError());
	}
	return fPendingIO;
}

inline void GetAnswerToRequest(LPPIPEINST pipe)
{
	_tprintf( TEXT("%s"), pipe->chRequest);
	//reserved:
/*	_tprintf( TEXT("[%p] %s"), pipe->hPipeInst, pipe->chRequest);
	lstrcpyn( pipe->chReply,  TEXT("") ,BUFSIZE);
	pipe->cbToWrite = (lstrlen(pipe->chReply)+1)*sizeof(TCHAR);*/
}
>>>>>>> racaljk/master
