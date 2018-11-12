#pragma once
#ifndef FUNCOES_H
#define FUNCOES_H

#include <string.h>
#include <string>
#include <Windows.h>
#include <Shlwapi.h>
using namespace std;

#pragma warning( disable : 4800 ) // stupid warning about bool

static struct Handles_Processo
{
	HANDLE g_hChildStd_OUT_Rd;
	HANDLE g_hChildStd_OUT_Wr;
	HANDLE g_hChildStd_ERR_Rd;
	HANDLE g_hChildStd_ERR_Wr;

}estrutura = { NULL, NULL, NULL, NULL };


typedef struct Handles_Processo HProcesso;

std::string getPathFB(); 

BOOL execAndWait(std::string FileName, std::string Params, WORD  WindowState, bool colocarAspas= FALSE);
std::wstring s2ws(const std::string& s);

BOOL fileExiste(std::string arquivo);



#endif // !FUNCOES_H
