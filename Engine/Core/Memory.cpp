#include "Memory.h"

namespace phoenix
{
	void InitializeMemory()
	{
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	}

}

