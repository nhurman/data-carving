#include "../BitGrapher/core/BitString.h"
#include "../BitGrapher/core/Exception.h"

#include <iostream>

TEST(BitString_size)
{
  BitString b(2);
  CHECK(2 == b.size());
}

TEST(BitString_hex)
{
  BitString b = BitString::fromHex("02");
  for (int i = 0; i < 6; ++i) {
    CHECK(false == b[i]);
  }

  CHECK(true == b[6]);
  CHECK(false == b[7]);

  // Incomplete bs
  BitString c = BitString::fromHex("1");
  for (int i = 0; i < 7; ++i) {
    CHECK(false == c[i]);
  }

  CHECK(true == c[7]);
}

TEST(BitString_bin)
{
  BitString b = BitString::fromBin("010");
  CHECK(!b[0]);
  CHECK(b[1]);
  CHECK(!b[2]);
}

TEST(BitString_raw)
{
  BitString b = BitString::fromRaw("01A");
  CHECK("001100000011000101000001" == b.toString());
}

TEST(BitString_set)
{
  BitString bs(2);
  CHECK(!bs[0]);
  bs.set(0, true);
  CHECK(bs[0]);
  CHECK_THROW(bs.set(2, true), BitStringException);
}

TEST(BitString_equals)
{
  BitString a = BitString::fromHex("011");
  BitString b = BitString::fromBin("0000000100001010");
  BitString c = BitString::fromBin("0000000100000001");

  CHECK(a != b);
  CHECK(a == c);
  CHECK(!(a == b));
  CHECK(!(a != c));
}

TEST(BitString_and)
{
  BitString a = BitString::fromHex("011");
  BitString b = BitString::fromHex("110");
  BitString expected = BitString::fromHex("010");
  CHECK((a & b) == expected);
}

TEST(BitString_or)
{
  BitString a = BitString::fromHex("011");
  BitString b = BitString::fromHex("110");
  BitString expected = BitString::fromHex("111");
  CHECK((a | b) == expected);
}

TEST(BitString_xor)
{
  BitString a = BitString::fromHex("011");
  BitString b = BitString::fromHex("110");
  BitString expected = BitString::fromHex("101");
  CHECK((a ^ b) == expected);
}

TEST(BitString_contains)
{
  BitString a = BitString::fromBin("0111010");
  BitString b = BitString::fromBin("111");
  BitString c = BitString::fromBin("11111");
  CHECK(a.contains(b));
  CHECK(!a.contains(c));
  CHECK(!b.contains(a));
}

TEST(BitString_substring)
{
  BitString a = BitString::fromBin("0111010");
  BitString expected = BitString::fromBin("110");
  CHECK(a.substring(2, 3) == expected);
  CHECK_THROW(a.substring(1, 10), BitStringException);
  CHECK_THROW(a.substring(10, 0), BitStringException);
}

TEST(Guess_binary)
{
  CHECK(BINARY == BitString::guessTextInputFormat("00110101"));
}

TEST(Guess_hexa)
{
  CHECK(HEXADECIMAL == BitString::guessTextInputFormat("00F0"));
}

TEST(Guess_raw)
{
  CHECK(RAW == BitString::guessTextInputFormat("01Z"));
}