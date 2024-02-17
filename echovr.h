#pragma once
#include <windows.h>

namespace EchoVR {
	CHAR* g_GameBaseAddress = (CHAR*)GetModuleHandle(NULL);

	typedef __int64 CalculateSymbolValueFunc(
		const char* name,
		__int64 a2,
		int a3,
		__int64 a4,
		unsigned int a5
	);
	CalculateSymbolValueFunc* CalculateSymbolValue = (CalculateSymbolValueFunc*)(g_GameBaseAddress + 0x0CE120);
}