// RepairFB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "constantes.h"
#include <iostream>
#include "funcoes.h"
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <Windows.h>
#include <shellapi.h>
#include <sstream>
#include <experimental/filesystem>
#include <cstring>
#include <atlbase.h>
#include <atlconv.h>
#define UNUSED( x ) ( &reinterpret_cast< const int& >( x ) )

#define BUFSIZE 4096
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;
HANDLE g_hChildStd_ERR_Rd = NULL;
HANDLE g_hChildStd_ERR_Wr = NULL;

using namespace std;

//const std::string PATH_FB = "D:\\CLIENTES\\JUVENIL\\SERVIDOR.FDB";
const std::string GFIX_FULL = " -v -full -user SYSDBA -pass \"masterkey\" ";



PROCESS_INFORMATION CreateChildProcess(std::string app, std::string pCmd);
void ReadFromPipe(PROCESS_INFORMATION);

int main(int argc, char ** argv)
{
	ofstream arquivo;
	std::string strfb = "";
	std::string pathFB = "";
	stringstream ss("");


	cout << pathApp << endl;

	if ( argv[1] !=  NULL)
	  ss << argv[1];

	cout << "ss : " << ss.str() << endl;
	if (ss.rdbuf()->in_avail() > 0 )
	{
		cout << "ok" << endl;
		pathFB = ss.str().c_str();
	}
	else {
		cout << "else" << endl;
		pathFB = "D:\\CLIENTES\\JUVENIL\\SERVIDOR.FDB";
	}

	cout << "existe: " << fileExiste(pathFB) << endl;

	cout << "PathFB: " << pathFB << endl;
	
	string app_fb =  getPathFB() ;
	app_fb += "gfix.exe";

	//strfb += getPathFB();
	//strfb += "gfix.exe";
	//strfb = "\"" + strfb + "\" ";
	//strfb = "\"" + strfb + "\" ";

	strfb += GFIX_FULL;
	strfb += pathFB;
	//strfb += " -Y log.txt";

	cout << strfb << endl;




	cout << "rodando : " << execAndWait(app_fb, strfb, SW_SHOWNORMAL) << endl;
	//ReadFromPipe(piProcInfo);



	cout << strfb << endl;
	return 0;
}

// Create a child process that uses the previously created pipes
//  for STDERR and STDOUT.

PROCESS_INFORMATION CreateChildProcess(std::string app, std::string pCmd) {
	// Set the text I want to run
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi = {0};
	std::string  CmdLine;
	bool bSuccess = FALSE;
	/* Coloca o nome do arquivo entre aspas. Isto é necessário devido aos espaços contidos em nomes longos*/

	
	

	si.cb = sizeof(si);

	si.hStdError = g_hChildStd_ERR_Wr;
	si.hStdOutput = g_hChildStd_OUT_Wr;
	si.dwFlags |= STARTF_USESTDHANDLES;

	bSuccess = CreateProcess(ATL::CA2W(app.c_str()), ATL::CA2W(pCmd.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE | CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if (bSuccess)
	{
		// Wait 2 minutes or something for the process to complete
		::WaitForSingleObject(pi.hProcess, INFINITE);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		
		CloseHandle(g_hChildStd_ERR_Wr);
		CloseHandle(g_hChildStd_OUT_Wr);
	}
	else
	{
		DWORD dwLast = GetLastError();
		printf("Error %d", dwLast);
	}
	return pi;
}

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT. 
// Stop when there is no more data. 
void ReadFromPipe(PROCESS_INFORMATION piProcInfo) {
	DWORD dwRead;
	CHAR chBuf[BUFSIZE];
	bool bSuccess = FALSE;
	std::string out = "", err = "";
	for (;;) {
		bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) break;

		std::string s(chBuf, dwRead);
		out += s;
	}
	dwRead = 0;
	for (;;) {
		bSuccess = ReadFile(g_hChildStd_ERR_Rd, chBuf, BUFSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) break;

		std::string s(chBuf, dwRead);
		err += s;

	}
	std::cout << "stdout:" << out << std::endl;
	std::cout << "stderr:" << err << std::endl;
	std::cout << "erro pipe : " << GetLastError() << endl;
}

