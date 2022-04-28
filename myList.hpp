#ifndef MYLIST_HPP
#define MYLIST_HPP

#include <algorithm>
#include <iostream>

namespace myList{
    template<typename ValueType>
    struct Node{
        ValueType value{};
        Node<ValueType>* next{nullptr};
    };

    /*
    Expects the head of a list and destroys every node in that list
    */
    template<typename ValueType>
    void delete_list(Node<ValueType>* head){
        auto currentNodePtr = head;
        while(currentNodePtr != nullptr){
            auto nextNodePtr = currentNodePtr->next;
            delete currentNodePtr;
            currentNodePtr = nextNodePtr;
        }
    }

    template<typename ValueType>
    using List = std::unique_ptr<
        Node<ValueType>,
        decltype(&delete_list<ValueType>)
    >;

    /*
    Creates a list with one element
    Returns a pointer to a Node containing the passed in value
    A list created with make_list has to be destroyed with delete_list to not leak memory
    */
    template<typename ValueType>
    List<ValueType> make_list(ValueType&& value){
        return List<ValueType>{
            new Node<ValueType>{std::forward<ValueType>(value)},
            &delete_list<ValueType>
        };
    }

    /*
    Creates a list consisting of the elements passed in
    Returns a pointer to the head of the list
    */
    template<typename ValueType, typename... ValueTypes>
    List<ValueType> make_list(ValueType&& value, ValueTypes&&... values){
        auto head  = make_list(std::forward<ValueType>(value));
        head->next = make_list(std::forward<ValueTypes>(values)...).release();
        return head;
    }


    template<typename ValueType>
    void print(const List<ValueType>& head){
        auto currentNodePtr = head.get();
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
    Returns a pointer to the last element of the reversed list
    Iterators to elements of the list stay valid
    */
    template<typename ValueType>
    Node<ValueType>* reverse_list(List<ValueType>& list){
        auto lastNodePtr = list.release();
        const auto lastElementPtr = lastNodePtr;
        auto currentNodePtr = lastNodePtr->next;

        lastNodePtr->next = nullptr;
        while(currentNodePtr != nullptr){
            auto nextNodePtr = currentNodePtr->next;
            currentNodePtr->next = lastNodePtr;

            lastNodePtr = currentNodePtr;
            currentNodePtr = nextNodePtr;
        }
        list = List<ValueType>{
            lastNodePtr,
            &delete_list
        };
        return lastElementPtr;
    }

    //
    // /*
    // Merges two lists
    // */
    // template<typename ValueType>
    // void merge_lists(Node<ValueType>* firstList, Node<ValueType>* secondList){
    //     auto lastNodePtr = firstList;
    //     while(lastNodePtr->next != nullptr){
    //         lastNodePtr = lastNodePtr->next;
    //     }
    //     lastNodePtr->next = secondList;
    // }
    //
    //
    // /*
    // Devides list in groups of size k and reverses each group. Nodes at the end of the list that do not fill a whole group are not reversed
    // Returns a pointer to the head of the modified list
    // */
    // template<typename ValueType>
    // Node<ValueType>* reverse_groups(Node<ValueType>* head, const unsigned int k){
    //     if( k<=1 ) return head;
    //
    //     auto reverseNodes = [](auto& ptrToGroupHead, auto ptrToGroupTail){
    //         //remove group from list
    //         auto nextGroupHead = split_after(ptrToGroupTail);
    //
    //         //reverse group
    //         ptrToGroupTail = ptrToGroupHead;
    //         ptrToGroupHead = reverse_list(ptrToGroupHead);
    //
    //         //insert group
    //         merge_lists(ptrToGroupTail, nextGroupHead);
    //
    //         return ptrToGroupTail;
    //     };
    //
    //     auto currentGroupTail = advance(head, k-1);
    //     if(currentGroupTail == nullptr) return head; //k is greater than nodes in the list
    //
    //     auto previousGroupTail = reverseNodes(head, currentGroupTail);
    //     currentGroupTail = advance(previousGroupTail, k);
    //
    //     while(currentGroupTail != nullptr){
    //         previousGroupTail = reverseNodes(previousGroupTail->next, currentGroupTail);
    //         currentGroupTail = advance(previousGroupTail, k);
    //     }
    //
    //     return head;
    // }
    /*
    Removes the nodes following nodePtr from the list
    Return pointer to the node that followed nodePtr
    */
    template<typename ValueType>
    List<ValueType> split_after(Node<ValueType>* nodePtr){
        if(nodePtr == nullptr){
            return List<ValueType>{
                nullptr,
                &delete_list
            };
        }
        auto newListHead = List<ValueType>{
            nodePtr->next,
            &delete_list
        };
        nodePtr->next = nullptr;
        return newListHead;
    }
}

#endif