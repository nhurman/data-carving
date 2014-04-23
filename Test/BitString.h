#include "../BitGrapher/core/bitstring.h"
#include <iostream>

TEST(BitString_size)
{
  BitString b(2);
  CHECK(2 == b.size());
}

TEST(Read_binary)
{
  BitString b("00110101", BINARY);
  CHECK("00110101 " == b.toString());
}

TEST(Read_hexa)
{
  BitString b("00F0", HEXADECIMAL);
  CHECK("00000000 11110000 " == b.toString());
}

TEST(Read_raw)
{
  BitString b("01A", RAW);
  CHECK("00110000 00110001 01000001 " == b.toString());
}

//TEST(Guess_format)
//{
//  CHECK(true);
//}