#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string LongestWord(string sen) {
  string res;
  string word;
  long long maxlen = 0;
  int n = sen.length();

  for (int i = 0; i <= n; i++) {
    if (sen[i] == ' ' || sen[i] == '\0') {
      if (!word.empty() && word.length() > maxlen) {
        maxlen = word.length();
        res = word;
      }
      word.clear();
    }
    else if (isalnum((unsigned char)sen[i])) {
      word.push_back(sen[i]);
    }
  }
  
  return res;
}

// keep this function call here
int main(void) { 
   
  cout << LongestWord(coderbyteInternalStdinFunction(stdin));
  return 0;
    
}