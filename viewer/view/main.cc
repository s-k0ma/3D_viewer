#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::CameraController &camera = s21::CameraController::getInstance();
  MainWindow mainWindow(&camera);
  mainWindow.show();

  return app.exec();
}
