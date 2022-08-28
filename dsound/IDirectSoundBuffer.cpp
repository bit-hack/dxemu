#include "IDirectSoundBuffer.h"

#include "../common/log.h"


ULONG __stdcall IDirectSoundBuffer_t::AddRef(void) {
  return ++_ref_count;
}

ULONG __stdcall IDirectSoundBuffer_t::Release(void) {
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectSoundBuffer_t::QueryInterface(REFIID riid,
                                                       void **ppvObject) {
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::GetCaps(LPDSBCAPS pDSBufferCaps) {

  pDSBufferCaps->dwFlags =
    DSBCAPS_CTRLFREQUENCY |
    DSBCAPS_CTRLPAN       |
    DSBCAPS_CTRLVOLUME    |
    DSBCAPS_LOCSOFTWARE;

  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::GetCurrentPosition(LPDWORD pdwCurrentPlayCursor,
                                                           LPDWORD pdwCurrentWriteCursor) {

  // note: write cursor always leads the read cursor

  *pdwCurrentPlayCursor  = 1;
  *pdwCurrentWriteCursor = 10;
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::GetFormat(LPWAVEFORMATEX pwfxFormat,
                                                  DWORD dwSizeAllocated,
                                                  LPDWORD pdwSizeWritten) {

  if (sizeof(_fmt) < dwSizeAllocated) {
    return DSERR_BUFFERTOOSMALL;
  }

  *pdwSizeWritten = sizeof(_fmt);
  memcpy(pwfxFormat, &_fmt, sizeof(_fmt));

  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::GetVolume(LPLONG plVolume) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::GetPan(LPLONG plPan) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::GetFrequency(LPDWORD pdwFrequency) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::GetStatus(LPDWORD pdwStatus) {

  if (pdwStatus) {
    *pdwStatus = DSBSTATUS_LOOPING |
                 DSBSTATUS_PLAYING;
  }
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::Initialize(LPDIRECTSOUND   pDirectSound,
                                                   LPCDSBUFFERDESC pcDSBufferDesc) {

  // note: can get called with just DSBCAPS_PRIMARYBUFFER set and all zeros

  log_t::inst().printf("%s(%p, %p)\n", __FUNCTION__, pDirectSound, pcDSBufferDesc);

  if (!pDirectSound || !pcDSBufferDesc) {
    return DSERR_INVALIDPARAM;
  }

  const DSBUFFERDESC &desc = *pcDSBufferDesc;
  log_t::inst().printf("pcDSBufferDesc.dwSize       =%u\n", desc.dwSize);
  log_t::inst().printf("pcDSBufferDesc.dwFlags      =%u\n", desc.dwFlags);
  log_t::inst().printf("pcDSBufferDesc.dwBufferBytes=%u\n", desc.dwBufferBytes);
  log_t::inst().printf("pcDSBufferDesc.dwReserved   =%u\n", desc.dwReserved);

  // primary buffer should have null pl
  if (desc.lpwfxFormat && (desc.dwFlags & DSBCAPS_PRIMARYBUFFER)) {
    return DSERR_INVALIDPARAM;
  }

  // if this is a primary buffer then allocate it
  if (desc.dwFlags & DSBCAPS_PRIMARYBUFFER) {
    _size = 1024 * 4;
  }
  else {
    _size = pcDSBufferDesc->dwBufferBytes;
  }

  // allocate the buffer
  if (_size) {
    _data.reset(new uint8_t[_size]);
  }

  // set the format if we have one
  if (desc.lpwfxFormat) {
    this->SetFormat(desc.lpwfxFormat);
  }

  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::Lock(DWORD    dwOffset,
                                             DWORD    dwBytes,
                                             LPVOID  *ppvAudioPtr1,
                                             LPDWORD  pdwAudioBytes1,
                                             LPVOID  *ppvAudioPtr2,
                                             LPDWORD  pdwAudioBytes2,
                                             DWORD    dwFlags) {

  // just fake that we got the entire region asked for

  *ppvAudioPtr1 = (LPVOID)(_data.get());
  *pdwAudioBytes1 = dwBytes;

  *ppvAudioPtr2 = nullptr;
  *pdwAudioBytes2 = 0;

  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::Play(DWORD dwReserved1,
                                             DWORD dwPriority,
                                             DWORD dwFlags) {
  log_t::inst().printf("%s(%u, %u, %u)\n", __FUNCTION__,
                       dwReserved1,
                       dwPriority,
                       dwFlags);
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::SetCurrentPosition(
  DWORD dwNewPosition) {

  _index_write = dwNewPosition;

  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::SetFormat(LPCWAVEFORMATEX pcfxFormat) {
  log_t::inst().printf("%s(%p)\n", __FUNCTION__, pcfxFormat);

  if (!pcfxFormat) {
    return DSERR_INVALIDPARAM;
  }

  // note: typical values
  //
  //    Name            Value
  //    wFormatTag      WAVE_FORMAT_PCM
  //    nChannels       2
  //    nSamplesPerSec  22050
  //    nAvgBytesPerSec 88200
  //    nBlockAlign     4
  //    wBitsPerSample  16
  //    cbSize          0

  _fmt = *pcfxFormat;
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::SetVolume(LONG lVolume) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::SetPan(LONG lPan) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::SetFrequency(DWORD dwFrequency) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::Stop(void) {
  __debugbreak();
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::Unlock(LPVOID pvAudioPtr1,
                                               DWORD  dwAudioBytes1,
                                               LPVOID pvAudioPtr2,
                                               DWORD  dwAudioBytes2) {
  return DS_OK;
}

HRESULT __stdcall IDirectSoundBuffer_t::Restore(void) {
  __debugbreak();
  return DS_OK;
}
