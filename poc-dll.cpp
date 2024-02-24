#pragma leco dll
import silog;

#ifdef LECO_TARGET_WINDOWS
#define A __declspec(dllexport)
#else
#define A
#endif

extern "C" A void hello() { silog::log(silog::info, "inside dll"); }
