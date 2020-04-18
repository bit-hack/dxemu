#include "IDirectInputDevice.h"
#include "log.h"

ULONG __stdcall IDirectInputDevice_t::AddRef(void) {
  __debugbreak();
  return ++_ref_count;
}

ULONG __stdcall IDirectInputDevice_t::Release(void) {
  __debugbreak();
  if (--_ref_count == 0) {
    // free thy self!
    delete this;
    return 0;
  }
  return _ref_count;
}

HRESULT __stdcall IDirectInputDevice_t::QueryInterface(REFIID riid,
                                                       void **ppvObject) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::GetCapabilities(LPDIDEVCAPS) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::EnumObjects(
    LPDIENUMDEVICEOBJECTSCALLBACKA, LPVOID, DWORD) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::GetProperty(REFGUID, LPDIPROPHEADER) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::SetProperty(REFGUID, LPCDIPROPHEADER) {
  //  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::Acquire() {
  //  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::Unacquire() {
  //  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::GetDeviceState(DWORD cbData,
                                                       LPVOID lpvData) {
  //  __debugbreak();

  memset(lpvData, 0, cbData);

  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::GetDeviceData(
    DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut,
    DWORD dwFlags) {
  //  __debugbreak();

  *pdwInOut = 0;

  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::SetDataFormat(LPCDIDATAFORMAT) {
  //  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::SetEventNotification(HANDLE) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::SetCooperativeLevel(HWND, DWORD) {
  //  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA,
                                                      DWORD, DWORD) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::GetDeviceInfo(LPDIDEVICEINSTANCEA) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::RunControlPanel(HWND, DWORD) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::Initialize(HINSTANCE hinst,
                                                   DWORD dwVersion,
                                                   REFGUID guid) {
  //  __debugbreak();
  return DI_OK;
}
