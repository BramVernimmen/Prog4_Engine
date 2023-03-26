#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>


bool dae::InputManager::ProcessInput()
{
	// first read SDL events
	if (ReadSDL_Events() == false) // quit has been hit
		return false;

	// update all controllers
	for (const auto& currController : m_pControllers)
	{
		currController->Update();
	}

	for (const auto& currCommand : m_Commands)
	{
		ResetValues();
		bool executeCommand{ false }; // we check if we can execute the command first
		if (currCommand.first.id >= 0) // we are using a controller
		{
			switch (currCommand.first.inputType)
			{
			case InputType::OnButtonDown:
				executeCommand = m_pControllers[currCommand.first.id]->IsDown(currCommand.first.buttons[0]);
				break;
			case InputType::OnButtonUp:
				executeCommand = m_pControllers[currCommand.first.id]->IsUp(currCommand.first.buttons[0]);
				break;
			case InputType::OnButton:
				executeCommand = m_pControllers[currCommand.first.id]->IsPressed(currCommand.first.buttons[0]);
				break;
			case InputType::AnalogAxis:
				// get the analog axis value from the controller
				m_AnalogAxisValue = m_pControllers[currCommand.first.id]->GetAxis(currCommand.first.buttons[0]);
				if (m_AnalogAxisValue > 0.0f)
					executeCommand = true;
				break;
			case InputType::Analog2DAxis:
				// get the 2D analog axis value from the controller
				m_2DAxisValue = m_pControllers[currCommand.first.id]->Get2DAxis(currCommand.first.buttons[0]);
				if (m_2DAxisValue.x != 0.0f || m_2DAxisValue.y != 0.0f)
					executeCommand = true;
				break;
			case InputType::Digital2DAxis:
				// get the 2D digital axis value from the controller
				// order of buttons are: LEFT, RIGHT, UP, DOWN
				glm::vec2 readOutput{};
				if (m_pControllers[currCommand.first.id]->IsPressed(currCommand.first.buttons[0])) // if left is down
					readOutput.x -= 1;
				if (m_pControllers[currCommand.first.id]->IsPressed(currCommand.first.buttons[1])) // if right is down
					readOutput.x += 1;
				if (m_pControllers[currCommand.first.id]->IsPressed(currCommand.first.buttons[2])) // if up is down
					readOutput.y += 1;
				if (m_pControllers[currCommand.first.id]->IsPressed(currCommand.first.buttons[3])) // if down is down
					readOutput.y -= 1;

				if (readOutput.x != 0 || readOutput.y != 0) // only if we actually moved
				{
					m_2DAxisValue = { readOutput.x, readOutput.y };
					executeCommand = true;
				}
				
				break;
			}
		}
		else // we are using a keyboard
		{
			switch (currCommand.first.inputType)
			{
			case InputType::OnButtonDown:
				executeCommand = m_KeysDown.contains(currCommand.first.buttons[0]);
				break;
			case InputType::OnButtonUp:
				executeCommand = m_KeysUp.contains(currCommand.first.buttons[0]);
				break;
			case InputType::OnButton:
				executeCommand = m_KeysPressed.contains(currCommand.first.buttons[0]);
				break;
			case InputType::AnalogAxis: // this is not supported on keyboard
				break;
			case InputType::Analog2DAxis: // this is not supported on keyboard
				break;
			case InputType::Digital2DAxis:
				glm::vec2 readOutput{};
				if (m_KeysPressed.contains(currCommand.first.buttons[0])) // if left is down
					readOutput.x -= 1;
				if (m_KeysPressed.contains(currCommand.first.buttons[1])) // if right is down
					readOutput.x += 1;
				if (m_KeysPressed.contains(currCommand.first.buttons[2])) // if up is down
					readOutput.y += 1;
				if (m_KeysPressed.contains(currCommand.first.buttons[3])) // if down is down
					readOutput.y -= 1;

				if (readOutput.x != 0 || readOutput.y != 0) // only if we actually moved
				{
					m_2DAxisValue = { readOutput.x, readOutput.y };
					executeCommand = true;
				}
				break;
			}
		}
		

		if (executeCommand)
		{
			currCommand.second->Execute();
		}
	}


	
	return true;
}

void dae::InputManager::BindCommand(const std::vector<unsigned int>& buttons, InputType inputType, std::unique_ptr<Command> pCommand, int id)
{
	if (inputType == InputType::Digital2DAxis && buttons.size() > 4) // this isn't allowed
		return;
	else if (inputType != InputType::Digital2DAxis && buttons.size() > 1) // also not allowed
		return;
	else if (buttons.empty())
		return;

	if (id >= 0) // we have a controller to use
	{
		ControllerIndexCheck(id); // creates extra controllers if the id isn't in the vector
	}
	//else  keyboard will be used
	
	InputInfo info{};
	info.id = id;
	info.buttons = buttons;
	info.inputType = inputType;
	
	m_Commands.emplace(info, std::move(pCommand));
}



bool dae::InputManager::ReadSDL_Events()
{
	// handle SDL -> later
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_KeysDown.emplace(e.key.keysym.sym);
			m_KeysPressed.emplace(e.key.keysym.sym);
		}
		if (e.type == SDL_KEYUP) {
			m_KeysUp.emplace(e.key.keysym.sym);
			m_KeysPressed.erase(e.key.keysym.sym); // the key is no longer pressed, remove it
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// etc...
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void dae::InputManager::ControllerIndexCheck(int id)
{
	if (id >= static_cast<int>(m_pControllers.size())) // we don't have enough controllers
	{
		const int amountOfNewControllers{ id + 1 - static_cast<int>(m_pControllers.size()) };
		for (int i{ 0 }; i < amountOfNewControllers; ++i)
		{
			m_pControllers.push_back(std::make_unique<Controller>(static_cast<int>(m_pControllers.size())));
		}
	}
}

void dae::InputManager::ResetValues()
{
	m_2DAxisValue = {};
	m_AnalogAxisValue = 0.0f;
}
