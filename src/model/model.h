#ifndef SMART_CALC_V2_0_MODEL_MODEL_H_
#define SMART_CALC_V2_0_MODEL_MODEL_H_

#include <iostream>
#include <string>
#include <vector>

#include "../source/calculation.h"

namespace sc2 {

class Model {
 public:
  Model() : data_("") {}
  Model(const Model &c) = delete;
  Model(Model &&c) = delete;
  Model &operator=(const Model &c) = delete;
  Model &operator=(Model &&c) = delete;
  ~Model() = default;

  void Calculation(std::string expression, double x) {
    if (expression.length() < 256) {
      double result = Calculation::Calc(expression, x);
      if (expression != "Error") {
        char buf[256] = {'\0'};
        snprintf(buf, sizeof(buf), "%.10g", result);
        expression = buf;
      }
      data_ = expression;
    } else {
      data_ = "Error";
    }
  }

  void PlotCalculation(std::string expression, double x_min, double x_max) {
    x_.clear();
    y_.clear();
    if (expression.length() < 256) {
      double val = Calculation::Calc(expression, x_min);
      if (expression != "Error" && val == val) {
        double h = 0.05;
        int N = (int)((x_max - x_min) / h) + 1;
        x_.reserve(N);
        y_.reserve(N);
        double x_value = x_min;
        for (int i = 0; i < N; i++, x_value += h) {
          x_.push_back(x_value);
          y_.push_back(Calculation::Calc(expression, x_[i]));
        }
      }
    }
  }

  std::string Get() { return data_; }

  std::vector<std::vector<double> *> GetPlotData() {
    return std::vector<std::vector<double> *>{&x_, &y_};
  }

 private:
  std::string data_;
  std::vector<double> x_;
  std::vector<double> y_;
};
}  // namespace sc2

#endif  // SMART_CALC_V2_0_MODEL_MODEL_H_
