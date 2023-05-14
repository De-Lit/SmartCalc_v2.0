#ifndef SMART_CALC_V2_0_VIEW_PLOT_H
#define SMART_CALC_V2_0_VIEW_PLOT_H

#include <QWidget>
#include <cstring>
#include <vector>

#include "../controller/controller.h"
#include "../source/qcustomplot.h"

namespace sc2 {

namespace Ui {
class Plot;
}

class Plot : public QWidget {
  Q_OBJECT

 public:
  Plot() = delete;
  Plot(Controller *c);
  Plot(const Plot &c) = delete;
  Plot(Plot &&c) = delete;
  Plot &operator=(const Plot &c) = delete;
  Plot &operator=(Plot &&c) = delete;
  ~Plot();

 private:
  void SetDefaultPlot();
  void RemovePlot();

  Ui::Plot *ui_;
  Controller *controller_;
  QCustomPlot *w_graphic_;

 public slots:
  void SignalClose();

 private slots:
  void PlotPressed();
  void PlotClearPressed();
  void MakePlot(QVector<double>, QVector<double>);
  void keyPressEvent(QKeyEvent *e) override;

 signals:
  std::string Signal();
};
}  // namespace sc2

#endif  // SMART_CALC_V2_0_VIEW_PLOT_H
