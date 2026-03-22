#include <QColor>
#include <QColorDialog>
#include <QGuiApplication>
#include <QImage>
#include <vector>

#include "../controller/obj_controller.h"
#include "QtGifImage/qgifimage.h"
#include "gl_widget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_PushButtonGif_clicked() {  // FIXME
  ui->PushButtonGif->setText("Идёт запись...");
  gif = new QGifImage();
  timer = new QTimer(this);
  screenTimer = new QTimer(this);
  gif->setDefaultDelay(100);

  connect(screenTimer, SIGNAL(timeout()), this, SLOT(make_Gif()));
  screenTimer->start(100);
  timer->singleShot(5000, screenTimer, SLOT(stop()));
  timer->singleShot(5000, this, SLOT(save_Gif()));
  timer->singleShot(5000, this,
                    [this]() { ui->PushButtonGif->setText("MAKE GIF"); });
  timer->start();
}

void MainWindow::slotLoad() {
  QString str = QFileDialog::getOpenFileName();
  if (!str.isEmpty()) {
    std::shared_ptr<s21::Controller> controllerNewInstance;
    try {
      controllerNewInstance =
          std::make_shared<s21::Controller>(str.toLocal8Bit().data());
    } catch (std::invalid_argument) {
      qDebug() << "Fail file parse attempt";
      return;
    }
    ui->openGLWidget->getDataFromFile(controllerNewInstance, str);
    ui->openGLWidget->resetObject();
    standartSliderPosition();
  }
}
void MainWindow::saveImage() {
  QImage image;
  QString strPath;
  QString str = QFileDialog::getSaveFileName(ui->openGLWidget, "Save image", "",
                                             "*.jpeg ;; *.bmp", &strPath);
  if (!str.isEmpty()) {
    if (strPath.contains("jpeg")) {
      image = ui->openGLWidget->grabFramebuffer();
      image.save(str, "JPEG");
    } else if (strPath.contains("bmp")) {
      image = ui->openGLWidget->grabFramebuffer();
      image.save(str, "BMP");
    } else {
      image = ui->openGLWidget->grabFramebuffer();
      image.save(str, "JPEG");
    }
  }
}

void MainWindow::make_Gif() {
  screen = ui->openGLWidget->grabFramebuffer();
  gif->addFrame(screen);
}

void MainWindow::save_Gif() {
  QString strFilename;
  QString strPath;

  strFilename = QFileDialog::getSaveFileName(ui->openGLWidget, "Save gif", "",
                                             "*.gif", &strPath);
  gif->save(strFilename);

  delete gif;
  delete timer;
  delete screenTimer;
}