#pragma once
#include "box2d.h"


namespace phoenix
{
	class ContactListener : public b2ContactListener
	{
	public:

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;

	};

}