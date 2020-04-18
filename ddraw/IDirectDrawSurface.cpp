#pragma once
#include <assert.h>

#include "common.h"

#include "IDirectDraw.h"
#include "IDirectDrawSurface.h"

ULONG __stdcall IDirectDrawSurface_t::AddRef(void) {
  __debugbreak();
  return ++_ref_count;
}

ULONG __stdcall IDirectDrawSurface_t::Release(void) {
  __debugbreak();
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectDrawSurface_t::QueryInterface(REFIID riid,
                                                       void **ppvObject) {
  __debugbreak();
  return E_NOINTERFACE;
};

HRESULT __stdcall IDirectDrawSurface_t::AddAttachedSurface(
    IDirectDrawSurface *a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::AddOverlayDirtyRect(LPRECT a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::Blt(LPRECT a, IDirectDrawSurface *b,
                                            LPRECT c, DWORD d, LPDDBLTFX e) {
//  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::BltBatch(LPDDBLTBATCH a, DWORD b,
                                                 DWORD c) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::BltFast(DWORD a, DWORD b,
                                                IDirectDrawSurface *c, LPRECT d,
                                                DWORD e) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::DeleteAttachedSurface(
    DWORD a, IDirectDrawSurface *b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::EnumAttachedSurfaces(
    LPVOID a, LPDDENUMSURFACESCALLBACK b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::EnumOverlayZOrders(
    DWORD a, LPVOID b, LPDDENUMSURFACESCALLBACK c) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::Flip(IDirectDrawSurface *a, DWORD b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetAttachedSurface(
    LPDDSCAPS a,
    IDirectDrawSurface **b) {
  if (!b) {
    return DDERR_INVALIDPARAMS;
  }
  // lets just say this surface is fine
  *b = this;
  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::GetBltStatus(DWORD a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetCaps(LPDDSCAPS a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetClipper(IDirectDrawClipper **out) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetColorKey(DWORD a, LPDDCOLORKEY b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetDC(HDC *dc) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetFlipStatus(DWORD a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetOverlayPosition(LPLONG a, LPLONG b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetPalette(IDirectDrawPalette **out) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetPixelFormat(LPDDPIXELFORMAT format) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::GetSurfaceDesc(LPDDSURFACEDESC desc) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::Initialize(IDirectDraw *ddraw,
                                                   LPDDSURFACEDESC lpDesc) {

  const DDSURFACEDESC &desc = *lpDesc;
  if (desc.dwSize != sizeof(DDSURFACEDESC)) {
    return DDERR_INVALIDPARAMS;
  }

  if (_ddraw->_window == nullptr) {
    return DDERR_INVALIDPARAMS;
  }

  _buffer._bpp = 4;

  if (desc.dwFlags & DDSD_CAPS) {
    const uint32_t caps = desc.ddsCaps.dwCaps;
    if (caps & DDSCAPS_PALETTE) {
      _buffer._bpp = 1;
    }
  }

  _buffer._width  = _ddraw->_displayMode._width;
  _buffer._height = _ddraw->_displayMode._height;
  _buffer._pitch  = round_up(_buffer._width, 16) * _buffer._bpp;

  const size_t size = _buffer._pitch * _buffer._height;
  _buffer._pixels = (uint8_t*)_aligned_malloc(size, 16);

  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::IsLost() {
  // we cant lose our surface
  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::Lock(LPRECT lpDestRect,
                                             LPDDSURFACEDESC lpDDSurfaceDesc,
                                             DWORD dwFlags,
                                             HANDLE hEvent) {

  DDSURFACEDESC &surf = *lpDDSurfaceDesc;
  if (surf.dwSize != sizeof(DDSURFACEDESC)) {
    __debugbreak();
    return DDERR_INVALIDPARAMS;
  }

  memset(&surf, 0, sizeof(surf));
  surf.dwSize = sizeof(surf);
  surf.ddpfPixelFormat.dwSize = sizeof(surf.ddpfPixelFormat);

  surf.dwFlags = 
    DDSD_HEIGHT |
    DDSD_PITCH |
    DDSD_WIDTH |
    DDSD_PIXELFORMAT |
    DDSD_REFRESHRATE |
    DDSD_BACKBUFFERCOUNT;

  surf.dwRefreshRate = 60;
  surf.dwBackBufferCount = 1;

  surf.dwWidth       = _buffer._width;
  surf.dwHeight      = _buffer._height;
  surf.lPitch        = _buffer._pitch;  // union with linearSize
  surf.lpSurface     = _buffer._pixels;

  if (lpDestRect) {
    __debugbreak();
  }

  switch (_buffer._bpp) {
  case 1:
    surf.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
    break;
  case 4:
    surf.ddpfPixelFormat.dwFlags |= DDPF_RGB;
    surf.ddpfPixelFormat.dwRGBBitCount = 32;  // may have to be 24?
    surf.ddpfPixelFormat.dwRBitMask = 0x00ff0000;
    surf.ddpfPixelFormat.dwGBitMask = 0x0000ff00;
    surf.ddpfPixelFormat.dwBBitMask = 0x000000ff;
  }

  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::ReleaseDC(HDC) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::Restore() {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::SetClipper(IDirectDrawClipper *) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::SetColorKey(DWORD, LPDDCOLORKEY) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::SetOverlayPosition(LONG, LONG) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::SetPalette(LPDIRECTDRAWPALETTE lpDDPalette) {
//  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::Unlock(LPVOID a) {
//  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::UpdateOverlay(LPRECT,
                                                      IDirectDrawSurface *,
                                                      LPRECT, DWORD,
                                                      LPDDOVERLAYFX) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::UpdateOverlayDisplay(DWORD) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::UpdateOverlayZOrder(
    DWORD, IDirectDrawSurface *) {
  __debugbreak();
  return 0;
}