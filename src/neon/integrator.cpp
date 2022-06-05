#include "integrator.hpp"
#include "neon/intersection.hpp"
#include "neon/material.hpp"
#include "neon/scene.hpp"


namespace ne {

    glm::vec3 unit_random_sphere() {
        while (true) {
            auto p = glm::vec3(random_float(-1,1));
            if (pow(glm::length(p), 2) >= 1)
                continue;
            else
                return p;
        }
    }

    namespace core {

        glm::vec3 Integrator::integrate(const ne::Ray &ray, std::shared_ptr<ne::Scene> scene, int depth) {
            glm::vec3 L{0.0f};
            ne::Ray r{ray};
            ne::Intersection hit;
            glm::vec3 light_dir{(0.0f,-1.0f,0.0f)};

            if (depth <= 0)
                 return glm::vec3(0.0f, 0.0f, 0.f);

            // if ray hit object in scene, apply shading
            if (scene->rayIntersect(r, hit)) {
                MaterialPointer material = hit.material;
                glm::vec3 target = hit.n + hit.p + unit_random_sphere();
                ne::Ray r2{ ray };
                r2.o = hit.p;
                r2.dir = target - hit.p;
                L += 0.5f * (integrate(r2, scene, depth-1));



                const glm::vec3 albedo = material->attenuation();
                //const glm::vec3 albedo = glm::vec3(0.18f);
                // L += scene->sampleDirectLight(r,hit);

                //diffuse
                //material->scatter(r,hit,r2);
                //L+=0.2f*glm::vec3{0.8f, 0.3f, 0.3f}+0.7f * 1 * std::max(0.f,abs(dot(hit.n,light_dir)));
                L += material->emitted() + albedo * scene->sampleBackgroundLight(r.dir);

            }

            // background color
            else
                L = scene->sampleBackgroundLight(r.dir);
          
            return L;
        }

    } // namespace core
} // namespace ne
