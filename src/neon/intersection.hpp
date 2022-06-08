#ifndef __INTERSECTION_H_
#define __INTERSECTION_H_

#include "neon/blueprint.hpp"
#include "neon/ray.hpp"
#include <glm/glm.hpp>


namespace ne {

	// Intersection(or HitRecord or Per ray data) class record information around
	// the hit point. you can easily extend intersection class by using polymorphism
	struct Intersection {
	  glm::vec3 p;                  // position at hit point
	  glm::vec3 n;                  // normal at hit point
	  ne::MaterialPointer material; // pointer to material at hit point
	  bool front_face;

	  inline void set_face_normal(const ne::Ray& r, const glm::vec3& outward_normal) {
		  front_face = glm::dot(r.dir, outward_normal) < 0;
		  n = front_face ? outward_normal : -outward_normal;
	  }
	};

} // namespace ne

#endif // __INTERSECTION_H_
