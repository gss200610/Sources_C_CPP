/*
cls
echo. criando arquivo zip
if exist "C:\BatchApkTool\Update_twrp\Update_twrp.zip" delete C:\BatchApkTool\Update_twrp\Update_twrp.zip

"C:\Program Files\7-Zip\7z.exe" a -aoa -tzip C:\BatchApkTool\Update_twrp\Update_twrp.zip "C:\BatchApkTool\Update_twrp\*"
echo.
echo. ***** SCRIPT UPDATE ********
echo. Removendo zip antigo.....
adb shell rm -f /storage/CFB4-9BCF/traducao/Update_twrp.zip
echo. Enviando arquivo novo.....
adb push "C:\BatchApkTool\Update_twrp\Update_twrp.zip" /storage/CFB4-9BCF/traducao/
echo. Reiniciando o celular...
adb reboot recovery
echo. FINALIZADO!!!!

*/

// MyADBTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Funcoes.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



char escreverTexto(char texto, int count) {

	char *retorno;
	for (int i = 0; i <= count; i++)
	{
		putchar(texto);
	}
	
	return  texto;

}
int main()
{
	int opcao = 0;
	system("cls");
	escreverTexto('*', 80);

	cout << "\n\n\t\t\tMenu do sistema\n" << endl;
	do {
		cout << "\t\t\t1 - Update_twrp.zip\n" << endl;
		cout << "\t\t\t2 - Update_data_twrp.zip\n" << endl;
		cout << "\t\t\t3 - Sair\n" << endl;

		cout << "Digite a opcao:";
		cin >> opcao;
		fflush(stdin);

		switch (opcao)
		{
		case 1:
			copiarUpdate_Normal();
			break;
		case 2:
			copiarUpdate_Data();
			break;
		default:
			cout << "Opção inválida"<<endl;
		}

	} while (opcao != 3);



}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
