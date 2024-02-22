export module dl;
import hai;
import jute;

export namespace dl {
class lib {
public:
  virtual ~lib() = default;
  virtual void *sym(const char *name) = 0;

  template <typename Fn> [[nodiscard]] auto fn(const char *name) {
    return reinterpret_cast<Fn *>(sym(name));
  }
};

hai::uptr<lib> open(const char *name);
} // namespace dl

#if LECO_TARGET_MACOSX
#pragma leco add_impl "osx.cpp"
#elif LECO_TARGET_WINDOWS
#pragma leco add_impl "windows.cpp"
#else
#error Unsupported platform
#endif
