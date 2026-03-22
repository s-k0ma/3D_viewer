#ifndef CAMERA_CONTROLLER_H_
#define CAMERA_CONTROLLER_H_
#include "../model/camera_model.h"
#include "../model/obj_model.h"
#include "obj_controller.h"

namespace s21 {
/**
 * @class CameraController
 * @brief Контроллер камеры для управления положением, масштабом и матрицами
 * модели, вида и проекции.
 */
class CameraController {
 public:
  /**
   * @brief Возвращает единственный экземпляр класса CameraController
   * (синглтон).
   * @return Ссылка на экземпляр класса CameraController.
   */
  static CameraController &getInstance();

  // Удаляем копирующий конструктор и оператор присваивания, чтобы запретить
  // копирование.
  CameraController(const CameraController &) = delete;
  CameraController &operator=(const CameraController &) = delete;

  /**
   * @brief Получает модель камеры.
   * @return Модель камеры (объект класса Camera).
   */
  s21::Camera getModel();

  /**
   * @brief Получает матрицу модели.
   * @return Указатель на матрицу модели (float*).
   */
  float *getModelMatrix();

  /**
   * @brief Получает матрицу вида.
   * @return Указатель на матрицу вида (float*).
   */
  float *getViewMatrix();

  /**
   * @brief Получает матрицу проекции.
   * @return Указатель на матрицу проекции (float*).
   */
  float *getProjectionMatrix();

  /**
   * @brief Получает матрицу модели-вида-проекции (MVP).
   * @return Указатель на матрицу MVP (float*).
   */
  float *getMvpMatrix();

  /**
   * @brief Получает матрицу вращения.
   * @return Указатель на матрицу вращения (float*).
   */
  float *getRotataionMatrix();

  /**
   * @brief Вычисляет матрицу модели на основе объекта Controller.
   * @param shape Указатель на объект Controller, представляющий модель.
   */
  void calculateModelMatrix(s21::Controller *shape);

  /**
   * @brief Устанавливает положение модели.
   * @param x Координата X.
   * @param y Координата Y.
   * @param z Координата Z.
   */
  void setModelPosition(float x, float y, float z);

  /**
   * @brief Устанавливает масштаб модели.
   * @param scale Значение масштаба.
   */
  void setModelScale(float scale);

  /**
   * @brief Вычисляет матрицу вращения по углам.
   * @param xAngle Угол вращения по оси X.
   * @param yAngle Угол вращения по оси Y.
   * @param zAngle Угол вращения по оси Z.
   */
  void calculateRotationMatrix(float xAngle, float yAngle, float zAngle);

  /**
   * @brief Создает матрицу перспективной проекции с использованием frustum.
   * @param aspect Соотношение сторон экрана.
   * @param fov Угол обзора (поле зрения).
   * @param near Ближняя плоскость отсечения.
   * @param far Дальняя плоскость отсечения.
   */
  void s21Frustum(float aspect, float fov, float near, float far);

  /**
   * @brief Создает матрицу ортографической проекции.
   * @param aspect Соотношение сторон экрана.
   * @param fov Угол обзора (поле зрения).
   * @param near Ближняя плоскость отсечения.
   * @param far Дальняя плоскость отсечения.
   */
  void s21Ortho(float aspect, float fov, float near, float far);

  /**
   * @brief Вычисляет матрицу вида.
   */
  void calculateViewMatrix();

  /**
   * @brief Применяет матрицу вращения к модели.
   */
  void multModelRotation();

  /**
   * @brief Применяет матрицу вида к модели-виду-проекции (MVP).
   */
  void multMvpView();

  /**
   * @brief Применяет матрицу проекции к модели-виду-проекции (MVP).
   */
  void multMvpProjection();

  /**
   * @brief Вычисляет векторное произведение двух векторов.
   * @param a Первый вектор.
   * @param b Второй вектор.
   * @return Векторное произведение (Vec4).
   */
  static Vec4 cross(Vec4 a, Vec4 b);

  /**
   * @brief Нормализует вектор.
   * @param v Вектор для нормализации.
   * @return Нормализованный вектор (Vec4).
   */
  static Vec4 normalize(Vec4 v);

  /**
   * @brief Вычитает один вектор из другого.
   * @param a Вектор уменьшаемый.
   * @param b Вектор вычитаемый.
   * @return Результат вычитания (Vec4).
   */
  static Vec4 subtract(Vec4 a, Vec4 b);

 private:
  /**
   * @brief Приватный конструктор для предотвращения создания дополнительных
   * экземпляров.
   */
  CameraController();

  s21::Camera cameraModel;  ///< Экземпляр камеры.
};
}  // namespace s21

#endif  // CAMERA_CONTROLLER_H_