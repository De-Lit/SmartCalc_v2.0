#include "calculation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>

double sc2::Calculation::Calc(std::string &argv, double x) {
  double result = 0;
  if (argv.length()) {
    int error = 0;
    error = Validator(argv);
    if (error) {
      argv = "Error";
    } else {
      List::ListT *head = Parser(argv, x);
      List::ReverseList(&head);
      head = CalculateStation(head);
      result = head->value;
      List::FreeList(&head);
    }
  }
  return result;
}

int sc2::Calculation::Validator(const std::string argv) {
  Pars pars = {};
  const std::string unary_operations("+-");
  const std::string binary_operations("+-*/^");
  const std::string digits("0123456789");
  const std::string exp("Ee");
  for (auto iter = argv.begin(); iter != argv.end() && !pars.error; ++iter) {
    pars.c = *iter;
    switch (pars.c_last_type) {
      case START:
        StartCase(pars, digits, unary_operations);
        break;
      case DIGIT:
        DigitCase(pars, digits, exp, binary_operations);
        break;
      case EXP:  // exp form
        ExpCase(pars, digits, unary_operations);
        break;
      case X:
        XCase(pars, binary_operations);
        break;
      case UNARY_OPERATION:  // unary
        UnaryOperationCase(pars, digits);
        break;
      case BINARY_OPERATION:  // binary
        BinaryOperationCase(pars, digits);
        break;
      case DECIMAL:  // decimal
        DecimalCase(pars, digits, exp, binary_operations);
        break;
      case OPEN_BRACKET:  // '('
        OpenBracketCase(pars, digits, unary_operations);
        break;
      case CLOSE_BRACKET:  // ')'
        CloseBracketCase(pars, binary_operations);
        break;
      case UNARY_OPERATION_WORD:  // '[:alpha:]' unary
        UnaryOperationWordCase(pars);
        break;
      case BINARY_OPERATION_WORD:  // '[:alpha:]' binary
        BinaryOperationWordCase(pars, digits);
        break;
    }
    if (pars.bracket_count < 0) {
      pars.error = 1;
    } else {
      pars.c_last = pars.c;
      pars.c_last_type = pars.c_type;
    }
  }
  if (pars.error == 0) {
    if (pars.bracket_count != 0) {
      pars.error = 1;
    } else {
      switch (pars.c_last_type) {
        case DIGIT:
          break;
        case X:
          break;
        case CLOSE_BRACKET:
          break;
        case DECIMAL:
          break;
        default:
          pars.error = 1;
      }
    }
  }
  return pars.error;
}

void sc2::Calculation::StartCase(Pars &pars, const std::string &digits,
                                 const std::string &unary_operations) {
  if (digits.find(pars.c) != std::string::npos) {
    pars.c_type = DIGIT;
    if (pars.c == '0') {
      pars.null_flag = 1;
    }
    pars.exp_flag = 1;
  } else if (pars.c == 'x') {
    pars.c_type = X;
  } else if (unary_operations.find(pars.c) != std::string::npos) {
    pars.c_type = UNARY_OPERATION;
  } else if (pars.c == '(') {
    pars.c_type = OPEN_BRACKET;
    ++pars.bracket_count;
  } else {
    IsValidWordUnary(&pars);
  }
}

void sc2::Calculation::DigitCase(Pars &pars, const std::string &digits,
                                 const std::string &exp,
                                 const std::string &binary_operations) {
  if (digits.find(pars.c) != std::string::npos) {
    pars.c_type = DIGIT;
    if (pars.null_flag == 1) {
      pars.error = 1;
    }
  } else if (exp.find(pars.c) != std::string::npos) {
    if (pars.exp_flag == 1) {
      pars.c_type = EXP;
      pars.exp_flag = 2;
      pars.decimal_flag = 1;
    } else {
      pars.error = 1;
    }
  } else if (binary_operations.find(pars.c) != std::string::npos) {
    pars.c_type = BINARY_OPERATION;
    pars.decimal_flag = 0;
    pars.null_flag = 0;
    pars.exp_flag = 0;
  } else if (pars.c == '.') {
    if (pars.decimal_flag == 0) {
      pars.c_type = DECIMAL;
      pars.decimal_flag = 1;
    } else {
      pars.error = 1;
    }
  } else if (pars.c == ')') {
    pars.c_type = CLOSE_BRACKET;
    --pars.bracket_count;
    pars.decimal_flag = 0;
    pars.exp_flag = 0;
  } else {
    IsValidWordBinary(&pars);
  }
}

void sc2::Calculation::ExpCase(Pars &pars, const std::string &digits,
                               const std::string &unary_operations) {
  if (digits.find(pars.c) != std::string::npos) {
    pars.c_type = DIGIT;
  } else if (unary_operations.find(pars.c) != std::string::npos) {
    pars.c_type = UNARY_OPERATION;
  } else {
    pars.error = 1;
  }
}

void sc2::Calculation::XCase(Pars &pars, const std::string &binary_operations) {
  if (binary_operations.find(pars.c) != std::string::npos) {
    pars.c_type = BINARY_OPERATION;
    pars.decimal_flag = 0;
    pars.null_flag = 0;
  } else if (pars.c == ')') {
    pars.c_type = CLOSE_BRACKET;
    --pars.bracket_count;
    pars.decimal_flag = 0;
  } else {
    IsValidWordBinary(&pars);
  }
}

void sc2::Calculation::UnaryOperationCase(Pars &pars,
                                          const std::string &digits) {
  if (digits.find(pars.c) != std::string::npos) {
    pars.c_type = DIGIT;
    if (pars.exp_flag == 0) {
      pars.exp_flag = 1;
      if (pars.c == '0') {
        pars.null_flag = 1;
      }
    }
  } else if (pars.c == 'x') {
    if (pars.exp_flag == 2) {
      pars.error = 1;
    } else {
      pars.c_type = X;
    }
  } else if (pars.c == '(') {
    if (pars.exp_flag == 2) {
      pars.error = 1;
    } else {
      pars.c_type = OPEN_BRACKET;
      ++pars.bracket_count;
    }
  } else {
    IsValidWordUnary(&pars);
  }
}

void sc2::Calculation::BinaryOperationCase(Pars &pars,
                                           const std::string &digits) {
  if (digits.find(pars.c) != std::string::npos) {
    pars.c_type = DIGIT;
    if (pars.c == '0') {
      pars.null_flag = 1;
    }
    pars.exp_flag = 1;
  } else if (pars.c == 'x') {
    pars.c_type = X;
  } else if (pars.c == '(') {
    pars.c_type = OPEN_BRACKET;
    ++pars.bracket_count;
  } else {
    IsValidWordUnary(&pars);
  }
}

void sc2::Calculation::DecimalCase(Pars &pars, const std::string &digits,
                                   const std::string &exp,
                                   const std::string &binary_operations) {
  if (digits.find(pars.c) != std::string::npos) {
    pars.c_type = DIGIT;
    pars.null_flag = 0;
  } else if (exp.find(pars.c) != std::string::npos) {
    pars.c_type = EXP;
    pars.exp_flag = 2;
  } else if (binary_operations.find(pars.c) != std::string::npos) {
    pars.c_type = BINARY_OPERATION;
    pars.decimal_flag = 0;
    pars.null_flag = 0;
  } else if (pars.c == ')') {
    pars.c_type = CLOSE_BRACKET;
    --pars.bracket_count;
    pars.decimal_flag = 0;
  } else {
    IsValidWordBinary(&pars);
  }
}

void sc2::Calculation::OpenBracketCase(Pars &pars, const std::string &digits,
                                       const std::string &unary_operations) {
  if (digits.find(pars.c) != std::string::npos) {
    pars.c_type = DIGIT;
    if (pars.c == '0') {
      pars.null_flag = 1;
    }
    pars.exp_flag = 0;
  } else if (pars.c == 'x') {
    pars.c_type = X;
  } else if (unary_operations.find(pars.c) != std::string::npos) {
    pars.c_type = UNARY_OPERATION;
  } else if (pars.c == '(') {
    pars.c_type = OPEN_BRACKET;
    ++pars.bracket_count;
  } else {
    IsValidWordUnary(&pars);
  }
}

void sc2::Calculation::CloseBracketCase(Pars &pars,
                                        const std::string &binary_operations) {
  if (binary_operations.find(pars.c) != std::string::npos) {
    pars.c_type = BINARY_OPERATION;
  } else if (pars.c == ')') {
    pars.c_type = CLOSE_BRACKET;
    --pars.bracket_count;
  } else {
    IsValidWordBinary(&pars);
  }
}

void sc2::Calculation::UnaryOperationWordCase(Pars &pars) {
  if (pars.word_flag == 1) {
    IsValidWordUnary(&pars);
  } else if (pars.c == '(') {
    pars.c_type = OPEN_BRACKET;
    ++pars.bracket_count;
  } else {
    pars.error = 1;
  }
}

void sc2::Calculation::BinaryOperationWordCase(Pars &pars,
                                               const std::string &digits) {
  if (pars.word_flag == 1) {
    IsValidWordBinary(&pars);
  } else if (pars.c == 'x') {
    pars.c_type = X;
  } else if (digits.find(pars.c) != std::string::npos) {
    pars.c_type = DIGIT;
    if (pars.c == '0') {
      pars.null_flag = 1;
    }
  } else if (pars.c == '(') {
    pars.c_type = OPEN_BRACKET;
    ++pars.bracket_count;
  } else {
    IsValidWordUnary(&pars);
  }
}

void sc2::Calculation::IsValidWordUnary(Pars *pars) {
  const std::string word_operations[]{"cos",  "sin",  "tan", "acos", "asin",
                                      "atan", "sqrt", "ln",  "log"};
  int flag = 0;
  int arr_len = sizeof word_operations / sizeof word_operations[0];
  pars->word.push_back(pars->c);
  for (int i = 0; i < arr_len && flag == 0; ++i) {
    if (pars->word.length() <= word_operations[i].length()) {
      if (std::equal(pars->word.begin(), pars->word.end(),
                     word_operations[i].begin())) {
        flag = 1;
        pars->word_flag = 1;
        pars->c_type = UNARY_OPERATION_WORD;
        if (pars->word.length() == word_operations[i].length()) {
          pars->word_flag = 0;
          pars->word.clear();
        }
      }
    }
  }
  if (!flag) {
    pars->error = 1;
  }
}

void sc2::Calculation::IsValidWordBinary(Pars *pars) {
  const std::string word_operations[]{"mod"};
  int flag = 0;
  int arr_len = sizeof word_operations / sizeof word_operations[0];
  pars->word.push_back(pars->c);
  for (int i = 0; i < arr_len && flag == 0; ++i) {
    if (pars->word.length() <= word_operations[i].length()) {
      if (std::equal(pars->word.begin(), pars->word.end(),
                     word_operations[i].begin())) {
        flag = 1;
        pars->word_flag = 1;
        pars->c_type = BINARY_OPERATION_WORD;
        if (pars->word.length() == word_operations[i].length()) {
          pars->word_flag = 0;
          pars->decimal_flag = 0;
          pars->word.clear();
        }
      }
    }
  }
  if (!flag) {
    pars->error = 1;
  }
}

sc2::Calculation::List::ListT *sc2::Calculation::Parser(std::string argv,
                                                        double x) {
  const std::string digits{"0123456789.Ee"};
  const std::string arithmetic_1{"+-"};
  const std::string arithmetic_2{"*/"};
  const std::string priority_4{"^"};
  const std::string binary_operation[]{"mod"};
  const std::string unary_operation[]{"cos",  "sin",  "tan", "acos", "asin",
                                      "atan", "sqrt", "ln",  "log"};
  const std::string priority_6{"()"};
  const std::string exp{"Ee"};

  List::ListT *head = nullptr;
  char c[16] = {'\0'};
  long double value = 0;
  int priority = 0;
  int unary_arr_len = sizeof unary_operation / sizeof unary_operation[0];
  int binary_arr_len = sizeof binary_operation / sizeof binary_operation[0];
  int flag = 0;
  int last_char = 0;
  for (auto iter = argv.begin(); iter < argv.end(); ++iter) {
    if (digits.find(*iter) != std::string::npos) {
      do {
        strncat(c, &(*iter), 1);
        last_char = *iter;
        ++iter;
      } while ((digits.find(*iter) != std::string::npos ||
                exp.find(last_char) != std::string::npos) &&
               iter != argv.end());
      value = atof(c);
      memset(c, '\0', strlen(c));
      priority = digit;
      List::Push(&head, value, c, priority);
      value = 0;
    }
    while (*iter >= 97 && *iter <= 122 && *iter != 'x' && *iter != 'e' &&
           *iter != 'E') {
      do {
        strncat(c, &(*iter), 1);
        for (int j = 0; j < unary_arr_len && !flag; j++) {
          if (!strcmp(c, unary_operation[j].c_str())) {
            priority = func_unary;
            flag = 1;
          }
        }
        for (int j = 0; j < binary_arr_len && !flag; j++) {
          if (!strcmp(c, binary_operation[j].c_str())) {
            priority = func_binary;
            flag = 1;
          }
        }
        ++iter;
      } while (!flag);
      List::Push(&head, 0., c, priority);
      flag = 0;
      memset(c, '\0', strlen(c));
    }
    if (iter != argv.end()) {
      if (digits.find(*iter) != std::string::npos) {
        do {
          strncat(c, &(*iter), 1);
          last_char = *iter;
          ++iter;
        } while ((digits.find(*iter) != std::string::npos ||
                  exp.find(last_char) != std::string::npos) &&
                 iter != argv.end());
        value = atof(c);
        priority = digit;
        memset(c, '\0', strlen(c));
        --iter;
      } else if (arithmetic_1.find(*iter) != std::string::npos) {
        if (head == nullptr || head->word[0] == '(') {
          List::Push(&head, 0., (char *)"\0", 0);
        }
        c[0] = *iter;
        priority = arithm_1;
      } else if (arithmetic_2.find(*iter) != std::string::npos) {
        c[0] = *iter;
        priority = arithm_2;
      } else if (priority_4.find(*iter) != std::string::npos) {
        c[0] = *iter;
        priority = exponent;
      } else if (priority_6.find(*iter) != std::string::npos) {
        c[0] = *iter;
        priority = bracket;
      } else if (*iter == 'x') {
        sprintf(c, "%.2lf", x);
        value = atof(c);
        priority = digit;
        memset(c, '\0', strlen(c));
      }
      List::Push(&head, value, c, priority);
      c[0] = '\0';
      value = 0.;
    }
  }
  return head;
}
void sc2::Calculation::Calculate(List::ListT **result_head,
                                 List::ListT **operations_head) {
  List::ListT a;
  List::ListT b;
  List::ListT result = {};
  List::ListT operation = List::Pop(operations_head);
  if (operation.word[0] == '+') {
    b = List::Pop(result_head);
    a = List::Pop(result_head);
    result.value = a.value + b.value;
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (operation.word[0] == '-') {
    b = List::Pop(result_head);
    a = List::Pop(result_head);
    result.value = a.value - b.value;
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (operation.word[0] == '*') {
    b = List::Pop(result_head);
    a = List::Pop(result_head);
    result.value = a.value * b.value;
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (operation.word[0] == '/') {
    b = List::Pop(result_head);
    a = List::Pop(result_head);
    result.value = a.value / b.value;
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (operation.word[0] == '^') {
    b = List::Pop(result_head);
    a = List::Pop(result_head);
    result.value = pow(a.value, b.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "mod") == 0) {
    b = List::Pop(result_head);
    a = List::Pop(result_head);
    result.value = fmod(a.value, b.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "cos") == 0) {
    a = List::Pop(result_head);
    result.value = cos(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "sin") == 0) {
    a = List::Pop(result_head);
    result.value = sin(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "tan") == 0) {
    a = List::Pop(result_head);
    result.value = tan(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "acos") == 0) {
    a = List::Pop(result_head);
    result.value = acos(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "asin") == 0) {
    a = List::Pop(result_head);
    result.value = asin(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "atan") == 0) {
    a = List::Pop(result_head);
    result.value = atan(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "sqrt") == 0) {
    a = List::Pop(result_head);
    result.value = sqrt(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "ln") == 0) {
    a = List::Pop(result_head);
    result.value = log(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "log") == 0) {
    a = List::Pop(result_head);
    result.value = log10(a.value);
    List::Push(result_head, result.value, result.word, result.priority);
  }
}

sc2::Calculation::List::ListT *sc2::Calculation::CalculateStation(
    List::ListT *infix_head) {
  List::ListT null_list = {};
  List::ListT *operations_head = nullptr;
  List::ListT *result_head = nullptr;
  List::ListT tmp;
  List::ListT operation;
  while (infix_head != nullptr) {
    tmp = List::Pop(&infix_head);
    if (tmp.priority == 0) {
      List::Push(&result_head, tmp.value, tmp.word, tmp.priority);
    } else {
      if (operations_head == nullptr) {
        List::Push(&operations_head, tmp.value, tmp.word, tmp.priority);
      } else {
        if (tmp.word[0] == '(') {
          List::Push(&operations_head, tmp.value, tmp.word, tmp.priority);
        } else if (tmp.word[0] == ')') {
          operation = List::Peep(&operations_head);
          while (operation.word[0] != '(') {
            Calculate(&result_head, &operations_head);
            operation = List::Peep(&operations_head);
          }
          List::Pop(&operations_head);
        } else {
          operation = List::Peep(&operations_head);
          while (operation.priority >= tmp.priority &&
                 operation.word[0] != '(') {
            Calculate(&result_head, &operations_head);
            if (operations_head != nullptr) {
              operation = List::Peep(&operations_head);
            } else {
              operation = null_list;
            }
          }
          List::Push(&operations_head, tmp.value, tmp.word, tmp.priority);
        }
      }
    }
  }
  while (operations_head != nullptr) {
    Calculate(&result_head, &operations_head);
  }
  return result_head;
}

void sc2::Calculation::List::Push(ListT **head, double value, char *word,
                                  int priority) {
  ListT *tmp = (ListT *)malloc(sizeof(ListT));
  tmp->value = value;
  memset(tmp->word, '\0', sizeof(tmp->word));
  strcat(tmp->word, word);
  tmp->priority = priority;
  tmp->next = (*head);
  (*head) = tmp;
}

sc2::Calculation::List::ListT sc2::Calculation::List::Pop(ListT **head) {
  ListT *prev = nullptr;
  ListT value = {};
  if (*head != nullptr) {
    value = **head;
    prev = *head;
    (*head) = (*head)->next;
    free(prev);
    prev = nullptr;
  }
  return value;
}
sc2::Calculation::List::ListT sc2::Calculation::List::Peep(ListT **head) {
  ListT value = {};
  if (*head != nullptr) {
    value = **head;
  }
  return value;
}

void sc2::Calculation::List::FreeList(ListT **head) {
  ListT *prev = nullptr;
  while (*head != nullptr) {
    prev = *head;
    (*head) = (*head)->next;
    free(prev);
  }
}

void sc2::Calculation::List::ReverseList(ListT **head) {
  if (*head != nullptr) {
    ListT *prev = nullptr;
    ListT *next = (*head)->next;
    while (next != nullptr) {
      (*head)->next = prev;
      prev = *head;
      *head = next;
      next = (*head)->next;
    }
    (*head)->next = prev;
  }
}
