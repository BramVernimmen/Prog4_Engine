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
//#include "RotatorComponent.h"
//#include "TrashTheCache_GameObjComponent.h"
//#include "TrashTheCache_IntegerComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "HealthComponent.h"
#include "DebugHealthComponent.h"
#include "DamageCommand.h"
#include "ScoreComponent.h"
#include "DebugScoreComponent.h"
#include "GiveScoreCommand.h"
#include "HowToPlayComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//auto& scene2 = dae::SceneManager::GetInstance().CreateScene("AnotherTest");

	// background
	auto bg = std::make_unique<dae::GameObject>();
	auto renderComp = bg->AddComponent<dae::RenderComponent>();
	auto transComp = bg->AddComponent<dae::TransformComponent>();
	auto textureComp = bg->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("background.tga");
	textureComp->AddToRenderer(renderComp);

	scene.Add(std::move(bg));


	//// logo
	//auto lg = std::make_unique<dae::GameObject>();
	//renderComp = lg->AddComponent<dae::RenderComponent>();
	//transComp = lg->AddComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(216.f, 180.f);
	//textureComp = lg->AddComponent<dae::TextureComponent>();
	//textureComp->SetTexture("logo.tga");
	//textureComp->AddToRenderer(renderComp);

	//renderComp->AddToDisplayGui(textureComp);
	//renderComp->AddToDisplayGui(transComp);

	//scene.Add(std::move(lg));



	//// prog4 text
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto txt = std::make_unique<dae::GameObject>();
	//renderComp = txt->AddComponent<dae::RenderComponent>();
	//transComp = txt->AddComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(80, 20);
	//auto textComponent = txt->AddComponent<dae::TextComponent>();
	//textComponent->SetFont(font);
	//textComponent->SetText("Programming 4 Assignment");
	//textComponent->AddToRenderer(renderComp);
	//scene.Add(std::move(txt));

	// fps
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fps = std::make_unique<dae::GameObject>();
	renderComp = fps->AddComponent<dae::RenderComponent>();
	transComp = fps->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0, 0);
	auto textComponent = fps->AddComponent<dae::TextComponent>();
	textComponent->SetFont(font);
	textComponent->SetText("FPS");
	textComponent->SetColor({ 150, 150, 0 });
	textComponent->AddToRenderer(renderComp);
	//auto test = fps->GetComponent<dae::RenderComponent>(); test;
	fps->AddComponent<dae::FPSComponent>(); //auto FPSComponent =  // just write this down, otherwise warning as unused
	scene.Add(std::move(fps));


	// bubby - has lives + score (P1)
	auto bubby = std::make_unique<dae::GameObject>();
	dae::GameObject* player1 = bubby.get();
	renderComp = bubby->AddComponent<dae::RenderComponent>();
	transComp = bubby->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(220.0f, 240.0f);
	textureComp = bubby->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("Bubby.png");
	textureComp->AddToRenderer(renderComp);
	auto healthComp = bubby->AddComponent<dae::HealthComponent>();
	auto scoreComp = bubby->AddComponent<dae::ScoreComponent>();
	healthComp->AddObserver(scoreComp); // our score needs to listen to our own health (for this test)
	scene.Add(std::move(bubby));


	// P1 health debug
	auto debugHealthP1 = std::make_unique<dae::GameObject>();
	renderComp = debugHealthP1->AddComponent<dae::RenderComponent>();
	transComp = debugHealthP1->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0.0f, 150.0f);
	textComponent = debugHealthP1->AddComponent<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	textComponent->SetFont(font);
	textComponent->SetText("Lives: ");
	textComponent->SetColor({ 0, 255, 0 });
	textComponent->AddToRenderer(renderComp);
	auto debugHealthComp = debugHealthP1->AddComponent<dae::DebugHealthComponent>();
	debugHealthComp->SetLastHealth(healthComp->GetCurrentHealth());
	scene.Add(std::move(debugHealthP1));

	// P1 score debug
	auto debugScoreP1 = std::make_unique<dae::GameObject>();
	renderComp = debugScoreP1->AddComponent<dae::RenderComponent>();
	transComp = debugScoreP1->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0.0f, 170.f);
	textComponent = debugScoreP1->AddComponent<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	textComponent->SetFont(font);
	textComponent->SetText("Score: ");
	textComponent->SetColor({ 0, 255, 0 });
	textComponent->AddToRenderer(renderComp);
	auto debugScoreComp = debugScoreP1->AddComponent<dae::DebugScoreComponent>();
	scene.Add(std::move(debugScoreP1));

	// add	debug observer to bubby
	healthComp->AddObserver(debugHealthComp);
	scoreComp->AddObserver(debugScoreComp);


	// bobby - has lives + score
	auto bobby = std::make_unique<dae::GameObject>();
	dae::GameObject* player2 = bobby.get();
	renderComp = bobby->AddComponent<dae::RenderComponent>();
	auto newTransComp = bobby->AddComponent<dae::TransformComponent>();
	newTransComp->SetLocalPosition(320.0f, 240.0f);
	textureComp = bobby->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("Bobby.png");
	textureComp->AddToRenderer(renderComp);
	healthComp = bobby->AddComponent<dae::HealthComponent>();
	scoreComp = bobby->AddComponent<dae::ScoreComponent>();
	healthComp->AddObserver(scoreComp); // our score needs to listen to our own health (for this test)
	scene.Add(std::move(bobby));


	// P2 health debug
	auto debugHealthP2 = std::make_unique<dae::GameObject>();
	renderComp = debugHealthP2->AddComponent<dae::RenderComponent>();
	transComp = debugHealthP2->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0.0f, 250.0f);
	textComponent = debugHealthP2->AddComponent<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	textComponent->SetFont(font);
	textComponent->SetText("Lives: ");
	textComponent->SetColor({ 130, 210, 255 });
	textComponent->AddToRenderer(renderComp);
	debugHealthComp = debugHealthP2->AddComponent<dae::DebugHealthComponent>();
	debugHealthComp->SetLastHealth(healthComp->GetCurrentHealth());
	scene.Add(std::move(debugHealthP2));

	// P2 score debug
	auto debugScoreP2 = std::make_unique<dae::GameObject>();
	renderComp = debugScoreP2->AddComponent<dae::RenderComponent>();
	transComp = debugScoreP2->AddComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0.0f, 270.f);
	textComponent = debugScoreP2->AddComponent<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	textComponent->SetFont(font);
	textComponent->SetText("Score: ");
	textComponent->SetColor({ 130, 210, 255 });
	textComponent->AddToRenderer(renderComp);
	debugScoreComp = debugScoreP2->AddComponent<dae::DebugScoreComponent>();
	scene.Add(std::move(debugScoreP2));

	// add	debug observer to bobby
	healthComp->AddObserver(debugHealthComp);
	scoreComp->AddObserver(debugScoreComp);



	// =========== How To Play? ========
	auto howToPlay = std::make_unique<dae::GameObject>();
	renderComp = howToPlay->AddComponent<dae::RenderComponent>();
	auto tutorialComp = howToPlay->AddComponent<dae::HowToPlayComponent>();
	renderComp->AddToDisplayGui(tutorialComp);
	scene.Add(std::move(howToPlay));

	//// bibby
	/*auto bibby = std::make_unique<dae::GameObject>();
	renderComp = bibby->AddComponent<dae::RenderComponent>();
	newTransComp = bibby->AddComponent<dae::TransformComponent>();
	newTransComp->SetLocalPosition(260.0f, 310.0f);
	textureComp = bibby->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("Bibby.png");
	textureComp->AddToRenderer(renderComp);
	scene.Add(std::move(bibby));*/

	
	// ======== damage/point commands ============

	// P1
	std::vector<unsigned int> p1DamageButtonsInput{
		SDLK_j
	};
	auto p1DamageCommand{ std::make_unique<dae::DamageCommand>(player1, 1) };
	dae::InputManager::GetInstance().BindCommand(p1DamageButtonsInput, dae::InputManager::InputType::OnButtonDown, std::move(p1DamageCommand));

	std::vector<unsigned int> p1GiveScoreButtonsInput{
		SDLK_u
	};
	auto p1ScoreCommand{ std::make_unique<dae::GiveScoreCommand>(player1, 100) };
	dae::InputManager::GetInstance().BindCommand(p1GiveScoreButtonsInput, dae::InputManager::InputType::OnButtonDown, std::move(p1ScoreCommand));


	// P2
	std::vector<unsigned int> p2DamageButtonsInput{
		SDLK_k
	};
	auto p2DamageCommand{ std::make_unique<dae::DamageCommand>(player2, 1) };
	dae::InputManager::GetInstance().BindCommand(p2DamageButtonsInput, dae::InputManager::InputType::OnButtonDown, std::move(p2DamageCommand));

	std::vector<unsigned int> p2GiveScoreButtonsInput{
		SDLK_i
	};
	auto p2ScoreCommand{ std::make_unique<dae::GiveScoreCommand>(player2, 100) };
	dae::InputManager::GetInstance().BindCommand(p2GiveScoreButtonsInput, dae::InputManager::InputType::OnButtonDown, std::move(p2ScoreCommand));



	// ========= Move Commands ===============

	const float baseSpeed{ 200.0f };
	std::vector<unsigned int> character1Input{
		SDLK_a,
		SDLK_d,
		SDLK_w,
		SDLK_s,
	};
	auto character1MoveCommand{ std::make_unique<dae::MoveCommand>(player1, baseSpeed)};
	dae::InputManager::GetInstance().BindCommand(character1Input, dae::InputManager::InputType::Digital2DAxis, std::move(character1MoveCommand));
	
	std::vector<unsigned int> character2Input{
		dae::Controller::ControllerButton::DPadLeft,
		dae::Controller::ControllerButton::DPadRight,
		dae::Controller::ControllerButton::DPadUp,
		dae::Controller::ControllerButton::DPadDown
	};
	
	auto character2MoveCommand{ std::make_unique<dae::MoveCommand>(player2, baseSpeed * 2.0f) };
	dae::InputManager::GetInstance().BindCommand(character2Input, dae::InputManager::InputType::Digital2DAxis, std::move(character2MoveCommand), 0);


	// EXTRA: 3rd character with left joystick input
	//std::vector<unsigned int> character3Input{
	//	dae::Controller::ControllerButton::LeftThumb
	//};
	//
	//auto character3MoveCommand{ std::make_unique<dae::MoveCommand>(bibby.get(), baseSpeed * 2.0f) };
	//dae::InputManager::GetInstance().BindCommand(character3Input, dae::InputManager::InputType::Analog2DAxis, std::move(character3MoveCommand), 1);
	











	// =========================== UNUSED PARENTING - STILL NEEDING FIX ===========================

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