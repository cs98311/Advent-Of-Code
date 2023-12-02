#include <iostream>
#include <string>

int main() {

  int sum{0};
  int init{0};
  int end{0};

  std::string word;
  while (std::cin >> word) {

    int first{1};
    for (char ch : word) {
      if (isdigit(ch) && first) {
        init = ch - '0';
        end = ch - '0';
        first = 0;
      } else if (isdigit(ch)) {
        end = ch - '0';
      }
    }
    sum += init * 10 + end;
    std::cout << sum << '\n';
  }
  return 0;
}
