#ifndef __INTEGRATOR_H_
#define __INTEGRATOR_H_

#include "neon/blueprint.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <random>



namespace ne {
    /*
    constexpr int FLOAT_MIN = -1;
    constexpr int FLOAT_MAX = 1;
    float random_float() {

        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<> distr(FLOAT_MIN, FLOAT_MAX);
        return distr(eng);
    }
    */

    inline float random_float() {
        // Returns a random real in [0,1).
        return rand() / (RAND_MAX + 1.0);
    }

    inline float random_float(double min, double max) {
        // Returns a random real in [min,max).
        return min + (max - min) * random_float();
    }

namespace core {

class Integrator {
public:
  // integration part of rendering equation
  virtual glm::vec3 integrate(const ne::Ray &ray,
                              std::shared_ptr<ne::Scene> scene, int depth);
};

} // namespace core

} // namespace ne

#endif // __INTEGRATOR_H_
