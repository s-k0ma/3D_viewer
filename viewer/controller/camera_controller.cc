#include "camera_controller.h"

#include "obj_controller.h"

s21::CameraController::CameraController() : cameraModel() {}
float *s21::CameraController::getModelMatrix() {
  return cameraModel.getModelMatrix();
}
float *s21::CameraController::getViewMatrix() {
  return cameraModel.getViewMatrix();
}
float *s21::CameraController::getProjectionMatrix() {
  return cameraModel.getProjectionMatrix();
}
float *s21::CameraController::getMvpMatrix() {
  return cameraModel.getMvpMatrix();
}
float *s21::CameraController::getRotataionMatrix() {
  return cameraModel.getRotataionMatrix();
}
void s21::CameraController::calculateModelMatrix(s21::Controller *shape) {
  cameraModel.calculateModelMatrix(shape);
}
void s21::CameraController::setModelPosition(float x, float y, float z) {
  cameraModel.setModelPosition(x, y, z);
}
void s21::CameraController::setModelScale(float scale) {
  cameraModel.setModelScale(scale);
}
void s21::CameraController::calculateRotationMatrix(float xAngle, float yAngle,
                                                    float zAngle) {
  cameraModel.calculateRotationMatrix(xAngle, yAngle, zAngle);
}
void s21::CameraController::s21Frustum(float aspect, float fov, float near,
                                       float far) {
  cameraModel.s21Frustum(aspect, fov, near, far);
}
void s21::CameraController::s21Ortho(float aspect, float fov, float near,
                                     float far) {
  cameraModel.s21Ortho(aspect, fov, near, far);
}
void s21::CameraController::calculateViewMatrix() {
  cameraModel.calculateViewMatrix();
}
void s21::CameraController::multModelRotation() {
  cameraModel.multModelRotation();
}
void s21::CameraController::multMvpView() { cameraModel.multMvpView(); }
void s21::CameraController::multMvpProjection() {
  cameraModel.multMvpProjection();
}
Vec4 s21::CameraController::cross(Vec4 a, Vec4 b) {
  return s21::Camera::cross(a, b);
}
Vec4 s21::CameraController::normalize(Vec4 v) {
  return s21::Camera::normalize(v);
}
Vec4 s21::CameraController::subtract(Vec4 a, Vec4 b) {
  return s21::Camera::subtract(a, b);
}
s21::CameraController &s21::CameraController::getInstance() {
  static CameraController instance;  // Единственный экземпляр класса.
  return instance;
}
