#pragma once

#include <cstdint>
#include <intrin.h>

#define DIRECTDRAW_VERSION 0x300
#include <ddraw.h>

#include "types.h"

struct IDirectDrawSurface_t : public IDirectDrawSurface {

  friend IDirectDraw_t;
  friend IDirectDrawPalette_t;

  IDirectDrawSurface_t(IDirectDraw_t *ddraw)
    : _ref_count(1)
    , _ddraw(ddraw)
    , _buffer{0}
    , _palette(nullptr) {
  }

  ULONG __stdcall AddRef(void) override;

  ULONG __stdcall Release(void) override;

  HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject) override;

  HRESULT __stdcall AddAttachedSurface(IDirectDrawSurface *a) override;

  HRESULT __stdcall AddOverlayDirtyRect(LPRECT a) override;

  HRESULT __stdcall Blt(LPRECT a, IDirectDrawSurface *b, LPRECT c, DWORD d,
                        LPDDBLTFX e) override;

  HRESULT __stdcall BltBatch(LPDDBLTBATCH a, DWORD b, DWORD c) override;

  HRESULT __stdcall BltFast(DWORD a, DWORD b, IDirectDrawSurface *c, LPRECT d,
                            DWORD e) override;

  HRESULT __stdcall DeleteAttachedSurface(DWORD a,
                                          IDirectDrawSurface *b) override;

  HRESULT __stdcall EnumAttachedSurfaces(LPVOID a,
                                         LPDDENUMSURFACESCALLBACK b) override;

  HRESULT __stdcall EnumOverlayZOrders(DWORD a, LPVOID b,
                                       LPDDENUMSURFACESCALLBACK c) override;

  HRESULT __stdcall Flip(IDirectDrawSurface *a, DWORD b) override;

  HRESULT __stdcall GetAttachedSurface(LPDDSCAPS a,
                                       IDirectDrawSurface **b) override;

  HRESULT __stdcall GetBltStatus(DWORD a) override;

  HRESULT __stdcall GetCaps(LPDDSCAPS a) override;

  HRESULT __stdcall GetClipper(IDirectDrawClipper **out) override;

  HRESULT __stdcall GetColorKey(DWORD a, LPDDCOLORKEY b) override;

  HRESULT __stdcall GetDC(HDC *dc) override;

  HRESULT __stdcall GetFlipStatus(DWORD a) override;

  HRESULT __stdcall GetOverlayPosition(LPLONG a, LPLONG b) override;

  HRESULT __stdcall GetPalette(IDirectDrawPalette **out) override;

  HRESULT __stdcall GetPixelFormat(LPDDPIXELFORMAT format) override;

  HRESULT __stdcall GetSurfaceDesc(LPDDSURFACEDESC desc) override;

  HRESULT __stdcall Initialize(IDirectDraw *, LPDDSURFACEDESC) override;

  HRESULT __stdcall IsLost() override;

  HRESULT __stdcall Lock(LPRECT, LPDDSURFACEDESC, DWORD, HANDLE) override;

  HRESULT __stdcall ReleaseDC(HDC) override;

  HRESULT __stdcall Restore() override;

  HRESULT __stdcall SetClipper(IDirectDrawClipper *) override;

  HRESULT __stdcall SetColorKey(DWORD, LPDDCOLORKEY) override;

  HRESULT __stdcall SetOverlayPosition(LONG, LONG) override;

  HRESULT __stdcall SetPalette(LPDIRECTDRAWPALETTE) override;

  HRESULT __stdcall Unlock(LPVOID) override;

  HRESULT __stdcall UpdateOverlay(LPRECT, IDirectDrawSurface *, LPRECT, DWORD,
                                  LPDDOVERLAYFX) override;

  HRESULT __stdcall UpdateOverlayDisplay(DWORD) override;

  HRESULT __stdcall UpdateOverlayZOrder(DWORD, IDirectDrawSurface *) override;

protected:

  bool _isPrimarySurface() const;

  struct buffer_t {
    uint32_t _width, _height, _pitch;
    uint8_t *_pixels;
    uint32_t _bpp;
  };

  int32_t _ref_count;
  IDirectDraw_t *_ddraw;

  IDirectDrawPalette_t *_palette;

  buffer_t _buffer;
};
