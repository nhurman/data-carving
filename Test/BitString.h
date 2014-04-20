#include "../BitGrapher/core/bitstring.h"

TEST(BitString_size)
{
  BitString b(2);
  CHECK(2 == b.size());
}
