#include "shared_ptr.hpp"
#include <memory>


int main() {
    custom_classes::shared_ptr<int> sh_ptr_1 {new int {7}};
    std::cout << *sh_ptr_1 << std::endl;
    return 0;
}  