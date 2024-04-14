#pragma leco dll
import silog;

#ifdef LECO_TARGET_WINDOWS
#define A __declspec(dllexport)
#else
#define A
#endif

struct global_scope_test {
  global_scope_test() { silog::log(silog::info, "dll loaded"); }
  ~global_scope_test() { silog::log(silog::info, "dll unloaded"); }
} i;

extern "C" A void hello() { silog::log(silog::info, "inside dll"); }
