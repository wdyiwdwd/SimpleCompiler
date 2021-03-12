#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "driver.h"
#include "symbol.h"
#include "signary.h"
#include "tempTable.h"
#include "Qualdruple.h"
#include "dataInit.h"
#include <cstdio>

using namespace std;
using namespace CP;

extern Signary sigTable;
extern TempTable tempTable;
extern Qualdruples qualdruples;
DataInit dataInit;

int main(const int argc, const char **argv)
{
	/** check for the right # of arguments **/
	if (argc == 2)
	{
		cout << "We Specify filename in Raw Code" << endl;
		return EXIT_FAILURE;
	}
	sigTable.enterScope();
	tempTable.enterScope();
	Driver driver;
	ifstream stream("test_code.ourcpp");
	//ofstream ostream("output.decl");
	freopen("output.decl", "w", stdout);
	driver.parse(stream);
	beforeLeave(sigTable.returnMap(), false);
	beforeLeave(tempTable.returnMap(), true);
	sigTable.leaveScope();
	tempTable.leaveScope();
	cout << qualdruples;
	if (freopen("output.decl", "r", stdin) == NULL)
		cout << "read error" << endl;
	string s;
	cin >> s;
	fclose(stdout);
	if (freopen("out.txt", "w", stdout) == NULL)
		cout << "write error" << endl;
	cout << dataInit;
	qualdruples.outputCode();
	cout << "}";
	fclose(stdin);
	fclose(stdout);			//有用
	//system("pause");		//句柄无效
	return EXIT_SUCCESS;
}
