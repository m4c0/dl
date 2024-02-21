export module dl;
import hai;

export namespace dl {
class lib {
public:
  virtual ~lib() = default;
  virtual void *sym(const char *name) = 0;
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
