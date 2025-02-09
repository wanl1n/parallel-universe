#ifndef CAMERA_H
#define CAMERA_H

#include "IExecutionEvent.h"
#include "RTImage.h"
#include "Renderer.h"

class camera : public IExecutionEvent {

public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width = 100;  // Rendered image width in pixel count
    int    samples_per_pixel = 10;   // Count of random samples for each pixel
    int    max_depth = 10;   // Maximum number of ray bounces into scene

    double vfov = 90;  // Vertical view angle (field of view)
    point3 lookfrom = point3(0, 0, 0);   // Point camera is looking from
    point3 lookat = point3(0, 0, -1);  // Point camera is looking at
    vec3   vup = vec3(0, 1, 0);     // Camera-relative "up" direction

    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

    RTImage* imagePNG;
    int threadsStarted = 0;

    void render(const hittable& world, int num) {
        initialize();

        //std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        this->imagePNG = new RTImage(image_width, image_height);

        int rowsPerThread = 10;
        for (int j = 0; j < image_height; j+= rowsPerThread) {
            std::clog << "\rInitializing threads: " << (image_height - j) << ' ' << std::flush;
            
			// Create a thread.
            cam_data data = {
                image_height, center,
                pixel00_loc, pixel_delta_u, pixel_delta_v,
                u, v, w, defocus_disk_u, defocus_disk_v, defocus_angle,
                j, rowsPerThread,
            	image_width, samples_per_pixel, max_depth,
            	pixel_samples_scale
            };

            Renderer* renderRows = new Renderer(data, (IExecutionEvent*)this, world, this->imagePNG);
            renderRows->start();
            threadsStarted++;
        }

        while (threadsStarted != threadsCompleted)
        {
            std::clog << "\rRendering Image " << num << ". Rows left: " << threadsStarted - threadsCompleted << ' ' << std::flush;
        }

        cv::String filename = "D:/C++ Projects/GDPARCM/parallel universe/render/The Render " + std::to_string(num) + ".png";
        this->imagePNG->saveImage(filename);
        std::clog << "\rYour image has been saved as The Render " << num << ". Please enjoy!\n";
    }

    int threadsCompleted = 0;
    void onFinishedExecution() override { threadsCompleted++; }

private:
    int    image_height;   // Rendered image height
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    vec3   u, v, w;        // Camera frame basis vectors
    vec3   defocus_disk_u;       // Defocus disk horizontal radius
    vec3   defocus_disk_v;       // Defocus disk vertical radius

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = lookfrom;

        // Determine viewport dimensions.
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }
};

#endif