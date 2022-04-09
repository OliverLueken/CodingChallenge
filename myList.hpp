#ifndef MYLIST_HPP
#define MYLIST_HPP

namespace myList{
    struct Node{
        int value{};
        Node* next{nullptr};
    };

    Node* make_list(int value){
        auto head = new Node{value};
        return head;
    }
}

#endif