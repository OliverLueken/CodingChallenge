#ifndef MYLIST_HPP
#define MYLIST_HPP

namespace myList{
    template<typename ValueType>
    struct Node{
        ValueType value{};
        Node<ValueType>* next{nullptr};
    };

    /*
    Creates a list with one element
    Returns a pointer to a Node containing the passed in value
    */
    template<typename ValueType>
    Node<ValueType>* make_list(ValueType value){
        auto head = new Node<ValueType>{value};
        return head;
    }

    /*
    Creates a list consisting of the elements passed in
    Returns a pointer to the head of the list
    */
    template<typename ValueType, typename... ValueTypes>
    Node<ValueType>* make_list(ValueType value, ValueTypes&&... values){
        auto head = new Node<ValueType>{value};
        head->next = make_list(values...);
        return head;
    }

    /*
    Exptects the head of a list and destroys every node in that list
    */
    template<typename ValueType>
    void delete_list(Node<ValueType>*& head){
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