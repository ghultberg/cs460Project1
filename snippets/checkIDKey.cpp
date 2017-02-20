#include <iostream>
#include <string>

using namespace std;

bool isIDKey(char);

int main(int argc, char * argv [])
{
  string str = argv[1];

  cout << "Could be a predicate or key word? " << !isIDKey(str[0]) << endl;

  return 0;
}

// Check if the first character of a string could be something other than IDKEY_T.
// Use a bitmask instead of switch to produce less complex code
bool isIDKey(char c)
{
  // 26-bit bitmask to allow A, C, D, I, L, O, N, S, Z
  int mask = 46291081;

  // Contains a '1' followed by as many zeroes as letters that come after 'char c' in the alphabet
  int cmp = 1 << (26 - int(c) - 64);

  // Bitwise and the mask and cmp number. If the result is 0, then no matches were found
  return ((mask & cmp) == 0);
}