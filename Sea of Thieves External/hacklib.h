#pragma once
#include <Windows.h>

#include <string>
#include <unordered_map>

namespace hacklib
{
	class SmartHandle
	{
	public:
		SmartHandle(HANDLE handle);
		SmartHandle &operator=(SmartHandle &&other) noexcept;
		~SmartHandle();

		operator HANDLE();

		bool is_valid() const;

	private:
		HANDLE _handle;
	};

	struct Module
	{
		void *_base;
		DWORD _size;
	};

	class Process
	{
	public:
		Process(const std::string &name)
			: _name(name)
			, _pid(0)
			, _handle(nullptr)
		{
		}

		bool attach(DWORD access_mask);
		Module get_module(const std::string &module_name);

		void read_memory(void *address, void *out, SIZE_T size)
		{
			ReadProcessMemory(this->_handle, address, out, size, nullptr);
		}

		template <typename T>
		T read_memory(void *address)
		{
			T result{ };
			ReadProcessMemory(this->_handle, address, &result, sizeof(result), nullptr);
			return result;
		}

	private:
		std::string _name;
		DWORD _pid;
		SmartHandle _handle;
		std::unordered_map<std::string, Module> _modules{ };
	};
}