//
// Created by rivatent on 10/8/24.
//

#ifndef VIEWER_FRONT_SRC_BACKEND_CAMERA_H_
#define VIEWER_FRONT_SRC_BACKEND_CAMERA_H_

#include "../controller/obj_controller.h"
#include "obj_model.h"

/**
 * @brief Структура для представления вектора в 4D пространстве.
 */
struct Vec4 {
  float x;  ///< Координата по оси X.
  float y;  ///< Координата по оси Y.
  float z;  ///< Координата по оси Z.
  float w;  ///< Четвёртая координата (обычно используется для однородных
            ///< координат).
};

/**
 * @brief Структура для представления матрицы 4x4.
 */
struct Mat4 {
  float m[16];  ///< Элементы матрицы.
};

namespace s21 {
/**
 * @brief Класс для представления камеры в 3D пространстве.
 */
class Camera {
 public:
  /**
   * @brief Конструктор камеры.
   *
   * Инициализирует матрицы модели, вида, проекции, MVP и вращения.
   */
  Camera() {
    modelMatrix_ = new float[16]{};
    viewMatrix_ = new float[16]{};
    projectionMatrix_ = new float[16]{};
    mvpMatrix_ = new float[16]{};
    rotationMatrix_ = new float[16]{};
  }

  /**
   * @brief Деструктор камеры.
   *
   * Освобождает память, занятую матрицами.
   */
  ~Camera() {
    delete[] modelMatrix_;
    delete[] viewMatrix_;
    delete[] projectionMatrix_;
    delete[] mvpMatrix_;
    delete[] rotationMatrix_;
  }
  /**
   * @brief Геттер матрицы модели.
   *
   * @return float* Указатель на матрицу модели.
   */
  float *getModelMatrix();

  /**
   * @brief Геттер матрицы вида.
   *
   * @return float* Указатель на матрицу вида.
   */
  float *getViewMatrix();

  /**
   * @brief Геттер матрицы проекции.
   *
   * @return float* Указатель на матрицу проекции.
   */
  float *getProjectionMatrix();

  /**
   * @brief Геттер MVP матрицы.
   *
   * @return float* Указатель на MVP матрицу.
   */
  float *getMvpMatrix();

  /**
   * @brief Геттер матрицы вращения.
   *
   * @return float* Указатель на матрицу вращения.
   */
  float *getRotataionMatrix();

  /**
   * @brief Вычисляет матрицу модели для заданной модели.
   *
   * @param shape Указатель на объект модели.
   */
  void calculateModelMatrix(Controller *shape);

  /**
   * @brief Устанавливает позицию модели.
   *
   * @param x Позиция по оси X.
   * @param y Позиция по оси Y.
   * @param z Позиция по оси Z.
   */
  void setModelPosition(float x, float y, float z);

  /**
   * @brief Устанавливает масштаб модели.
   *
   * @param scale Масштабирование модели.
   */
  void setModelScale(float scale);

  /**
   * @brief Вычисляет матрицу вращения на основе углов вращения.
   *
   * @param xAngle Угол вращения вокруг оси X.
   * @param yAngle Угол вращения вокруг оси Y.
   * @param zAngle Угол вращения вокруг оси Z.
   */
  void calculateRotationMatrix(float xAngle, float yAngle, float zAngle);

  /**
   * @brief Устанавливает параметры перспективной проекции.
   *
   * @param aspect Соотношение сторон.
   * @param fov Поле зрения.
   * @param near Ближняя плоскость отсечения.
   * @param far Дальняя плоскость отсечения.
   */
  void s21Frustum(float aspect, float fov, float near, float far);

  /**
   * @brief Устанавливает параметры ортографической проекции.
   *
   * @param aspect Соотношение сторон.
   * @param fov Поле зрения.
   * @param near Ближняя плоскость отсечения.
   * @param far Дальняя плоскость отсечения.
   */
  void s21Ortho(float aspect, float fov, float near, float far);

  /**
   * @brief Вычисляет матрицу вида.
   */
  void calculateViewMatrix();

  /**
   * @brief Умножает матрицу вращения модели.
   */
  void multModelRotation();

  /**
   * @brief Умножает MVP матрицу на матрицу вида.
   */
  void multMvpView();

  /**
   * @brief Умножает MVP матрицу на матрицу проекции.
   */
  void multMvpProjection();

  /**
   * @brief Вычисляет векторное произведение двух векторов.
   *
   * @param a Первый вектор.
   * @param b Второй вектор.
   * @return Vec4 Результат векторного произведения.
   */
  static Vec4 cross(Vec4 a, Vec4 b);

  /**
   * @brief Нормализует вектор.
   *
   * @param v Вектор для нормализации.
   * @return Vec4 Нормализованный вектор.
   */
  static Vec4 normalize(Vec4 v);

  /**
   * @brief Вычитает векторы.
   *
   * @param a Первый вектор.
   * @param b Второй вектор.
   * @return Vec4 Результат вычитания.
   */
  static Vec4 subtract(Vec4 a, Vec4 b);

 private:
  /**
   * @brief Умножает две матрицы.
   *
   * @param a Первая матрица.
   * @param b Вторая матрица.
   * @param result Результирующая матрица.
   */
  void multiply(float *a, float *b, float *result);

  float *modelMatrix_;       ///< Матрица модели.
  float *viewMatrix_;        ///< Матрица вида.
  float *projectionMatrix_;  ///< Матрица проекции.
  float *mvpMatrix_;         ///< MVP матрица.
  float *rotationMatrix_;    ///< Матрица вращения.
};

}  // namespace s21

#endif  // VIEWER_FRONT_SRC_BACKEND_CAMERA_H_
