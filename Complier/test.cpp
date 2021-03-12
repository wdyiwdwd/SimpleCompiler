//#include "Qualdruple.h"
//#include <iostream>
//
//using namespace std;
//
//extern Signary sigTable;
//extern TempTable tempTable;

//int main() {
//	sigTable.enterScope();
//	tempTable.enterScope();
//	Qualdruples q;
//	Symbol a;
//	a.style = TYPE_INT;
//	Symbol b;
//	b.style = TYPE_POINTER(TYPE_INT, 2);
//	Symbol c;
//	c.style = TYPE_DOUBLE;
//	sigTable.put("a", a);
//	sigTable.put("b", b);
//	sigTable.put("c", c);
//	q.append("*", "a", "b");
//	q.append("-", "a", "c");
//	q.append("-", "a", "c", "d");
//	q.insert(1, "if", "a", "", 0);
//	cout << q << endl;
//	cout << tempTable.get("0").style;
//	system("pause");
//	return 0;
//}