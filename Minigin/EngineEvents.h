#pragma once
#include "Event.h"

namespace dae
{
	class PlayerDamaged final : public Event {};
	class PlayerDied final : public Event {};
	class GainedScore final : public Event {};
}