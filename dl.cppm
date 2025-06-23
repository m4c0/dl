export module dl;
import hai;

namespace dl {
export class lib {
  unsigned long m_time{};

protected:
  void mtime(unsigned long t) { m_time = t; }

public:
  virtual ~lib() = default;
  virtual void *sym(const char *name) = 0;

  template <typename Fn> [[nodiscard]] auto fn(const char *name) {
    return reinterpret_cast<Fn *>(sym(name));
  }

  [[nodiscard]] virtual unsigned long mtime() const noexcept = 0;

  [[nodiscard]] bool modified() const noexcept { return m_time < mtime(); }
};

export hai::uptr<lib> open(const char *name);
} // namespace dl

#if LECO_TARGET_MACOSX
#pragma leco add_impl "osx.cpp"
#elif LECO_TARGET_WINDOWS
#pragma leco add_impl "windows.cpp"
#elif LECO_TARGET_LINUX
#pragma leco add_impl "linux.cpp"
#else
#error Unsupported platform
#endif
