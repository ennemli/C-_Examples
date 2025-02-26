#include <bitset>
#include <cstdint>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
  vector<uint8_t> buffer;
  buffer.push_back(4);
  buffer.push_back(12);
  buffer.push_back(1);
  buffer.push_back(19);
  cout << buffer[0] << "\n";
  uint16_t *ptr = reinterpret_cast<uint16_t *>(buffer.data());
  for (size_t i = 0; i < buffer.size(); ++i) {
    cout << hex << ptr[i] << "\n";
  }
  /*uint32_t x = 0xFFFF;
  x += 0x2FFFF;
  cout << hex << (x & 0xFFFF) << "\n";
  cout << "(x>>16): " << (x >> 16) << "\n";
  x = (x & 0xFFFF) + (x >> 16);
  cout << hex << x << "\n";
  */

  /* uint32_t sum(0b0100101011000010);
   uint32_t sender_checksum(0b1011010100111101);
   sum += sender_checksum;
   cout << sum << "\n";
   sum = sum >> 16 ? (sum & 0xFFFF) + (sum >> 16) : sum;
   constexpr uint8_t bitsize = (sizeof(uint16_t)) * 8;
   cout << bitset<bitsize>(~sum) << '\n';
   ///---------------
   ///
   uint8_t x = 60;
   uint8_t co_x = ~x;
   cout << static_cast<int8_t>(co_x) << "\n";
   cout << bitset<bitsize>(co_x + x) << '\n';
 */
  return 0;
}
