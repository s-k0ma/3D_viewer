#include "gl_widget.h"

#include <fstream>
#include <sstream>
#include <string>

#include "../model/camera_model.h"

GLWidget::GLWidget(QWidget *pwgt /*=0*/) : QOpenGLWidget(pwgt) {
  loadedData = false;
  loadedData_2 = false;
}

void GLWidget::GLWidget::resizeEvent(QResizeEvent *event) {
  event->accept();

  if (event->size().width() > event->size().height()) {
    QWidget::resize(event->size().height(), event->size().height());
  } else {
    QWidget::resize(event->size().width(), event->size().width());
  }
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  m_program = new QOpenGLShaderProgram;
  QFile vertexShader(":/vertexShader.glsl");
  if (vertexShader.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&vertexShader);
    QString vertexShaderCode = in.readAll();
    vertexShader.close();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       vertexShaderCode.toLatin1().constData());
  } else {
    qDebug() << "Vertex shader file doesn't open";
  }

  QFile fragmentShader(":/fragmentShader.glsl");
  if (fragmentShader.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&fragmentShader);
    QString fragmentShaderCode = in.readAll();
    fragmentShader.close();
    m_program->addShaderFromSourceCode(
        QOpenGLShader::Fragment, fragmentShaderCode.toLatin1().constData());
  } else {
    qDebug() << "Fragment shader file doesn't open";
  }

  m_program->link();

  colorEdgeUniform = m_program->uniformLocation("edgeColor");
  colorVertexUniform = m_program->uniformLocation("vertexColor");
  isVertexLocation = m_program->uniformLocation("isVertex");
  drawingModeLocation = m_program->uniformLocation("drawMode");
  lineShapeLocation = m_program->uniformLocation("vertexShape");

  m_program->bind();
  glUniform4f(colorEdgeUniform, colorEdge.redF(), colorEdge.greenF(),
              colorEdge.blueF(), colorEdge.alphaF());
  glUniform4f(colorVertexUniform, colorVertex.redF(), colorVertex.greenF(),
              colorVertex.blueF(), colorVertex.alphaF());
  m_program->release();

  m_program->log();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLWidget::resizeGL(int nWidth, int nHeight) {
  glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void GLWidget::paintGL() {
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(colorBG.redF(), colorBG.greenF(), colorBG.blueF(),
               colorBG.alphaF());
  if (loadedData_2) {
    if (loadedData) {
      createObject(shape);
      initMvp(shape);

      //    shape->destroyShape();
      loadedData = false;
      setProjectionType(0);
    }

    m_program->bind();
    m_program->setUniformValue("modelViewProjection", m_projection);

    glBindVertexArray(VAO);
    glUniform1i(isVertexLocation, 0);
    glUniform1i(drawingModeLocation, drawingMode);
    glLineWidth(this->edgeSize);
    glDrawElements(GL_TRIANGLES, facest, GL_UNSIGNED_INT, 0);

    glUniform1i(isVertexLocation, 1);
    glUniform1i(lineShapeLocation, vertexShape);
    glPointSize(vertexSize);
    if (vertexShape == 1) ::glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, vertexes);
    if (vertexShape == 1) ::glDisable(GL_POINT_SMOOTH);

    glBindVertexArray(0);
    m_program->release();
  }
}

void GLWidget::createObject(s21::Controller *openedShape) {
  cleanup();
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * openedShape->getVertexCount() * 3,
               openedShape->getVertexes().data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);  // Enable the position attribute

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * openedShape->getFacetsCount(),
               openedShape->getEdges().data(), GL_STATIC_DRAW);

  glBindVertexArray(0);
}

void GLWidget::getDataFromFile(std::shared_ptr<s21::Controller> model,
                               QString str) {
  this->model = model;
  shape = model.get();
  vertexes = shape->getVertexCount();
  facest = shape->getFacetsCount();
  loadedData = true;
  loadedData_2 = true;
  setFileInfo(str);
  update();
}

void GLWidget::setFileInfo(QString str) {
  QFileInfo fileInfo(str);
  filename = fileInfo.fileName();
  filename.append(" vertices: ");
  filename.append(QString::number(vertexes));
  filename.append(" facets: ");
  filename.append(QString::number(facest));

  setStatusTip(filename);
}

void GLWidget::cleanup() {
  if (VAO) {
    glDeleteVertexArrays(1, &VAO);
    VAO = 0;  // Reset to 0 after deletion
  }
  if (VBO) {
    glDeleteBuffers(1, &VBO);
    VBO = 0;  // Reset to 0 after deletion
  }
  if (EBO) {
    glDeleteBuffers(1, &EBO);
    EBO = 0;  // Reset to 0 after deletion
  }
}

void GLWidget::initMvp(s21::Controller *shape) {
  camera->calculateModelMatrix(shape);
  originScale = camera->getModelMatrix()[0];
  camera->calculateViewMatrix();

  switch (projection_type) {
    case 0:
      camera->s21Frustum(static_cast<float>(width()) / height(), 60, 100,
                         0.001);
      break;
    case 1:
      camera->s21Ortho(static_cast<float>(width()) / height(), 60, 0.01, 100);
      break;
  }
  camera->calculateRotationMatrix(0, 0, 0);
  camera->multModelRotation();
  camera->multMvpView();
  camera->multMvpProjection();
  m_projection = adjustModelMatrix(camera->getMvpMatrix());
}

QMatrix4x4 GLWidget::adjustModelMatrix(float *modelMatrix) {
  QMatrix4x4 qtModelMatrix;

  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      qtModelMatrix(row, col) = modelMatrix[row * 4 + col];
    }
  }
  return qtModelMatrix;
}

void GLWidget::setBgColor(QColor color) {
  colorBG = QColor(color);
  update();
}

void GLWidget::setBgColorFromSettings(QColor color) { colorBG = QColor(color); }

void GLWidget::setEdgeColor(QColor color) {
  colorEdge = color;
  m_program->bind();
  glUniform4f(colorEdgeUniform, color.redF(), color.greenF(), color.blueF(),
              color.alphaF());
  m_program->release();
  update();
}

void GLWidget::setEdgeColorFromSettings(QColor color) { colorEdge = color; }

void GLWidget::setVertexColor(QColor color) {
  colorVertex = color;
  m_program->bind();
  glUniform4f(colorVertexUniform, color.redF(), color.greenF(), color.blueF(),
              color.alphaF());
  m_program->release();
  update();
}

void GLWidget::setVertexColorFromSettings(QColor color) { colorVertex = color; }

void GLWidget::setVertexSize(int vertexSize) {
  this->vertexSize = (float)vertexSize;
  update();
}

void GLWidget::setEdgeSize(int edgeSize) {
  this->edgeSize = (float)edgeSize;
  update();
}

void GLWidget::setLineMode(int mode) {
  this->drawingMode = mode;
  update();
}

void GLWidget::setVertexShape(int vertexShape) {
  this->vertexShape = vertexShape;
  update();
}

QColor GLWidget::getColorBG() { return this->colorBG; }

QColor GLWidget::getColorVert() { return this->colorVertex; }

QColor GLWidget::getColorEdge() { return this->colorEdge; }

void GLWidget::setRotateX(float rotation) {
  m_zRotate = rotation;

  camera->calculateRotationMatrix(m_xRotate, m_yRotate, m_zRotate);
  refreshObject();
}

void GLWidget::setRotateY(float rotation) {
  m_yRotate = rotation;

  camera->calculateRotationMatrix(m_xRotate, m_yRotate, m_zRotate);
  refreshObject();
}

void GLWidget::setRotateZ(float rotation) {
  m_xRotate = rotation;

  camera->calculateRotationMatrix(m_xRotate, m_yRotate, m_zRotate);
  refreshObject();
}

void GLWidget::setMoveX(float move) {
  m_xMove = move;

  camera->setModelPosition(m_xMove, m_yMove, m_zMove);
  refreshObject();
}

void GLWidget::setMoveY(float move) {
  m_yMove = move;

  camera->setModelPosition(m_xMove, m_yMove, m_zMove);
  refreshObject();
}

void GLWidget::setMoveZ(float move) {
  m_zMove = move;

  camera->setModelPosition(m_xMove, m_yMove, m_zMove);
  refreshObject();
}

void GLWidget::setScale(float scale) {
  camera->setModelScale(scale * originScale);
  refreshObject();
}

void GLWidget::setProjectionType(int type) {
  projection_type = type;
  switch (projection_type) {
    case 0:
      camera->s21Frustum(static_cast<float>(width()) / height(), 60, 100,
                         0.001);
      break;
    case 1:
      camera->s21Ortho(static_cast<float>(width()) / height(), 60, 0.01, 100);
      break;
  }
  refreshObject();
}

void GLWidget::resetObject() {
  camera->setModelScale(originScale);
  camera->setModelPosition(0, 0, 0);
  camera->calculateRotationMatrix(0, 0, 0);
  refreshObject();
}

void GLWidget::refreshObject() {
  camera->multModelRotation();
  camera->multMvpView();
  camera->multMvpProjection();
  m_projection = adjustModelMatrix(camera->getMvpMatrix());
  update();
}

void GLWidget::updateBgColor(QColor color) { setBgColor(color); }

GLWidget::~GLWidget() { cleanup(); }
