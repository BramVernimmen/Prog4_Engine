#include "LivesComponent.h"
#include "GameEvents.h"
#include "GameTime.h"

dae::LivesComponent::LivesComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	ResetLives();
}



void dae::LivesComponent::Update()
{
	if (m_IsInvincible)
	{
		m_CurrentInvincibility += GameTime::GetInstance().GetDeltaTime();

		if (m_CurrentInvincibility >= m_MaxInvincibility)
		{
			m_IsInvincible = false;
			m_CurrentInvincibility = 0.0f;
		}
	}
}

void dae::LivesComponent::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(PlayerHit) && !m_IsInvincible) // handle things here
	{
		RemoveLife();
	}
}

void dae::LivesComponent::ResetLives()
{
	m_CurrentLives = m_MaxLives;
}

void dae::LivesComponent::RemoveLife()
{
	if (m_CurrentLives <= 0) // player is dead
		return;

	--m_CurrentLives;
	
	if (m_CurrentLives <= 0) // player has died
	{
		m_CurrentLives = 0; // safe reset to 0
		// send death event
		NotifyObservers(PlayerDied());
		// don't return as we also took a hit, so we need to send an event for that too
	}

	// we lost a live, send event
	NotifyObservers(PlayerHit(), this);
	m_IsInvincible = true;
}
