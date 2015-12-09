#include <string>
using std::string;
using std::size_t;
#include <map>
using std::map;
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
	

int main(){
	string fname;
	cout << "Enter a filename: ";
	getline(cin,fname);

	ifstream ifs(fname);
	string input;
	map<string, size_t> count;

	if(ifs.is_open()){
		while(ifs.good()){
			ifs >> input;
			if(count.find(input) == count.end()) count[input] = 1;
			else count[input]++;

			if(ifs.eof()) break;
		}

		for(auto i = count.begin(); i != count.end(); i++){
			cout << i->first << " " << i->second << endl;
		}
	}
	else {
		cout << "Could not open file." << endl;
	}

	return 0;
}