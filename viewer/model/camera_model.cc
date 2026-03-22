//
// Created by rivatent on 10/8/24.
//

#include "camera_model.h"

namespace s21 {

void Camera::calculateModelMatrix(Controller *shape) {
  float translationMatrix[16] = {1,   0.0, 0.0, 0.0, 0.0, 1,   0.0, 0.0,
                                 0.0, 0.0, 1,   -1,  0.0, 0.0, 0.0, 1};

  float maxExtent = shape->getMaxX() > shape->getMaxY()
                        ? shape->getMaxX() > shape->getMaxZ() ? shape->getMaxX()
                                                              : shape->getMaxZ()
                    : shape->getMaxY() > shape->getMaxZ() ? shape->getMaxY()
                                                          : shape->getMaxZ();
  float scaleFactor = 0.6 / maxExtent;

  float scalingMatrix[16] = {
      scaleFactor, 0.0f, 0.0f,        0.0f, 0.0f, scaleFactor, 0.0f, 0.0f,
      0.0f,        0.0f, scaleFactor, 0.0f, 0.0f, 0.0f,        0.0f, 1.0f};
  multiply(scalingMatrix, translationMatrix, modelMatrix_);
}
void Camera::multiply(float *a, float *b, float *result) {
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      float sum = 0.0;
      for (int i = 0; i < 4; ++i) {
        sum += a[row * 4 + i] * b[i * 4 + col];
      }
      result[row * 4 + col] = sum;
    }
  }
}
void Camera::setModelPosition(float x, float y, float z) {
  modelMatrix_[3] = x;
  modelMatrix_[7] = y;
  modelMatrix_[11] = z;
}
void Camera::setModelScale(float scale) {
  modelMatrix_[0] = scale;
  modelMatrix_[5] = scale;
  modelMatrix_[10] = scale;
}
void Camera::calculateRotationMatrix(float xAngle, float yAngle, float zAngle) {
  float xRad = xAngle * (M_PI / 180.0);
  float yRad = yAngle * (M_PI / 180.0);
  float zRad = zAngle * (M_PI / 180.0);
  float sinX = sin(xRad);
  float sinY = sin(yRad);
  float sinZ = sin(zRad);
  float cosX = cos(xRad);
  float cosY = cos(yRad);
  float cosZ = cos(zRad);

  float rotateXmatrix[16] = {1, 0,    0,    0, 0, cosX, -sinX, 0,
                             0, sinX, cosX, 0, 0, 0,    0,     1};

  float rotateYmatrix[16] = {cosY, 0, -sinY, 0, 0, 1, 0, 0,
                             sinY, 0, cosY,  0, 0, 0, 0, 1};

  float rotateZmatrix[16] = {cosZ, -sinZ, 0, 0, sinZ, cosZ, 0, 0,
                             0,    0,     1, 0, 0,    0,    0, 1};

  multiply(rotateXmatrix, rotateZmatrix, rotationMatrix_);
  multiply(rotateYmatrix, rotationMatrix_, rotationMatrix_);
}

void Camera::s21Frustum(float aspect, float fov, float near, float far) {
  float fovRadians = fov * M_PI / 180.0f;
  float tanHalfFov = tanf(fovRadians / 2.0f);

  float top = near * tanHalfFov;
  float bot = -top;
  float right = top * aspect;
  float left = -right;

  float A = (right + left) / (right - left);
  float B = (top + bot) / (top - bot);
  float C = -(far + near) / (far - near);
  float D = -(2.0f * far * near) / (far - near);

  projectionMatrix_[0] = (2.0f * near) / (right - left);
  projectionMatrix_[1] = 0.0f;
  projectionMatrix_[2] = 0.0f;
  projectionMatrix_[3] = 0.0f;

  projectionMatrix_[4] = 0.0f;
  projectionMatrix_[5] = (2.0f * near) / (top - bot);
  projectionMatrix_[6] = 0.0f;
  projectionMatrix_[7] = 0.0f;

  projectionMatrix_[8] = A;
  projectionMatrix_[9] = B;
  projectionMatrix_[10] = C;
  projectionMatrix_[11] = -1.0f;

  projectionMatrix_[12] = 0.0f;
  projectionMatrix_[13] = 0.0f;
  projectionMatrix_[14] = D;
  projectionMatrix_[15] = 1.0f;
}

void Camera::s21Ortho(float aspect, float fov, float near, float far) {
  float fovRadians = fov * M_PI / 180.0f;
  float tanHalfFov = tanf(fovRadians / 2.0f);

  float top = near * tanHalfFov;
  float bot = -top;
  float right = top * aspect;
  float left = -right;

  float tx = -(right + left) / (right - left);
  float ty = -(top + bot) / (top - bot);
  float tz = -(far + near) / (far - near);

  projectionMatrix_[0] = 2.0f / (right - left);
  projectionMatrix_[1] = 0.0f;
  projectionMatrix_[2] = 0.0f;
  projectionMatrix_[3] = 0.0f;

  projectionMatrix_[4] = 0.0f;
  projectionMatrix_[5] = 2.0f / (top - bot);
  projectionMatrix_[6] = 0.0f;
  projectionMatrix_[7] = 0.0f;

  projectionMatrix_[8] = 0.0f;
  projectionMatrix_[9] = 0.0f;
  projectionMatrix_[10] = -2.0f / (far - near);
  projectionMatrix_[11] = 0.0f;

  projectionMatrix_[12] = tx;
  projectionMatrix_[13] = ty;
  projectionMatrix_[14] = tz;
  projectionMatrix_[15] = 1.0f;
}

void Camera::calculateViewMatrix() {
  Vec4 cameraPos = {0.0f, 0.0f, -1.0f, 0.0f};
  Vec4 cameraTarget = {0.0f, 0.0f, 0.0f, 0.0f};
  Vec4 cameraDirection = normalize(subtract(cameraPos, cameraTarget));
  Vec4 up = {0.0f, 1.0f, 0.0f, 0.0f};
  Vec4 cameraRight = normalize(cross(up, cameraDirection));
  Vec4 cameraUp = cross(cameraDirection, cameraRight);

  float a[16] = {cameraRight.x,
                 cameraRight.y,
                 cameraRight.z,
                 0,
                 cameraUp.x,
                 cameraUp.y,
                 cameraUp.z,
                 0,
                 cameraDirection.x,
                 cameraDirection.y,
                 cameraDirection.z,
                 0,
                 0,
                 0,
                 0,
                 1};

  float b[16] = {1, 0, 0, -cameraPos.x, 0, 1, 0, -cameraPos.y,
                 0, 0, 1, -cameraPos.z, 0, 0, 0, 1};

  multiply(b, a, viewMatrix_);
}

Vec4 Camera::cross(Vec4 a, Vec4 b) {
  return (Vec4){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x, 1};
}

Vec4 Camera::normalize(Vec4 v) {
  float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
  return (Vec4){v.x / length, v.y / length, v.z / length, 1.0};
}

Vec4 Camera::subtract(Vec4 a, Vec4 b) {
  return (Vec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}
void Camera::multModelRotation() {
  Camera::multiply(modelMatrix_, rotationMatrix_, mvpMatrix_);
}
void Camera::multMvpView() {
  Camera::multiply(mvpMatrix_, viewMatrix_, mvpMatrix_);
}
void Camera::multMvpProjection() {
  Camera::multiply(mvpMatrix_, projectionMatrix_, mvpMatrix_);
}
float *Camera::getModelMatrix() { return modelMatrix_; }
float *Camera::getViewMatrix() { return viewMatrix_; }
float *Camera::getProjectionMatrix() { return projectionMatrix_; }
float *Camera::getMvpMatrix() { return mvpMatrix_; }
float *Camera::getRotataionMatrix() { return rotationMatrix_; }

}  // namespace s21