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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	
	// in this example we make 4 different GameObjects
	// it should be possible to just make 1 and add everything to it.
	auto go = std::make_shared<dae::GameObject>();
	auto renderComp = go->AddComponent<dae::RenderComponent>();
	auto textureComp = go->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("background.tga");
	textureComp->AddToRenderer(renderComp);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	renderComp = go->AddComponent<dae::RenderComponent>();
	textureComp = go->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("logo.tga");
	textureComp->SetPosition(216.f, 180.f);
	textureComp->AddToRenderer(renderComp);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	renderComp = go->AddComponent<dae::RenderComponent>();
	auto textComponent = go->AddComponent<dae::TextComponent>();
	textComponent->SetFont(font);
	textComponent->SetText("Programming 4 Assignment");
	textComponent->SetPosition(80, 20);
	textComponent->AddToRenderer(renderComp);
	scene.Add(go);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<dae::GameObject>();
	renderComp = go->AddComponent<dae::RenderComponent>();
	auto FPSComponent = go->AddComponent<dae::FPSComponent>();
	textComponent = FPSComponent->GetTextComponent();
	textComponent->SetFont(font);
	textComponent->SetPosition(0, 0);
	textComponent->SetColor({ 150, 150, 0 });
	textComponent->AddToRenderer(renderComp);
	scene.Add(go);

	// below there is an example that it is possible to add all components to 1 GameObject and still get the right results
	// keep in mind, order matters
	/*
	auto go = std::make_shared<dae::GameObject>();
	auto renderComp = go->AddComponent<dae::RenderComponent>(go);
	auto textureComp = go->AddComponent<dae::TextureComponent>(go);
	textureComp->SetTexture("background.tga");
	textureComp->AddToRenderer(renderComp);
	textureComp = go->AddComponent<dae::TextureComponent>(go);
	textureComp->SetTexture("logo.tga");
	textureComp->SetPosition(216.f, 180.f);
	textureComp->AddToRenderer(renderComp);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = go->AddComponent<dae::TextComponent>(go);
	textComponent->SetFont(font);
	textComponent->SetText("Programming 4 Assignment");
	textComponent->SetPosition(80, 20);
	textComponent->AddToRenderer(renderComp);
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	renderComp = go->AddComponent<dae::RenderComponent>(go);
	auto FPSComponent = go->AddComponent<dae::FPSComponent>(go);
	textComponent = FPSComponent->GetTextComponent();
	textComponent->SetFont(font);
	textComponent->SetPosition(0, 0);
	textComponent->SetColor({ 150, 150, 0 });
	textComponent->AddToRenderer(renderComp);
	scene.Add(go);
	*/
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}