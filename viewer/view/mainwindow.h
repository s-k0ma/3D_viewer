#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "QtGifImage/qgifimage.h"
#include "gl_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::CameraController *camera, QWidget *parent = nullptr);
  ~MainWindow();
  QColor colorVertex;
  QColor colorEdge;
  QColor colorBG;
  void saveSettings();
  void loadSettings();

 private slots:
  void slotLoad();
  void on_PushButtonBgColor_clicked();
  void on_PushButtonEdgeColor_clicked();
  void on_PushButtonVertexColor_clicked();
  void on_SliderVertex_valueChanged(int value);
  void on_SliderEdge_valueChanged(int value);
  void on_Line_clicked();
  void on_DottedLine_clicked();
  void on_NoForm_clicked();
  void on_SquareForm_clicked();
  void on_CircleForm_clicked();
  void saveImage();
  void on_PushButtonGif_clicked();
  void make_Gif();
  void save_Gif();
  void on_SpinBoxX_valueChanged(double arg1);
  void on_SpinBoxY_valueChanged(double arg1);
  void on_SpinBoxZ_valueChanged(double arg1);
  void on_RotationX_valueChanged(int value);
  void on_RotationY_valueChanged(int value);
  void on_RotationZ_valueChanged(int value);
  void on_CentralProjection_clicked();
  void on_ParallelProjection_clicked();
  void on_SliderScale_valueChanged(int value);
  void on_Sbros_clicked();

 private:
  Ui::MainWindow *ui;
  QSettings *settings;
  QGifImage *gif;
  QTimer *timer;
  QTimer *screenTimer;
  QImage screen;
  void standartSliderPosition();
  s21::CameraController *camera_;
};

#endif  // MAINWINDOW_H
