#pragma leco app
#pragma leco add_build_dep "poc-dll.cpp"

import dl;
import silog;

int main(int argc, char **argv) {
  auto h = dl::open("poc-dll");
  auto fn = h->fn<void()>("hello");
  fn();
}
