#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"

int main(int, char**)
{
	static int width = 400;
	static int height = 300;

	std::cout << "Hello world\n";
	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", width, height);
	Canvas canvas(width, height, renderer);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		// with clear({0,0,0,1}) it turns blue, right now its acting like a r g b rather than r g b a
		canvas.Clear({ 0, 0, 0, 0 });
		for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random(0, width), random(0,height)}, {random(0, 1), random(0, 1), random(0, 1), 1});
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}