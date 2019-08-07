
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include<vector>
#include<CSV.h>
using namespace std;

string printSelectedColumn() {

	return "********************\n"
		   "*  Select Column   *\n"
		   "********************"
		;
}
string systemInfo() {
	return "**************************\n"
		   "*   CSV simple Parser    *\n"
		   "*  Create By Ben Chang   *\n"
	 	   "**************************"
		;
}
int main() {
	char* columnName = "address";
	string excel_file = "E://code_IMP//c++_string_parse_pratice_code//data_sheet//SacramentocrimeJanuary2006.csv";

	CSV::Paeser file = CSV::Paeser(excel_file);
	cout << systemInfo() << endl;
	cout << "row count: " << file.rowCount() << endl;

	cout << printSelectedColumn() <<endl;

	vector<string> r = file[columnName];
	for (unsigned int i = 0; i < r.size(); i++)
		cout << r[i]<<endl;

	cout << "column quantity test: " << file.columnCount() << endl;
	
	system("pause");

	return 0;
}