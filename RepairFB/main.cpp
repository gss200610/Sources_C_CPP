#include <iostream>
#include "funcoes.h"
#include "funcoes.cpp"
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <Windows.h>
#include <shellapi.h>
#include <sstream>

#define UNUSED( x ) ( &reinterpret_cast< const int& >( x ) )

using namespace std;

const std::string PATH_FB = "D:\\CLIENTES\\JUVENIL\\SERVIDOR.FDB";
const std::string GFIX_FULL = "-v -full -user SYSDBA -pass \"masterkey\" ";

int main(int argc, char ** argv)
{
    ofstream arquivo;
    std::string strfb = "";
    stringstream ss("");

    cout << argc << endl;
    ss << argv[1];

    cout << "ss : " << ss.str() << endl;    
    if( ss.str() != " " )
    {
      cout << "ok" << endl;
      strfb = ss.str().c_str();
    }else{
      cout << "else" << endl;
      strfb = getPathFB();
    }
    


    strfb += "gfix.exe";
    strfb = "\"" + strfb + "\" ";
    strfb += GFIX_FULL;
    strfb += PATH_FB;

    cout << strfb << endl;

    arquivo.open("log.txt");
    arquivo << strfb;
    arquivo.close();


  cout << "executando: " << execAndWait(strfb, "", SW_SHOWNORMAL)<< endl;

    cout << strfb << endl;
    return 0;
}

