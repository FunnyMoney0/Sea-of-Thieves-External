#pragma once
#include <cstdint>
#include <vector>
#include <string>

#include "hacklib.h"
#include "offsets.h"

namespace sdk
{
	bool init(hacklib::Process *process);
	hacklib::Process *process();

	class Vector3
	{
	public:
		Vector3()
		{
			memset(this, 0, sizeof(this));
		}

		Vector3(float x, float y, float z)
			: _x(x)
			, _y(y)
			, _z(z)
		{
		}

		float dot(const Vector3 &other) const
		{
			return this->_x * other._x + this->_y * other._y + this->_z * other._z;
		}

		Vector3 operator*(float scalar) const
		{
			return Vector3{ this->_x * scalar, this->_y * scalar, this->_z * scalar };
		}

		Vector3 operator-(const Vector3 &other)
		{
			return Vector3{ this->_x - other._x, this->_y - other._y, this->_z - other._z };
		}

		float _x;
		float _y;
		float _z;
	};

	class Vector2
	{
	public:
		Vector2()
		{
			memset(this, 0, sizeof(this));
		}

		Vector2(float x, float y)
			: _x(x)
			, _y(y)
		{
		}

		float _x;
		float _y;
	};

	class Matrix3x3
	{
	public:
		Matrix3x3()
		{
			memset(this, 0, sizeof(this));
		}

		float *operator[](int index)
		{
			return this->_values[index];
		}
	private:
		float _values[3][3];
	};

	class ExternalObject abstract
	{
	public:
		ExternalObject(void *instance)
			: _instance(instance)
		{
		}

		ExternalObject()
			: _instance(nullptr)
		{
		}

		void *instance() const
		{
			return this->_instance;
		}

		template <typename T>
		T read_member(uint32_t offset) const
		{
			return process()->read_memory<T>(static_cast<char *>(this->_instance) + offset);
		}

	protected:
		void *_instance;
	};

#define EXTERN_OBJECT_CCTOR(class_name) class_name() : ExternalObject() {} class_name(void *instance) : ExternalObject(instance) {}

	template <typename T>
	class TArray : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(TArray);

		std::vector<T> get_data(int size) const
		{
			void *data = process()->read_memory<void *>(this->_instance);
			std::vector<T> result{ };
			result.resize(size);
			process()->read_memory(data, result.data(), size * sizeof(T));
			return result;
		}

		int array_num() const
		{
			return this->read_member<int>(0x8);
		}

		int array_max() const
		{
			return this->read_member<int>(0xC);
		}
	};
	/*
	* ================================================================
	*/
	class FString : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(FString);

		TArray<wchar_t> data() const
		{
			return TArray<wchar_t>{ this->_instance };
		}
	};
	/*
	* ================================================================
	*/
	class FMinimalViewInfo : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(FMinimalViewInfo);

		Vector3 location() const
		{
			return this->read_member<Vector3>(offsets::Location);
		}

		Vector3 rotation() const
		{
			return this->read_member<Vector3>(offsets::Rotation);
		}

		float fov() const
		{
			return this->read_member<float>(offsets::FOV);
		}
	};

	/*
	* ================================================================
	*/
	class FCameraCacheEntry : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(FCameraCacheEntry);

		FMinimalViewInfo pov() const
		{
			return FMinimalViewInfo{ static_cast<char *>(this->_instance) + offsets::POV };
		}
	};

	/*
	* ================================================================
	*/
	class APlayerCameraManager : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(APlayerCameraManager);

		FCameraCacheEntry camera_cache() const
		{
			return FCameraCacheEntry{ static_cast<char *>(this->_instance) + offsets::CameraCache };
		}
	};
	/*
	* ================================================================
	*/
	class APlayerState : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(APlayerState);

		FString player_name() const
		{
			return FString{ static_cast<char *>(this->_instance) + offsets::PlayerName };
		}
	};
	/*
	* ================================================================
	*/
	class APawn : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(APawn);

		APlayerState player_state() const
		{
			return this->read_member<APlayerState>(offsets::PlayerState);
		}
	};
	class USceneComponent : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(USceneComponent);

		Vector3 relative_location() const
		{
			return this->read_member<Vector3>(offsets::RelativeLocation);
		}
	};
	/*
	* ================================================================
	*/
	class AActor : public APawn
	{
	public:
		AActor(void *instance)
			: APawn(instance)
		{
		}

		AActor()
			: APawn(nullptr)
		{
		}

		int id() const
		{
			return this->read_member<int>(0x18);
		}

		USceneComponent root_component() const
		{
			return this->read_member<USceneComponent>(offsets::RootComponent);
		}

		TArray<AActor> children()
		{
			return TArray<AActor>{ static_cast<char *>(this->_instance) + offsets::Children };
		}
	};
	/*
	* ================================================================
	*/
	class UHealthComponent : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(UHealthComponent);

		float max_health() const
		{
			return this->read_member<float>(offsets::MaxHealth);
		}

		float current_health() const
		{
			return this->read_member<float>(offsets::CurrentHealthInfo + offsets::Health);
		}
	};
	/*
	* ================================================================
	*/
	class AAthenaCharacter : public AActor
	{
	public:
		AAthenaCharacter(void *instance)
			: AActor(instance)
		{
		}

		UHealthComponent health_component() const
		{
			return this->read_member<UHealthComponent>(offsets::HealthComponent);
		}
	};
	/*
	* ================================================================
	*/
	class APlayerController : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(APlayerController);

		APlayerCameraManager player_camera_manager() const
		{
			return this->read_member<APlayerCameraManager>(offsets::PlayerCameraManager);
		}

		APawn acknowledged_pawn() const
		{
			return this->read_member<APawn>(offsets::AcknowledgedPawn);
		}
	};
	/*
	* ================================================================
	*/
	class UPlayer : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(UPlayer);

		APlayerController player_controller() const
		{
			return this->read_member<APlayerController>(offsets::PlayerController);
		}
	};
	/*
	* ================================================================
	*/
	class UGameInstance : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(UGameInstance);

		UPlayer local_player() const
		{
			UPlayer *local_players = this->read_member<UPlayer *>(offsets::LocalPlayers);
			return process()->read_memory<UPlayer>(local_players + 0);
		}
	};
	/*
	* ================================================================
	*/
	class ULevel : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(ULevel);

		TArray<AActor> actors() const
		{
			return TArray<AActor>{ static_cast<char *>(this->_instance) + offsets::Actors };
		}
	};
	/*
	* ================================================================
	*/
	class UWorld : public ExternalObject
	{
	public:
		EXTERN_OBJECT_CCTOR(UWorld);

		UGameInstance owning_game_instance() const
		{
			return this->read_member<UGameInstance>(offsets::OwningGameInstance);
		};

		ULevel persistent_level() const
		{
			return this->read_member<ULevel>(offsets::PersistentLevel);
		}
	};

#undef EXTERN_OBJECT_CCTOR
}