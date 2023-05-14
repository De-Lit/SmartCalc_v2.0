#ifndef SMART_CALC_V2_0_CONTROLLER_CONTROLLER_H_
#define SMART_CALC_V2_0_CONTROLLER_CONTROLLER_H_

#include <string>
#include <vector>

#include "../model/model.h"

namespace sc2 {

class Controller {
 public:
  Controller(Model *m) : model_(m) {}
  Controller(const Controller &c) = delete;
  Controller(Controller &&c) = delete;
  Controller &operator=(const Controller &c) = delete;
  Controller &operator=(Controller &&c) = delete;
  ~Controller() = default;

  std::string Calculation(std::string expression, double x) {
    model_->Calculation(expression, x);
    return model_->Get();
  }
  std::vector<std::vector<double> *> PlotCalculation(std::string expression,
                                                     double x_min,
                                                     double x_max) {
    model_->PlotCalculation(expression, x_min, x_max);
    return model_->GetPlotData();
  }

 private:
  Model *model_;
};
}  // namespace sc2

#endif  // SMART_CALC_V2_0_CONTROLLER_CONTROLLER_H_
