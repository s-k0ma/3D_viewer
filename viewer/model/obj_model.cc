#include "obj_model.h"
namespace s21 {
Model::Model()
    : minX_{},
      maxX_{},
      minY_{},
      maxY_{},
      minZ_{},
      maxZ_{},
      centerX_{},
      centerY_{},
      centerZ_{},
      filename_{},
      vertexes_{},
      edges_{},
      vertexCount_{},
      facetsCount_{} {}

Model::Model(std::string filename)
    : minX_{},
      maxX_{},
      minY_{},
      maxY_{},
      minZ_{},
      maxZ_{},
      centerX_{},
      centerY_{},
      centerZ_{},
      filename_{std::move(filename)},
      vertexes_{},
      edges_{},
      vertexCount_{},
      facetsCount_{} {
  parseFile();
}

Model::~Model() = default;

bool Model::checkFilename() {
  const std::string extension = ".obj";

  return filename_.size() >= extension.size() &&
         filename_.compare(filename_.size() - extension.size(),
                           extension.size(), extension) == 0;
}

int Model::fillInfo() {
  int result{};

  std::fstream file(filename_);
  if (file.is_open()) {
    std::string line{};
    int vCounter{};
    facetsCount_ = 0;
    while (std::getline(file, line)) {
      if (line[0] == 'v' && line[1] == ' ') {
        Model::extractVertexes(line, vCounter);
        vCounter += 3;
      }
      if (line[0] == 'f' && line[1] == ' ') {
        Model::extractFacets(line);
      }
    }
    file.close();
  } else {
    result = 1;
  }
  return result;
}

int Model::extractVertexes(const std::string &line, int step) {
  std::stringstream ss(line.substr(2));
  std::string tmp;
  int code = 0;

  while (ss >> tmp) {
    float value = std::stof(tmp);
    switch (code) {
      case 0:
        vertexes_[step] = value;
        updateMinMax(value, minX_, maxX_);
        break;
      case 1:
        vertexes_[step + 1] = value;
        updateMinMax(value, minY_, maxY_);
        break;
      case 2:
        vertexes_[step + 2] = value;
        updateMinMax(value, minZ_, maxZ_);
        break;
    }
    code++;
  }
  return (code == 3) ? 0 : 1;
}

int Model::extractFacets(const std::string &line) {
  int result{};
  std::vector<int> tmpDigits{};
  int tmpCount{};

  for (size_t i = 0; i < line.size(); i++) {
    if (std::isdigit(line[i]) && line[i - 1] == ' ') {
      std::string digit{};
      while (line[i] != '/') {
        digit.push_back(line[i]);
        if (i + 1 == line.size())
          break;
        else
          i++;
      }
      tmpDigits.push_back(std::stoi(digit));
      tmpCount++;
    }
  }
  this->edges_.resize(facetsCount_ + tmpCount);
  for (int i = 0; i < tmpCount; i++) {
    this->edges_[i + facetsCount_] = tmpDigits[i] - 1;
  }
  facetsCount_ += tmpCount;

  return result;
}

int Model::checkObjectFile() {
  int result = 0;
  if (Model::checkFilename()) {
    std::ifstream file(filename_);

    if (file.is_open()) {
      std::string line{};
      while (std::getline(file, line)) {
        vertexCount_ += (line[0] == 'v' && line[1] == ' ');
        facetsCount_ += (line[0] == 'f' && line[1] == ' ');
      }
      file.close();
    } else {
      std::cerr << "Error opening file:" << filename_ << '\n';
      result = 1;
    }
  } else
    result = 1;

  return result;
}
const std::vector<float> &Model::getVertexes() { return vertexes_; }
const std::vector<int> &Model::getEdges() { return edges_; }
unsigned int Model::getVertexCount() const { return vertexCount_; }
unsigned int Model::getFacetsCount() const { return facetsCount_; }
void Model::parseFile() {
  if (Model::checkObjectFile() == 0) {
    vertexes_.resize(vertexCount_ * 3);
    edges_.resize(facetsCount_ * 3);
    if (Model::fillInfo() == 0) {
      centerX_ = (maxX_ + minX_) / 2.0f;
      centerY_ = (maxY_ + minY_) / 2.0f;
      centerZ_ = (maxZ_ + minZ_) / 2.0f;
    } else
      throw std::invalid_argument("Error in file parse");
  } else
    throw std::invalid_argument("Error in file parse");
}
void Model::updateMinMax(float value, float &min, float &max) {
  min = std::min(min, value);
  max = std::max(max, value);
}

float Model::getMinX() const { return minX_; }
float Model::getMaxX() const { return maxX_; }
float Model::getMinY() const { return minY_; }
float Model::getMaxY() const { return maxY_; }
float Model::getMinZ() const { return minZ_; }
float Model::getMaxZ() const { return maxZ_; }
}  // namespace s21