#include "parseCmd.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	int result;
	pCallback p = parseCallback;
	parseData parseData;

	parseData.key[0] = (char*) "TYPE";
	parseData.key[1] = (char*) "LSTART";
	parseData.key[2] = (char*) "LEND";
	parseData.key[3] = (char*) "LCONSTANT";
	parseData.key[4] = (char*) "LEFTANGLE";
	parseData.key[5] = (char*) "RIGHTANGLE";
	parseData.key[6] = (char*) "XO";
	parseData.key[7] = (char*) "YO";
	parseData.key[8] = (char*) "XF";
	parseData.key[9] = (char*) "YF";





	result = parseCmdLine(argc, argv, p, &parseData);
	if (result == ERROR1)
		cout << "Error tipo 1, se ha ingresado una opcion sin valor" << endl;
	else if (result == ERROR2)
		cout << "Error tipo 2, se ha ingresado una opcion sin clave" << endl;
	else if (result == ERROR3)
		cout << "Error tipo 3, los datos ingresados no corresponden con nuestra base de datos" << endl;
	else
		cout << "Todo joya." << endl;

	getchar();

	return 0;
}