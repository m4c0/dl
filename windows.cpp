module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

module dl;
import hai;

namespace dl {
class win_lib : public lib {
  HMODULE m_h;

public:
  explicit win_lib(const char *name) : m_h{LoadLibraryA(name)} {}
  ~win_lib() { FreeLibrary(m_h); }

  void *sym(const char *name) { return GetProcAddress(m_h, name); }
};

hai::uptr<lib> open(const char *name) {
  return hai::uptr<lib>{new win_lib(name)};
}
} // namespace dl
