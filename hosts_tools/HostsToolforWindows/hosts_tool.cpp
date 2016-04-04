//Copyright (C) 2016 Too-Naive 
//E-mail:sweheartiii@hotmail.com


#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "download.hpp"
#include <tchar.h>
#include <stdlib.h>
#include "ptrerr.hpp"


#define WIN32_LEAN_AND_MEAN

#define DEFBUF(x,y) x[y]=_T("")
#define THROWERR(x) throw expection(x)
#define hostsfile _T("https://raw.githubusercontent.com/racaljk/hosts/master/hosts")
#define Shell(x) ShellExecute(NULL,(_os_.dwMajorVersion<=5)?_T("open"):_T("runas"),argv[0],_T(x),NULL,SW_SHOWNORMAL)

#define CASE(x,y) case x : y; break;

#define DownLocated _T(".\\hosts")
#define ChangeCTLR _T(".\\hostsq")


struct expection{
	const TCHAR *Message;
	expection(const TCHAR * _1){
		this->Message=_1;
	}
};

#define SHOW_HELP "\n\
Usage: hosts_tool [-fi | -fu | -h]\n\n\n\
Options:\n\
    -h  : Show this help message.\n\
    -fi : Install Auto-Update hosts service(Service Name:%s).\n\
    -fu : uninstall service.\n\n\n\
    Copyright (C) 2016 @Too-Naive\n\
    License:MIT LICENSE\n\n\n"


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

TCHAR Sname[]=_T("racaljk-hoststool");
TCHAR const *SzName[]={
	Sname
};


SERVICE_STATUS_HANDLE ssh;
SERVICE_STATUS ss;
HANDLE hdThread=INVALID_HANDLE_VALUE;


int __fastcall __Check_Parameters(int,TCHAR const**);
void WINAPI Service_Main(DWORD, LPTSTR *);
void WINAPI Service_Control(DWORD);
DWORD CALLBACK Main_Thread(LPVOID);
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
};

int __fastcall __Check_Parameters(int argc,TCHAR const **argv){
	if (argc==1) return EXEC_START_NORMAL;
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
		default:break;
	}
	return 0;
}


void NormalEntry(){
	SYSTEMTIME st={0,0,0,0,0,0,0,0};
	FILE * fp=NULL,*_=NULL;
	TCHAR DEFBUF(buf1,32000),DEFBUF(buf2,32000),DEFBUF(buf3,32000),DEFBUF(szline,1000);
	GetLocalTime(&st);
	_tprintf(_T("    LICENSE:MIT LICENSE\n%s\n    Copyright (C) 2016 @Too-Naive\n\n"),welcomeShow);
	_tprintf(_T("    Bug report:sweheartiii[at]hotmail.com \n\t       Or open new issue\n\n\n"));
	_tprintf(_T("    Start replace hosts file:\n    Step1:Get System Driver..."));
	try {
		if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
			THROWERR(_T("GetEnvironmentVariable() Error!\n\tCannot get system path!"));
		_stprintf(buf1,_T("%s\\system32\\drivers\\etc\\hosts"),buf3);
		_stprintf(buf2,_T("%s\\system32\\drivers\\etc\\hosts.%04d%02d%02d.%02d%02d%02d"),
		buf3,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
		_tprintf(_T("\t\tDone.\n    Step2:Download hosts file..."));
		for (int _count=0;!Func_Download(hostsfile,DownLocated);_count++)
			if (_count>2) THROWERR(_T("DownLoad hosts file Error!"));
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

void Func_Service_UnInstall(){
	SC_HANDLE shMang=NULL,shSvc=NULL;
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
	}
	catch (expection re){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
Please contact the application's support team for more information.\n"),
		re.Message,GetLastError());
		_tprintf(_T("\n[Debug Message]\n%s\n%s\n"),buf1,buf2);
		CloseServiceHandle(shSvc);
		CloseServiceHandle(shMang);
		abort();
	}
	_tprintf(_T("Service Uninstall Successfully\n"));
	CloseServiceHandle(shSvc);
	CloseServiceHandle(shMang);
	return ;
}


void Func_Service_Install(const TCHAR * st){
	SC_HANDLE shMang=NULL,shSvc=NULL;
	TCHAR DEFBUF(buf1,32000),DEFBUF(buf2,32000),DEFBUF(buf3,32000);
	_tprintf(_T("    LICENSE:MIT LICENSE\n    Copyright (C) 2016 @Too-Naive\n\n"));
	_tprintf(_T("    Bug report:sweheartiii[at]hotmail.com \n\t       Or open new issue\n------------------------------------------------------\n\n"));
	try{
		if (!GetEnvironmentVariable(_T("SystemRoot"),buf3,BUFSIZ))
			THROWERR(_T("GetEnvironmentVariable() Error in Install Service."));
		_stprintf(buf1,_T("%s\\hoststools.exe"),buf3);
		_stprintf(buf2,_T("%s\\hoststools.exe -svc"),buf3);
		_tprintf(_T("    Step1:Copy file.\n"));
		if (!CopyFile(st,buf1,FALSE))
			THROWERR(_T("CopyFile() Error in Install Service.(Is service has been installed?)"));
		_tprintf(_T("    Step2:Connect to SCM.\n"));
		if (!(shMang=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)))
			THROWERR(_T("OpenSCManager() failed."));
		_tprintf(_T("    Step3:Write service.\n"));
		if (!(shSvc=CreateService(shMang,Sname,_T("racaljk-hosts Tool"),
		SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,
			buf2,NULL,NULL,NULL,NULL,NULL))){
//			_tprintf("%ld ---\n",GetLastError());
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
						THROWERR(_T("CreateService() failed.(2)")),CloseServiceHandle(shMang);
			}
			else 
			THROWERR(_T("CreateService() failed."));
		}
		else MessageBox(NULL,_T("Service installed successfully"),_T("Congratulations!"),MB_SETFOREGROUND|MB_ICONINFORMATION);
		if (!(shSvc=OpenService(shMang,Sname,SERVICE_START)))
			THROWERR(_T("OpenService() Failed"));
		else
			if (!StartService(shSvc,1,SzName))
				THROWERR(_T("StartService() Failed."));
	}
	catch (expection runtimeError){
		_tprintf(_T("\nFatal Error:\n%s (GetLastError():%ld)\n\
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
	while (1){
		Sleep(60000);//Waiting for network
		GetLocalTime(&st);
		_stprintf(buf2,_T("%s\\system32\\drivers\\etc\\hosts.%04d%02d%02d.%02d%02d%02d"),
		buf3,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
		Func_FastPMNTS(_T("Open log file.\n"));
		Func_FastPMNTS(_T("LICENSE:MIT LICENSE\n"));
		Func_FastPMNSS(_T("Copyright (C) 2016 Too-Naive\n"));
		Func_FastPMNSS(_T("Bug report:sweheartiii[at]hotmail.com\n"));
		Func_FastPMNSS(_T("           Or open new issue.(https://github.com/racaljk/hosts)\n"));
		Func_FastPMNTS(_T("Start replace hosts file.\n"));
		try {
			for (int _count=0;!Func_Download(hostsfile,DownLocated);_count++)
				if (_count>2) THROWERR(_T("DownLoad hosts file Error!"));
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
				Func_FastPMNTS(_T("Finish:Hosts file Not update.\n"));
				DeleteFile(ChangeCTLR);
//				return GetLastError();
			}
			else {
				if (!SetFileAttributes(buf1,FILE_ATTRIBUTE_NORMAL)); //for avoid CopyFile failed.
				if (!CopyFile(buf1,buf2,FALSE))
					THROWERR(_T("CopyFile() Error on copy a backup file"));
				if (!CopyFile(ChangeCTLR,buf1,FALSE))
					THROWERR(_T("CopyFile() Error on copy hosts file to system path"));
				if (!DeleteFile(ChangeCTLR));
				Func_FastPMNTS(_T("Replace File Successfully\n"));
			}
		}
		catch(expection runtimeerr){
			Func_FastPMNTS(_T("\nFatal Error:\n"));
			Func_FastPMNSS(_T("%s (GetLastError():%ld)\n"),runtimeerr.Message,GetLastError());
			Func_FastPMNSS(_T("Please contact the application's support team for more information.\n"));
		}
		Sleep(29*60000);
	}
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
	ss.dwCurrentState=SERVICE_RUNNING;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=0;
	SetServiceStatus(ssh,&ss);
	if ((hdThread=CreateThread(NULL,0,HostThread,NULL,0,NULL)));
	WaitForSingleObject(hdThread,INFINITE);
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
			TerminateThread(hdThread,0);
			ss.dwCurrentState=SERVICE_STOPPED;
			ss.dwCheckPoint=0;
			ss.dwWaitHint=0;
			SetServiceStatus(ssh,&ss);
		default:break;
	}
}

