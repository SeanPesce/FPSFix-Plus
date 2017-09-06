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
	#define _SP_WRAPPED_LIB_ "d3d9"
	#define _SP_EXPORT_COUNT_ 18
	UINT_PTR mProcs[_SP_EXPORT_COUNT_] = { 0 };
	LPCSTR mImportNames[] = { "D3DPERF_BeginEvent", "D3DPERF_EndEvent", "D3DPERF_GetStatus", "D3DPERF_QueryRepeatFrame", "D3DPERF_SetMarker", "D3DPERF_SetOptions", "D3DPERF_SetRegion", "DebugSetLevel", "DebugSetMute", "Direct3D9EnableMaximizedWindowedModeShim", "Direct3DCreate9", "Direct3DCreate9Ex", "Direct3DShaderValidatorCreate9", "PSGPError", "PSGPSampleTexture", (LPCSTR)16, (LPCSTR)17, (LPCSTR)18 };
#endif // _SP_WRAP_D3D9_DLL_
#ifdef _SP_WRAP_DINPUT8_DLL_
	#define _SP_WRAPPED_LIB_ "dinput8"
	#define _SP_EXPORT_COUNT_ 6
	UINT_PTR mProcs[_SP_EXPORT_COUNT_] = { 0 };
	LPCSTR mImportNames[] = { "DirectInput8Create", "DllCanUnloadNow", "DllGetClassObject", "DllRegisterServer", "DllUnregisterServer", "GetdfDIJoystick" };
#endif //  _SP_WRAP_DINPUT8_DLL_



// Main loop that checks if bonfire input bug conditions exist
DWORD WINAPI detection_thread(LPVOID lpParam)
{
	// Check whether to beep when fix is applied
	if ((int)GetPrivateProfileInt("Bonfire Input Fix", "BeepOnDetection", beep_on_fix, CONFIG_FILE) != 0)
		beep_on_fix = true;

	// Wait a bit for the game to load, just in case
	Sleep(1000);

	// Pointer to current player character status (loading, human, hollow, white phantom, or black phantom)
	SpPointer player_char_status = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF7E204), { 0xA28 });

	// Records time at which the bug conditions were first detected
	DWORD first_detected = 0;

	// Bug detection loop
	while (run_thread)
	{
		Sleep(200);

		// Get current player status
		int status = DS1_PLAYER_STATUS_LOADING;
		if (player_char_status.read(&status) != ERROR_SUCCESS)
			// Error reading memory location
			continue;

		// Check for bonfire input glitch conditions
		if (status == DS1_PLAYER_STATUS_HOLLOW || status == DS1_PLAYER_STATUS_HUMAN) // Check if player is hollow/human
		{
			// Get pointer to current character animation
			SpPointer bonfire_anim_fix = SpPointer((void*)0x12E29E8, { 0x0, 0xFC });

			// Read current character animation
			uint32_t current_anim;
			if (bonfire_anim_fix.read(&current_anim) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}


			// Read bonfire menu flag
			SpPointer bonfire_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x40 });
			uint8_t bonfire_menu_is_open;
			if (bonfire_menu_flag.read(&bonfire_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read repair menu flag
			SpPointer repair_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x4C });
			uint8_t repair_menu_is_open;
			if (repair_menu_flag.read(&repair_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read level up menu flag
			SpPointer level_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x78 });
			uint8_t level_menu_is_open;
			if (level_menu_flag.read(&level_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read bottomless box menu flag
			SpPointer bottomless_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x84 });
			uint8_t bottomless_menu_is_open;
			if (bottomless_menu_flag.read(&bottomless_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read attune magic menu flag
			SpPointer attune_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x80 });
			uint8_t attune_menu_is_open;
			if (attune_menu_flag.read(&attune_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read reinforce weapon/armor menu flag
			SpPointer reinforce_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x50 });
			uint8_t reinforce_menu_is_open;
			if (reinforce_menu_flag.read(&reinforce_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read warp menu flag
			SpPointer warp_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0xAC });
			uint8_t warp_menu_is_open;
			if (warp_menu_flag.read(&warp_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read "reverse hollowing?"/"can't kindle"/"can't reverse hollowing"/"insufficient attunement slots" dialog flag
			SpPointer dialog_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x60 });
			uint8_t dialog_menu_is_open;
			if (dialog_menu_flag.read(&dialog_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}


			// Check bonfire input bug conditions
			if ((current_anim == 7701 || current_anim == 7711 || current_anim == 7721) // 3 different bonfire resting animation IDs
				&& !bonfire_menu_is_open && !repair_menu_is_open && !bottomless_menu_is_open && !reinforce_menu_is_open && !level_menu_is_open && !attune_menu_is_open && !dialog_menu_is_open && !warp_menu_is_open) // Make sure no bonfire menus are open
			{
				// Bonfire input glitch conditions currently exist

				if (first_detected == 0)
				{
					// First detection; log time
					first_detected = GetTickCount();
					continue;
				}
				else if ((GetTickCount() - first_detected) >= 1000)
				{
					// Too much time has elapsed; bonfire input glitch is definitely present
					
					// Fix bonfire input glitch
					bonfire_anim_fix.write((uint32_t)0); // Write zero to player animation address, forcing player to leave bonfire
					if(beep_on_fix)
						Beep(500, 500);
				}
				else
				{
					// Not enough time has elapsed; return and check again later
					continue;
				}
			}
		}

		// Reset detection time
		first_detected = 0;
	}

	return 0;
}


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


#ifdef _SP_WRAP_D3D9_DLL_

extern "C" __declspec(naked) void __stdcall D3DPERF_BeginEvent_wrapper(){__asm{jmp mProcs[0*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_EndEvent_wrapper(){__asm{jmp mProcs[1*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_GetStatus_wrapper(){__asm{jmp mProcs[2*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_QueryRepeatFrame_wrapper(){__asm{jmp mProcs[3*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_SetMarker_wrapper(){__asm{jmp mProcs[4*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_SetOptions_wrapper(){__asm{jmp mProcs[5*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_SetRegion_wrapper(){__asm{jmp mProcs[6*4]}}
extern "C" __declspec(naked) void __stdcall DebugSetLevel_wrapper(){__asm{jmp mProcs[7*4]}}
extern "C" __declspec(naked) void __stdcall DebugSetMute_wrapper(){__asm{jmp mProcs[8*4]}}
extern "C" __declspec(naked) void __stdcall Direct3D9EnableMaximizedWindowedModeShim_wrapper(){__asm{jmp mProcs[9*4]}}
extern "C" __declspec(naked) void __stdcall Direct3DCreate9_wrapper(){__asm{jmp mProcs[10*4]}}
extern "C" __declspec(naked) void __stdcall Direct3DCreate9Ex_wrapper(){__asm{jmp mProcs[11*4]}}
extern "C" __declspec(naked) void __stdcall Direct3DShaderValidatorCreate9_wrapper(){__asm{jmp mProcs[12*4]}}
extern "C" __declspec(naked) void __stdcall PSGPError_wrapper(){__asm{jmp mProcs[13*4]}}
extern "C" __declspec(naked) void __stdcall PSGPSampleTexture_wrapper(){__asm{jmp mProcs[14*4]}}
extern "C" __declspec(naked) void __stdcall ExportByOrdinal16(){__asm{jmp mProcs[15*4]}}
extern "C" __declspec(naked) void __stdcall ExportByOrdinal17(){__asm{jmp mProcs[16*4]}}
extern "C" __declspec(naked) void __stdcall ExportByOrdinal18(){__asm{jmp mProcs[17*4]}}

#endif // _SP_WRAP_D3D9_DLL_


#ifdef _SP_WRAP_DINPUT8_DLL_

extern "C" __declspec(naked) void __stdcall DirectInput8Create_wrapper() { __asm {jmp mProcs[0 * 4]} }
extern "C" __declspec(naked) void __stdcall DllCanUnloadNow_wrapper() { __asm {jmp mProcs[1 * 4]} }
extern "C" __declspec(naked) void __stdcall DllGetClassObject_wrapper() { __asm {jmp mProcs[2 * 4]} }
extern "C" __declspec(naked) void __stdcall DllRegisterServer_wrapper() { __asm {jmp mProcs[3 * 4]} }
extern "C" __declspec(naked) void __stdcall DllUnregisterServer_wrapper() { __asm {jmp mProcs[4 * 4]} }
extern "C" __declspec(naked) void __stdcall GetdfDIJoystick_wrapper() { __asm {jmp mProcs[5 * 4]} }

#endif // _SP_WRAP_DINPUT8_DLL_


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

