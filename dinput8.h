// Author: Sean Pesce
/*
	dinput8.h

	Defines the jumps to all functions exported by the dinput8.dll shared library.
*/


#pragma once


#ifndef _SP_DS1_FPS_FIX_PLUS_DINPUT8_H_
	#define _SP_DS1_FPS_FIX_PLUS_DINPUT8_H_


#ifdef _SP_WRAP_DINPUT8_DLL_


#define _SP_WRAPPED_LIB_ "dinput8"
#define _SP_EXPORT_COUNT_ 6
UINT_PTR mProcs[_SP_EXPORT_COUNT_] = { 0 };
LPCSTR mImportNames[] = { "DirectInput8Create", "DllCanUnloadNow", "DllGetClassObject", "DllRegisterServer", "DllUnregisterServer", "GetdfDIJoystick" };

extern "C" __declspec(naked) void __stdcall DirectInput8Create_wrapper() { __asm {jmp mProcs[0 * 4]} }
extern "C" __declspec(naked) void __stdcall DllCanUnloadNow_wrapper() { __asm {jmp mProcs[1 * 4]} }
extern "C" __declspec(naked) void __stdcall DllGetClassObject_wrapper() { __asm {jmp mProcs[2 * 4]} }
extern "C" __declspec(naked) void __stdcall DllRegisterServer_wrapper() { __asm {jmp mProcs[3 * 4]} }
extern "C" __declspec(naked) void __stdcall DllUnregisterServer_wrapper() { __asm {jmp mProcs[4 * 4]} }
extern "C" __declspec(naked) void __stdcall GetdfDIJoystick_wrapper() { __asm {jmp mProcs[5 * 4]} }

#endif // _SP_WRAP_DINPUT8_DLL_


#endif // _SP_DS1_FPS_FIX_PLUS_DINPUT8_H_

