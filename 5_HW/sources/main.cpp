#include <iostream>

#include "unique_ptr.hpp" 
//===========================================================================================================

int main()
{
    std::cout << "Create my ptr:" << std::endl;
    custom_classes::unique_ptr<int> my_ptr_1 = new int {100};
    custom_classes::unique_ptr<int> my_ptr_2 = new int {50};
    std::cout <<"my ptr_1: "<< *my_ptr_1 << " and my ptr_2: " << *my_ptr_2 << std::endl;

    std::cout << "\n\nTest copy:" << std::endl;
    custom_classes::unique_ptr<int> my_ptr_3 = std::move(my_ptr_2);
    // custom_classes::unique_ptr<int> my_ptr_3 = my_ptr_2;  // Don't work;
    std::cout <<"my ptr_1: "<< *my_ptr_1 << " and my ptr_3: " << *my_ptr_3 << std::endl;

    std::cout << "\n\nTest assignment:" << std::endl;
    my_ptr_2 = std::move(my_ptr_3);
    // my_ptr_2 = my_ptr_3;  // Don't work;
    std::cout <<"my ptr_1: "<< *my_ptr_1 << " and my ptr_2: " << *my_ptr_2 << std::endl;
    
    return 0;
}