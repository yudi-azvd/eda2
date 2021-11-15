#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "../str_htable.h"

TEST_SUITE_BEGIN("str_htable");

TEST_CASE("create and destroy")
{
  LPHashTable *ht = LPHashTable_create();
  LPHashTable_destroy(ht);
}

TEST_CASE("set and search")
{
  LPHashTable *ht = LPHashTable_create();
  int indexes[4];

  indexes[0] = LPHashTable_set(ht, "aaa");
  indexes[1] = LPHashTable_set(ht, "bbb");
  indexes[2] = LPHashTable_set(ht, "ccc");
  indexes[3] = LPHashTable_set(ht, "ddd");

  // LPHashTable_print(ht);

  CHECK(indexes[0] == LPHashTable_search(ht, "aaa"));
  CHECK(indexes[1] == LPHashTable_search(ht, "bbb"));
  CHECK(indexes[2] == LPHashTable_search(ht, "ccc"));
  CHECK(indexes[3] == LPHashTable_search(ht, "ddd"));

  LPHashTable_destroy(ht);
}

TEST_SUITE_END();
