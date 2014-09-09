#include "bits.h"
#include <iostream>
#include <cassert>
#include <climits>

int main()
{
  std::cout<<"Testing bitNor:\n\r";
  //bitNor(0x6, 0x5) = 0xFFFFFFF8
  assert(bitNor(0x6, 0x5) == 0xFFFFFFF8);

  std::cout<<"Testing isNotEqual:\n\r";
  //isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
  assert(isNotEqual(5,5) == 0);
  assert(isNotEqual(4,5) == 1);

  std::cout<<"Testing copyLSB:\n\r";
  //copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
  assert(copyLSB(5) == 0xFFFFFFFF);
  assert(copyLSB(6) == 0x00000000);

  std::cout<<"Testing bitCount:\n\r";
  //bitCount(5) = 2, bitCount(7) = 3
  assert(bitCount(5) == 2);
  assert(bitCount(7) == 3);

  std::cout<<"Testing leastBitPos:\n\r";
  //leastBitPos(96) = 0x20
  assert(leastBitPos(96) == 0x20);

  std::cout<<"Testing tmax:\n\r";
  assert(tmax() == INT_MAX);

  std::cout<<"Testing isGreater:\n\r";
  //isGreater(4,5) = 0, isGreater(5,4) = 1
  assert(isGreater(4,5) == 0);
  assert(isGreater(5,4) == 1);
  assert(isGreater(-5,4) == 0);
  assert(isGreater(4,-5) == 1);
  assert(isGreater(5,5) == 0);

  /*
  for(int i = INT_MIN; i != INT_MAX; i++)
    {
      std::cout<<"testing at: "<<i<<" "<<-i<<std::endl;
      assert(isGreater(i, -i) == i > -i);

    }
  */

  std::cout<<"Testing abs:\n\r";
  //abs(-1) = 1
  assert(abs(-1) == 1);

}
