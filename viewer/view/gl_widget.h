#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtWidgets>

#include "../controller/camera_controller.h"
#include "../controller/obj_controller.h"
#include "../model/camera_model.h"
#include "../model/obj_model.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions {
  Q_OBJECT
 private:
  GLuint VBO, VAO, EBO;
  QOpenGLShaderProgram *m_program;
  QMatrix4x4 m_projection;
  int projection_type, drawingMode, vertexShape;
  float vertexSize, edgeSize;
  float originScale;
  GLint colorEdgeUniform;
  GLint colorVertexUniform;
  GLint isVertexLocation;
  GLint lineShapeLocation;
  GLint drawingModeLocation;
  float m_xRotate, m_yRotate, m_zRotate;
  float m_xMove, m_yMove, m_zMove;
  std::shared_ptr<s21::Controller> model;
  s21::Controller *shape;
  QString filename;
  int vertexes;
  int facest;
  bool loadedData;
  bool loadedData_2;

  QColor colorBG;
  QColor colorVertex;
  QColor colorEdge;
  ~GLWidget();

 protected:
  virtual void initializeGL();
  virtual void resizeGL(int nWidth, int nHeight);
  virtual void paintGL();
  void createObject(s21::Controller *shape);
  QMatrix4x4 adjustModelMatrix(float *modelMatrix);
  void cleanup();
  void initMvp(s21::Controller *shape);
  void refreshObject();
  void setFileInfo(QString str);
  virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

 public:
  GLWidget(QWidget *pwgt = 0);
  void getDataFromFile(std::shared_ptr<s21::Controller> model, QString str);
  void setBgColor(QColor color);
  void setBgColorFromSettings(QColor color);
  void setEdgeColor(QColor colorEdge);
  void setEdgeColorFromSettings(QColor color);
  void setVertexColor(QColor colorVertex);
  void setVertexColorFromSettings(QColor color);
  QColor getColorBG();
  QColor getColorVert();
  QColor getColorEdge();
  void setEdgeSize(int edgeSize);
  void setVertexSize(int vertexSize);
  void setLineMode(int mode);
  void setVertexShape(int vertexShape);
  void setRotateX(float rotation);
  void setRotateY(float rotation);
  void setRotateZ(float rotation);
  void setMoveX(float move);
  void setMoveY(float move);
  void setMoveZ(float move);
  void setScale(float scale);
  void setProjectionType(int type);
  void resetObject();
  s21::CameraController *camera;

 public slots:
  void updateBgColor(QColor color);
};
