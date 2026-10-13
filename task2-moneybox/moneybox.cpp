#include <iostream>
// для поиска по названию команды
bool AreEqual(const char* first, const char* second) {
  int i = 0;
  while (first[i] != '\0') {
    if (first[i] != second[i]) {
      return false;
    }
    ++i;
  }
  return second[i] == '\0';
}

bool Deposit(int& balance, int amount) {
  if (amount <= 0) {
    return false;
  }
  balance += amount;
  return true;
}

bool Withdraw(int& balance, int amount) {
  if (amount <= 0 || amount > balance) {
    return false;
  }
  balance -= amount;
  return true;
}

bool PrintBalance(int& balance, int) {
  std::cout << balance << '\n';
  return true;
}

bool Reset(int& balance, int) {
  balance = 0;
  return true;
}

bool Triple(int& balance, int) {
  balance *= 3;
  return true;
}

using Operation = bool (*)(int&, int);

struct Command {
  const char* name;
  Operation operation;  // указатель на функцию
  bool needsAmount;
};

const Command commands[] = {
    {"deposit", Deposit, true},       {"withdraw", Withdraw, true},
    {"balance", PrintBalance, false}, {"reset", Reset, false},
    {"triple", Triple, false},
};

// Читаем остаток строки посимвольно, чтобы перейти к следующей команде.
void SkipLine() {
  char symbol;
  while (std::cin.get(symbol) && symbol != '\n') {
  }
}

int main() {
  int balance = 0;
  char command[32]{};
  const int commandCount = sizeof(commands) / sizeof(commands[0]);

  while (std::cin >> command) {
    if (AreEqual(command, "stop")) {
      break;
    }

    int commandIndex = -1;
    for (int i = 0; i < commandCount; ++i) {
      if (AreEqual(command, commands[i].name)) {
        commandIndex = i;
        break;
      }
    }

    if (commandIndex == -1) {
      std::cout << "error\n";
      SkipLine();
      continue;
    }

    int amount = 0;
    if (commands[commandIndex].needsAmount) {
      if (!(std::cin >> amount)) {
        std::cout << "error\n";
        break;
      }
    }

    if (!commands[commandIndex].operation(balance, amount)) {
      std::cout << "error\n";
    }
    SkipLine();
  }
}
