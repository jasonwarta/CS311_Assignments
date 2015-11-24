#include "treesort.h"

#include <vector>
using std::vector;
#include <iostream>
using namespace::std;

int main(){

	vector<int> v = {5,1,9,2,8,3,7,4,6};
	// vector<int> v = {3,2,1};
	treesort(v.begin(),v.end());
	for(auto x : v){
		cout <<x << endl;
	}

	return 0;
}
