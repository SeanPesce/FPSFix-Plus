// Author: Sean Pesce
/*
	d3d9.h

	Defines the jumps to all functions exported by the d3d9.dll shared library.
*/


#pragma once


#ifndef _SP_DS1_FPS_FIX_PLUS_D3D9_H_
	#define _SP_DS1_FPS_FIX_PLUS_D3D9_H_


#ifdef _SP_WRAP_D3D9_DLL_


#define _SP_WRAPPED_LIB_ "d3d9"
#define _SP_EXPORT_COUNT_ 18
UINT_PTR mProcs[_SP_EXPORT_COUNT_] = { 0 };
LPCSTR mImportNames[] = { "D3DPERF_BeginEvent", "D3DPERF_EndEvent", "D3DPERF_GetStatus", "D3DPERF_QueryRepeatFrame", "D3DPERF_SetMarker", "D3DPERF_SetOptions", "D3DPERF_SetRegion", "DebugSetLevel", "DebugSetMute", "Direct3D9EnableMaximizedWindowedModeShim", "Direct3DCreate9", "Direct3DCreate9Ex", "Direct3DShaderValidatorCreate9", "PSGPError", "PSGPSampleTexture", (LPCSTR)16, (LPCSTR)17, (LPCSTR)18 };

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


#endif // _SP_DS1_FPS_FIX_PLUS_D3D9_H_

