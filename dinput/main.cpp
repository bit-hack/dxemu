#define DIRECTDRAW_VERSION 0x300
#include <Windows.h>
#include <ddraw.h>

#include "IDirectInput.h"

#include "../common/log.h"
log_t *log_t::log;


extern HRESULT WINAPI DirectInputCreateA(HINSTANCE hinst,
                                         DWORD dwVersion, 
                                         LPDIRECTINPUT *lplpDI,
                                         IUnknown *pUnkOuter) {
#pragma comment(linker, "/EXPORT:DirectInputCreateA=" __FUNCDNAME__)

//  __debugbreak();

  log_t::init("dinput.log");

  IDirectInput_t *imp = new IDirectInput_t;
  *lplpDI = imp;

  return imp->Initialize(hinst, dwVersion);
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason,
                    _In_ LPVOID lpvReserved) {
  return TRUE;
}
