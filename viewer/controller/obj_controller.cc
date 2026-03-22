#include "obj_controller.h"

s21::Controller::Controller(std::string filename) {
  // std::shared_ptr<s21::Model> modelNewInstance =
  // std::make_shared<s21::Model>(filename);
  this->model = s21::Model(filename);
}

// s21::Model *s21::Controller::getModel()
// {
//   return &model;
// }

const std::vector<float> &s21::Controller::getVertexes() {
  return model.getVertexes();
}
const std::vector<int> &s21::Controller::getEdges() { return model.getEdges(); }
unsigned int s21::Controller::getVertexCount() const {
  return model.getVertexCount();
}
unsigned int s21::Controller::getFacetsCount() const {
  return model.getFacetsCount();
}
float s21::Controller::getMinX() const { return model.getMinX(); }
float s21::Controller::getMaxX() const { return model.getMaxX(); }
float s21::Controller::getMinY() const { return model.getMinY(); }
float s21::Controller::getMaxY() const { return model.getMaxY(); }
float s21::Controller::getMinZ() const { return model.getMinZ(); }
float s21::Controller::getMaxZ() const { return model.getMaxZ(); }