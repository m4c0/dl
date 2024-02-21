module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

module dl;
import hai;

namespace dl {
class win_lib : public lib {
  HMODULE m_h;

public:
  explicit win_lib(HMODULE h) : m_h{h} {}
  ~win_lib() { FreeLibrary(m_h); }

  void *sym(const char *name) { return GetProcAddress(m_h, name); }
};

hai::uptr<lib> open(const char *name) {
  auto h = LoadLibraryA(name);
  if (!h)
    return {};

  return hai::uptr<lib>{new win_lib(name)};
}
} // namespace dl
