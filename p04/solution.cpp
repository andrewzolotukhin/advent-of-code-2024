#include <iostream>
#include <string>
#include <vector>

int main() {
  int n = 140;
  std::vector<std::string> ss;

  int i = 0, j = 0, k, r = 0;
  std::string pattern = "XMAS";
  int ps = pattern.size();

  for (i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    ss.push_back(s);
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      // std::cout << i << " x " << j << std::endl;
      if (ss[i][j] != pattern[0]) {
        continue;
      }

      if (j + ps - 1 < n) {
        for (k = 0; k < ps; k++) {
          if (pattern[k] != ss[i][j + k]) {
            break;
          } else {
            if (k == ps - 1) {
              std::cout << i << " " << j << std::endl;
              r++;
            }
          }
        }
      }

      if (i + ps - 1 < n) {
        for (k = 0; k < ps; k++) {
          if (pattern[k] != ss[i + k][j]) {
            break;
          } else {
            if (k == ps - 1) {
              std::cout << i << " " << j << std::endl;
              r++;
            }
          }
        }
      }

      if ((j - ps + 1) >= 0) {
        for (k = 0; k < ps; k++) {
          if (pattern[k] != ss[i][j - k]) {
            break;
          } else {
            if (k == ps - 1) {
              std::cout << i << " " << j << std::endl;
              r++;
            }
          }
        }
      }

      if ((i - ps + 1) >= 0) {
        for (k = 0; k < ps; k++) {
          if (pattern[k] != ss[i - k][j]) {
            break;
          } else {
            if (k == ps - 1) {
              std::cout << i << " " << j << std::endl;
              r++;
            }
          }
        }
      }

      if ((i - ps + 1 >= 0) && (j + ps - 1 < n)) {
        for (k = 0; k < ps; k++) {
          if (pattern[k] != ss[i - k][j + k]) {
            break;
          } else {
            if (k == ps - 1) {
              std::cout << i << " " << j << std::endl;
              r++;
            }
          }
        }
      }

      if ((i - ps + 1 >= 0) && (j - ps + 1 >= 0)) {
        for (k = 0; k < ps; k++) {
          if (pattern[k] != ss[i - k][j - k]) {
            break;
          } else {
            if (k == ps - 1) {
              std::cout << i << " " << j << std::endl;
              r++;
            }
          }
        }
      }

      if ((i + ps - 1 < n) && (j + ps - 1 < n)) {
        for (k = 0; k < ps; k++) {
          if (pattern[k] != ss[i + k][j + k]) {
            break;
          } else {
            if (k == ps - 1) {
              std::cout << i << " " << j << std::endl;
              r++;
            }
          }
        }
      }

      if ((i + ps - 1 < n) && (j - ps + 1 >= 0)) {
        for (k = 0; k < ps; k++) {
          if (pattern[k] != ss[i + k][j - k]) {
            break;
          } else {
            if (k == ps - 1) {
              std::cout << i << " " << j << std::endl;
              r++;
            }
          }
        }
      }
    }
  }

  std::cout << r << std::endl;
  return 0;
}
