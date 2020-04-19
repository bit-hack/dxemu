#include "IDirectInput.h"
#include "IDirectInputDevice.h"
#include "log.h"

ULONG __stdcall IDirectInput_t::AddRef(void) {
  __debugbreak();
  return ++_ref_count;
}

ULONG __stdcall IDirectInput_t::Release(void) {
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectInput_t::QueryInterface(REFIID riid,
                                                 void **ppvObject) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInput_t::CreateDevice(REFGUID guid,
                                               LPDIRECTINPUTDEVICEA *lpDIDevice,
                                               LPUNKNOWN) {

  IDirectInputDevice_t *inst = new IDirectInputDevice_t(this);
  HRESULT res = inst->Initialize(_hinst, _version, guid);

  *lpDIDevice = nullptr;

  if (res == DI_OK) {
    *lpDIDevice = inst;
    return DI_OK;
  }

  return res;
}

HRESULT __stdcall IDirectInput_t::EnumDevices(DWORD, LPDIENUMDEVICESCALLBACKA,
                                              LPVOID, DWORD) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInput_t::GetDeviceStatus(REFGUID) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInput_t::RunControlPanel(HWND, DWORD) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInput_t::Initialize(HINSTANCE hInst, DWORD dwVersion) {

  _hinst = hInst;
  _version = dwVersion;

  return DI_OK;
}
