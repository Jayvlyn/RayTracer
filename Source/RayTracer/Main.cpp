#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <vector>

int main(int, char**)
{
	static int width = 800;
	static int height = 600;

	//std::cout << "Hello world\n";
	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", width, height);
	Canvas canvas(width, height, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene(10);
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = ((int)random(0,2) == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-2,2), random(-2,2), random(-3,0) }, random(0.1, 0.5), material);
		scene.AddObject(std::move(sphere));
	}

	// render scene 
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, 10);
	canvas.Update();

	bool quit = false;
	while (!quit)
	{
		renderer.PresentCanvas(canvas);

		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}