#include "neon/material.hpp"
#include "neon/integrator.hpp"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>
#include <random>
#include <numeric>

namespace ne {

    //light
    bool DiffuseLight::scatter(const ne::Ray &r_in, const ne::Intersection &hit,
                               ne::Ray &r_out) const {
      // Implement your code
      return false;
    }

    glm::vec3 DiffuseLight::emitted() const {
      // Implement your code
      return glm::vec3(1.0f);
    }

    glm::vec3 DiffuseLight::attenuation() const {
      // implement your code
      return glm::vec3(0.0f);
    }

    //specular, mirror
    bool Dielectric::scatter(const ne::Ray &r_in, const ne::Intersection &hit,
                             ne::Ray &r_out) const {
      // Implement your code

        float x=2*(glm::dot(hit.n,r_in.dir));
        r_out.dir=r_in.dir-x*hit.n ;

      return false;
    }

    glm::vec3 Dielectric::attenuation() const {
      // implement your code
        glm::vec3 albedo = color_;

        return albedo;
    }

    // diffuse
    bool Lambertian::scatter(const ne::Ray &r_in, const ne::Intersection &hit,
                             ne::Ray &r_out) const {
      // Implement your code        

        /*
        auto scatter_direction = hit.n +  unit_random_vector();
        //if ((scatter_direction[0] < 1e-8)&& (scatter_direction[1] < 1e-8)&& (scatter_direction[2] < 1e-8))
        //    scatter_direction = hit.n;
        ne::Ray scattered(hit.p, scatter_direction);
        r_out = scattered;
        return true;
        */

        glm::vec3 target = hit.n + hit.p + random_in_unit_sphere();
        r_out.o = hit.p;
        r_out.dir = target - hit.p;
        return true;
    }

    glm::vec3 Lambertian::attenuation() const {
      // implement your code
        glm::vec3 albedo = color_;

      return albedo;
    }


    bool Metal::scatter(const ne::Ray &r_in, const ne::Intersection &hit,
                        ne::Ray &r_out) const {
        glm::vec3 v = glm::normalize(r_in.dir);
        glm::vec3 n = hit.n;
        glm::vec3 reflected = v - 2 * glm::dot(v, n) * n;
        ne::Ray scattered(hit.p, reflected + 0.5f*random_in_unit_sphere());
        r_out = scattered;
        return (glm::dot(r_out.dir, hit.n) > 0);
    }

    glm::vec3 Metal::attenuation() const {
      // implement your code
        glm::vec3 albedo = color_;

        return albedo;
    }

} // namespace ne
