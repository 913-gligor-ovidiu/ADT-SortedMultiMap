#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
	testReplace();
	testAllExtended();
	
    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
