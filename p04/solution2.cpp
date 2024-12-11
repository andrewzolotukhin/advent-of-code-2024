#include <iostream>
#include <string>
#include <vector>

int main() {
  int n = 140;
  std::vector<std::string> ss;

  int i = 0, j = 0, k, r = 0;

  for (i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    ss.push_back(s);
  }

  // M S
  //  A
  // M S
  //
  // S S
  //  A
  // M M
  //
  // S M
  //  A
  // S M
  //
  // M M
  //  A
  // S S

  std::vector<std::vector<std::string>> patterns = {
      {"M S", " A ", "M S"},

      {"S S", " A ", "M M"},

      {"S M", " A ", "S M"},

      {"M M", " A ", "S S"},
  };

  //  M
  // MAS
  //  S
  //
  //  S
  // MAS
  //  M
  //
  //  S
  // SAM
  //  M
  //
  //  M
  // SAM
  //  S
  // ================
  std::vector<std::vector<std::string>> patterns2 = {
      {" M ", "MAS", " S "},

      {" S ", "MAS", " M "},

      {" S ", "SAM", " M "},

      {" M ", "SAM", " S "},
  };

  for (i = 0; i < n - 2; i++) {
    for (j = 0; j < n - 2; j++) {
      {
        for (k = 0; k < patterns.size(); k++) {
          // std::cout << i << " x " << j << std::endl;
          if (ss[i][j] == patterns[k][0][0] &&
              ss[i + 1][j + 1] == patterns[k][1][1] &&
              ss[i + 2][j + 2] == patterns[k][2][2] &&
              ss[i][j + 2] == patterns[k][0][2] &&
              ss[i + 2][j] == patterns[k][2][0]) {
            std::cout << i << " " << j << std::endl;
            r++;
          }
        }

        // for (k = 0; k < patterns2.size(); k++) {
        //   // std::cout << i << " x " << j << std::endl;
        //   if (ss[i + 1][j + 1] == patterns2[k][1][1] &&
        //       ss[i][j + 1] == patterns2[k][0][1] &&
        //       ss[i + 1][j] == patterns2[k][1][0] &&
        //       ss[i + 1][j + 2] == patterns2[k][1][2] &&
        //       ss[i + 2][j + 1] == patterns2[k][2][1]) {
        //     std::cout << i << " x " << j << std::endl;
        //     r++;
        //   }
        // }
      }
    }
  }

  std::cout << r << std::endl;
  return 0;
}
