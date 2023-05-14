#include "plot.h"

#include <QWidget>
#include <cstring>
#include <vector>

#include "../controller/controller.h"
#include "../source/qcustomplot.h"
#include "ui_plot.h"

sc2::Plot::Plot(Controller *c) : ui_(new Ui::Plot), controller_(c) {
  ui_->setupUi(this);
  this->setWindowFlags(Qt::Window | Qt::WindowTitleHint |
                       Qt::CustomizeWindowHint);

  connect(ui_->bin_plot, SIGNAL(released()), this, SLOT(PlotPressed()));
  connect(ui_->bin_plot_clear, SIGNAL(released()), this,
          SLOT(PlotClearPressed()));

  w_graphic_ = new QCustomPlot();
  ui_->gridLayout->addWidget(w_graphic_, 0, 0, 1, 1);
  w_graphic_->xAxis->setLabel("x");
  w_graphic_->yAxis->setLabel("y");

  SetDefaultPlot();
}

sc2::Plot::~Plot() { delete ui_; }

void sc2::Plot::SetDefaultPlot() {
  w_graphic_->xAxis->setRange(-10, 10);
  w_graphic_->yAxis->setRange(-10, 10);
  w_graphic_->replot();
}

void sc2::Plot::RemovePlot() {
  w_graphic_->removeGraph(0);
  w_graphic_->addGraph(w_graphic_->xAxis, w_graphic_->yAxis);
  SetDefaultPlot();
}

void sc2::Plot::PlotPressed() {
  if (ui_->spinBox_x_max->value() > ui_->spinBox_x_min->value() &&
      ui_->spinBox_y_max->value() > ui_->spinBox_y_min->value()) {
    auto coordinates =
        controller_->PlotCalculation(emit Signal(), ui_->spinBox_x_min->value(),
                                     ui_->spinBox_x_max->value());
    if (coordinates[0]->size()) {
      MakePlot(QVector<double>(coordinates[0]->begin(), coordinates[0]->end()),
               QVector<double>(coordinates[1]->begin(), coordinates[1]->end()));
    } else {
      RemovePlot();
    }
  } else {
    RemovePlot();
  }
}

void sc2::Plot::PlotClearPressed() { RemovePlot(); }

void sc2::Plot::MakePlot(QVector<double> x, QVector<double> y) {
  w_graphic_->xAxis->setRange(ui_->spinBox_x_min->value(),
                              ui_->spinBox_x_max->value());
  w_graphic_->yAxis->setRange(ui_->spinBox_y_min->value(),
                              ui_->spinBox_y_max->value());

  w_graphic_->addGraph(w_graphic_->xAxis, w_graphic_->yAxis);
  w_graphic_->graph(0)->setData(x, y);
  w_graphic_->graph(0)->setLineStyle(QCPGraph::lsNone);
  w_graphic_->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

  w_graphic_->replot();
  w_graphic_->setInteraction(QCP::iRangeZoom, true);
  w_graphic_->setInteraction(QCP::iRangeDrag, true);
}

void sc2::Plot::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
    Plot::PlotPressed();
  }
}

void sc2::Plot::SignalClose() {
  this->close();
  ui_->~Plot();
}
