module;
#include <dlfcn.h>

module dl;

namespace dl {
class linux_lib : public lib {
  void *m_h;

public:
  explicit linux_lib(void *h) : m_h{h} {}
  ~linux_lib() { dlclose(m_h); }
  
  void *sym(const char *name) override {
    return dlsym(m_h, name);
  }
  unsigned long mtime() const noexcept override {
    return 0;
  }
};
} // namespace dl

hai::uptr<dl::lib> dl::open(const char *name) {
  auto un = jute::view::unsafe(name);
  auto fn = un + ".so";
  auto fns = fn.cstr();
  auto h = dlopen(fns.data(), RTLD_NOW | RTLD_LOCAL);
  if (!h)
    return {};

  return hai::uptr<lib>{new linux_lib(h)};
}
