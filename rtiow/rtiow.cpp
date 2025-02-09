// rtiow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

void renderImage1()
{
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    int counter = 0;
    for (int a = -6; a < 6; a++) {
        for (int b = -6; b < 6; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                counter++;
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.33);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.3, 1, 0.56));
    world.add(make_shared<sphere>(point3(-3, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(3, 1, 0), 1.0, material3));

    auto material4 = make_shared<metal>(color(1, 0.7, 0.75), 0);
    world.add(make_shared<sphere>(point3(-6, 1, 0), 1.0, material4));

    camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 1080;
    cam.samples_per_pixel = 500;
    cam.max_depth = 50;

    cam.vfov = 30;
    cam.lookfrom = point3(-15, 2, -15);
    cam.lookat = point3(-2, 1, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 15.0;

    cam.render(world, 1);

    std::cout << "Rendered " << counter << " small spheres and " << 4 << " big spheres.\n" << std::endl;
}

void renderImage2()
{
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    int counter = 0;
    for (int a = -6; a < 6; a++) {
        for (int b = -6; b < 6; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                counter++;
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.33);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.3, 1, 0.56));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    auto material4 = make_shared<metal>(color(1, 0.7, 0.75), 0);
    world.add(make_shared<sphere>(point3(-8, 1, 0), 1.0, material4));

    camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 1080;
    cam.samples_per_pixel = 500;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 3.5;
    cam.focus_dist = 9.0;

    cam.render(world, 2);

    std::cout << "Rendered " << counter << " small spheres and " << 4 << " big spheres.\n" << std::endl;
}

void renderImage3()
{
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    double count = random_double(5, 11);
    float radius = 0.2f;
    for (int a = 0; a < count; a++) {
        auto choose_mat = random_double();
        point3 center(0, radius * 2 * (a + 1), 0);

        shared_ptr<material> sphere_material;
        if (choose_mat < 0.8) {
            // diffuse
            auto albedo = color::random() * color::random();
            sphere_material = make_shared<lambertian>(albedo);
            world.add(make_shared<sphere>(center, radius, sphere_material));
        }
        else if (choose_mat < 0.95) {
            // metal
            auto albedo = color::random(0.5, 1);
            auto fuzz = random_double(0, 0.5);
            sphere_material = make_shared<metal>(albedo, fuzz);
            world.add(make_shared<sphere>(center, radius, sphere_material));
        }
        else {
            // glass
            sphere_material = make_shared<dielectric>(1.5);
            world.add(make_shared<sphere>(center, radius, sphere_material));
        }
    }

    camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 1080;
    cam.samples_per_pixel = 500;
    cam.max_depth = 50;

    cam.vfov = 30;
    cam.lookfrom = point3(13, 3, 3);
    cam.lookat = point3(0, 2.8, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.1;
    cam.focus_dist = 10.0;

    cam.render(world, 3);

    std::cout << "Rendered " << count << " small spheres.\n" << std::endl;
}

int main() {
	renderImage1();
	//renderImage2();
	//renderImage3();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file