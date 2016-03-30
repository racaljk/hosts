//main.cpp
//Author:qdxllecrn E-mail:sweheartiii@hotmail.com
//Last update:Dec. 24th ,2015
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
TCHAR Sname[]=_T("racaljk-hoststool");

SERVICE_STATUS_HANDLE ssh;
SERVICE_STATUS ss;
HANDLE hdThread,hdProcess;

void WINAPI Service_Main(DWORD, LPTSTR *);
void WINAPI Service_Control(DWORD);
void Func_Service_Install(const TCHAR *);
//void Func_Exit();
DWORD ______EnablePrivilege() ;

int _tmain(int argc,LPTSTR * argv)
{
	SERVICE_TABLE_ENTRY STE[2]={{Sname,(LPSERVICE_MAIN_FUNCTION)Service_Main},{NULL,NULL}};
//	atexit(Func_Exit);
	OSVERSIONINFO _os_={sizeof(OSVERSIONINFO),0,0,0,0,_T("")};
	GetVersionEx(&_os_);
	if (argc==1)
			ShellExecute(NULL,(_os_.dwMajorVersion==5)?_T("open"):_T("runas"),argv[0],_T("-i"),NULL,SW_SHOWNORMAL);
	else
		if (!_tcscmp(_T("-i"),argv[1])) Func_Service_Install(argv[0]),exit(EXIT_SUCCESS);
		else
			if (!_tcscmp(_T("-svc"),argv[1])) ______EnablePrivilege(),StartServiceCtrlDispatcher(STE),exit(EXIT_SUCCESS);
	return 0;
}

void Func_Service_Install(const TCHAR * st)
{
	SC_HANDLE shMang=NULL,shSvc=NULL;
	if (!CopyFile(st,_T("c:\\windows\\hosttools.exe"),FALSE));
	if (!(shMang=OpenSCManagerA(NULL,NULL,SC_MANAGER_ALL_ACCESS)))
		_tprintf(_T("OpenSCManager failed (%ld)\n"), GetLastError()),exit(EXIT_FAILURE);
	if (!(shSvc=CreateService(shMang,Sname,_T("racaljk-hosts tool. Auto check hosts file update."),
	SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,_T("\"c:\\windows\\hosttools.exe\" -svc "),NULL,NULL,NULL,NULL,NULL);)){
		_tprintf(_T("CreateService failed (%ld)\n"), GetLastError());//,CloseServiceHandle(shMang),exit(EXIT_FAILURE);
		if (GetLastError()==1073l){
			if (!(shSvc=OpenService(shMang,Sname,SERVICE_ALL_ACCESS)));
			if (!DeleteService(shSvc));
			if (!(shSvc=CreateService(shMang,Sname,_T("Protect roommate Plan A"),SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,"\"c:\\windows\\hosttools.exe\" -svc ",NULL,NULL,NULL,NULL,NULL)));
					_tprintf(_T("CreateService failed (%ld)\n"), GetLastError()),CloseServiceHandle(shMang),abort();
		}
	}
	else _tprintf(_T("Service installed successfully\n"));
	if (!(shSvc=OpenService(shMang,Sname,SERVICE_START)))
		_tprintf(_T("OpenService Failed (%ld)\n"),GetLastError());
	else
		if (!StartService(shSvc,0,NULL))
			_tprintf(_T("StartService Failed (%ld)\n"),GetLastError());
		else
			_tprintf(_T("Service started successfully!\n"));
	CloseServiceHandle(shMang);
	CloseServiceHandle(shSvc);
	return ;
}


DWORD CALLBACK Main_Thread(LPVOID)
{
	return GetLastError();
}

void WINAPI Service_Main(DWORD,LPTSTR *){
	if ((ssh=RegisterServiceCtrlHandler(Sname,Service_Control)));
	ss.dwServiceType=SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState=SERVICE_START_PENDING;
	ss.dwControlsAccepted=SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_SHUTDOWN;
	ss.dwServiceSpecificExitCode=0;
	ss.dwWin32ExitCode=0;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=1000;
	SetServiceStatus(ssh,&ss);
	hdThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Main_Thread,NULL,0,NULL);
	ss.dwCurrentState=SERVICE_RUNNING;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=0;
	SetServiceStatus(ssh,&ss);
	WaitForSingleObject(hdThread,INFINITE);
	CloseHandle(hdThread);
	return ;
}



void WINAPI Service_Control(DWORD dwControl){
	switch (dwControl)
	{
		case SERVICE_CONTROL_SHUTDOWN:
		case SERVICE_CONTROL_STOP:
			TerminateThread(hdThread,0);
			ss.dwCurrentState=SERVICE_STOPPED;
			ss.dwCheckPoint=0;
			ss.dwWaitHint=0;
			SetServiceStatus(ssh,&ss);
		default:break;
	}
}

