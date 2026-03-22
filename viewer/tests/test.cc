//
// Created by rivatent on 10/8/24.
//
#include "test.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <iostream>

void CreateTestObjFile() {
  std::ofstream file("test.obj");
  file << "# Simple cube\n";
  file << "v -1.0 -1.0 -1.0\n";
  file << "v  1.0 -1.0 -1.0\n";
  file << "v  1.0  1.0 -1.0\n";
  file << "v -1.0  1.0 -1.0\n";
  file << "v -1.0 -1.0  1.0\n";
  file << "v  1.0 -1.0  1.0\n";
  file << "v  1.0  1.0  1.0\n";
  file << "v -1.0  1.0  1.0\n";
  file << "f 1 2 3 4\n";
  file << "f 5 6 7 8\n";
  file << "f 1 2 6 5\n";
  file << "f 2 3 7 6\n";
  file << "f 3 4 8 7\n";
  file << "f 4 1 5 8\n";
  file.close();
}

void DeleteTestObjFile() { std::remove("test.obj"); }

bool CompareMatrices(const float *a, const float *b, float epsilon = 1e-5) {
  for (int i = 0; i < 16; ++i) {
    if (fabs(a[i] - b[i]) > epsilon) {
      return false;
    }
  }
  return true;
}

TEST(ModelTest, Constructor) {
  CreateTestObjFile();
  s21::Model model;
  EXPECT_EQ((int)model.getVertexCount(), 0);
  CreateTestObjFile();
}

TEST(ModelTest, DefaultConstructorTest) {
  s21::Model model;
  EXPECT_EQ((int)model.getVertexCount(), 0);
  EXPECT_EQ((int)model.getFacetsCount(), 0);
  EXPECT_FLOAT_EQ(model.getMinX(), 0.0);
  EXPECT_FLOAT_EQ(model.getMaxX(), 0.0);
  EXPECT_FLOAT_EQ(model.getMinY(), 0.0);
  EXPECT_FLOAT_EQ(model.getMaxY(), 0.0);
  EXPECT_FLOAT_EQ(model.getMinZ(), 0.0);
  EXPECT_FLOAT_EQ(model.getMaxZ(), 0.0);
}

TEST(ModelTest, ConstructorWithFilenameTest) {
  CreateTestObjFile();
  s21::Model model("test.obj");

  EXPECT_EQ((int)model.getVertexCount(), 8);
  EXPECT_EQ((int)model.getFacetsCount(), 6);

  DeleteTestObjFile();
}

TEST(ModelTest, GetVertexesTest) {
  CreateTestObjFile();
  s21::Model model("test.obj");

  const std::vector<float> &vertexes = model.getVertexes();
  EXPECT_EQ((int)vertexes.size(), 24);

  DeleteTestObjFile();
}

TEST(ModelTest, GetEdgesTest) {
  CreateTestObjFile();
  s21::Model model("test.obj");

  const std::vector<int> &edges = model.getEdges();
  EXPECT_EQ((int)edges.size(), 6);

  DeleteTestObjFile();
}

TEST(ModelTest, WrongFilename) {
  CreateTestObjFile();
  EXPECT_ANY_THROW(s21::Model model("test.ob"));

  DeleteTestObjFile();
}

TEST(CameraTest, ModelMatrixCalculation) {
  CreateTestObjFile();

  s21::Controller shape("test.obj");
  s21::Camera camera;
  camera.calculateModelMatrix(&shape);

  float expectedModelMatrix[16] = {0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.6f,
                                   0.0f, 0.0f, 0.0f, 0.0f, 0.6f, -0.6f,
                                   0.0f, 0.0f, 0.0f, 1.0f};

  for (int i = 0; i < 16; i++) {
    EXPECT_FLOAT_EQ(camera.getModelMatrix()[i], expectedModelMatrix[i]);
  }

  DeleteTestObjFile();
}

TEST(CameraTest, SetModelPositionWithTestFile) {
  s21::Camera camera;

  camera.setModelPosition(2.0f, 3.0f, 3.0f);

  EXPECT_FLOAT_EQ(camera.getModelMatrix()[3], 2.0f);
  EXPECT_FLOAT_EQ(camera.getModelMatrix()[7], 3.0f);
  EXPECT_FLOAT_EQ(camera.getModelMatrix()[11], 3.0f);
}

TEST(CameraTest, SetModelScaleWithTestFile) {
  s21::Camera camera;

  camera.setModelScale(2.0f);

  EXPECT_FLOAT_EQ(camera.getModelMatrix()[0], 2.0f);
  EXPECT_FLOAT_EQ(camera.getModelMatrix()[5], 2.0f);
  EXPECT_FLOAT_EQ(camera.getModelMatrix()[10], 2.0f);
}

TEST(CameraTest, CalculateRotationMatrix) {
  s21::Camera camera;

  camera.calculateRotationMatrix(45.0f, 30.0f, 60.0f);

  EXPECT_NEAR(camera.getRotataionMatrix()[0], 0.1269f, 0.001f);
  EXPECT_NEAR(camera.getRotataionMatrix()[5], 0.3536f, 0.001f);
}

TEST(CameraTest, FrustumProjectionMatrix) {
  s21::Camera camera;

  camera.s21Frustum(1.0f, 45.0f, 0.1f, 100.0f);

  EXPECT_NEAR(camera.getProjectionMatrix()[0], 2.41421f, 0.001f);
  EXPECT_NEAR(camera.getProjectionMatrix()[5], 2.41421f, 0.001f);
  EXPECT_NEAR(camera.getProjectionMatrix()[10], -1.002002f, 0.001f);
  EXPECT_NEAR(camera.getProjectionMatrix()[14], -0.2002002f, 0.001f);
}

TEST(CameraTest, OrthoProjectionMatrix) {
  s21::Camera camera;

  camera.s21Ortho(1.0f, 45.0f, 0.1f, 100.0f);

  EXPECT_NEAR(camera.getProjectionMatrix()[0], 24.142f, 0.001f);
  EXPECT_NEAR(camera.getProjectionMatrix()[5], 24.142f, 0.001f);
  EXPECT_NEAR(camera.getProjectionMatrix()[10], -0.02020202f, 0.001f);
}

TEST(CameraTest, ViewMatrixCalculation) {
  s21::Camera camera;

  camera.calculateViewMatrix();

  EXPECT_FLOAT_EQ(camera.getViewMatrix()[10], -1.0f);
  EXPECT_FLOAT_EQ(camera.getViewMatrix()[15], 1.0f);
}

TEST(CameraTest, MultModelRotation) {
  CreateTestObjFile();
  s21::Controller shape("test.obj");
  s21::Camera camera;
  camera.calculateModelMatrix(&shape);
  camera.calculateViewMatrix();
  camera.calculateRotationMatrix(45.0f, 30.0f, 60.0f);
  camera.multModelRotation();

  float expected[16] = {0.0760,  -0.556, -0.2121, 0,       0.3674, 0.2121,
                        -0.4242, 0,      0.3562,  -0.0943, 0.2613, -0.6,
                        0,       0,      0,       1};
  for (auto i = 0; i < 16; i++) {
    EXPECT_NEAR(expected[i], camera.getMvpMatrix()[i], 0.01);
  }
  DeleteTestObjFile();
}

TEST(CameraTest, MultMvpView) {
  CreateTestObjFile();
  s21::Controller shape("test.obj");
  s21::Camera camera;
  camera.calculateModelMatrix(&shape);
  camera.calculateViewMatrix();
  camera.calculateRotationMatrix(45.0f, 30.0f, 60.0f);
  camera.multModelRotation();
  camera.multMvpView();

  float expected[16] = {-0.0538079, -0.393198,  0.212132,  0.212132,
                        -0.259808,  0.15,       0.424264,  0.424264,
                        -0.251904,  -0.0666952, -0.261357, -0.861357,
                        0,          0,          0,         1};
  for (auto i = 0; i < 16; i++) {
    EXPECT_NEAR(expected[i], camera.getMvpMatrix()[i], 0.01);
  }
  DeleteTestObjFile();
}

TEST(CameraTest, MultMvpProjection) {
  CreateTestObjFile();
  s21::Controller shape("test.obj");
  s21::Camera camera;
  camera.calculateModelMatrix(&shape);
  camera.calculateViewMatrix();
  camera.calculateRotationMatrix(45.0f, 30.0f, 60.0f);
  camera.multModelRotation();
  camera.s21Frustum(1.0f, 45.0f, 0.1f, 100.0f);
  camera.multMvpProjection();

  float expected[16] = {0.183712, -1.34246,  0.212557,  -0.212557,
                        0.887039, 0.512132,  0.425113,  -0.425113,
                        0.860054, -0.227712, -0.141761, -0.458239,
                        0,        0,         -0.2002,   1.2002};
  for (auto i = 0; i < 16; i++) {
    EXPECT_NEAR(expected[i], camera.getMvpMatrix()[i], 0.01);
  }
  DeleteTestObjFile();
}