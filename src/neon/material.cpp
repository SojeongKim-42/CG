#include "neon/material.hpp"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>
#include <random>

namespace ne {

bool DiffuseLight::scatter(const ne::Ray &r_in, const ne::Intersection &hit,
                           ne::Ray &r_out) const {
  // Implement your code
  return false;
}

glm::vec3 DiffuseLight::emitted() const {
  // Implement your code
  return glm::vec3(0.0f);
}

glm::vec3 DiffuseLight::attenuation() const {
  // implement your code
  return glm::vec3(0.0f);
}

bool Dielectric::scatter(const ne::Ray &r_in, const ne::Intersection &hit,
                         ne::Ray &r_out) const {
  // Implement your code
  return false;
}

glm::vec3 Dielectric::attenuation() const {
  // implement your code
  return glm::vec3(0.0f);
}

bool Lambertian::scatter(const ne::Ray &r_in, const ne::Intersection &hit,
                         ne::Ray &r_out) const {
  // Implement your code
  return false;
}

glm::vec3 Lambertian::attenuation() const {
  // implement your code
  return glm::vec3(0.0f);
}

bool Metal::scatter(const ne::Ray &r_in, const ne::Intersection &hit,
                    ne::Ray &r_out) const {
  // Implement your code
  return false;
}

glm::vec3 Metal::attenuation() const {
  // implement your code
  return glm::vec3(0.0f);
}

} // namespace ne
