#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "linkedlist.h"


TEST_CASE("add head") {
  List* ls = create_list();

  REQUIRE(list_size(ls) == 0);
  add_head(ls, 1);
  REQUIRE(list_size(ls) == 1);
  add_head(ls, 2);
  REQUIRE(list_size(ls) == 2);

  destroy_list(ls);
}


TEST_CASE("add tail") {
  List* ls = create_list();

  REQUIRE(list_size(ls) == 0);
  add_tail(ls, 1);
  REQUIRE(list_size(ls) == 1);
  add_tail(ls, 2);
  REQUIRE(list_size(ls) == 2);

  destroy_list(ls);
}


TEST_CASE("intermixed add head and tail") {
  List* ls = create_list();

  add_tail(ls, 1);
  add_head(ls, 2);
  add_tail(ls, 4);
  add_head(ls, 7);
  REQUIRE(list_size(ls) == 4);
  add_tail(ls, 10);
  add_head(ls, 12);
  REQUIRE(list_size(ls) == 6);

  destroy_list(ls);
}


TEST_CASE("remove head") {
  List* ls = create_list();
  int data = 0;

  add_head(ls, 1);
  add_head(ls, 2);
  REQUIRE(list_size(ls) == 2);

  data = remove_head(ls);
  REQUIRE(data == 2);
  REQUIRE(list_size(ls) == 1);

  data = remove_head(ls);
  REQUIRE(data == 1);
  REQUIRE(list_size(ls) == 0);

  destroy_list(ls);
}

TEST_CASE("remove tail") {
  List* ls = create_list();
  int data = 0;

  add_head(ls, 1);
  add_head(ls, 2);
  REQUIRE(list_size(ls) == 2);

  data = remove_tail(ls);
  REQUIRE(data == 1);
  REQUIRE(list_size(ls) == 1);

  data = remove_tail(ls);
  REQUIRE(data == 2);
  REQUIRE(list_size(ls) == 0);

  destroy_list(ls);
}


TEST_CASE("intermixed remove head and tail") {
  List* ls = create_list();
  int data = 0;

  add_tail(ls, 1);
  add_tail(ls, 2);
  add_tail(ls, 4);
  add_tail(ls, 7);
  add_tail(ls, 10);
  add_tail(ls, 12);
  REQUIRE(list_size(ls) == 6);

  data = remove_head(ls);
  REQUIRE(data == 1);
  REQUIRE(list_size(ls) == 5);
  data = remove_tail(ls);
  REQUIRE(data == 12);
  REQUIRE(list_size(ls) == 4);
  data = remove_head(ls);
  REQUIRE(data == 2);
  REQUIRE(list_size(ls) == 3);

  destroy_list(ls);
}



TEST_CASE("remove tail and grow it again") {
  List* ls = create_list();
  int data = 0;

  add_head(ls, 1);
  add_head(ls, 2);
  REQUIRE(list_size(ls) == 2);

  data = remove_tail(ls);
  REQUIRE(data == 1);
  REQUIRE(list_size(ls) == 1);

  data = remove_tail(ls);
  REQUIRE(data == 2);
  REQUIRE(list_size(ls) == 0);

  add_head(ls, 1);
  add_tail(ls, 2);
  add_head(ls, 9);
  add_tail(ls, 10);
  add_head(ls, 6);
  REQUIRE(list_size(ls) == 5);

  destroy_list(ls);
}
