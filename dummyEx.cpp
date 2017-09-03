#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>  
#include <stdlib.h>  
#include <string>
#include <time.h>   
using namespace std;  
int main( int argc, char* argv[] )
{
	double dummyAr[100000] = {0.1};
	clock_t td;
	td = clock();
	
	clock_t tdE;
	tdE = clock();
	
	std::cout<<"Time dummy exec: "<<((double)(tdE-td) / CLOCKS_PER_SEC)<<" seconds. \n";
	return 0;
}
