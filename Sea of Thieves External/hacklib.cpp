#include "hacklib.h"

#undef UNICODE
#include <TlHelp32.h>
#define UNICODE

namespace hacklib
{
	SmartHandle::SmartHandle(HANDLE handle)
	{
		if (handle == INVALID_HANDLE_VALUE) handle = nullptr;
		this->_handle = nullptr;
		auto current_process = GetCurrentProcess();
		DuplicateHandle(current_process, handle, current_process, &this->_handle, 0, FALSE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);
	}

	SmartHandle &SmartHandle::operator=(SmartHandle &&other) noexcept
	{
		this->_handle = other._handle;
		other._handle = nullptr;
		return *this;
	}

	SmartHandle::~SmartHandle()
	{
		if (this->_handle) CloseHandle(this->_handle);
	}

	SmartHandle::operator HANDLE()
	{
		return this->_handle;
	}

	bool SmartHandle::is_valid() const
	{
		return this->_handle != nullptr;
	}

	DWORD find_process_pid(const std::string &process_name)
	{
		DWORD result = 0;
		SmartHandle snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
		if (!snapshot.is_valid()) return result;
		PROCESSENTRY32 process_entry{ };
		process_entry.dwSize = sizeof(process_entry);
		for (bool b = Process32First(snapshot, &process_entry); b; b = Process32Next(snapshot, &process_entry))
		{
			if (process_name.compare(process_entry.szExeFile) == 0)
			{
				result = process_entry.th32ProcessID;
				break;
			}
		}
		return result;
	}

	bool Process::attach(DWORD access_mask)
	{
		this->_pid = find_process_pid(this->_name);
		if (!this->_pid) return false;
		this->_handle = SmartHandle{ OpenProcess(access_mask, FALSE, this->_pid) };
		if (!this->_handle) return false;
		return true;
	}

	Module Process::get_module(const std::string &module_name)
	{
		if (this->_modules.count(module_name)) return this->_modules[module_name];
		Module result{ nullptr, 0 };
		SmartHandle snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->_pid) };
		if (!snapshot.is_valid()) return result;
		MODULEENTRY32 module_entry{ };
		module_entry.dwSize = sizeof(module_entry);
		for (bool b = Module32First(snapshot, &module_entry); b; b = Module32Next(snapshot, &module_entry))
		{
			if (module_name.compare(module_entry.szModule) == 0)
			{
				result._base = module_entry.modBaseAddr;
				result._size = module_entry.dwSize;
				break;
			}
		}
		if (result._base) this->_modules[module_name] = result;
		return result;
	}
}