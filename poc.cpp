#pragma leco tool

import dl;
import silog;

int main(int argc, char **argv) {
  auto h = dl::open("poc-dll");
  silog::log(silog::info, "loaded: %p", &*h);

  auto fn = reinterpret_cast<void (*)()>(h->sym("hello"));
  silog::log(silog::info, "symbol: %p", fn);

  fn();
}
