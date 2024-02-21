#pragma leco tool

import dl;
import silog;

int main() {
  auto h = dl::open("poc-hello");
  silog::log(silog::info, "loaded: %p", &*h);

  auto fn = reinterpret_cast<void (*)()>(h->sym("hello"));
  silog::log(silog::info, "symbol: %p", fn);

  fn();
}
