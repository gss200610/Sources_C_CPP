#include "funcoes.h"
#include "constantes.h" 
#include <iostream>
#include <Windows.h>
//#include <shellapi.h>
#include "Shlwapi.h"

const int BUFSIZE = 4096;

void getPathFB(char** param) {

	char path[MAX_PATH];
	
	*param = (char*)malloc( MAX_PATH * sizeof(char*) );

	GetCurrentDirectoryA(MAX_PATH, path);
	//PathAddBackslashA(path);
	printf("1 %s\n", path);

	strcpy_s(*param, MAX_PATH * sizeof(char*) + 1, path);
	printf("RETURN: %s\n", *param);
	
}


BOOL execAndWait(char* arquivo, char* Params, WORD  WindowState, int colocarAspas) {
	
	

	CHAR ReadBuffer[BUFSIZE];

	SECURITY_ATTRIBUTES Security;
	HANDLE ReadPipe, WritePipe ;
	STARTUPINFO start;
	PROCESS_INFORMATION ProcessInfo;
	char* Buffer;
	DWORD BytesRead;
	BOOL bSuccess;
	char out[] = "";

	//cout << "arquivo: " << arquivo << endl;
	//cout << "parametros: " << Params << endl;

	Security.nLength = sizeof(SECURITY_ATTRIBUTES);
	Security.bInheritHandle = TRUE;
	Security.lpSecurityDescriptor = NULL;

	if ( CreatePipe(&ReadPipe, &WritePipe, &Security, 0)) {
	    Buffer = (char*) malloc( sizeof(char*) + BUFSIZE + 1);
		ZeroMemory(&start, sizeof(start));

	}

	start.cb = sizeof(start);
	start.hStdOutput = WritePipe;
	start.hStdInput  = ReadPipe;
	start.dwFlags = STARTF_USESTDHANDLES + STARTF_USESHOWWINDOW;
	start.wShowWindow  = SW_HIDE;


	if (CreateProcess( (LPCWSTR)arquivo,
		(LPWSTR)Params,
		&Security,
		&Security,
		TRUE,
		NORMAL_PRIORITY_CLASS,
		NULL,
		NULL,
		&start,
		&ProcessInfo) )
	{

		WaitForInputIdle(ProcessInfo.hProcess, INFINITE);
		CloseHandle(ProcessInfo.hThread);

		CloseHandle(WritePipe);

		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
		//CloseHandle(ProcessInfo.hProcess);

		for (;;) {
			bSuccess = ReadFile(ReadPipe, ReadBuffer, BUFSIZE, &BytesRead, NULL);
			if (!bSuccess || BytesRead == 0) break;

			//std::string s(ReadBuffer, BytesRead);
			//out += s;
			//break;
		}

		bSuccess = TRUE;



	}

	
	CloseHandle(ProcessInfo.hProcess);

	CloseHandle(ReadPipe);

	


	return bSuccess;

}


BOOL fileExiste(char* arquivo) {
	

	return TRUE;
}

