#include "sdk.h"

namespace sdk
{
	hacklib::Process *_process;

	bool init(hacklib::Process *process)
	{
		_process = process;
		return _process != nullptr;
	}

	hacklib::Process *process()
	{
		return _process;
	}
}