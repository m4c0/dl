module;
#include <dlfcn.h>

module dl;
import hai;

namespace dl {
class osx_lib : public lib {
  void *m_h;

public:
  explicit osx_lib(const char *name)
      : m_h{dlopen(name, RTLD_NOW | RTLD_LOCAL)} {}
  ~osx_lib() { dlclose(m_h); }

  void *sym(const char *name) { return dlsym(m_h, name); }
};

hai::uptr<lib> open(const char *name) {
  return hai::uptr<lib>{new osx_lib(name)};
}
} // namespace dl
