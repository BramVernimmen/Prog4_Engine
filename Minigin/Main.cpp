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
#include "TextObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextureComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<dae::GameObject>();
	//go->SetTexture("background.tga");
	//scene.Add(go);
	
	//go = std::make_shared<dae::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);

	auto go = std::make_shared<dae::GameObject>();
	auto renderComp = go->AddComponent<dae::RenderComponent>(go);
	auto textureComp = go->AddComponent<dae::TextureComponent>(go);
	textureComp->SetTexture("background.tga");
	textureComp->AddToRenderer(renderComp);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	renderComp = go->AddComponent<dae::RenderComponent>(go);
	textureComp = go->AddComponent<dae::TextureComponent>(go);
	textureComp->SetTexture("logo.tga");
	textureComp->SetPosition(216.f, 180.f);
	textureComp->AddToRenderer(renderComp);
	scene.Add(go);

	go->RemoveComponent<dae::RenderComponent>();


}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}