#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "./model.h"

int main(int argc, char **argv) {
  double result = 0;
  if (argc > 1 && argv[1] != NULL) {
    double value = 0;
    if (argv[2] != NULL) {
      value = atof(argv[2]);
    }
    result = s21::Calculation::Calc(argv[1], value);
    if (strcmp(argv[1], "Error\0")) {
      printf("%.7lf\n", result);
    } else {
      printf("%s\n", argv[1]);
    }
  }
  std::cout << "" << std::endl;
  auto a = new s21::Model();
  a->Calculation("1+1-x", 70);
  std::cout << a->Get() << std::endl;
  return 0;
}