#pragma leco tool

import dl;
import silog;

int main(int argc, char **argv) {
  auto h = dl::open("poc-dll");
  silog::log(silog::info, "loaded: %p - mtime: %zd", &*h, h->mtime());

  auto fn = h->fn<void()>("hello");
  silog::log(silog::info, "symbol: %p", fn);

  // This second call is here to show a weird bug in MacOS implementation
  silog::log(silog::info, "mtime: %zd -- modified: %d", h->mtime(),
             h->modified());
  silog::log(silog::info, "mtime: %zd -- modified: %d", h->mtime(),
             h->modified());

  fn();
}
