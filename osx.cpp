module;
#include <dlfcn.h>

module dl;
import hai;

namespace dl {
class osx_lib : public lib {
  void *m_h;

public:
  explicit osx_lib(void *h) : m_h{h} {}
  ~osx_lib() { dlclose(m_h); }

  void *sym(const char *name) { return dlsym(m_h, name); }
};

hai::uptr<lib> open(const char *name) {
  auto h = dlopen(name, RTLD_NOW | RTLD_LOCAL);
  if (!h)
    return {};

  return hai::uptr<lib>{new osx_lib(h)};
}
} // namespace dl
