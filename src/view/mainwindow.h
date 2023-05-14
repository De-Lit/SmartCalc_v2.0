#ifndef SMART_CALC_V2_0_VIEW_MAINWINDOW_H
#define SMART_CALC_V2_0_VIEW_MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <cstring>

#include "../controller/controller.h"
#include "plot.h"

namespace sc2 {

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow() = delete;
  MainWindow(Controller *c);
  MainWindow(const MainWindow &c) = delete;
  MainWindow(MainWindow &&c) = delete;
  MainWindow &operator=(const MainWindow &c) = delete;
  MainWindow &operator=(MainWindow &&c) = delete;
  ~MainWindow();

 private:
  void closeEvent(QCloseEvent *event) override;

  Ui::MainWindow *ui_;
  Controller *controller_;
  Plot *plot_;

 private slots:
  void on_checkBox_stateChanged(int arg1);
  void keyPressEvent(QKeyEvent *e) override;
  std::string Slot();
  void ButtonPressed();
  void ButtonUnarPressed();
  void Calculation();
  void Clear();
  void AllClear();

 signals:
  void SignalClose();
};
}  // namespace sc2
#endif  // SMART_CALC_V2_0_VIEW_MAINWINDOW_H
