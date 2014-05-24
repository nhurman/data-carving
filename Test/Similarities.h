#include "../BitGrapher/algorithms/similarities.h"

TEST(Probabilities)
{
  std::list<int> list;
  list.push_back(1024);
  list.push_back(1024);
  CHECK(18 == Similarities::minStringSize(list));
}
