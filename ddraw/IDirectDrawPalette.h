#pragma once

#include <array>
#include <cstdint>

#include <intrin.h>

#define DIRECTDRAW_VERSION 0x300
#include <ddraw.h>

#include "types.h"

struct IDirectDrawPalette_t : public IDirectDrawPalette {

  friend IDirectDraw_t;

  IDirectDrawPalette_t(IDirectDraw_t *ddraw) : _ref_count(1), _ddraw(ddraw) {}

  ULONG __stdcall AddRef(void) override;

  ULONG __stdcall Release(void) override;

  HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject) override;

  HRESULT __stdcall GetCaps(DWORD *a) override;

  HRESULT __stdcall GetEntries(DWORD a, DWORD b, DWORD c,
                               PALETTEENTRY *d) override;

  HRESULT __stdcall Initialize(IDirectDraw *a, DWORD b,
                               PALETTEENTRY *c) override;

  HRESULT __stdcall SetEntries(DWORD a, DWORD b, DWORD c,
                               PALETTEENTRY *d) override;

protected:
  int32_t _ref_count;
  struct IDirectDraw_t *_ddraw;

  std::array<PALETTEENTRY, 256> _entry;
};
