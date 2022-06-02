#include "neon/material.hpp"
#include "neon/scene.hpp"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace ne {

void Scene::add(ne::RendablePointer object) {
  objects_.push_back(object);
  if (glm::length(object->material_->emitted()) > 0.0f) {
    lights_.push_back(object);
  }
}

bool Scene::rayIntersect(ne::Ray &ray, ne::Intersection &inter) {
  bool foundIntersection = false;

  // Do not change order between a || b.
  // sometimes result(a || b) != result (b || a) and this is the case!
  // this is because b will not evaluated if a is true in this statment.
  // e.g. a = a || b (b will not be evaluated because a is true)
  for (const auto o : objects_) {
    foundIntersection = o->rayIntersect(ray, inter) || foundIntersection;
  }

  return foundIntersection;
}

glm::vec3 Scene::sampleBackgroundLight(const glm::vec3 &dir) const {
  glm::vec3 unit = glm::normalize(dir);
  float t = 0.5f * (unit.y + 1.0f);
  return ((1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5, 0.5, 0.9));
}

glm::vec3 Scene::sampleDirectLight(ne::Ray &ray, ne::Intersection &hit) const {
  // implement your code
  glm::vec3 result;
  return result;
}

} // namespace ne
