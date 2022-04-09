/*
Test cases to test the functionality of myList
*/

#include "catch.hpp"
#include "myList.hpp"



TEST_CASE("List creation", "[generators]"){

    SECTION("Create list with one element"){
        auto head = myList::make_list(1);
        REQUIRE(head->value == 1 );
        REQUIRE(head->next  == nullptr );
        myList::delete_list(head);
    }
}



