#pragma leco app
#pragma leco add_build_dep "poc-dll.cpp"

import dl;
import silog;
import sitime;

int main(int argc, char **argv) {
  while (true) {
    auto h = dl::open("poc-dll");
    auto fn = h->fn<void()>("hello");
    fn();

    while (!h->modified()) {
      sitime::sleep(1);
    }
  }
}
