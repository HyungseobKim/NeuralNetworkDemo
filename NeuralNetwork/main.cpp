#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "ImGuiClient.h"
#include "NeuralNetwork.h"

int main(int /*argc*/, char* /*argv*/[])
{
	// SDL: Initialize and create a window
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL error: " << SDL_GetError();
		return -1;
	}

	const char* title = "Neural Network Demo";
	const int width = 1300, height = 800;
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_Window* window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		window_flags
	);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// GLEW: get function bindings (if possible)
	glewInit();
	if (!GLEW_VERSION_2_0)
	{
		std::cout << "OpenGL version is not 3.0 or better" << std::endl;
		return -1;
	}

	// ImGui: setup
	ImGuiClient imguiClient;
	imguiClient.Init(window, context, "#version 400");

	constexpr int dataSize = 21;
	NeuralNetwork NN(dataSize);
	NN.Initialize();

	double x_data[dataSize];
	double y_data[dataSize];
	NN.GetData(x_data, y_data);

	// Loop
	try
	{
		// Client variables
		bool done = false;
		bool start = false;
		
		// Neural Network variables
		double output[dataSize];
		int iteration = NN.GetResult(output);

		while (!done)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				imguiClient.ProcessEvent(&event);

				if (event.type == SDL_QUIT ||
					(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)))
					done = true;
			}

			if (imguiClient.Draw(window, start, x_data, y_data, output, dataSize, iteration))
				NN.Initialize();

			// Draw
			glClearColor(1.f, 1.f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			imguiClient.RenderDrawData();
			SDL_GL_SwapWindow(window);

			if (start) // Compute for next frame
				iteration = NN.GetResult(output);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	// SDL: Cleanup
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}