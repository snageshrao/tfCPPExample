#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>  
#include <stdlib.h>  
#include <string>
using namespace std;  
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
void main( int argc, char* argv[] )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
	//si.wShowWindow = SW_HIDE;
	//si.dwFlags = STARTF_USESHOWWINDOW;

    ZeroMemory( &pi, sizeof(pi) );

    
	std::string s = "4.0 3.0";
	
	char args[1000];
	strcpy(args,s.c_str());
	
	// file list loadcppEx dummyEx
	clock_t t;
	t = clock();
	if( !CreateProcess("loadcppEx.exe",
        args,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
		unsigned long exitCode;
		GetExitCodeProcess  (   pi.hProcess,    &exitCode);
		std::cout <<"Exit code is: "<<exitCode<< "\n";
        return;
    }
	
	

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );
	unsigned long exitCode;
	GetExitCodeProcess  (   pi.hProcess,    &exitCode);
	//int actChoice = int(exitCode);
	//std::cout <<"return value is: "<<actChoice<< "\n";
    
	clock_t tE;
	tE = clock()-t;
	std::cout<<"Time end proc: "<<((double)tE/CLOCKS_PER_SEC )<<"  seconds. \n";
	
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}
