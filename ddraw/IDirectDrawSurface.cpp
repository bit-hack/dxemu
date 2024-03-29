#pragma once
#include <assert.h>

#include "common.h"

#include "IDirectDraw.h"
#include "IDirectDrawSurface.h"
#include "IDirectDrawPalette.h"

#include "../common/log.h"


ULONG __stdcall IDirectDrawSurface_t::AddRef(void) {
  return ++_ref_count;
}

ULONG __stdcall IDirectDrawSurface_t::Release(void) {
  if (--_ref_count == 0) {
    _ddraw->_freeSurface(this);
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

HRESULT __stdcall IDirectDrawSurface_t::Blt(LPRECT lpDstRect,
                                            IDirectDrawSurface *lpDDSrcSurface,
                                            LPRECT lpSrcRect,
                                            DWORD dwFlags,
                                            LPDDBLTFX lpDDBltFX) {

  if (!lpDDSrcSurface) {
    _ddraw->_updatePixels();
    // COMI comes in here and I think DK95 did also (is nullptr primary surface?)
    return DDERR_INVALIDPARAMS;
  }

  const IDirectDrawSurface_t *source = (const IDirectDrawSurface_t*)lpDDSrcSurface;

  const uint8_t *src = source->_buffer._pixels;
  uint8_t *dst = _buffer._pixels;

  src += lpSrcRect->left + lpSrcRect->top * source->_buffer._pitch;
  dst += lpDstRect->left + lpDstRect->top * _buffer._pitch;

  int32_t w = min(lpSrcRect->right  - lpSrcRect->left,
                  lpDstRect->right  - lpDstRect->left);
  int32_t h = min(lpSrcRect->bottom - lpSrcRect->top,
                  lpDstRect->bottom - lpDstRect->top);

  for (int32_t y = 0; y < h; ++y) {
    for (int32_t x = 0; x < w; ++x) {
      dst[x] = src[x];
    }
    src += source->_buffer._pitch;
    dst += _buffer._pitch;
  }

  // if this is the primary surface
  if (_isPrimarySurface()) {
    _ddraw->_updatePixels();
    _ddraw->_present();
  }

  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::BltBatch(LPDDBLTBATCH a, DWORD b,
                                                 DWORD c) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawSurface_t::BltFast(DWORD dwX,
                                                DWORD dwY,
                                                IDirectDrawSurface *lpDDSrcSurface,
                                                LPRECT lpSrcRect,
                                                DWORD dwTrans) {

  __debugbreak();
  return DD_OK;
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
  if (a == _ddraw->_primarySurface) {
    _ddraw->_present();
  }
  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::GetAttachedSurface(
    LPDDSCAPS a,
    IDirectDrawSurface **b) {
  log_t::inst().printf("%s\n", __FUNCTION__);

  if (!b) {
    return DDERR_INVALIDPARAMS;
  }
  // lets just say this surface is fine
  *b = this;
  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::GetBltStatus(DWORD a) {
  if (a == DDGBS_CANBLT) {
    // blits are instantaneous
    return DD_OK;
  }
  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::GetCaps(LPDDSCAPS lpDDSCaps) {
  __debugbreak();
  if (!lpDDSCaps) {
    return DDERR_INVALIDPARAMS;
  }

  lpDDSCaps->dwCaps = DDSCAPS_PALETTE;

  if (_ddraw->_primarySurface == this) {
    lpDDSCaps->dwCaps |= DDSCAPS_PRIMARYSURFACE;
    lpDDSCaps->dwCaps |= DDSCAPS_STANDARDVGAMODE;
  }

  return DD_OK;
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

  memset(format, 0, sizeof(DDPIXELFORMAT));
  format->dwSize = sizeof(DDPIXELFORMAT);

  switch (_buffer._bpp) {
  case 1:
    format->dwFlags = DDPF_PALETTEINDEXED8;
    format->dwRGBBitCount = 8;
    return DD_OK;
  case 2:
    format->dwFlags = DDPF_RGB;
    format->dwRGBBitCount = 16;
    format->dwRBitMask = 0xF800;  // 5
    format->dwGBitMask = 0x07E0;  // 6
    format->dwBBitMask = 0x001F;  // 5
    format->dwRGBAlphaBitMask = 0;
    return DD_OK;
  }

  // unsupported format
  __debugbreak();
  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::GetSurfaceDesc(LPDDSURFACEDESC desc) {

  DDSURFACEDESC &surf = *desc;

  memset(&surf, 0, sizeof(surf));
  surf.dwSize = sizeof(surf);
  surf.ddpfPixelFormat.dwSize = sizeof(surf.ddpfPixelFormat);

  surf.dwFlags = 
    DDSD_HEIGHT |
    DDSD_PITCH |
    DDSD_WIDTH |
    DDSD_PIXELFORMAT |
    DDSD_CAPS;

  surf.dwWidth        = _buffer._width;
  surf.dwHeight       = _buffer._height;
  surf.lPitch         = _buffer._pitch;  // union with linearSize
  surf.lpSurface      = _buffer._pixels;

  surf.ddsCaps.dwCaps = DDSCAPS_LOCALVIDMEM | DDSCAPS_VIDEOMEMORY;

  if (this == _ddraw->_primarySurface) {
    surf.ddsCaps.dwCaps |= DDSCAPS_PRIMARYSURFACE;
    surf.ddsCaps.dwCaps |= DDSCAPS_PRIMARYSURFACELEFT;
    surf.ddsCaps.dwCaps |= DDSCAPS_VISIBLE;
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
    break;
  }

  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::Initialize(IDirectDraw *ddraw,
                                                   LPDDSURFACEDESC lpDesc) {
  log_t::inst().printf("%s(%p, %p)\n", __FUNCTION__, ddraw, lpDesc);

  const DDSURFACEDESC &desc = *lpDesc;
  if (desc.dwSize != sizeof(DDSURFACEDESC)) {
    return DDERR_INVALIDPARAMS;
  }

  if (_ddraw->_window == nullptr) {
    return DDERR_INVALIDPARAMS;
  }

  _buffer._bpp    = 1;
  // diablo 1 demo seems to need this as it has a valid DDSCAPS but doesnt mark it as valid in dwFlags.
  _buffer._width  = _ddraw->_displayMode._width;
  _buffer._height = _ddraw->_displayMode._height;
  _buffer._pitch  = _buffer._width;

  if (desc.dwFlags & DDSD_PIXELFORMAT) {
    _buffer._bpp = (desc.ddpfPixelFormat.dwRGBBitCount / 8);
  }

  if (desc.dwFlags & DDSD_CAPS) {
    const uint32_t caps = desc.ddsCaps.dwCaps;
    if (caps & DDSCAPS_PALETTE) {
      _buffer._bpp = 1;
    }
    if (caps & DDSCAPS_PRIMARYSURFACE) {
      _buffer._bpp    = _ddraw->_displayMode._bpp / 8;
      _buffer._width  = _ddraw->_displayMode._width;
      _buffer._height = _ddraw->_displayMode._height;
      _buffer._pitch  = _buffer._width * _buffer._bpp;
    }
  }

  if (desc.dwFlags & DDSD_WIDTH) {
    _buffer._width = desc.dwWidth;
    _buffer._pitch = desc.dwWidth;
  }
  if (desc.dwFlags & DDSD_HEIGHT) {
    _buffer._height = desc.dwHeight;
  }
  if (desc.dwFlags & DDSD_PITCH) {
    _buffer._pitch = desc.lPitch;
  }

  if (_buffer._width == 0 || _buffer._height == 0) {
    return DDERR_INVALIDPARAMS;
  }

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

  // get our surface descriptor
  GetSurfaceDesc(lpDDSurfaceDesc);

  // we dont handle this yet but might need to
  if (lpDestRect) {
    __debugbreak();
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
  if (_palette) {
    _palette->Release();
    _palette = nullptr;
  }
  _palette = (IDirectDrawPalette_t*)lpDDPalette;
  _palette->AddRef();
  return DD_OK;
}

HRESULT __stdcall IDirectDrawSurface_t::Unlock(LPVOID a) {
  if (_isPrimarySurface()) {
    _ddraw->_updatePixels();

    // this seems to be needed for fallouts main drawing as it doesnt call flip
    _ddraw->_present();
  }
  return DD_OK;
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

bool IDirectDrawSurface_t::_isPrimarySurface() const {
  return (this == _ddraw->_primarySurface);
}
