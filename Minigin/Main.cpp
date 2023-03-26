#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "RotatorComponent.h"
#include "TrashTheCache_GameObjComponent.h"
#include "TrashTheCache_IntegerComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//auto& scene2 = dae::SceneManager::GetInstance().CreateScene("AnotherTest");

	// background
	auto bg = std::make_shared<dae::GameObject>();
	auto renderComp = bg->AddComponent<dae::RenderComponent>();
	auto transComp = bg->AddComponent<dae::TransformComponent>();
	auto textureComp = bg->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("background.tga");
	textureComp->AddToRenderer(renderComp);

	scene.Add(bg);


	// logo
	auto lg = std::make_shared<dae::GameObject>();
	renderComp = lg->AddComponent<dae::RenderComponent>();
	transComp = lg->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(216.f, 180.f);
	textureComp = lg->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("logo.tga");
	textureComp->AddToRenderer(renderComp);

	renderComp->AddToDisplayGui(textureComp);
	renderComp->AddToDisplayGui(transComp);

	scene.Add(lg);



	// prog4 text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto txt = std::make_shared<dae::GameObject>();
	renderComp = txt->AddComponent<dae::RenderComponent>();
	transComp = txt->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(80, 20);
	auto textComponent = txt->AddComponent<dae::TextComponent>();
	textComponent->SetFont(font);
	textComponent->SetText("Programming 4 Assignment");
	textComponent->AddToRenderer(renderComp);
	scene.Add(txt);

	// fps
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fps = std::make_shared<dae::GameObject>();
	renderComp = fps->AddComponent<dae::RenderComponent>();
	transComp = fps->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0, 0);
	textComponent = fps->AddComponent<dae::TextComponent>();
	textComponent->SetFont(font);
	textComponent->SetText("FPS");
	textComponent->SetColor({ 150, 150, 0 });
	textComponent->AddToRenderer(renderComp);
	auto test = fps->GetComponent<dae::RenderComponent>();
	auto FPSComponent = fps->AddComponent<dae::FPSComponent>();
	scene.Add(fps);


	// bubby
	auto bubby = std::make_shared<dae::GameObject>();
	renderComp = bubby->AddComponent<dae::RenderComponent>();
	transComp = bubby->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(220.0f, 240.0f);
	textureComp = bubby->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("Bubby.png");
	textureComp->AddToRenderer(renderComp);
	scene.Add(bubby);

	// bobby
	auto bobby = std::make_shared<dae::GameObject>();
	renderComp = bobby->AddComponent<dae::RenderComponent>();
	auto newTransComp = bobby->AddComponent<dae::TransformComponent>();
	newTransComp->SetLocalPosition(320.0f, 240.0f);
	textureComp = bobby->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("Bobby.png");
	textureComp->AddToRenderer(renderComp);
	scene.Add(bobby);

	
	const float baseSpeed{ 200.0f };
	std::vector<unsigned int> character1Input{
		SDLK_a,
		SDLK_d,
		SDLK_w,
		SDLK_s,
	};
	auto character1MoveCommand{ std::make_unique<dae::MoveCommand>(bubby, baseSpeed) };
	dae::InputManager::GetInstance().BindCommand(character1Input, dae::InputManager::InputType::Digital2DAxis, std::move(character1MoveCommand));
	
	std::vector<unsigned int> character2Input{
		dae::Controller::ControllerButton::DPadLeft,
		dae::Controller::ControllerButton::DPadRight,
		dae::Controller::ControllerButton::DPadUp,
		dae::Controller::ControllerButton::DPadDown
	};
	
	auto character2MoveCommand{ std::make_unique<dae::MoveCommand>(bobby, baseSpeed * 2.0f) };
	dae::InputManager::GetInstance().BindCommand(character2Input, dae::InputManager::InputType::Digital2DAxis, std::move(character2MoveCommand), 0);

	/*std::vector<unsigned int> character2Input{
		dae::Controller::ControllerButton::LeftThumb
	};*/

	

	//lg->SetParent(txt);
	//lg->SetParent(nullptr); // how do I tell the scene to add go?
	//fps->SetParent(lg);

	//bubby->SetParent(bobby);
	//bobby->SetParent(bubby);




}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}