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

    template<typename ValueType>
    void print(const Node<ValueType>* head){
        auto currentNodePtr = head;
        std::cout << "List: ";
        while(currentNodePtr != nullptr){
            std::cout << currentNodePtr->value << ' ';
            currentNodePtr = currentNodePtr->next;
        }
        std::cout << '\n';
    }

    template<typename ValueType>
    Node<ValueType>* advance(Node<ValueType>* head, const unsigned int k){
        auto stepsTaken = 0u;
        auto advancedNodePtr = head;
        while(stepsTaken<k && advancedNodePtr != nullptr){
            advancedNodePtr = advancedNodePtr->next;
            ++stepsTaken;
        }
        return advancedNodePtr;
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

    template<typename ValueType>
    Node<ValueType>* reverseGroups(Node<ValueType>*& head, const unsigned int k){
        if( k<=1 ) return head;

        auto currentGroupHead = head;
        auto currentGroupTail = advance(head, k-1);
        const auto newHead = currentGroupTail;

        while(currentGroupTail != nullptr){
            //remove group from list
            //reverse group
            //insert group
            //update pointer
        }

        return newHead;
    }
}

#endif