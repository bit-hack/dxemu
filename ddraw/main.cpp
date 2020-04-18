#define DIRECTDRAW_VERSION 0x300
#include <ddraw.h>
#include <Windows.h>

#include "IDirectDraw.h"


#define DEFINE_GUID_(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const GUID DECLSPEC_SELECTANY name                       \
        = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
DEFINE_GUID_(IID_IDirectDraw,  0x6C14DB80, 0xA733, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60);
DEFINE_GUID_(IID_IDirectDraw2, 0xB3A6F3E0, 0x2B43, 0x11CF, 0xA2, 0xDE, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56);
DEFINE_GUID_(IID_IDirectDraw4, 0x9c59509a, 0x39bd, 0x11d1, 0x8c, 0x4a, 0x00, 0xc0, 0x4f, 0xd9, 0x30, 0xc5);
DEFINE_GUID_(IID_IDirectDraw7, 0x15e65ec0, 0x3b9c, 0x11d2, 0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b);


extern HRESULT WINAPI DirectDrawCreate(
    _In_ GUID FAR* lpGUID,
    _Out_ LPDIRECTDRAW FAR* lplpDD,
    _In_ IUnknown FAR* pUnkOuter)
{
#pragma comment(linker, "/EXPORT:DirectDrawCreate=" __FUNCDNAME__)

    IDirectDraw_t * imp = new IDirectDraw_t;
    *lplpDD = imp;

    return imp->Initialize(lpGUID);
}

BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD fdwReason,
    _In_ LPVOID lpvReserved)
{
    return TRUE;
}
