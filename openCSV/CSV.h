#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

namespace CSV {


	class Paeser {
		public:
			Paeser(const std::string &filename, char sp = ',');
			//~Parser(void);
		public:
			unsigned int rowCount(void)const;
			unsigned int columnCount(void)const;
			std::vector<string> operator[](std::string columnName);

		private:
			void parseHeader();
			void parseContent();
			unsigned int getHeadPosition(string element);

			template < typename T>
			std::pair<bool, int > findInVector(std::vector<T>  & vecOfElements, T & element);

			//unsigned int getHeadPosition(string element);
		private://private µ¹class½Õ¥Î
			const char _sp;
			string _fileName;
			vector<string>_Head;
			vector<string>_fileList;
			vector<vector<string>>_allValue;
			//vector<string>_allValue;


	};



}