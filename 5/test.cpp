#include <vector>
using std::vector;
#include <iostream>

#include "tsmarray.h"

int main(){
	TSmArray<int> t1(9);

	for(int i = 0; i < t1.size(); i++){
		t1[i] = i+1;
	}

	// t1.remove(t1.begin()+3);
	t1.insert(t1.begin()+3,33);

	for(int i = 0; i < t1.size(); i++){
		std::cout << t1[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}