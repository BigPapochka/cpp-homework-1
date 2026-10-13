#include <cmath>  // чтобы не изобретать велосипед подключил для округления
#include <iostream>

struct TempretureRange {
  int minimum = 0;
  int maximum = 0;
};

double AverageTempreture(const int* const& tempretures, int n) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += tempretures[i];
  }
  return std::round(sum * 10 / n) / 10.0;
}
TempretureRange MinMaxTempreture(const int* const& tempretures, int n) {
  int min = *tempretures;
  int max = *tempretures;
  for (int i = 0; i < n; i++) {
    if (min > tempretures[i]) {
      min = tempretures[i];
    }
    if (max < tempretures[i]) {
      max = tempretures[i];
    }
  }
  return TempretureRange{min, max};
}
int LessThanZero(const int* const& tempretures, int n) {
  int counter = 0;
  for (int i = 0; i < n; i++) {
    if (0 > tempretures[i]) {
      counter++;
    }
  }
  return counter;
}
int main() {
  int number_of_days;
  std::cin >> number_of_days;
  int* tempretures = new int[number_of_days]{};
  for (int i = 0; i < number_of_days; i++) {
    std::cin >> tempretures[i];
  }
  std::cout << AverageTempreture(tempretures, number_of_days) << '\n';
  TempretureRange range = MinMaxTempreture(tempretures, number_of_days);
  std::cout << range.minimum << " " << range.maximum << '\n';
  std::cout << LessThanZero(tempretures, number_of_days) << '\n';
  delete[] tempretures;
}