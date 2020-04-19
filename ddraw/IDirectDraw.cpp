#pragma once

#include "IDirectDraw.h"
#include "IDirectDrawClipper.h"
#include "IDirectDrawPalette.h"
#include "IDirectDrawSurface.h"

ULONG __stdcall IDirectDraw_t::AddRef(void) {
  return ++_ref_count;
}

ULONG __stdcall IDirectDraw_t::Release(void) {
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectDraw_t::QueryInterface(REFIID riid, void **ppvObject) {
  log_t::inst().printf("%s()\n", __func__);

  if (!ppvObject) {
    return E_POINTER;
  }
  *ppvObject = nullptr;
  if (riid == IID_IDirectDraw) {
    __debugbreak();
    return E_NOINTERFACE;
  }
  if (riid == IID_IDirectDraw2) {
    this->AddRef();
    *ppvObject = this;
    return DD_OK;
  }
  if (riid == IID_IDirectDraw4) {
    __debugbreak();
    return E_NOINTERFACE;
  }
  if (riid == IID_IDirectDraw7) {
    __debugbreak();
    return E_NOINTERFACE;
  }
  __debugbreak();
  return E_NOINTERFACE;
}

HRESULT __stdcall IDirectDraw_t::Compact(void) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::CreateClipper(
    DWORD dwFlags, LPDIRECTDRAWCLIPPER *lplpDDrawClipper, IUnknown *c) {
  __debugbreak();
  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::CreatePalette(
    DWORD dwFlags, LPPALETTEENTRY lpDDColorArray,
    LPDIRECTDRAWPALETTE *lplpDDPalette, IUnknown *pUnkOuter) {

  *lplpDDPalette = nullptr;
  IDirectDrawPalette_t *palette = new IDirectDrawPalette_t(this);
  HRESULT res = palette->Initialize(this, dwFlags, lpDDColorArray);
  if (res != DD_OK) {
    palette->Release();
    return res;
  }

  _palettes.push_back(palette);

  *lplpDDPalette = palette;
  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::CreateSurface(
    LPDDSURFACEDESC desc, LPDIRECTDRAWSURFACE *lplpDDSurface,
    IUnknown *pUnkOuter) {
  log_t::inst().printf("%s\n", __func__);

  *lplpDDSurface = nullptr;
  IDirectDrawSurface_t *surface = new IDirectDrawSurface_t(this);
  HRESULT res = surface->Initialize(this, desc);
  if (res != DD_OK) {
    surface->Release();
    return res;
  }

  _surfaces.push_back(surface);

  if (desc->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE) {
    // this is the primary surface
    _primarySurface = surface;

    const size_t size = surface->_buffer._width * surface->_buffer._height;
    _pixels.reset(new uint32_t[size]);
    memset(_pixels.get(), 0xff, size * sizeof(uint32_t));
  }

  *lplpDDSurface = surface;
  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::DuplicateSurface(LPDIRECTDRAWSURFACE a,
                                                  LPDIRECTDRAWSURFACE *b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::EnumDisplayModes(DWORD dwFlags,
                                                  LPDDSURFACEDESC lpDDSurfaceDesc2,
                                                  LPVOID lpContext,
                                                  LPDDENUMMODESCALLBACK lpEnumModesCallback) {
  __debugbreak();
  log_t::inst().printf("%s(%d, %p, %p, %p)\n", __func__, dwFlags, lpDDSurfaceDesc2, lpContext, lpEnumModesCallback);

  DDSURFACEDESC desc = {0};
  desc.dwSize = sizeof(DDSURFACEDESC);
  desc.dwFlags = DDSD_BACKBUFFERCOUNT | DDSD_HEIGHT | DDSD_REFRESHRATE | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_CAPS;
  desc.dwBackBufferCount = 1;
  desc.dwWidth = 640;
  desc.dwHeight = 480;
  desc.dwRefreshRate = 60;
  desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_STANDARDVGAMODE | DDSCAPS_VISIBLE;

  desc.ddpfPixelFormat.dwFlags = DDPF_RGB;
  desc.ddpfPixelFormat.dwRGBBitCount = 8;
  desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);

  HRESULT res = lpEnumModesCallback(&desc, lpContext);

  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::EnumSurfaces(DWORD a, LPDDSURFACEDESC b,
                                              LPVOID c,
                                              LPDDENUMSURFACESCALLBACK d) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::FlipToGDISurface() {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::GetCaps(LPDDCAPS lpDDDriverCaps,
                                         LPDDCAPS lpDDHELCaps) {
  log_t::inst().printf("%s(%p, %p)\n", __func__, lpDDDriverCaps, lpDDHELCaps);

  if (lpDDDriverCaps->dwSize != sizeof(DDCAPS)) {
    return DDERR_INVALIDOBJECT;
  }

  lpDDDriverCaps->dwCaps = DDCAPS_BLT;
  lpDDDriverCaps->dwCaps2 = 0;
  lpDDDriverCaps->dwPalCaps = DDPCAPS_8BIT | DDPCAPS_ALLOW256;
  lpDDDriverCaps->dwVidMemTotal = 16 * 1024 * 1024;  // 16Mb
  lpDDDriverCaps->dwVidMemFree = 16 * 1024 * 1024;

  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::GetDisplayMode(LPDDSURFACEDESC desc) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::GetFourCCCodes(DWORD *a, DWORD *b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::GetGDISurface(LPDIRECTDRAWSURFACE *a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::GetMonitorFrequency(DWORD *a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::GetScanLine(DWORD *a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::GetVerticalBlankStatus(LPBOOL a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::Initialize(GUID *a) {
  log_t::inst().printf("%s()\n", __func__);

  memset(&_displayMode, 0, sizeof(_displayMode));
  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::RestoreDisplayMode() {
  return 0;
}

HRESULT __stdcall IDirectDraw_t::SetCooperativeLevel(HWND window, DWORD level) {
  log_t::inst().printf("%s(%p, %d)\n", __func__, window, level);

  _window = window;

  RECT rect = {0};
  if (GetClientRect(window, &rect)) {
    _displayMode._width = rect.right;
    _displayMode._height = rect.bottom;
  }

  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::SetDisplayMode(DWORD width,
                                                DWORD height,
                                                DWORD bpp) {
  log_t::inst().printf("%s(%d, %d, %d)\n", __func__, width, height, bpp);

  _displayMode._width  = width;
  _displayMode._height = height;
  _displayMode._bpp    = bpp;

  ClipCursor(nullptr);

  int32_t style = WS_OVERLAPPED | WS_TILEDWINDOW;
  int32_t styleEx = WS_EX_OVERLAPPEDWINDOW;

  LONG_PTR ptr = SetWindowLongPtrA(_window, GWL_STYLE, style);
  ptr = SetWindowLongPtrA(_window, GWL_EXSTYLE, styleEx);

  RECT rect = {0, 0, width, height};
  if (AdjustWindowRect(&rect, style, FALSE)) {
    SetWindowPos(_window,
                 HWND_NOTOPMOST,
                 64, 64,
                 (rect.right - rect.left), (rect.bottom - rect.top),
                 SWP_SHOWWINDOW | SWP_FRAMECHANGED);
  }
  else {
    MoveWindow(_window, 64, 64, width + 32, height + 32, FALSE);
  }

  UpdateWindow(_window);
  ShowWindow(_window, SW_SHOW);

  RedrawWindow(nullptr, nullptr, nullptr, RDW_INVALIDATE);

  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::WaitForVerticalBlank(DWORD a, HANDLE b) {
  __debugbreak();
  return DD_OK;
}

void IDirectDraw_t::_freeSurface(IDirectDrawSurface_t *s) {
  if (_primarySurface == s) {
    _primarySurface = nullptr;
  }
  for (auto itt = _surfaces.begin(); itt != _surfaces.end();) {
    itt = (*itt == s) ? _surfaces.erase(itt) : ++itt;
  }
}

void IDirectDraw_t::_freePalette(IDirectDrawPalette_t *p) {
  for (auto itt = _palettes.begin(); itt != _palettes.end();) {
    itt = (*itt == p) ? _palettes.erase(itt) : ++itt;
  }
}

void IDirectDraw_t::_freeClipper(IDirectDrawClipper_t *c) {
  for (auto itt = _clippers.begin(); itt != _clippers.end();) {
    itt = (*itt == c) ? _clippers.erase(itt) : ++itt;
  }
}

void IDirectDraw_t::_redrawWindow() {

  if (!_primarySurface || !_pixels) {
    return;
  }

  HDC dc = GetDC(_window);
  if (dc == NULL) {
    return;
  }

  const auto &buffer = _primarySurface->_buffer;

  IDirectDrawPalette_t *pal = _primarySurface->_palette;
  if (pal) {
    uint8_t *src = buffer._pixels + buffer._pitch * (_displayMode._height-1);
    uint32_t *dst = _pixels.get();
    for (int y = 0; y < _displayMode._height; ++y) {
      for (int x = 0; x < _displayMode._width; ++x) {

        const auto &p = pal->_entry[src[x]];

        dst[x] = (p.peRed << 16) | (p.peGreen << 8) | (p.peBlue);
      }
      dst += _displayMode._width;
      src -= buffer._pitch;
    }

  }
  
  BITMAPINFO bmp;
  memset(&bmp, 0, sizeof(bmp));
  BITMAPINFOHEADER &b = bmp.bmiHeader;
  b.biSize     = sizeof(BITMAPINFOHEADER);
  b.biBitCount = 32;
  b.biWidth    = _displayMode._width;
  b.biHeight   = _displayMode._height;
  b.biPlanes   = 1;
  b.biCompression = BI_RGB;

  const int r =
      StretchDIBits(dc,
                    // src
                    0, 0, int(b.biWidth), int(b.biHeight),
                    // dst
                    0, 0, int(b.biWidth), int(b.biHeight),
                    // pixels
                    _pixels.get(),
                    &bmp,
                    DIB_RGB_COLORS, SRCCOPY);

  ReleaseDC(_window, dc);
  ValidateRect(_window, NULL);

  // dont burn the CPU
  Sleep(1);
}
