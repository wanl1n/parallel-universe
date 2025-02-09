#include "Renderer.h"

#include "IExecutionEvent.h"
#include "hittable.h"

Renderer::Renderer(cam_data data, IExecutionEvent* event, const hittable& world, RTImage* imagePNG)
	: world(world) {
	this->data = data;
	this->imagePNG = imagePNG;
	this->execEvent = event;
}

Renderer::~Renderer()
{
}

void Renderer::run()
{
    for (int j = data.rowMin; j < data.rowMin + data.numRows; j++)
    {
		for (int i = 0; i < data.image_width; i++) {
			color pixel_color(0, 0, 0);
			for (int sample = 0; sample < data.samples_per_pixel; sample++) {
				ray r = get_ray(i, j);
				pixel_color += ray_color(r, data.max_depth, world);
			}
			vec3 color = write_color(data.pixel_samples_scale * pixel_color);

			this->imagePNG->setPixel(i, j, int(color.x()), int(color.y()), int(color.z()));
		}
    }

    this->execEvent->onFinishedExecution();
    delete this;
}