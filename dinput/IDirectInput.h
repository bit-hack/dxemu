#pragma once

#define DIRECTINPUT_VERSION 0x300
#include <dinput.h>

#include <cstdint>


struct IDirectInputDevice_t;


struct IDirectInput_t: public IDirectInputA {

  friend IDirectInputDevice_t;

  IDirectInput_t()
    : _ref_count(1)
    , _hinst(nullptr)
    , _version(0)
  {}

  ULONG __stdcall AddRef(void) override;

  ULONG __stdcall Release(void) override;

  HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject) override;

  HRESULT __stdcall CreateDevice(REFGUID, LPDIRECTINPUTDEVICEA *,
                                 LPUNKNOWN) override;

  HRESULT __stdcall EnumDevices(DWORD, LPDIENUMDEVICESCALLBACKA, LPVOID,
                                DWORD) override;

  HRESULT __stdcall GetDeviceStatus(REFGUID) override;

  HRESULT __stdcall RunControlPanel(HWND, DWORD) override;

  HRESULT __stdcall Initialize(HINSTANCE, DWORD) override;

protected:
  int32_t _ref_count;
  HINSTANCE _hinst;
  DWORD _version;
};
