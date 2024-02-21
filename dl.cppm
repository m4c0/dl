export module dl;

#if LECO_TARGET_MACOSX
#pragma leco add_impl "osx.cpp"
#elif LECO_TARGET_WINDOWS
#pragma leco add_impl "windows.cpp"
#else
#error Unsupported platform
#endif
