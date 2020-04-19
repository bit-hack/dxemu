#pragma once

#include <cstdint>
#include <intrin.h>
#include <vector>
#include <memory>

#define DIRECTDRAW_VERSION 0x300
#include <ddraw.h>

#include "types.h"
#include "log.h"


struct IDirectDraw_t : public IDirectDraw {

  friend IDirectDrawSurface_t;
  friend IDirectDrawClipper_t;
  friend IDirectDrawPalette_t;

  IDirectDraw_t()
    : _ref_count(1)
    , _window(nullptr)
    , _primarySurface(nullptr) {
  }

  ULONG __stdcall AddRef(void) override;

  ULONG __stdcall Release(void) override;

  HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject) override;

  HRESULT __stdcall Compact(void) override;

  HRESULT __stdcall CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER *b,
                                  IUnknown *c) override;

  HRESULT __stdcall CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpDDColorArray,
                                  LPDIRECTDRAWPALETTE *lplpDDPalette,
                                  IUnknown *pUnkOuter) override;

  HRESULT __stdcall CreateSurface(LPDDSURFACEDESC desc,
                                  LPDIRECTDRAWSURFACE *surf,
                                  IUnknown *pUnkOuter) override;

  HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE a,
                                     LPDIRECTDRAWSURFACE *b) override;

  HRESULT __stdcall EnumDisplayModes(DWORD a, LPDDSURFACEDESC b, LPVOID c,
                                     LPDDENUMMODESCALLBACK d) override;

  HRESULT __stdcall EnumSurfaces(DWORD a, LPDDSURFACEDESC b, LPVOID c,
                                 LPDDENUMSURFACESCALLBACK d) override;

  HRESULT __stdcall FlipToGDISurface() override;

  HRESULT __stdcall GetCaps(LPDDCAPS a, LPDDCAPS b) override;

  HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC desc) override;

  HRESULT __stdcall GetFourCCCodes(DWORD *a, DWORD *b) override;

  HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE *a) override;

  HRESULT __stdcall GetMonitorFrequency(DWORD *a) override;

  HRESULT __stdcall GetScanLine(DWORD *a) override;

  HRESULT __stdcall GetVerticalBlankStatus(LPBOOL a) override;

  HRESULT __stdcall Initialize(GUID *a) override;

  HRESULT __stdcall RestoreDisplayMode() override;

  HRESULT __stdcall SetCooperativeLevel(HWND window, DWORD level) override;

  HRESULT __stdcall SetDisplayMode(DWORD width, DWORD height,
                                   DWORD bpp) override;

  HRESULT __stdcall WaitForVerticalBlank(DWORD a, HANDLE b) override;

protected:
  void _redrawWindow();

  void _freeSurface(IDirectDrawSurface_t *s);
  void _freePalette(IDirectDrawPalette_t *p);
  void _freeClipper(IDirectDrawClipper_t *c);

  int32_t _ref_count;
  HWND _window;

  struct displayMode_t {
    uint32_t _width, _height, _bpp;
  };

  std::unique_ptr<uint32_t[]> _pixels;

  displayMode_t _displayMode;

  IDirectDrawSurface_t *_primarySurface;
  std::vector<IDirectDrawSurface_t *> _surfaces;
  std::vector<IDirectDrawPalette_t *> _palettes;
  std::vector<IDirectDrawClipper_t *> _clippers;
};
