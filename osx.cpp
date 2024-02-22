module;
#include <dlfcn.h>

module dl;
import hai;
import jute;

namespace dl {
class osx_lib : public lib {
  void *m_h;

public:
  explicit osx_lib(void *h) : m_h{h} {}
  ~osx_lib() { dlclose(m_h); }

  void *sym(const char *name) { return dlsym(m_h, name); }
};

// TODO: check if this works in iOS as-is
hai::uptr<lib> open(const char *name) {
  auto fn = jute::view::unsafe(name) + ".dylib";
  auto fns = fn.cstr();
  auto h = dlopen(fns.data(), RTLD_NOW | RTLD_LOCAL);
  if (!h)
    return {};

  return hai::uptr<lib>{new osx_lib(h)};
}
} // namespace dl
