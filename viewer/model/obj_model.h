#ifndef BACKEND_TYPES_H
#define BACKEND_TYPES_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace s21 {
/**
 * @brief Класс для работы с 3D моделью.
 */
class Model {
 public:
  // Constructors & Destructor
  /**
   * @brief Конструктор по умолчанию.
   */
  Model();

  /**
   * @brief Конструктор, загружающий модель из файла.
   *
   * @param filename Путь к файлу, содержащему модель.
   */
  explicit Model(std::string filename);

  /**
   * @brief Деструктор класса Model.
   */
  ~Model();

  // Getters
  /**
   * @brief Получает вектор вершин модели.
   *
   * @return const std::vector<float>& Ссылка на вектор вершин.
   */
  [[nodiscard]] const std::vector<float> &getVertexes();

  /**
   * @brief Получает вектор рёбер модели.
   *
   * @return const std::vector<int>& Ссылка на вектор рёбер.
   */
  [[nodiscard]] const std::vector<int> &getEdges();

  /**
   * @brief Получает количество вершин модели.
   *
   * @return unsigned int Количество вершин.
   */
  [[nodiscard]] unsigned int getVertexCount() const;

  /**
   * @brief Получает количество граней модели.
   *
   * @return unsigned int Количество граней.
   */
  [[nodiscard]] unsigned int getFacetsCount() const;

  /**
   * @brief Получает минимальное значение по оси X.
   *
   * @return float Минимальное значение по оси X.
   */
  [[nodiscard]] float getMinX() const;

  /**
   * @brief Получает максимальное значение по оси X.
   *
   * @return float Максимальное значение по оси X.
   */
  [[nodiscard]] float getMaxX() const;

  /**
   * @brief Получает минимальное значение по оси Y.
   *
   * @return float Минимальное значение по оси Y.
   */
  [[nodiscard]] float getMinY() const;

  /**
   * @brief Получает максимальное значение по оси Y.
   *
   * @return float Максимальное значение по оси Y.
   */
  [[nodiscard]] float getMaxY() const;

  /**
   * @brief Получает минимальное значение по оси Z.
   *
   * @return float Минимальное значение по оси Z.
   */
  [[nodiscard]] float getMinZ() const;

  /**
   * @brief Получает максимальное значение по оси Z.
   *
   * @return float Максимальное значение по оси Z.
   */
  [[nodiscard]] float getMaxZ() const;

 private:
  /**
   * @brief Парсинг файла.
   */
  void parseFile();

  /**
   * @brief Заполняет информацию о модели.
   *
   * @return int Статус выполнения операции.
   */
  int fillInfo();

  /**
   * @brief Извлекает грани из строки.
   *
   * @param line Строка, содержащая информацию о грани.
   * @return int Статус выполнения операции.
   */
  int extractFacets(const std::string &line);

  /**
   * @brief Извлекает вершины из строки.
   *
   * @param line Строка, содержащая информацию о вершине.
   * @param step Шаг для обработки.
   * @return int Статус выполнения операции.
   */
  int extractVertexes(const std::string &line, int step);

  /**
   * @brief Проверяет файл объекта на корректность.
   *
   * @return int Статус выполнения операции.
   */
  int checkObjectFile();

  /**
   * @brief Проверяет имя файла на корректность.
   *
   * @return bool true, если имя корректно; в противном случае false.
   */
  bool checkFilename();

  /**
   * @brief Обновляет минимальные и максимальные значения.
   *
   * @param value Значение для обновления.
   * @param min Ссылка на минимальное значение.
   * @param max Ссылка на максимальное значение.
   */
  void updateMinMax(float value, float &min, float &max);

  float minX_, maxX_;  ///< Минимальное и максимальное значения по оси X.
  float minY_, maxY_;  ///< Минимальное и максимальное значения по оси Y.
  float minZ_, maxZ_;  ///< Минимальное и максимальное значения по оси Z.
  float centerX_, centerY_, centerZ_;  ///< Центр модели.

  std::string filename_;         ///< Имя файла модели.
  std::vector<float> vertexes_;  ///< Вектор вершин.
  std::vector<int> edges_;       ///< Вектор рёбер.
  unsigned int vertexCount_;     ///< Количество вершин.
  unsigned int facetsCount_;     ///< Количество граней.
};
}  // namespace s21

#endif  // BACKEND_TYPES_H
