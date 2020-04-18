#pragma once

#include "IDirectDrawPalette.h"

ULONG __stdcall IDirectDrawPalette_t::AddRef(void) {
  __debugbreak();
  return ++_ref_count;
}

ULONG __stdcall IDirectDrawPalette_t::Release(void) {
  __debugbreak();
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectDrawPalette_t::QueryInterface(REFIID riid,
                                                       void **ppvObject) {
  __debugbreak();
  return E_NOINTERFACE;
}

HRESULT __stdcall IDirectDrawPalette_t::GetCaps(DWORD *a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawPalette_t::GetEntries(DWORD dwFlags,
                                                   DWORD dwStartingEntry,
                                                   DWORD dwCount,
                                                   PALETTEENTRY *lpEntries) {
  __debugbreak();
  return DD_OK;
}

HRESULT __stdcall IDirectDrawPalette_t::Initialize(IDirectDraw *a,
                                                   DWORD dwFlags,
                                                   PALETTEENTRY *entry) {

  if (dwFlags & DDPCAPS_8BIT) {
    for (int i = 0; i < 256; ++i) {
      _entry[i] = entry[i];
    }
  }
  return DD_OK;
}

HRESULT __stdcall IDirectDrawPalette_t::SetEntries(DWORD dwFlags,
                                                   DWORD dwStartingEntry,
                                                   DWORD dwCount,
                                                   PALETTEENTRY *lpEntries) {

  for (int i = 0; i < dwCount; ++i) {
    _entry[dwStartingEntry + i] = lpEntries[i];
  }
  return DD_OK;
}
