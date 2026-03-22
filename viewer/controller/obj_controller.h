#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "../model/obj_model.h"

namespace s21 {
/**
 * @class Controller
 * @brief Класс контроллера для работы с 3D-моделями, включая управление
 * вершинами и рёбрами модели.
 */
class Controller {
 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  Controller() = default;

  /**
   * @brief Конструктор, принимающий имя файла модели для загрузки.
   * @param filename Имя файла, содержащего модель.
   */
  Controller(std::string filename);

  /**
   * @brief Получает ссылку на вектор вершин модели.
   * @return Константная ссылка на вектор вершин (std::vector<float>).
   */
  [[nodiscard]] const std::vector<float> &getVertexes();

  /**
   * @brief Получает ссылку на вектор рёбер модели.
   * @return Константная ссылка на вектор рёбер (std::vector<int>).
   */
  [[nodiscard]] const std::vector<int> &getEdges();

  /**
   * @brief Получает количество вершин модели.
   * @return Количество вершин (unsigned int).
   */
  [[nodiscard]] unsigned int getVertexCount() const;

  /**
   * @brief Получает количество граней модели.
   * @return Количество граней (unsigned int).
   */
  [[nodiscard]] unsigned int getFacetsCount() const;

  /**
   * @brief Получает минимальное значение координаты X среди вершин модели.
   * @return Минимальное значение X (float).
   */
  [[nodiscard]] float getMinX() const;

  /**
   * @brief Получает максимальное значение координаты X среди вершин модели.
   * @return Максимальное значение X (float).
   */
  [[nodiscard]] float getMaxX() const;

  /**
   * @brief Получает минимальное значение координаты Y среди вершин модели.
   * @return Минимальное значение Y (float).
   */
  [[nodiscard]] float getMinY() const;

  /**
   * @brief Получает максимальное значение координаты Y среди вершин модели.
   * @return Максимальное значение Y (float).
   */
  [[nodiscard]] float getMaxY() const;

  /**
   * @brief Получает минимальное значение координаты Z среди вершин модели.
   * @return Минимальное значение Z (float).
   */
  [[nodiscard]] float getMinZ() const;

  /**
   * @brief Получает максимальное значение координаты Z среди вершин модели.
   * @return Максимальное значение Z (float).
   */
  [[nodiscard]] float getMaxZ() const;

 private:
  /**
   * @brief Модель, управляемая данным контроллером.
   */
  s21::Model model;
};
}  // namespace s21
#endif  // CONTROLLER_H_