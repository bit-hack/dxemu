#pragma once

#include "IDirectDraw.h"
#include "IDirectDrawClipper.h"
#include "IDirectDrawPalette.h"
#include "IDirectDrawSurface.h"

ULONG __stdcall IDirectDraw_t::AddRef(void) {
  __debugbreak();
  return ++_ref_count;
}

ULONG __stdcall IDirectDraw_t::Release(void) {
  __debugbreak();
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectDraw_t::QueryInterface(REFIID riid, void **ppvObject) {
  if (!ppvObject) {
    return E_POINTER;
  }
  *ppvObject = nullptr;
  if (riid == IID_IDirectDraw) {
    __debugbreak();
    return E_NOINTERFACE;
  }
  if (riid == IID_IDirectDraw2) {
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
  *lplpDDrawClipper = nullptr;
  IDirectDrawClipper_t *clipper = new IDirectDrawClipper_t(this);
  HRESULT res = clipper->Initialize(this, dwFlags);
  if (res == DD_OK) {
    *lplpDDrawClipper = clipper;
    return DD_OK;
  }
  clipper->Release();
  return res;
}

HRESULT __stdcall IDirectDraw_t::CreatePalette(
    DWORD dwFlags, LPPALETTEENTRY lpDDColorArray,
    LPDIRECTDRAWPALETTE *lplpDDPalette, IUnknown *pUnkOuter) {

//  __debugbreak();
  *lplpDDPalette = nullptr;
  IDirectDrawPalette_t *palette = new IDirectDrawPalette_t(this);
  HRESULT res = palette->Initialize(this, dwFlags, lpDDColorArray);
  if (res == DD_OK) {
    *lplpDDPalette = palette;
    return DD_OK;
  }
  palette->Release();
  return res;
}

HRESULT __stdcall IDirectDraw_t::CreateSurface(
    LPDDSURFACEDESC desc, LPDIRECTDRAWSURFACE *lplpDDSurface,
    IUnknown *pUnkOuter) {

//  __debugbreak();
  *lplpDDSurface = nullptr;
  IDirectDrawSurface_t *surface = new IDirectDrawSurface_t(this);
  HRESULT res = surface->Initialize(this, desc);
  if (res == DD_OK) {
    *lplpDDSurface = surface;
    return DD_OK;
  }
  surface->Release();
  return res;
}

HRESULT __stdcall IDirectDraw_t::DuplicateSurface(LPDIRECTDRAWSURFACE a,
                                                  LPDIRECTDRAWSURFACE *b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::EnumDisplayModes(DWORD a, LPDDSURFACEDESC b,
                                                  LPVOID c,
                                                  LPDDENUMMODESCALLBACK d) {
  __debugbreak();
  return 0;
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

HRESULT __stdcall IDirectDraw_t::GetCaps(LPDDCAPS a, LPDDCAPS b) {
  __debugbreak();
  return 0;
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
  memset(&_displayMode, 0, sizeof(_displayMode));
  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::RestoreDisplayMode() {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDraw_t::SetCooperativeLevel(HWND window, DWORD level) {

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

  _displayMode._width  = width;
  _displayMode._height = height;
  _displayMode._bpp    = bpp;

  ClipCursor(nullptr);

  LONG_PTR ptr = SetWindowLongPtrA(_window, GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW);
  BOOL res = SetWindowPos(_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

  UpdateWindow(_window);
  ShowWindow(_window, SW_SHOW);

  return DD_OK;
}

HRESULT __stdcall IDirectDraw_t::WaitForVerticalBlank(DWORD a, HANDLE b) {
  __debugbreak();
  return 0;
}
