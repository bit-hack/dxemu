#include "IDirectSound.h"
#include "IDirectSoundBuffer.h"

#include "../common/log.h"


ULONG __stdcall IDirectSound_t::AddRef(void) {
  return ++_ref_count;
}

ULONG __stdcall IDirectSound_t::Release(void) {
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectSound_t::QueryInterface(REFIID   riid,
                                                 void   **ppvObject) {
  __debugbreak();
  return DS_OK;
}

// IDirectSound methods
HRESULT __stdcall IDirectSound_t::CreateSoundBuffer(LPCDSBUFFERDESC      pcDSBufferDesc,
                                                    LPDIRECTSOUNDBUFFER *ppDSBuffer,
                                                    LPUNKNOWN            pUnkOuter) {

  log_t::inst().printf("%s(%p, %p, %p)\n", __FUNCTION__, pcDSBufferDesc, ppDSBuffer, pUnkOuter);

  IDirectSoundBuffer_t *buffer = new IDirectSoundBuffer_t;

  HRESULT res = buffer->Initialize(this, pcDSBufferDesc);
  if (res != DS_OK) {
    buffer->Release();
    return res;
  }

  *ppDSBuffer = buffer;
  return DS_OK;
}

HRESULT __stdcall IDirectSound_t::GetCaps(LPDSCAPS pDSCaps) {
  if (pDSCaps) {
    pDSCaps->dwSize = 96;
    pDSCaps->dwFlags =
      DSCAPS_CONTINUOUSRATE |
      DSCAPS_PRIMARY16BIT   |
      DSCAPS_PRIMARY8BIT    |
      DSCAPS_PRIMARYMONO    |
      DSCAPS_PRIMARYSTEREO  |
      DSCAPS_SECONDARY16BIT |
      DSCAPS_SECONDARY8BIT  |
      DSCAPS_SECONDARYMONO  |
      DSCAPS_SECONDARYSTEREO;
    pDSCaps->dwMinSecondarySampleRate      = 100;
    pDSCaps->dwMaxSecondarySampleRate      = 200000;
    pDSCaps->dwPrimaryBuffers              = 1;
    pDSCaps->dwMaxHwMixingAllBuffers       = 1;
    pDSCaps->dwMaxHwMixingStaticBuffers    = 1;
    pDSCaps->dwMaxHwMixingStreamingBuffers = 1;
  }
  return DS_OK;
}

HRESULT __stdcall IDirectSound_t::DuplicateSoundBuffer(LPDIRECTSOUNDBUFFER  pDSBufferOriginal,
                                                       LPDIRECTSOUNDBUFFER *ppDSBufferDuplicate) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSound_t::SetCooperativeLevel(HWND  hwnd,
                                                      DWORD dwLevel) {

  log_t::inst().printf("%s(%p, %u)\n", __FUNCTION__, hwnd, dwLevel);
  return DS_OK;
}

HRESULT __stdcall IDirectSound_t::Compact(void) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSound_t::GetSpeakerConfig(LPDWORD pdwSpeakerConfig) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSound_t::SetSpeakerConfig(DWORD dwSpeakerConfig) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSound_t::Initialize(LPCGUID pcGuidDevice) {

  log_t::inst().printf("%s(%p)\n", __FUNCTION__, pcGuidDevice);
  return DS_OK;
}
