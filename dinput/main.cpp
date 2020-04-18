#define DIRECTDRAW_VERSION 0x300
#include <Windows.h>
#include <ddraw.h>

#include "IDirectInput.h"

extern HRESULT WINAPI DirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, 
                                         LPDIRECTINPUT *lplpDI,
                                         IUnknown *pUnkOuter) {
#pragma comment(linker, "/EXPORT:DirectInputCreateA=" __FUNCDNAME__)

//  __debugbreak();

  IDirectInput_t *imp = new IDirectInput_t;
  *lplpDI = imp;

  return imp->Initialize(hinst, dwVersion);
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason,
                    _In_ LPVOID lpvReserved) {
  return TRUE;
}
