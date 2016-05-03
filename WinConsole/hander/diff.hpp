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

#pragma once
#include <tchar.h>
#include <stdio.h>
#include <memory.h>

bool Func_CheckDiff(const TCHAR *lFilePath, const TCHAR * rFilePath) throw(){
	const size_t BUFFER_SIZE=2048;
	FILE * lFile=_tfopen(lFilePath,_T("rb")),*rFile=_tfopen(rFilePath,_T("rb"));
	if(!(lFile && rFile))
		return false;
	char *lBuffer = new char[BUFFER_SIZE];
	char *rBuffer = new char[BUFFER_SIZE];
	if (!lBuffer||!rBuffer)
		_tprintf(_T("Can't allocate memory to buffer in Func_diff\n")),abort();
	do {
		memset(lBuffer,0,BUFFER_SIZE);
		memset(rBuffer,0,BUFFER_SIZE);
		fread(lBuffer,sizeof(char),BUFFER_SIZE,lFile);
		fread(rBuffer,sizeof(char),BUFFER_SIZE,rFile);
		if (memcmp(lBuffer, rBuffer, BUFFER_SIZE)||
			((!feof(lFile)&&feof(rFile))||(feof(lFile)&&!(feof(rFile))))){
			delete [] lBuffer;
			delete [] rBuffer;
			fclose(lFile);
			fclose(rFile);
			return false;
		}
	} while ((!feof(lFile))&&(!feof(rFile)));
	delete [] lBuffer;
	delete [] rBuffer;
	fclose(lFile);
	fclose(rFile);
	return true;
}
