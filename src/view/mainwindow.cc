#include "mainwindow.h"

#include <QKeyEvent>
#include <QMainWindow>
#include <cstring>

#include "../controller/controller.h"
#include "plot.h"
#include "ui_mainwindow.h"

sc2::MainWindow::MainWindow(Controller *c)
    : QMainWindow(nullptr), ui_(new Ui::MainWindow), controller_(c) {
  plot_ = new Plot(c);
  connect(plot_, &Plot::Signal, this, &MainWindow::Slot);
  connect(this, &MainWindow::SignalClose, plot_, &Plot::SignalClose);

  ui_->setupUi(this);

  connect(ui_->bin_0, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_1, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_2, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_3, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_4, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_5, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_6, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_7, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_8, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_9, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_add, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_sub, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_mul, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_div, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_dec, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_open_bracket, SIGNAL(released()), this,
          SLOT(ButtonPressed()));
  connect(ui_->bin_close_bracket, SIGNAL(released()), this,
          SLOT(ButtonPressed()));
  connect(ui_->bin_mod, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_pow, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_x, SIGNAL(released()), this, SLOT(ButtonPressed()));
  connect(ui_->bin_ln, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));
  connect(ui_->bin_log, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));
  connect(ui_->bin_sin, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));
  connect(ui_->bin_cos, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));
  connect(ui_->bin_tan, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));
  connect(ui_->bin_asin, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));
  connect(ui_->bin_acos, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));
  connect(ui_->bin_atan, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));
  connect(ui_->bin_sqrt, SIGNAL(released()), this, SLOT(ButtonUnarPressed()));

  connect(ui_->bin_clear, SIGNAL(released()), this, SLOT(Clear()));
  connect(ui_->bin_all_clear, SIGNAL(released()), this, SLOT(AllClear()));
  connect(ui_->bin_equal, SIGNAL(released()), this, SLOT(Calculation()));
}

sc2::MainWindow::~MainWindow() {
  delete plot_;
  delete ui_;
}

void sc2::MainWindow::ButtonPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString newLable;
  newLable = ui_->lineEdit->text() + button->text();
  ui_->lineEdit->setText(newLable);
}

void sc2::MainWindow::ButtonUnarPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString newLable;
  newLable = ui_->lineEdit->text() + button->text() + "(";
  ui_->lineEdit->setText(newLable);
}

void sc2::MainWindow::Calculation() {
  setlocale(LC_NUMERIC, "C");
  ui_->outputLabel->setText(QString::fromStdString(
      controller_->Calculation(ui_->lineEdit->text().toStdString().c_str(),
                               ui_->double_x_input->value())));
}

void sc2::MainWindow::Clear() { ui_->lineEdit->backspace(); }

void sc2::MainWindow::AllClear() {
  ui_->lineEdit->clear();
  ui_->outputLabel->setText("0");
  ui_->double_x_input->setValue(0);
}

void sc2::MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
    MainWindow::Calculation();
  }
}

std::string sc2::MainWindow::Slot() {
  return ui_->lineEdit->text().toStdString();
}

void sc2::MainWindow::on_checkBox_stateChanged(int arg1) {
  if (arg1) {
    plot_->show();
  } else {
    plot_->close();
  }
}

void sc2::MainWindow::closeEvent(QCloseEvent *event) {
  emit SignalClose();
  event->accept();
}
