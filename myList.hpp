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
    A list created with make_list has to be destroyed with delete_list to not leak memory
    */
    template<typename ValueType>
    Node<ValueType>* make_list(ValueType&& value){
        auto head = new Node<ValueType>{std::forward<ValueType>(value)};
        return head;
    }

    /*
    Creates a list consisting of the elements passed in
    Returns a pointer to the head of the list
    */
    template<typename ValueType, typename... ValueTypes>
    Node<ValueType>* make_list(ValueType&& value, ValueTypes&&... values){
        auto head = new Node<ValueType>{std::forward<ValueType>(value)};
        head->next = make_list(std::forward<ValueTypes>(values)...);
        return head;
    }

    /*
    Expects the head of a list and destroys every node in that list
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

    template<typename ValueType>
    void print(const Node<ValueType>* head){
        auto currentNodePtr = head;
        while(currentNodePtr != nullptr){
            std::cout << currentNodePtr->value << ' ';
            currentNodePtr = currentNodePtr->next;
        }
        std::cout << '\n';
    }

    /*
    Receives a pointer to a list nodePtr and a positive integer n and
    returns the pointer to the nth next element in the list
    returns nullptr if list contains less than n+1 elements
    */
    template<typename ValueType>
    Node<ValueType>* advance(Node<ValueType>* nodePtr, unsigned int n){
        while(n>0 && nodePtr != nullptr){
            nodePtr = nodePtr->next;
            --n;
        }
        return nodePtr;
    }

    /*
    Reverses the elements inside the list
    Returns a pointer to the head of the reversed list
    The passed in head pointer stays valid and points to the last element in the list
    */
    template<typename ValueType>
    Node<ValueType>* reverse_list(Node<ValueType>* head){
        auto lastNodePtr = head;
        auto currentNodePtr = head->next;

        head->next = nullptr;
        while(currentNodePtr != nullptr){
            auto nextNodePtr = currentNodePtr->next;
            currentNodePtr->next = lastNodePtr;

            lastNodePtr = currentNodePtr;
            currentNodePtr = nextNodePtr;
        }
        return lastNodePtr;
    }

    /*
    Removes the nodes following nodePtr from the list
    Return pointer to the node that followed nodePtr
    */
    template<typename ValueType>
    Node<ValueType>* split_after(Node<ValueType>* nodePtr){
        auto newListHead = nodePtr->next;
        nodePtr->next = nullptr;
        return newListHead;
    }

    /*
    Merges two lists
    */
    template<typename ValueType>
    void merge_lists(Node<ValueType>* firstList, Node<ValueType>* secondList){
        auto lastNodePtr = firstList;
        while(lastNodePtr->next != nullptr){
            lastNodePtr = lastNodePtr->next;
        }
        lastNodePtr->next = secondList;
    }

    /*
    Devides list in groups of size k and reverses each group, nodes at the end of the list that do not fill a whole group are not reversed
    Returns a pointer to the head of the modified list
    */
    template<typename ValueType>
    Node<ValueType>* reverse_groups(Node<ValueType>* head, const unsigned int k){
        if( k<=1 ) return head;

        auto currentGroupHead = head;
        auto currentGroupTail = advance(head, k-1);
        if(currentGroupTail == nullptr) return head; //k is greater than nodes in the list 
        head = currentGroupTail;

        //remove group from list
        auto nextGroupHead = split_after(currentGroupTail);

        //reverse group
        currentGroupTail = currentGroupHead;
        currentGroupHead = reverse_list(currentGroupHead);

        //insert group
        merge_lists(currentGroupTail, nextGroupHead);

        //update pointer
        auto lastGroupTail = currentGroupTail;
        currentGroupTail = advance(nextGroupHead, k-1);

        while(currentGroupTail != nullptr){
            currentGroupHead = nextGroupHead;

            //remove group from list
            lastGroupTail->next = nullptr;
            nextGroupHead = split_after(currentGroupTail);

            //reverse group
            currentGroupTail = currentGroupHead;
            currentGroupHead = reverse_list(currentGroupHead);

            //insert group
            lastGroupTail->next = currentGroupHead;
            merge_lists(currentGroupTail, nextGroupHead);

            //update pointer
            lastGroupTail = currentGroupTail;
            currentGroupTail = advance(nextGroupHead, k-1);
        }

        return head;
    }
}

#endif