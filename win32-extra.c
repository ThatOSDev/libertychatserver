
#include "win32-extra.h"

// NOTE : Although GCC loads user32.lib by default,
//        you might still need to include it for your compiler.
// EXAMPLE : #pragma comment(lib, "user32.lib")

typedef struct tagPOINT {
  long x;
  long y;
} POINT, *LPPOINT;

__declspec(dllexport) int GetCursorPos(LPPOINT lpPoint);

struct vec2 that_getGlobalMousePos()
{
    POINT p;
    GetCursorPos(&p);
    struct vec2 v;
    v.x = (int)p.x;
    v.y = (int)p.y;
    return v;
}

