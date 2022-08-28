#pragma once
#define DIRECTSOUND_VERSION 0x300
#include <dsound.h>

#include <cstdint>


struct IDirectSound_t: public IDirectSound {

  friend struct IDirectSoundBuffer_t;

  ULONG __stdcall AddRef(void) override;

  ULONG __stdcall Release(void) override;

  HRESULT __stdcall QueryInterface(
    REFIID riid,
    void **ppvObject) override;

  // IDirectSound methods
  HRESULT __stdcall CreateSoundBuffer(
    LPCDSBUFFERDESC pcDSBufferDesc,
    LPDIRECTSOUNDBUFFER *ppDSBuffer,
    LPUNKNOWN pUnkOuter
  ) override;

  HRESULT __stdcall GetCaps(
    LPDSCAPS pDSCaps
  ) override;

  HRESULT __stdcall DuplicateSoundBuffer(
    LPDIRECTSOUNDBUFFER pDSBufferOriginal, 
    LPDIRECTSOUNDBUFFER *ppDSBufferDuplicate
  ) override;

  HRESULT __stdcall SetCooperativeLevel(
    HWND hwnd,
    DWORD dwLevel
  ) override;

  HRESULT __stdcall Compact(
    void
  ) override;

  HRESULT __stdcall GetSpeakerConfig(
    LPDWORD pdwSpeakerConfig
  ) override;

  HRESULT __stdcall SetSpeakerConfig(
    DWORD dwSpeakerConfig
  ) override;

  HRESULT __stdcall Initialize(
    LPCGUID pcGuidDevice
  ) override;

protected:
  int32_t _ref_count;
};
