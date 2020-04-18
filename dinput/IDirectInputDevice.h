#define DIRECTINPUT_VERSION 0x300
#include <dinput.h>

#include <cstdint>

struct IDirectInput_t;

struct IDirectInputDevice_t : public IDirectInputDeviceA {

  IDirectInputDevice_t(IDirectInput_t *dinput)
    : _ref_count(1)
    , _dinput(dinput)
    , _format(nullptr) {}

  ULONG __stdcall AddRef(void) override;

  ULONG __stdcall Release(void) override;

  HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject) override;

  HRESULT __stdcall GetCapabilities(LPDIDEVCAPS) override;
  HRESULT __stdcall EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA, LPVOID,
                                DWORD) override;
  HRESULT __stdcall GetProperty(REFGUID, LPDIPROPHEADER) override;
  HRESULT __stdcall SetProperty(REFGUID, LPCDIPROPHEADER) override;
  HRESULT __stdcall Acquire() override;
  HRESULT __stdcall Unacquire() override;
  HRESULT __stdcall GetDeviceState(DWORD, LPVOID) override;
  HRESULT __stdcall GetDeviceData(DWORD, LPDIDEVICEOBJECTDATA, LPDWORD,
                                  DWORD) override;
  HRESULT __stdcall SetDataFormat(LPCDIDATAFORMAT) override;
  HRESULT __stdcall SetEventNotification(HANDLE) override;
  HRESULT __stdcall SetCooperativeLevel(HWND, DWORD) override;
  HRESULT __stdcall GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA, DWORD,
                                  DWORD) override;
  HRESULT __stdcall GetDeviceInfo(LPDIDEVICEINSTANCEA) override;
  HRESULT __stdcall RunControlPanel(HWND, DWORD) override;
  HRESULT __stdcall Initialize(HINSTANCE, DWORD, REFGUID) override;

protected:
  int32_t _ref_count;
  IDirectInput_t *_dinput;
  const GUID *_guid;
  const DIDATAFORMAT *_format;

  POINT _old_mouse_pos;
};
