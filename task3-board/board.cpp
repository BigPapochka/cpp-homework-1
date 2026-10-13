#include <iostream>

bool AreEqual(const char* first, const char* second) {
  int i = 0;
  while (first[i] != '\0' && second[i] != '\0') {
    if (first[i] != second[i]) {
      return false;
    }
    ++i;
  }
  return first[i] == second[i];
}

void SkipLine() {
  char symbol;
  while (std::cin.get(symbol) && symbol != '\n') {
  }
}

bool IsInside(int x, int y) { return x >= 0 && x < 10 && y >= 0 && y < 5; }

void Clear(char board[][10]) {
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 10; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool Put(char board[][10], int x, int y, char symbol) {
  if (!IsInside(x, y)) {
    return false;
  }
  board[y][x] = symbol;
  return true;
}

bool Text(char board[][10], int x, int y, const char* word) {
  int length = 0;
  while (word[length] != '\0') {
    ++length;
  }

  if (!IsInside(x, y)) {
    return false;
  }
  if (!IsInside(x + length - 1, y)) {
    return false;
  }

  for (int i = 0; i < length; ++i) {
    Put(board, x + i, y, word[i]);
  }
  return true;
}

void Print(const char board[5][10]) {
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 10; ++x) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

int main() {
  char board[5][10];
  Clear(board);

  char command[32]{};
  while (std::cin >> command) {
    if (AreEqual(command, "quit")) {
      break;
    }

    if (AreEqual(command, "clear")) {
      Clear(board);
    } else if (AreEqual(command, "put")) {
      int x;
      int y;
      char symbol;
      if (!(std::cin >> x >> y >> symbol)) {
        break;
      }
      if (!Put(board, x, y, symbol)) {
        std::cout << "error\n";
      }
    } else if (AreEqual(command, "text")) {
      int x;
      int y;
      char word[11]{};
      if (!(std::cin >> x >> y >> word)) {
        break;
      }
      if (!Text(board, x, y, word)) {
        std::cout << "error\n";
      }
    } else if (AreEqual(command, "print")) {
      Print(board);
    } else {
      std::cout << "error\n";
    }
    SkipLine();
  }
}
