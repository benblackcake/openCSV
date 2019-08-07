#include "CSV.h"

using namespace std;
/**

constractor
**/
CSV::Paeser::Paeser(const std::string & filename, char sp):_sp(sp){//初始化const 變數or去parent class initialized
	
	_fileName = filename;
	string line;

	ifstream ifile(_fileName);
	if (ifile.is_open()) {
		while (ifile.good()) {
			getline(ifile, line);
			if (line != "") {
				_fileList.push_back(line);
			}
		}
		ifile.close();

		if (_fileList.size() == 0) {
			cout << "No data In" << endl;
		}
	
		parseHeader();
		parseContent();
	}


}

/********************************
*
* get header quantity
*
*********************************/
unsigned int CSV::Paeser::rowCount(void) const{

	return _Head.size();
}
/********************************
*
* get column quantity
*
*********************************/
unsigned int CSV::Paeser::columnCount(void) const
{
	return _allValue.size();
}
/********************************
*
* put header element into _Head vector
*
*********************************/
void CSV::Paeser::parseHeader(){
	std::stringstream ss(_fileList[0]);
	std::string stn;
	while (getline(ss,stn,_sp)) {
		_Head.push_back(stn);
	}

}
/********************************
*
* parse all data row by row 
* definie two dimensional vector 
*
*********************************/
void CSV::Paeser::parseContent(){

	std::string stnTmp;
	std::string stn;
	unsigned quotes = 0;
	bool finis = false;
	vector<string> st;

	for (int i = 1; i < _fileList.size(); i++) {
		std::stringstream ss(_fileList[i]);
		stnTmp = "";

		while (getline(ss,stn,_sp)) {
			int k = stn.find('"');
			if (k >-1) {//found
				finis = true;
				quotes++;

			}else finis = false;
			if (quotes>0||finis ) {
				quotes = quotes % 2;
				stnTmp += stn+",";
				//cout << "stnTmp:" << stnTmp << endl;
				if (quotes == 0) {
					//cout << "find left" << endl;
					st.push_back(stnTmp);
					stnTmp = "";
				}
			}

			if (!finis&&quotes==0) 
				st.push_back(stn);			
		}
		_allValue.push_back(st);
		st.clear();

	}
	//cout<<"_t_size" << _t[0] << endl;
}
/********************************
*
* operator overloading 
* object["column name"]
*
*********************************/
std::vector<string> CSV::Paeser::operator[](std::string columnName){
	vector<string>result;

	int colPosition=getHeadPosition(columnName);
	for (unsigned int i = 0; i < _allValue.size(); i++)
		result.push_back(_allValue[i][colPosition]);
	return result;
}
/********************************
*
* get Header position and return header index
*
*********************************/
unsigned int CSV::Paeser::getHeadPosition(string element){

	std::pair<bool, int> result = findInVector<string>(_Head, element);
	return result.second;
}

/********************************
*
* search vector element position
*
*********************************/
template<typename T>
pair<bool, int>CSV::Paeser::findInVector(std::vector<T>& vecOfElements, T & element){
	std::pair<bool, int > result;

	// Find given element in vector
	typename vector<T>::iterator it = std::find(vecOfElements.begin(), vecOfElements.end(), element);

	if (it != vecOfElements.end()){
		result.second = distance(vecOfElements.begin(), it);
		result.first = true;
	}
	else{
		result.first = false;
		result.second = -1;
	}

	return result;
}