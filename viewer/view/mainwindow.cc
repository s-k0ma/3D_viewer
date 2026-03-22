#include "mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <QGuiApplication>
#include <QImage>
#include <vector>

#include "../controller/camera_controller.h"
#include "../controller/obj_controller.h"
#include "QtGifImage/qgifimage.h"
#include "gl_widget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::CameraController *camera, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), camera_(camera) {
  setlocale(LC_ALL, "C");
  ui->setupUi(this);
  ui->openGLWidget->camera = camera_;
  statusBar()->showMessage("Ready", 2000);

  QMenu *pmnuFile = new QMenu("&File");

  pmnuFile->addAction("&Open...", this,
                    &MainWindow::slotLoad,
                    QKeySequence("Ctrl+O"));

  pmnuFile->addSeparator();
  pmnuFile->addAction("&Quit", qApp,
                    &QCoreApplication::quit,
                    QKeySequence("Ctrl+Q"));

  menuBar()->addMenu(pmnuFile);
  pmnuFile->addAction("&Save as ...", this,
                    &MainWindow::saveImage,
                    QKeySequence("Ctrl+S"));

  pmnuFile->addSeparator();

  settings = new QSettings("develop", "3D_viewer", this);
  loadSettings();

  ui->SliderVertex->setRange(0, 100);
  ui->SliderEdge->setRange(0, 100);
  ui->SliderScale->setRange(0, 200);

  ui->RotationX->setRange(0, 360);
  ui->RotationY->setRange(0, 360);
  ui->RotationZ->setRange(0, 360);

  ui->SpinBoxX->setRange(-1, 1);
  ui->SpinBoxX->setSingleStep(0.01);
  ui->SpinBoxY->setRange(-1, 1);
  ui->SpinBoxY->setSingleStep(0.01);
  ui->SpinBoxZ->setRange(-1, 1);
  ui->SpinBoxZ->setSingleStep(0.01);
  standartSliderPosition();

  this->setWindowTitle("3DViewer V2.0");
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_PushButtonVertexColor_clicked() {
  colorVertex =
      QColorDialog::getColor(Qt::white, this, tr("Выберите цвет вершин"));
  ui->openGLWidget->setVertexColor(colorVertex);
}

void MainWindow::on_PushButtonEdgeColor_clicked() {
  colorEdge =
      QColorDialog::getColor(Qt::white, this, tr("Выберите цвет рёбер"));
  ui->openGLWidget->setEdgeColor(colorEdge);
}

void MainWindow::on_PushButtonBgColor_clicked() {
  colorBG = QColorDialog::getColor(Qt::black, this, tr("Выберите цвет фона"));
  ui->openGLWidget->setBgColor(colorBG);
}

void MainWindow::on_SliderVertex_valueChanged(int value) {
  ui->openGLWidget->setVertexSize(ui->SliderVertex->value());
}

void MainWindow::on_SliderEdge_valueChanged(int value) {
  ui->openGLWidget->setEdgeSize(ui->SliderEdge->value());
}

void MainWindow::on_Line_clicked() { ui->openGLWidget->setLineMode(0); }

void MainWindow::on_DottedLine_clicked() { ui->openGLWidget->setLineMode(1); }

void MainWindow::on_NoForm_clicked() { ui->openGLWidget->setVertexShape(2); }

void MainWindow::on_SquareForm_clicked() {
  ui->openGLWidget->setVertexShape(0);
}

void MainWindow::on_CircleForm_clicked() {
  ui->openGLWidget->setVertexShape(1);
}

void MainWindow::on_RotationX_valueChanged(int value) {
  ui->openGLWidget->setRotateX((float) value);
}

void MainWindow::on_RotationZ_valueChanged(int value) {
  ui->openGLWidget->setRotateZ((float) value);
}

void MainWindow::on_RotationY_valueChanged(int value) {
  ui->openGLWidget->setRotateY((float) value);
}

void MainWindow::on_SpinBoxX_valueChanged(double arg1) {
  ui->openGLWidget->setMoveX((float) arg1);
}

void MainWindow::on_SpinBoxY_valueChanged(double arg1) {
  ui->openGLWidget->setMoveY((float) arg1);
}

void MainWindow::on_SpinBoxZ_valueChanged(double arg1) {
  ui->openGLWidget->setMoveZ((float) arg1);
}

void MainWindow::on_SliderScale_valueChanged(int value) {
  ui->openGLWidget->setScale(value * 0.01);
}

void MainWindow::on_CentralProjection_clicked() {
  ui->openGLWidget->setProjectionType(1);
}

void MainWindow::on_ParallelProjection_clicked() {
  ui->openGLWidget->setProjectionType(0);
}

void MainWindow::on_Sbros_clicked() {
  ui->openGLWidget->resetObject();
  standartSliderPosition();
}

void MainWindow::standartSliderPosition() {
  ui->SliderScale->setValue(100);
  ui->RotationX->setValue(0);
  ui->RotationY->setValue(0);
  ui->RotationZ->setValue(0);
  ui->SpinBoxX->setValue(0);
  ui->SpinBoxY->setValue(0);
}
