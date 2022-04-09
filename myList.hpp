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
    Creates a list consisting of the elements passed in
    Returns a pointer to the head of the list
    */
    template<typename... ValueTypes>
    Node* make_list(int value, ValueTypes&&... values){
        auto head = new Node{value};
        head->next = make_list(values...);
        return head;
    }

    /*
    Exptects the head of a list and destroys every node in that list
    */
    void delete_list(Node*& head){
        auto currentNodePtr = head;
        while(currentNodePtr != nullptr){
            auto nextNodePtr = currentNodePtr->next;
            delete currentNodePtr;
            currentNodePtr = nextNodePtr;
        }
        head = nullptr;
    }
}

#endif