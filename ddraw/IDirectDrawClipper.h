#pragma once

#include <cstdint>
#include <intrin.h>

#define DIRECTDRAW_VERSION 0x300
#include <ddraw.h>

#include "types.h"

struct IDirectDrawClipper_t : public IDirectDrawClipper {

  IDirectDrawClipper_t(IDirectDraw_t *ddraw) : _ref_count(1), _ddraw(ddraw) {}

  ULONG __stdcall AddRef(void) override;

  ULONG __stdcall Release(void) override;

  HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject) override;

  HRESULT __stdcall GetClipList(LPRECT a, LPRGNDATA b, DWORD *c) override;

  HRESULT __stdcall GetHWnd(HWND *a) override;

  HRESULT __stdcall Initialize(IDirectDraw *a, DWORD b) override;

  HRESULT __stdcall IsClipListChanged(int *a) override;

  HRESULT __stdcall SetClipList(LPRGNDATA a, DWORD b) override;

  HRESULT __stdcall SetHWnd(DWORD a, HWND b) override;

protected:
  int32_t _ref_count;
  IDirectDraw_t *_ddraw;
};
