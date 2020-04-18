#pragma once

#include "IDirectDrawClipper.h"

ULONG __stdcall IDirectDrawClipper_t::AddRef(void) {
  __debugbreak();
  return ++_ref_count;
}

ULONG __stdcall IDirectDrawClipper_t::Release(void) {
  __debugbreak();
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectDrawClipper_t::QueryInterface(REFIID riid,
                                                       void **ppvObject) {
  __debugbreak();
  return E_NOINTERFACE;
}

HRESULT __stdcall IDirectDrawClipper_t::GetClipList(LPRECT a, LPRGNDATA b,
                                                    DWORD *c) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawClipper_t::GetHWnd(HWND *a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawClipper_t::Initialize(IDirectDraw *a, DWORD b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawClipper_t::IsClipListChanged(int *a) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawClipper_t::SetClipList(LPRGNDATA a, DWORD b) {
  __debugbreak();
  return 0;
}

HRESULT __stdcall IDirectDrawClipper_t::SetHWnd(DWORD a, HWND b) {
  __debugbreak();
  return 0;
}
