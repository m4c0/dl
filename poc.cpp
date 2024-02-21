#pragma leco tool

import dl;
import silog;

int main(int argc, char **argv) {
  // TODO: better path detection (like an rpath?)
  auto h = dl::open(argv[1]);
  silog::log(silog::info, "loaded: %p", &*h);

  auto fn = reinterpret_cast<void (*)()>(h->sym("hello"));
  silog::log(silog::info, "symbol: %p", fn);

  fn();
}
