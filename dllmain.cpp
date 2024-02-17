#include <map>
#include <string>
#include <iostream>
#include <windows.h>
#include "echovr.h"
#include "detours.h"

static VOID PatchDetour(PVOID* ppPointer, PVOID pDetour)
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(ppPointer, pDetour);
    DetourTransactionCommit();
}

static __int64 CalculateSymbolValueHook(
    const char* name,
    __int64 a2,
    int a3,
    __int64 a4,
    unsigned int a5
)
{
    if (name[0] == '{' && name[strlen(name) - 1] == '}')
        return std::stoll(std::string(name).substr(1, strlen(name) - 2));
    else
		return EchoVR::CalculateSymbolValue(name, a2, a3, a4, a5);
}

static VOID MAIN() {
    PatchDetour((PVOID*)&EchoVR::CalculateSymbolValue, CalculateSymbolValueHook);
}

static BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		MAIN();
	return TRUE;
}

