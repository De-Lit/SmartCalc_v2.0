#ifndef SMART_CALC_V2_0_SOURCE_CALCULATION_H_
#define SMART_CALC_V2_0_SOURCE_CALCULATION_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

namespace sc2 {

class Calculation {
 public:
  Calculation(const Calculation &c) = delete;
  Calculation(Calculation &&c) = delete;
  Calculation &operator=(const Calculation &c) = delete;
  Calculation &operator=(Calculation &&c) = delete;
  ~Calculation() = default;
  static double Calc(std::string &argv, double x);

 private:
  Calculation() = default;

  class List {
   public:
    List(const List &c) = delete;
    List(List &&c) = delete;
    List &operator=(const List &c) = delete;
    List &operator=(List &&c) = delete;
    ~List() = default;

    struct ListT {
      long double value;
      char word[7];
      int priority;
      struct ListT *next;
    };

    static void Push(ListT **head, double value, char *word, int priority);
    static ListT Pop(ListT **head);
    static ListT Peep(ListT **head);
    static void FreeList(ListT **head);
    static void ReverseList(ListT **head);

   protected:
   private:
    List() = default;
  };

  enum TypeT {
    digit = 0,
    arithm_1 = 1,
    arithm_2 = 2,
    func_binary = 2,
    exponent = 3,
    func_unary = 4,
    bracket = 7
  };
  enum SymbolEnum {
    START,
    DIGIT,
    X,
    UNARY_OPERATION,
    BINARY_OPERATION,
    DECIMAL,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    UNARY_OPERATION_WORD,
    BINARY_OPERATION_WORD,
    EXP,
  };
  struct Pars {
    char c;
    int c_type;
    char c_last;
    int c_last_type;
    int bracket_count;
    int decimal_flag;
    int null_flag;
    int word_flag;
    int exp_flag;
    std::string word;
    int error;
  };
  static void IsValidWordUnary(Pars *pars);
  static void IsValidWordBinary(Pars *pars);
  static int Validator(const std::string argv);
  static List::ListT *Parser(std::string argv, double x);
  static List::ListT *CalculateStation(List::ListT *infix_head);
  static void Calculate(List::ListT **result_head,
                        List::ListT **operations_head);
  static void StartCase(Pars &pars, const std::string &digits,
                        const std::string &unary_operations);
  static void DigitCase(Pars &pars, const std::string &digits,
                        const std::string &exp,
                        const std::string &binary_operations);
  static void ExpCase(Pars &pars, const std::string &digits,
                      const std::string &unary_operations);
  static void XCase(Pars &pars, const std::string &binary_operations);
  static void UnaryOperationCase(Pars &pars, const std::string &digits);
  static void BinaryOperationCase(Pars &pars, const std::string &digits);
  static void DecimalCase(Pars &pars, const std::string &digits,
                          const std::string &exp,
                          const std::string &binary_operations);
  static void OpenBracketCase(Pars &pars, const std::string &digits,
                              const std::string &unary_operations);
  static void CloseBracketCase(Pars &pars,
                               const std::string &binary_operations);
  static void UnaryOperationWordCase(Pars &pars);
  static void BinaryOperationWordCase(Pars &pars, const std::string &digits);
};
}  // namespace sc2

#endif  // SMART_CALC_V2_0_SOURCE_CALCULATION_H_
