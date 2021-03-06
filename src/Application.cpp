
#include "Application.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Graphics.hpp"
#include "SDLException.hpp"

Window *Application::window = NULL;
bool Application::quitRequested = false;
State *Application::state = NULL;

void Application::init(std::string title) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) throw SDLException("Could not initialize application!");
	window = new Window(title);
	Time::init();
	Input::init();
	Graphics::init();
}

void Application::close() {
	delete window;
	SDL_Quit();
}

void Application::quit() {
	quitRequested = true;
}

void Application::run() {
	while (!quitRequested) {
		Time::update();
		Input::update();
		if (state) {
			state->update(Time::getDelta());
			Graphics::clear();
			state->render();
			window->swapBuffers();
		}
	}
}

void Application::setState(State *state) {
	if (Application::state) Application::state->onexit();
	if (state) state->onenter();
	Application::state = state;
}

