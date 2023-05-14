#include <QApplication>

#include "model/model.h"
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  sc2::Model m;
  sc2::Controller c(&m);
  sc2::MainWindow w(&c);
  w.show();
  return a.exec();
}
