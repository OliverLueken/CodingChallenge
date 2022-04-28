
#include <algorithm>
#include <iostream>

#include "myList.hpp"

template<typename... ListValues>
auto test_reverse_group(unsigned int k, ListValues&&... values){
    auto list = myList::make_list(std::forward<ListValues>(values)...);

    std::cout << "Testing reverse_groups with k = " << k << '\n';
    std::cout << "Before: ";
    myList::print(list);

    myList::reverse_groups(list, k);
    std::cout << "After:  ";
    myList::print(list);
    std::cout << '\n';
}

int main(){
    for(auto k=0; k<17; ++k){
        test_reverse_group(k, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    }
}