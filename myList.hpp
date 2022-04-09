#ifndef MYLIST_HPP
#define MYLIST_HPP

namespace myList{
    struct Node{
        int value{};
        Node* next{nullptr};
    };

    /*
    Creates a list with one element
    Returns a pointer to a Node containing the passed in value
    */
    Node* make_list(int value){
        auto head = new Node{value};
        return head;
    }

    /*
    Exptects the head of a list and destroys every node in that list
    */
    void delete_list(Node* head){
        auto currentNodePtr = head;
        while(currentNodePtr != nullptr){
            auto nextNodePtr = currentNodePtr->next;
            delete currentNodePtr;
            currentNodePtr = nextNodePtr;
        }
    }
}

#endif