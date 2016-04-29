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
//ptrerr.hpp

#pragma once

#include <stdio.h>
#include <tchar.h>
#include <windows.h>


FILE * ptr_ErrorFileStream=stderr;
bool is_ErrorFileSet=0;
const TCHAR * sz__ErrorFileName__=NULL;
const TCHAR * sz__ErrorFileStream__=NULL;

FILE * Func_SetErrorFile(const TCHAR*, const TCHAR*);
inline void * __fastcall ___Func_Close_File_Stream(FILE *) throw();
inline int __fastcall ___Func_PrintErrorTimeToFileStream(FILE *) throw();
inline void * ___Func__Check_File_Set(void);

#define __BEGIN__ Func_SetErrorFileEx(sz__ErrorFileName__,sz__ErrorFileStream__)
#define __END__ ___Func_Close_File_Stream(NULL)

#define Func_PETTFS ___Func_PrintErrorTimeToFileStream
#define Func_PETTStdout \
		Func_PETTFS(stdout)
#define Func_PETTStderr \
		Func_PETTFS(stderr)
#define Func_PET(___ptr_fp) \
		Func_PETTFS(___ptr_fp)

#define Func_FastPETTS(___ptr_fp) \
		__BEGIN__, \
		Func_PET(___ptr_fp), \
		__END__
#define Func_FastPETTSS \
		__BEGIN__, \
		Func_PET(ptr_ErrorFileStream),\
		__END__


#ifndef _MSC_VER

	#define Func_PrintMessage(___ptr_fp,arg...) \
		_ftprintf(___ptr_fp, ##arg)
	#define Func_PM Func_PrintMessage
	#define Func_PMNT(___ptr_fp,arg...) \
		___Func_PrintErrorTimeToFileStream(___ptr_fp), \
		_ftprintf(___ptr_fp, ##arg)
	#define Func_PMNTTStdout(arg...) \
		Func_PMNT(stdout, ##arg)
	#define Func_PMNTTStderr(arg...) \
		Func_PMNT(stderr, ##arg)
	#define Func_PMNTTS(arg...) \
		Func_PMNT(ptr_ErrorFileStream, ##arg)

	#define Func_FastPMNT(___ptr_fp,arg...) \
		__BEGIN__, \
		Func_PMNT(___ptr_fp, ##arg), \
		__END__
	#define Func_FastPMNTS(arg...) \
		Func_FastPMNT(ptr_ErrorFileStream, ##arg)

	#define Func_PrintMessageNeedSpace(___ptr_fp,arg...) \
		_ftprintf(___ptr_fp, _T("                    ")), \
		_ftprintf(___ptr_fp, ##arg)
	#define Func_PMNS(___ptr_fp,arg...) \
		Func_PrintMessageNeedSpace(___ptr_fp, ##arg)
	#define Func_PMNStdout(arg...) \
		Func_PMNS(stdout, ##arg)
	#define Func_PMNStderr(arg...) \
		Func_PMNS(stderr, ##arg)
	#define Func_PMNSS(arg...) \
		Func_PMNS(ptr_ErrorFileStream, ##arg)

	#define Func_FastPMNS(___ptr_fp,arg...) \
		__BEGIN__, \
		Func_PMNS(___ptr_fp, ##arg), \
		__END__
	#define Func_FastPMNSS(arg...) \
		Func_FastPMNS(ptr_ErrorFileStream, ##arg)

#else

	#define Func_PrintMessage(___ptr_fp,...) \
		_ftprintf(___ptr_fp, ##__VA_ARGS__)
	#define Func_PM Func_PrintMessage
	#define Func_PMNT(___ptr_fp,...) \
		___Func_PrintErrorTimeToFileStream(___ptr_fp), \
		_ftprintf(___ptr_fp, ##__VA_ARGS__)
	#define Func_PMNTTStdout(...) \
		Func_PMNT(stdout, ##__VA_ARGS__)
	#define Func_PMNTTStderr(...) \
		Func_PMNT(stderr, ##__VA_ARGS__)
	#define Func_PMNTTS(...) \
		Func_PMNT(ptr_ErrorFileStream, ##__VA_ARGS__)

	#define Func_FastPMNT(___ptr_fp,...) \
		__BEGIN__, \
		Func_PMNT(___ptr_fp, ##__VA_ARGS__), \
		__END__
	#define Func_FastPMNTS(...) \
		Func_FastPMNT(ptr_ErrorFileStream, ##__VA_ARGS__)

	#define Func_PrintMessageNeedSpace(___ptr_fp,...) \
		_ftprintf(___ptr_fp, _T("                    ")), \
		_ftprintf(___ptr_fp, ##__VA_ARGS__)
	#define Func_PMNS(___ptr_fp,...) \
		Func_PrintMessageNeedSpace(___ptr_fp, ##__VA_ARGS__)
	#define Func_PMNStdout(...) \
		Func_PMNS(stdout, ##__VA_ARGS__)
	#define Func_PMNStderr(...) \
		Func_PMNS(stderr, ##__VA_ARGS__)
	#define Func_PMNSS(...) \
		Func_PMNS(ptr_ErrorFileStream, ##__VA_ARGS__)

	#define Func_FastPMNS(___ptr_fp,...) \
		__BEGIN__, \
		Func_PMNS(___ptr_fp, ##__VA_ARGS__), \
		__END__
	#define Func_FastPMNSS(...) \
		Func_FastPMNS(ptr_ErrorFileStream, ##__VA_ARGS__)

#endif


inline void * ___Func__Check_File_Set(void){
	if (!is_ErrorFileSet) SetLastError(ERROR_FILE_OFFLINE);
	return NULL;
}

inline void * __fastcall ___Func_Close_File_Stream(FILE * ___ptr_fp) throw(){
	if (!___ptr_fp && ptr_ErrorFileStream) fclose(ptr_ErrorFileStream);
	else fclose(___ptr_fp);
	return NULL;
}



FILE * Func_SetErrorFileEx(const TCHAR * _FileName_,const TCHAR * _StreamStatus){
	if (!(ptr_ErrorFileStream=_tfopen(_FileName_,_StreamStatus)))
		MessageBox(NULL,_T("_tfopen() Error!"),_T("Fatal Error!"),MB_SETFOREGROUND|MB_ICONSTOP);
	return ptr_ErrorFileStream;
}

FILE * Func_SetErrorFile(const TCHAR * _FileName_,const TCHAR * _StreamStatus){
	sz__ErrorFileName__=_FileName_;
	sz__ErrorFileStream__=_StreamStatus;
	if (!(ptr_ErrorFileStream=_tfopen(_FileName_,_StreamStatus)))
		MessageBox(NULL,_T("_tfopen() Error!"),_T("Fatal Error!"),MB_SETFOREGROUND|MB_ICONSTOP);
	return ptr_ErrorFileStream;
}

inline int __fastcall ___Func_PrintErrorTimeToFileStream(FILE * ___ptr_fp) throw(){
	SYSTEMTIME _st_={0,0,0,0,0,0,0,0};
	GetLocalTime(&_st_);
	return _ftprintf(___ptr_fp,_T("%04d/%02d/%02d %02d:%02d:%02d "),_st_.wYear,_st_.wMonth,
	_st_.wDay,_st_.wHour,_st_.wMinute,_st_.wSecond);
}
