#pragma once
#ifndef FUNCOES_H
#define FUNCOES_H

#include <string.h>
#include <string>
#include <Windows.h>
#include <Shlwapi.h>
#include <minwindef.h>

#pragma warning( disable : 4800 ) // stupid warning about bool




void getPathFB(char**); 

BOOL execAndWait(char* , char* , WORD, int);

BOOL fileExiste(char* arquivo);



#endif // !FUNCOES_H
