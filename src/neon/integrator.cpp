#include "integrator.hpp"
#include "neon/intersection.hpp"
#include "neon/material.hpp"
#include "neon/scene.hpp"


namespace ne {


    namespace core {

        glm::vec3 Integrator::integrate(const ne::Ray &ray, std::shared_ptr<ne::Scene> scene, int depth) {
            glm::vec3 L{0.0f};
            ne::Ray r{ray};
            ne::Intersection hit;               

            if (depth <= 0)
                 return glm::vec3(0.0f);

            // if ray hit object in scene, apply shading
            if (scene->rayIntersect(r, hit)) {    
                MaterialPointer material =  hit.material;
                ne::Ray scattered(glm::vec3(0.0f),glm::vec3(0.0f));
                glm::vec3 albedo = material->attenuation();
                
                if (material->scatter(r, hit, scattered)) {
                    L+= albedo * integrate(scattered, scene, depth - 1); 
                    return L;
                }    
                // lighting
                //else 
                L += material->emitted();
                return L;
            }          

            // background color

            else {
                L = scene->sampleBackgroundLight(r.dir);
                return L;
            }          
            
        }
    } // namespace core
} // namespace ne
