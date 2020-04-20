#define DIRECTDRAW_VERSION 0x300
#include <ddraw.h>
#include <Windows.h>

#include "IDirectDraw.h"


#define DEFINE_GUID_(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const GUID DECLSPEC_SELECTANY name                             \
        = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
DEFINE_GUID_(IID_IDirectDraw,  0x6C14DB80, 0xA733, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60);
DEFINE_GUID_(IID_IDirectDraw2, 0xB3A6F3E0, 0x2B43, 0x11CF, 0xA2, 0xDE, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56);
DEFINE_GUID_(IID_IDirectDraw4, 0x9c59509a, 0x39bd, 0x11d1, 0x8c, 0x4a, 0x00, 0xc0, 0x4f, 0xd9, 0x30, 0xc5);
DEFINE_GUID_(IID_IDirectDraw7, 0x15e65ec0, 0x3b9c, 0x11d2, 0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b);


bool onPrivInstruction(struct _EXCEPTION_POINTERS *ExceptionInfo) {
  const uint32_t eip = ExceptionInfo->ContextRecord->Eip;
  uint8_t opcode = *(const uint8_t*)eip;

  // CLI instruction
  if (opcode == 0xFA) {
    // jump over it
    ExceptionInfo->ContextRecord->Eip += 1;
    return true;
  }

  return false;
}

static LONG NTAPI vectoredHandler(struct _EXCEPTION_POINTERS *ExceptionInfo) {

  switch (ExceptionInfo->ExceptionRecord->ExceptionCode) {
  case EXCEPTION_PRIV_INSTRUCTION:
    if (onPrivInstruction(ExceptionInfo)) {
      return EXCEPTION_CONTINUE_EXECUTION;
    }
    break;
  }

  return EXCEPTION_EXECUTE_HANDLER;
}

extern HRESULT WINAPI DirectDrawCreate(_In_ GUID FAR *lpGUID,
                                       _Out_ LPDIRECTDRAW FAR *lplpDD,
                                       _In_ IUnknown FAR *pUnkOuter) {

  AddVectoredExceptionHandler(1, vectoredHandler);

#pragma comment(linker, "/EXPORT:DirectDrawCreate=" __FUNCDNAME__)
  log_t::inst().printf("%s(%p, %p, %p)\n", __FUNCTION__, lpGUID, lplpDD, pUnkOuter);

  if (lpGUID) {
    if (*lpGUID == IID_IDirectDraw) {
      log_t::inst().printf("  IID_IDirectDraw requested\n");
      log_t::inst().printf("  Interface not supported!\n");
    }
    if (*lpGUID == IID_IDirectDraw2) {
      log_t::inst().printf("  IID_IDirectDraw2 requested\n");
    }
    if (*lpGUID == IID_IDirectDraw4) {
      log_t::inst().printf("  IID_IDirectDraw4 requested\n");
      log_t::inst().printf("  Interface not supported!\n");
    }
    if (*lpGUID == IID_IDirectDraw7) {
      log_t::inst().printf("  IID_IDirectDraw7 requested\n");
      log_t::inst().printf("  Interface not supported!\n");
    }
  }

  IDirectDraw_t *imp = new IDirectDraw_t;
  *lplpDD = imp;
  return imp->Initialize(lpGUID);
}

extern HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback,
                                           LPVOID lpContext) {
#pragma comment(linker, "/EXPORT:DirectDrawEnumerateA=" __FUNCDNAME__)
  log_t::inst().printf("%s(%p, %p)\n", __FUNCTION__, lpCallback, lpContext);

  // LPDDENUMCALLBACKA arguments:
  // - lpGUID
  // - lpDriverDescription
  // - lpDriverName
  // - lpContext
  if (lpCallback((GUID*)nullptr, "dxemu", "dxemu", lpContext) != DDENUMRET_OK) {
    // COMI seems to want a nullptr callback even though it doesnt take it
    log_t::inst().printf("  nullptr selected\n");
    return DD_OK;
  }
  if (lpCallback((GUID*)&IID_IDirectDraw, "dxemu", "dxemu", lpContext) != DDENUMRET_OK) {
    log_t::inst().printf("  IID_IDirectDraw selected\n");
    return DD_OK;
  }
  if (!lpCallback((GUID*)&IID_IDirectDraw2, "dxemu", "dxemu", lpContext) != DDENUMRET_OK) {
    log_t::inst().printf("  IID_IDirectDraw2 selected\n");
    return DD_OK;
  }
  if (!lpCallback((GUID*)&IID_IDirectDraw4, "dxemu", "dxemu", lpContext) != DDENUMRET_OK) {
    log_t::inst().printf("  IID_IDirectDraw4 selected\n");
    return DD_OK;
  }
  if (!lpCallback((GUID*)&IID_IDirectDraw7, "dxemu", "dxemu", lpContext) != DDENUMRET_OK) {
    log_t::inst().printf("  IID_IDirectDraw7 selected\n");
    return DD_OK;
  }

  return DD_OK;
}

BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD fdwReason,
    _In_ LPVOID lpvReserved)
{
    return TRUE;
}
