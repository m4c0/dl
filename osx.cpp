module;
#include <dlfcn.h>
#include <stdio.h>
#include <sys/stat.h>

module dl;
import hai;
import jute;
import mtime;

namespace dl {
class osx_lib : public lib {
  void *m_h;
  void *m_last_sym;

public:
  explicit osx_lib(void *h) : m_h{h} {}
  ~osx_lib() { dlclose(m_h); }

  void *sym(const char *name) override {
    bool first = m_last_sym == nullptr;
    m_last_sym = dlsym(m_h, name);
    if (first)
      lib::mtime(mtime());
    return m_last_sym;
  }

  unsigned long mtime() const noexcept override {
    // Using a address/symbol from the library is the only sane way to fetch the
    // library path in OSX. Somehow it gets worse if we use dyld's functions.
    Dl_info dli{};
    dladdr(m_last_sym, &dli);
    return mtime::of(dli.dli_fname);
  }
};

// TODO: check if this works in iOS as-is
hai::uptr<lib> open(const char *name) {
  auto un = jute::view::unsafe(name);
  auto fn = un + ".dylib";
  auto fns = fn.cstr();
  auto h = dlopen(fns.data(), RTLD_NOW | RTLD_LOCAL);
  if (!h)
    return {};

  return hai::uptr<lib>{new osx_lib(h)};
}
} // namespace dl
