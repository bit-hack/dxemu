#define DIRECTSOUND_VERSION 0x300
#include <Windows.h>
#include <dsound.h>

#include "IDirectSound.h"

#include "../common/log.h"
log_t *log_t::log;


extern HRESULT WINAPI DirectSoundCreate(LPCGUID        pcGuidDevice,
                                        LPDIRECTSOUND *ppDS,
                                        LPUNKNOWN      pUnkOuter) {
#pragma comment(linker, "/EXPORT:DirectSoundCreate=" __FUNCDNAME__)

  log_t::init("dsound.log");
  log_t::inst().printf("%s(%p, %p, %p)\n", __FUNCTION__, pcGuidDevice, ppDS, pUnkOuter);

  IDirectSound_t *imp = new IDirectSound_t;
  *ppDS = imp;

  return imp->Initialize(pcGuidDevice);
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL,
                    _In_ DWORD fdwReason,
                    _In_ LPVOID lpvReserved) {
  return TRUE;
}
