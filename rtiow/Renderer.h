#pragma once
#include "IETThread.h"
#include "RTImage.h"
#include "material.h"

struct cam_data
{
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    vec3   u, v, w;        // Camera frame basis vectors
    vec3   defocus_disk_u;       // Defocus disk horizontal radius
    vec3   defocus_disk_v;       // Defocus disk vertical radius
    double defocus_angle;  // Variation angle of rays through each pixel

    int rowMin, numRows;
    int image_width, samples_per_pixel, max_depth;
	double pixel_samples_scale;
};

class IExecutionEvent;

class Renderer : public IETThread

{
public:
	Renderer(cam_data data, IExecutionEvent* event, const hittable& world, RTImage* imagePNG);
	~Renderer();

    bool isRunning() { return this->running; }

private:
	void run() override;

    cam_data data;

    RTImage* imagePNG;
    IExecutionEvent* execEvent;
    const hittable& world;

private:
    ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the defocus disk and directed at a randomly
        // sampled point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = data.pixel00_loc
            + ((i + offset.x()) * data.pixel_delta_u)
            + ((j + offset.y()) * data.pixel_delta_v);

        auto ray_origin = (data.defocus_angle <= 0) ? data.center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return data.center + (p[0] * data.defocus_disk_u) + (p[1] * data.defocus_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0, 0, 0);

        hit_record rec;

        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1, world);
            return color(0, 0, 0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};