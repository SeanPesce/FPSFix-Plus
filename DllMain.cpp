// Author: Sean Pesce

/*
	Wrapper DLL template was generated using Sean Pesce's fork of
	Lin Min's (mavenlin on GitHub) DLL Wrapper Generator.

	Credit to Nullby7e for the original bonfire input fix (FPSFix).
*/

#include <Windows.h>
#include <stdio.h>
#include "SpPointer.h"



// Player status codes
enum DS1_PLAYER_STATUS_ENUM {
	DS1_PLAYER_STATUS_LOADING = -1,
	DS1_PLAYER_STATUS_HUMAN = 0,
	DS1_PLAYER_STATUS_COOP = 1,
	DS1_PLAYER_STATUS_INVADER = 2,
	DS1_PLAYER_STATUS_HOLLOW = 8
};


const char *CONFIG_FILE = ".\\FPSFix.ini";



HANDLE fix_thread_handle;		// Bug-checking thread handle
DWORD fix_thread_id;			// Bug-checking thread ID
bool run_thread = true;			// While true, continue checking for bonfire input glitch conditions
bool beep_on_fix = false;		// If true, a beep will sound if bonfire input glitch is automatically detected and fixed


HINSTANCE mHinst = 0, mHinstDLL = 0;

void LoadOriginalDll();
int InitSettings();


#ifdef _SP_WRAP_D3D9_DLL_
	#include "d3d9.h"
#endif // _SP_WRAP_D3D9_DLL_
#ifdef _SP_WRAP_DINPUT8_DLL_
	#include "dinput8.h"
#endif //  _SP_WRAP_DINPUT8_DLL_
#ifdef _SP_WRAP_D3DX9_43_DLL_
	#include "d3dx9_43.h"
#endif //  _SP_WRAP_D3DX9_43_DLL_
#ifdef _SP_WRAP_WINMM_DLL_
	#include "winmm.h"
#endif //  _SP_WRAP_WINMM_DLL_


#include "FPSFix.h"


BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
	mHinst = hinstDLL;
	if ( fdwReason == DLL_PROCESS_ATTACH ) {
		InitSettings();
		if (!mHinstDLL)
		{
			// No chain was loaded; get original DLL from system directory
			LoadOriginalDll();
		}
		if ( !mHinstDLL )
			return ( FALSE );
		for ( int i = 0; i < _SP_EXPORT_COUNT_; i++ )
			mProcs[ i ] = (UINT_PTR)GetProcAddress( mHinstDLL, mImportNames[ i ] );
		// Initialize the thread that checks for the bug conditions:
		fix_thread_handle = CreateThread(
			NULL,				// Default security attributes
			0,					// Use default stack size
			detection_thread,	// Thread function name
			NULL,				// Argument to thread function
			0,					// Use default creation flags
			&fix_thread_id);	// Returns the thread identifier
	} else if ( fdwReason == DLL_PROCESS_DETACH ) {
		run_thread = false;
		FreeLibrary( mHinstDLL );
	}
	return ( TRUE );
}


// Loads the original DLL from the default system directory
//	Function originally written by Michael Koch
void LoadOriginalDll()
{
	char buffer[MAX_PATH + 2];

	// Get path to system dir and to system DLL
	GetSystemDirectory(buffer, MAX_PATH + 1);

	// Append DLL name
	strcat_s(buffer, "\\" _SP_WRAPPED_LIB_ ".dll");

	// Try to load the system's DLL, if pointer empty
	if (!mHinstDLL) mHinstDLL = LoadLibrary(buffer);

	// Debug
	if (!mHinstDLL)
	{
		OutputDebugString("PROXYDLL: Original " _SP_WRAPPED_LIB_ ".dll not loaded ERROR ****\r\n");
		ExitProcess(0); // Exit the hard way
	}
}


// Parses FPSFix.ini for intialization settings
int InitSettings()
{
	char dll_chain_buffer[128];

	// Check settings file for DLL chain
	GetPrivateProfileString("DLL Chain", "DllChain", NULL, dll_chain_buffer, 128, CONFIG_FILE);

	if (dll_chain_buffer[0] != '\0') // Found chain entry in settings file
	{
		mHinstDLL = LoadLibrary(dll_chain_buffer);
		if (!mHinstDLL)
		{
			// Failed to load next wrapper DLL
			OutputDebugString("PROXYDLL: Failed to load chained DLL; loading original from system directory instead...\r\n");
			return 2; // Return 2 if given DLL could not be loaded
		}
	}
	else
	{
		OutputDebugString("PROXYDLL: No DLL chain specified; loading original from system directory...\r\n");
		return 1; // Return 1 if config file or chain entry could not be located
	}
	return 0; // Return 0 on success
}

