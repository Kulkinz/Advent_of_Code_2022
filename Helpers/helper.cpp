#include <string>
#include <vector>
#include <set>

#include "HelperFunctions.h"

// Taken from https://www.techiedelight.com/split-string-cpp-using-delimiter/
void tokenize(std::string const &str, const char delim,
              std::vector<std::string> &out) {
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
  {
    end = str.find(delim, start);
    out.push_back(str.substr(start, end - start));
  }
}

void tokenize(std::string const &str, const string& delim,
              std::vector<std::string> &out) {
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
  {
    end = str.find(delim, start);
    out.push_back(str.substr(start, end - start));
  }
}

bool uniqueCharacters(string str) {
  set<char> char_set;
  for(char c : str) {
    char_set.insert(c);
  }
  return char_set.size() == str.size();
}