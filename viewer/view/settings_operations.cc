#include <QColor>
#include <QColorDialog>
#include <QGuiApplication>
#include <QImage>
#include <vector>

#include "QtGifImage/qgifimage.h"
#include "gl_widget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::saveSettings()
{
  settings->setValue("geometry", geometry());

  settings->setValue("vertexNoForm", ui->NoForm->isChecked());
  settings->setValue("vertexCircleForm", ui->CircleForm->isChecked());
  settings->setValue("vertexSquareForm", ui->SquareForm->isChecked());

  settings->setValue("edgeLine", ui->Line->isChecked());
  settings->setValue("edgeDottedLine", ui->DottedLine->isChecked());

  settings->setValue("ProectionP", ui->ParallelProjection->isChecked());
  settings->setValue("ProectionC", ui->CentralProjection->isChecked());

  settings->setValue("ColorBGr", ui->openGLWidget->getColorBG().red());
  settings->setValue("ColorBGg", ui->openGLWidget->getColorBG().green());
  settings->setValue("ColorBGb", ui->openGLWidget->getColorBG().blue());
  settings->setValue("ColorBGa", ui->openGLWidget->getColorBG().alpha());

  settings->setValue("ColorVertr", ui->openGLWidget->getColorVert().red());
  settings->setValue("ColorVertg", ui->openGLWidget->getColorVert().green());
  settings->setValue("ColorVertb", ui->openGLWidget->getColorVert().blue());
  settings->setValue("ColorVerta", ui->openGLWidget->getColorVert().alpha());

  settings->setValue("ColorEdger", ui->openGLWidget->getColorEdge().red());
  settings->setValue("ColorEdgeg", ui->openGLWidget->getColorEdge().green());
  settings->setValue("ColorEdgeb", ui->openGLWidget->getColorEdge().blue());
  settings->setValue("ColorEdgea", ui->openGLWidget->getColorEdge().alpha());

  settings->setValue("Scale", ui->SliderScale->value());
  settings->setValue("SizeVertex", ui->SliderVertex->value());
  settings->setValue("SizeEdge", ui->SliderEdge->value());
}

void MainWindow::loadSettings()
{
  colorBG = QColor(settings->value("ColorBGr", 59).toInt(),
                   settings->value("ColorBGg", 154).toInt(),
                   settings->value("ColorBGb", 156).toInt(),
                   settings->value("ColorBGa", 1).toInt());
  ui->openGLWidget->setBgColorFromSettings(colorBG);

  colorEdge = QColor(settings->value("ColorEdger", 30).toInt(),
                     settings->value("ColorEdgeg", 40).toInt(),
                     settings->value("ColorEdgeb", 145).toInt(),
                     settings->value("ColorEdgea", 1).toInt());
  ui->openGLWidget->setEdgeColorFromSettings(colorEdge);

  colorVertex = QColor(settings->value("ColorVertr", 30).toInt(),
                       settings->value("ColorVertg", 40).toInt(),
                       settings->value("ColorVertb", 145).toInt(),
                       settings->value("ColorVerta", 1).toInt());
  ui->openGLWidget->setVertexColorFromSettings(colorVertex);

  setGeometry(settings->value("geometry", QRect(500, 500, 500, 500)).toRect());

  ui->NoForm->setChecked(settings->value("vertexNoForm", true).toBool());
  ui->CircleForm->setChecked(
      settings->value("vertexCircleForm", false).toBool());
  ui->SquareForm->setChecked(
      settings->value("vertexSquareForm", false).toBool());
  ui->Line->setChecked(settings->value("edgeLine", false).toBool());
  ui->DottedLine->setChecked(settings->value("edgeDottedLine", true).toBool());
  ui->ParallelProjection->setChecked(true);
  ui->SliderScale->setValue(settings->value("Scale", 0).toInt());
  ui->SliderVertex->setValue(settings->value("SizeVertex", 0).toInt());
  ui->SliderEdge->setValue(settings->value("SizeEdge", 0).toInt());
}