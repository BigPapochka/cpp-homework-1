// Кинотеатр: бронируем места в выбранном зале и ряду
// int*** хранит залы, массивы рядов и массивы состояний мест
// void* хранит заявку: индексы int[] либо буквы мест char[]

#include <iostream>

int main() {
  // Сначала вводим hallCount rowCount seatCount; в ряду не больше 26 мест.
  // Затем заявки: format hall row count, после них count номеров или букв.
  // format: 1 - числовые индексы от 0, 2 - буквы A ... Z, 0 - закончить.
  // Залы, ряды и числовые места нумеруются с нуля: A = 0, B = 1 и т.д.
  // int*** нужен для динамических массивов залов, рядов и мест.
  // Формат ввода выбирается при работе, поэтому общий буфер void*.
  // Места обрабатываем отдельно: ошибка одного не отменяет другие брони.
  int hallCount;
  int rowCount;
  int seatCount;
  if (!(std::cin >> hallCount >> rowCount >> seatCount) || hallCount <= 0 ||
      rowCount <= 0 || seatCount <= 0 || seatCount > 26) {
    std::cout << "error\n";
    return 1;
  }

  int*** seats = new int**[hallCount];
  for (int hall = 0; hall < hallCount; ++hall) {
    seats[hall] = new int*[rowCount];
    for (int row = 0; row < rowCount; ++row) {
      seats[hall][row] = new int[seatCount]{};
    }
  }

  int format;
  while (std::cin >> format && format != 0) {
    int hall;
    int row;
    int count;
    if ((format != 1 && format != 2) || !(std::cin >> hall >> row >> count) ||
        hall < 0 || hall >= hallCount || row < 0 || row >= rowCount ||
        count <= 0) {
      std::cout << "error\n";
      break;
    }

    // Один буфер хранит список мест в выбранном пользователем формате, он может
    // быть как char, так и int
    void* chosenSeats = nullptr;
    if (format == 1) {
      chosenSeats = new int[count]{};
    } else {
      chosenSeats = new char[count]{};
    }

    for (int i = 0; i < count; ++i) {
      if (format == 1) {
        std::cin >> ((int*)chosenSeats)[i];
      } else {
        std::cin >> ((char*)chosenSeats)[i];
      }
    }

    if (std::cin) {
      for (int i = 0; i < count; ++i) {
        int seat;
        if (format == 1) {
          seat = ((int*)chosenSeats)[i];
        } else {
          seat = ((char*)chosenSeats)[i] - 'A';
        }

        if (seat < 0 || seat >= seatCount) {
          std::cout << "error\n";
        } else if (seats[hall][row][seat] == 1) {
          std::cout << "occupied\n";
        } else {
          seats[hall][row][seat] = 1;
          std::cout << "booked\n";
        }
      }
    } else {
      std::cout << "error\n";
    }

    // Удаляем массив с тем типом, с которым его создали
    if (format == 1) {
      delete[] (int*)chosenSeats;
    } else {
      delete[] (char*)chosenSeats;
    }
    if (!std::cin) {
      break;
    }
  }

  // Выводим все места: 0 - свободно 1 - занято
  for (int hall = 0; hall < hallCount; ++hall) {
    std::cout << "Hall " << hall << '\n';
    for (int row = 0; row < rowCount; ++row) {
      std::cout << "Row " << row << ':';
      for (int seat = 0; seat < seatCount; ++seat) {
        std::cout << ' ' << seats[hall][row][seat];
      }
      std::cout << '\n';
    }
  }

  // Удаляем с конца
  for (int hall = 0; hall < hallCount; ++hall) {
    for (int row = 0; row < rowCount; ++row) {
      delete[] seats[hall][row];
    }
    delete[] seats[hall];
  }
  delete[] seats;
  return 0;
}
