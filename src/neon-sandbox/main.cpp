#include "test.hpp"

#include "neon/camera.hpp"
#include "neon/image.hpp"
#include "neon/integrator.hpp"
#include "neon/ray.hpp"
#include "neon/scene.hpp"
#include "neon/sphere.hpp"
#include "neon/utils.hpp"

#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <memory>
#include <taskflow/taskflow.hpp>

using namespace std;
using namespace glm;

int main(int argc, char *argv[]) {
  int nx = 512;
  int ny = 512;
  int spp = 128;

  // create output image
  ne::Image canvas(nx, ny);
  uvec2 tilesize(32, 32);

  // Split images into set of tiles.
  // Each thread render its corresponding tile.
  vector<ne::TileIterator> tiles = canvas.toTiles(tilesize);

  // create scene
  shared_ptr<ne::Scene> scene = testScene1();

  // spwan camera
  static ne::Camera camera;
  float distToFocus = 4;
  float aperture = 0.1f;
  vec3 lookfrom(0, 0, 3);
  vec3 lookat(0, 0, 0);
  camera = ne::Camera(lookfrom, lookat, vec3(0, 1, 0), 60,
                      float(canvas.width()) / float(canvas.height()), aperture,
                      distToFocus);

  // summon progress bar. this is just eye candy.
  // you can use timer class instead
  ne::utils::Progressbar progressbar(canvas.numPixels());

  // prep to build task graph
  tf::Taskflow tf;
  tf::Task taskRenderStart =
      tf.emplace([&progressbar]() { progressbar.start(); });
  tf::Task taskRenderEnd = tf.emplace([&progressbar]() { progressbar.end(); });

  // build rendering task graph
  for (auto &tile : tiles) {
    tf::Task taskTileRender = tf.emplace([&]() {
      // Iterate pixels in tile
      for (auto &index : tile) {
        vec3 color{0.0f};


        // construct multiple ray
        int sample_per_pixel = 64;
        ne::core::Integrator Li;
        for (int s = 0; s < sample_per_pixel; ++s) {
            float u = (float(index.x) + ne::random_float()) / float(canvas.width() - 1);
            float v = (float(index.y) + ne::random_float()) / float(canvas.height() - 1);
            ne:: Ray r = camera.sample(u, v);
            color += Li.integrate(r, scene, 50);
        }

        // record to canvas
        float scale = 1.0 / sample_per_pixel;
        color *= scale;
        color = clamp(color, 0.0f, 1.0f);   
        canvas(index) = u8vec4(color * 255.99f, 255.0f);


        

        // update progressbar and draw it every 10 progress
        if (++progressbar % 20 == 0)
          progressbar.display();
      }
    });

    taskRenderStart.precede(taskTileRender);
    taskTileRender.precede(taskRenderEnd);
  }

  // start rendering
  tf.wait_for_all();

  canvas.save("test.png");
  return 0;
}
