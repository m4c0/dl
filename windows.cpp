module;
#define WIN32_LEAN_AND_MEAN
#include <sys/stat.h>
#include <windows.h>

module dl;
import hai;

namespace dl {
class win_lib : public lib {
  HMODULE m_h;

public:
  explicit win_lib(HMODULE h) : m_h{h} { lib::mtime(mtime()); }
  ~win_lib() { FreeLibrary(m_h); }

  void *sym(const char *name) override { return GetProcAddress(m_h, name); }

  unsigned long mtime() const noexcept override {
    char buf[1024]{};
    GetModuleFileNameA(m_h, buf, sizeof(buf));

    struct __stat64 s {};
    _stat64(buf, &s);
    return s.st_mtime;
  }
};

hai::uptr<lib> open(const char *name) {
  auto h = LoadLibraryA(name);
  if (!h)
    return {};

  return hai::uptr<lib>{new win_lib(h)};
}
} // namespace dl
