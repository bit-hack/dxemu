#include <map>

#define INITGUID
#include "IDirectInputDevice.h"
#include "IDirectInput.h"
#include "log.h"


static const std::map<uint8_t, uint8_t> keyMap = {
  {VK_ESCAPE    , DIK_ESCAPE   },
  {VK_LEFT      , DIK_LEFT     },
  {VK_RIGHT     , DIK_RIGHT    },
  {VK_UP        , DIK_UP       },
  {VK_DOWN      , DIK_DOWN     },
  {VK_LCONTROL  , DIK_LCONTROL },
  {VK_LSHIFT    , DIK_LSHIFT   },
  {VK_RETURN    , DIK_RETURN   },
  {VK_SPACE     , DIK_SPACE    },
  {VK_TAB       , DIK_TAB      },
  {VK_DELETE    , DIK_DELETE   },
  {VK_BACK      , DIK_BACKSPACE},
  {'A'          , DIK_A        },
  {'B'          , DIK_B        },
  {'C'          , DIK_C        },
  {'D'          , DIK_D        },
  {'E'          , DIK_E        },
  {'F'          , DIK_F        },
  {'G'          , DIK_G        },
  {'H'          , DIK_H        },
  {'I'          , DIK_I        },
  {'J'          , DIK_J        },
  {'K'          , DIK_K        },
  {'L'          , DIK_L        },
  {'M'          , DIK_M        },
  {'N'          , DIK_N        },
  {'O'          , DIK_O        },
  {'P'          , DIK_P        },
  {'Q'          , DIK_Q        },
  {'R'          , DIK_R        },
  {'S'          , DIK_S        },
  {'T'          , DIK_T        },
  {'U'          , DIK_U        },
  {'V'          , DIK_V        },
  {'W'          , DIK_W        },
  {'X'          , DIK_X        },
  {'Y'          , DIK_Y        },
  {'Z'          , DIK_Z        },
  {'0'          , DIK_0        },
  {'1'          , DIK_1        },
  {'2'          , DIK_2        },
  {'3'          , DIK_3        },
  {'4'          , DIK_4        },
  {'5'          , DIK_5        },
  {'6'          , DIK_6        },
  {'7'          , DIK_7        },
  {'8'          , DIK_8        },
  {'9'          , DIK_9        },
  {VK_OEM_MINUS , DIK_MINUS    },
  {VK_F6        , DIK_F6       },
  {VK_F7        , DIK_F7       },
  {VK_F12       , DIK_F12      },
};

static LRESULT CALLBACK WndProcHook(HWND hwnd,
                                    UINT uMsg,
                                    WPARAM wParam,
                                    LPARAM lParam) {

  bool ungrab = false;

  switch (uMsg) {
  case WM_ACTIVATE:
    switch (wParam) {
    case WA_INACTIVE:
      ungrab = true;
      break;
    }
    break;
  case WM_KILLFOCUS:
    ungrab = true;
    break;
  }

  if (ungrab) {
    ClipCursor(nullptr);
  }

  WNDPROC oldProc = (WNDPROC)GetWindowLong(hwnd, GWL_USERDATA);
  return CallWindowProcA(oldProc, hwnd, uMsg, wParam, lParam);
}

ULONG __stdcall IDirectInputDevice_t::AddRef(void) {
  __debugbreak();
  return ++_ref_count;
}

ULONG __stdcall IDirectInputDevice_t::Release(void) {
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

  if (*_guid == GUID_SysMouse) {

    DIMOUSESTATE state;
    memset(&state, 0, sizeof(state));

    POINT pos = {0, 0};
    GetCursorPos(&pos);

    state.lX = pos.x - _old_mouse_pos.x;
    state.lY = pos.y - _old_mouse_pos.y;

    SHORT lmb = GetAsyncKeyState(VK_LBUTTON);
    SHORT rmb = GetAsyncKeyState(VK_RBUTTON);

    state.rgbButtons[0] = lmb ? 0xff : 0x00;
    state.rgbButtons[1] = rmb ? 0xff : 0x00;

    memcpy(lpvData, &state, sizeof(state));

    if (GetFocus() == _window) {
      RECT rect = {0};
      if (GetClientRect(_window, &rect)) {
        // find the middle of the window
        rect.right /= 2;
        rect.bottom /= 2;
        POINT p = {rect.right / 2, rect.bottom / 2};
        if (ClientToScreen(_window, &p)) {
          // set the cursor to the middle of the screen
          SetCursorPos(p.x, p.y);
          _old_mouse_pos = p;
        }
      }

      {
        RECT r = {0};
        if (GetClientRect(_window, &r)) {
          POINT lo = {0, 0};
          if (ClientToScreen(_window, &lo)) {
            POINT hi = {r.right, r.bottom};
            if (ClientToScreen(_window, &hi)) {
              RECT c = {lo.x, lo.y, hi.x + 1, hi.y + 1};
              ClipCursor(&c);
            }
          }
        }
      }

    }
  }

  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::GetDeviceData(
    DWORD cbObjectData,
    LPDIDEVICEOBJECTDATA rgdod,
    LPDWORD pdwInOut,
    DWORD dwFlags) {

  if (!rgdod) {
    *pdwInOut = 0;
    return DI_OK;
  }

  const DWORD max = *pdwInOut;
  DWORD i = 0;

  if (*_guid == GUID_SysKeyboard) {
    for (auto &p : keyMap) {

      if (i >= max) {
        break;
      }

      SHORT state = GetAsyncKeyState(p.first) & 0x8000;
      if (_key_state[p.first] != state) {
        rgdod[i].dwOfs = p.second;
        rgdod[i].dwData = state ? 0x80 : 0;
        rgdod[i].dwSequence = 0;
        rgdod[i].dwTimeStamp = 0;
        ++i;
      }
      _key_state[p.first] = state;
    }
  }

  *pdwInOut = i;

  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::SetDataFormat(LPCDIDATAFORMAT lpFormat) {
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::SetEventNotification(HANDLE) {
  __debugbreak();
  return DI_OK;
}

HRESULT __stdcall IDirectInputDevice_t::SetCooperativeLevel(HWND hwnd, DWORD dwFlags) {

  _window = hwnd;

  if (*_guid == GUID_SysMouse) {
    const LONG oldProc = GetWindowLongPtrA(_window, GWLP_WNDPROC);
    if (oldProc) {
      SetWindowLongPtrA(_window, GWLP_USERDATA, oldProc);
      SetWindowLongPtrA(_window, GWLP_WNDPROC, (LONG)WndProcHook);
    }
  }

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

  std::memset(_key_state, 0, sizeof(_key_state));

  // save the guid
  _guid = &guid;
  return DI_OK;
}
