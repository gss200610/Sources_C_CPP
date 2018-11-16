#include <stdio.h>
#include "funcoes.h"
#include "Shlwapi.h"
int main(int argc, char* argv[])
{

	char* pathApp;
	char** ptPath = &pathApp;

	getPathFB(ptPath);
	printf("%s",  pathApp);

	printf("\n\nexiste: %d\n\n", PathFileExistsA("C:\\") );
	return 0;
}