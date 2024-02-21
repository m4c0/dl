#pragma leco dll
import silog;

extern "C" void hello() { silog::log(silog::info, "inside dll"); }
