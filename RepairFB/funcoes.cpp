#include "pch.h"
#include "funcoes.h"
#include "constantes.h" 
#include <iostream>
#include <Windows.h>
#include <shellapi.h>
#include <Shlwapi.h>
#include <fstream>
#include <atlbase.h>
#include <atlconv.h>



std::string getPathFB(){

    return "C:\\Program Files (x86)\\Firebird\\Firebird_2_5\\bin\\";

}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

BOOL execAndWait(std::string arquivo, std::string Params, WORD  WindowState, bool colocarAspas) {
	
	const int BUFSIZE = 4096;

	CHAR ReadBuffer[BUFSIZE];

	SECURITY_ATTRIBUTES Security;
	HANDLE ReadPipe, WritePipe ;
	STARTUPINFO start;
	PROCESS_INFORMATION ProcessInfo;
	CHAR Buffer;
	DWORD BytesRead, Apprunning;
    std::string AMemo ;
	BOOL bSuccess;
	std::string out = "";

	Security.nLength = sizeof(SECURITY_ATTRIBUTES);
	Security.bInheritHandle = true;
	Security.lpSecurityDescriptor = NULL;

	if ( CreatePipe(&ReadPipe, &WritePipe, &Security, 0)) {
	    Buffer = (CHAR) malloc( sizeof(CHAR) + BUFSIZE + 1);
		ZeroMemory(&start, sizeof(start));

	}

	start.cb = sizeof(start);
	start.hStdOutput = WritePipe;
	start.hStdInput  = ReadPipe;
	start.dwFlags = STARTF_USESTDHANDLES + STARTF_USESHOWWINDOW;
	start.wShowWindow  = SW_HIDE;


	if (CreateProcess(ATL::CA2W(arquivo.c_str()),
		ATL::CA2W(Params.c_str()),
		&Security,
		&Security,
		true,
		NORMAL_PRIORITY_CLASS,
		NULL,
		NULL,
		&start,
		&ProcessInfo) )
	{

		WaitForInputIdle(ProcessInfo.hProcess, INFINITE);
		CloseHandle(ProcessInfo.hThread);

		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
		//CloseHandle(ProcessInfo.hProcess);

		for (;;) {
			bSuccess = ReadFile(ReadPipe, ReadBuffer, BUFSIZE, &BytesRead, NULL);
			if (!bSuccess || BytesRead == 0) break;

			std::string s(ReadBuffer, BytesRead);
			out += s;
			break;
		}




	}

	cout << out << endl;
	
	CloseHandle(ProcessInfo.hProcess);
	
	CloseHandle(ReadPipe);
	CloseHandle(WritePipe);
	


	return bSuccess;

}


BOOL fileExiste(std::string arquivo) {
	
	ofstream arq;
	uintmax_t tamanho = 0;
	arq.open(arquivo.c_str());
	if (arq.is_open() ) {
		arq.close();
		return true;
		
	}else
	
	return false;
}
