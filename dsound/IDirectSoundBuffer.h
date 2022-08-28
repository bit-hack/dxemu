#pragma once
#define DIRECTSOUND_VERSION 0x300
#include <dsound.h>

#include <cstdint>
#include <memory>


struct IDirectSoundBuffer_t : public IDirectSoundBuffer {

  friend struct IDirectSound_t;

  IDirectSoundBuffer_t()
    : _ref_count  (1)
    , _index_read (0)
    , _index_write(0)
    , _size       (0)
  {
  }

  ULONG   __stdcall AddRef            (void) override;
  ULONG   __stdcall Release           (void) override;
  HRESULT __stdcall QueryInterface    (REFIID riid, void **ppvObject) override;

  HRESULT __stdcall GetCaps           (LPDSBCAPS pDSBufferCaps) override;
  HRESULT __stdcall GetCurrentPosition(LPDWORD pdwCurrentPlayCursor, LPDWORD pdwCurrentWriteCursor) override;
  HRESULT __stdcall GetFormat         (LPWAVEFORMATEX pwfxFormat, DWORD dwSizeAllocated, LPDWORD pdwSizeWritten) override;
  HRESULT __stdcall GetVolume         (LPLONG plVolume) override;
  HRESULT __stdcall GetPan            (LPLONG plPan) override;
  HRESULT __stdcall GetFrequency      (LPDWORD pdwFrequency) override;
  HRESULT __stdcall GetStatus         (LPDWORD pdwStatus) override;
  HRESULT __stdcall Initialize        (LPDIRECTSOUND pDirectSound, LPCDSBUFFERDESC pcDSBufferDesc) override;
  HRESULT __stdcall Lock              (DWORD dwOffset, DWORD dwBytes, LPVOID *ppvAudioPtr1, LPDWORD pdwAudioBytes1, LPVOID *ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags) override;
  HRESULT __stdcall Play              (DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags) override;
  HRESULT __stdcall SetCurrentPosition(DWORD dwNewPosition) override;
  HRESULT __stdcall SetFormat         (LPCWAVEFORMATEX pcfxFormat) override;
  HRESULT __stdcall SetVolume         (LONG lVolume) override;
  HRESULT __stdcall SetPan            (LONG lPan) override;
  HRESULT __stdcall SetFrequency      (DWORD dwFrequency) override;
  HRESULT __stdcall Stop              (void) override;
  HRESULT __stdcall Unlock            (LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2) override;
  HRESULT __stdcall Restore           (void) override;

protected:
  int32_t  _ref_count;
  uint32_t _index_read;
  uint32_t _index_write;

  size_t _size;
  std::unique_ptr<uint8_t[]> _data;
  WAVEFORMATEX _fmt;
};
