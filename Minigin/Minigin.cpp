#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include <chrono>
#include <thread>
#include "CollisionManager.h"
#include "PhysicsManager.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_MIXER_VERSION(&version)
		printf("We compiled against SDL_mixer version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

	version = *Mix_Linked_Version();
	printf("We are linking against SDL_mixer version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		868,
		700,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	auto& time = GameTime::GetInstance();
	auto& collisions = CollisionManager::GetInstance(); 
	auto& physics = PhysicsManager::GetInstance();

	bool doContinue = true;
	//constexpr float fixedTimeStepSec{ 0.02f }; // use this for a fixedUpdate
	constexpr float desiredFPS{ 60.0f };
	constexpr int frameTimeMS{ static_cast<int>(1000 / desiredFPS) };

	while (doContinue)
	{
		const auto& currentTime = time.GetTimeCurrent();
		time.Update(); // update to get DeltaTime

		doContinue = input.ProcessInput();
		sceneManager.Update();

		sceneManager.CheckForRemoval(); // this will remove any gameobjects marked for delete

		physics.Update();
		collisions.Update();

		renderer.Render();

		// sleeping to get desired fps
		const auto sleepTime = currentTime + std::chrono::milliseconds{ frameTimeMS } - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}
