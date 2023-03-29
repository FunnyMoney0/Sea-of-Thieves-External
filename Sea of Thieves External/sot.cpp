#include "sot.h"

#include <unordered_map>

#include "sdk.h"

namespace cheat
{
	constexpr const DWORD access_mask = PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
	constexpr const float pi = 3.141592f;

	SOT _game{ };
	
	const std::unordered_map<std::string, SOT::ActorType> _actor_name_map
	{
		{ "BP_PlayerPirate_C",	SOT::ActorType::PLAYER_PIRATE },

		{ "BP_OrderOfSouls_Oprah_C",		SOT::ActorType::OOS_OPRAH },
		{ "BP_Orderofsouls_Olive_C",		SOT::ActorType::OOS_OLIVE },
		{ "BP_Orderofsouls_MadameOlwen_C",	SOT::ActorType::OOS_MADAME_OLWEN },
		{ "BP_Orderofsouls_Olivia_C",		SOT::ActorType::OOS_OLIVIA },
		{ "BP_Orderofsouls_Oksana_C",		SOT::ActorType::OOS_OKSANA },
		{ "BP_Orderofsouls_Olga_C",			SOT::ActorType::OOS_OLGA },
		{ "BP_OrderOfSouls_Oya_C",			SOT::ActorType::OOS_OYA },

		{ "BP_Goldhoarder_Horace_C",	SOT::ActorType::GHD_HORACE },
		{ "BP_Goldhoarder_Humphrey_C",	SOT::ActorType::GHD_HUMPHREY },
		{ "BP_Goldhoarder_Herbert_C",	SOT::ActorType::GHD_HERBERT },
		{ "BP_Goldhoarder_Harry_C",		SOT::ActorType::GHD_HARRY },
		{ "BP_Goldhoarder_Henry_C",		SOT::ActorType::GHD_HENRY },
		{ "BP_Goldhoarder_Hugh_C",		SOT::ActorType::GHD_HUGH },
		{ "BP_Goldhoarder_Hyde_C",		SOT::ActorType::GHD_HYDE },

		{ "BP_Merchant_Mandy_C",	SOT::ActorType::MCH_MANDY },
		{ "BP_Merchant_Mollie_C",	SOT::ActorType::MCH_MOLLIE },
		{ "BP_Merchant_Mildred_C",	SOT::ActorType::MCH_MILDRED },
		{ "BP_Merchant_Meg_C",		SOT::ActorType::MCH_MEG },
		{ "BP_Merchant_Mavis_C",	SOT::ActorType::MCH_MAVIS },
		{ "BP_Merchant_Maureen_C",	SOT::ActorType::MCH_MAUREEN },
		{ "BP_Merchant_DVR_C",		SOT::ActorType::MCH_MATILDA },

		{ "BP_Cargorun_Charlotte_C",	SOT::ActorType::CGR_CHARLOTTE },

		{ "BP_GhostShipCaptain_C",	SOT::ActorType::GHOST_SHIP_CAPTAIN },

		{ "BP_SmallShipTemplate_C",		SOT::ActorType::S_SHIP_TEMPLATE },
		{ "BP_SmallShipNetProxy_C",		SOT::ActorType::S_SHIP_TEMPLATE },
		{ "BP_MediumShipTemplate_C",	SOT::ActorType::M_SHIP_TEMPLATE },
		{ "BP_MediumShipNetProxy_C",	SOT::ActorType::M_SHIP_TEMPLATE },
		{ "BP_LargeShipTemplate_C",		SOT::ActorType::L_SHIP_TEMPLATE },
		{ "BP_LargeShipNetProxy_C",		SOT::ActorType::L_SHIP_TEMPLATE },

		{ "BP_Mermaid_C",	SOT::ActorType::MERMAID },

		{ "BP_Pig_Common_C",	SOT::ActorType::PIG },
		{ "BP_Pig_Rare_C",		SOT::ActorType::PIG },
		{ "BP_Pig_Legendary_C",	SOT::ActorType::PIG },
		{ "BP_Pig_Mythical_C",	SOT::ActorType::PIG },

		{ "BP_Chicken_Common_C",	SOT::ActorType::CHICKEN },
		{ "BP_Chicken_Rare_C",		SOT::ActorType::CHICKEN },
		{ "BP_Chicken_Legendary_C",	SOT::ActorType::CHICKEN },
		{ "BP_Chicken_Mythical_C",	SOT::ActorType::CHICKEN },

		{ "BP_Snake_Common_C",		SOT::ActorType::SNAKE },
		{ "BP_Snake_Rare_C",		SOT::ActorType::SNAKE },
		{ "BP_Snake_Legendary_C",	SOT::ActorType::SNAKE },
		{ "BP_Snake_Mythical_C",	SOT::ActorType::SNAKE },

		{ "BP_Shark_C",		SOT::ActorType::SHARK },
		{ "BP_TinySHark_C",	SOT::ActorType::TINY_SHARK },

		{ "BP_SkeletonPawnBase_C",	SOT::ActorType::SKELETON },
		{ "BP_PhantomPawnBase_C",	SOT::ActorType::PHANTOM },
		{ "BP_SirenPawnBase_C",		SOT::ActorType::SIREN },

		{ "BP_OceanCrawlerCharacter_Hermit_C",		SOT::ActorType::OCEAN_CRAWLER_HERMIT },
		{ "BP_OceanCrawlerCharacter_Crab_C",		SOT::ActorType::OCEAN_CRAWLER_CRAB },
		{ "BP_OceanCrawlerCharacter_Eelectric_C",	SOT::ActorType::OCEAN_CRAWLER_EELECTRIC },

		{ "BP_SirenTrident_Proxy_C",								SOT::ActorType::SIREN_TRIDENT },
		{ "BP_MerchantCrate_BigGunpowderBarrelProxy_C",				SOT::ActorType::B_GUNPOWDER_BARREL },
		{ "BP_LowValueGift_Proxy_C",								SOT::ActorType::LOW_VALUE_GIFT },
		{ "BP_Ritual_Skull_Proxy_C",								SOT::ActorType::RITUAL_SKULL },
		{ "BP_BountyRewardSkull_Proxy_Mythical_C",					SOT::ActorType::MY_BOUNTY_REWARD_SKULL },
		{ "BP_SkeletonOrders_Proxy_C",								SOT::ActorType::SKELETON_ORDERS },
		{ "BP_EmergentGoldPouchProxy_C",							SOT::ActorType::GOLD_POUCH },
		{ "BP_TreasureChest_Proxy_Mythical_C",						SOT::ActorType::MY_TREASURE_CHEST },
		{ "BP_ShipwreckTreasureChest_Proxy_Mythical_C",				SOT::ActorType::MY_TREASURE_CHEST },
		{ "BP_TreasureChest_Proxy_Rare_C",							SOT::ActorType::RA_TREASURE_CHEST },
		{ "BP_ShipwreckTreasureChest_Proxy_Rare_C",					SOT::ActorType::RA_TREASURE_CHEST },
		{ "BP_AncientCollectorsChest_Proxy_C",						SOT::ActorType::ANCIENT_COLLECTORS_CHEST },
		{ "BP_AshenChestCollectorsChest_Proxy_C",					SOT::ActorType::ASHEN_CHEST_COLLECTORS_CHEST },
		{ "BP_AshenKey_Proxy_C",									SOT::ActorType::ASHEN_KEY },
		{ "BP_CollectorsChest_Proxy_C",								SOT::ActorType::COLLECTORS_CHEST },
		{ "BP_MermaidGem_Proxy_Ruby_C",								SOT::ActorType::MERMAID_GEM_RUBY },
		{ "BP_MermaidGem_Proxy_Emerald_C",							SOT::ActorType::MERMAID_GEM_EMERALD },
		{ "BP_MermaidGem_Proxy_Sapphire_C",							SOT::ActorType::MERMAID_GEM_SAPPHIRE },
		{ "BP_AmmoPouchProxy_C",									SOT::ActorType::AMMO_POUCH },
		{ "BP_BountyRewardSkull_Proxy_Rare_C",						SOT::ActorType::RA_BOUNTY_REWARD_SKULL },
		{ "BP_MessageInABottle_Coral_Proxy_C",						SOT::ActorType::CORAL_MESSAGE_IN_A_BOTTLE },
		{ "BP_MessageInABottleProxy_C",								SOT::ActorType::MESSAGE_IN_A_BOTTLE },
		{ "BP_SunkenCurseArtefact_Ruby_EasierBetterRewards_C",		SOT::ActorType::SUNKEN_CURSE_RUBY },
		{ "BP_SunkenCurseArtefact_Emerald_EasierBetterRewards_C",	SOT::ActorType::SUNKEN_CURSE_EMERALD },
		{ "BP_SunkenCurseArtefact_Sapphire_EasierBetterRewards_C",	SOT::ActorType::SUNKEN_CURSE_SAPPHIRE },
		{ "BP_MerchantCrate_BananaCrateProxy_C",					SOT::ActorType::BANANA_CRATE },
		{ "BP_Treasure_Artifact_Proxy_vase_01_a_C",					SOT::ActorType::TREASURE_ARTIFACT_VASE_01 },
		{ "BP_Treasure_Artifact_Proxy_vase_02_a_C",					SOT::ActorType::TREASURE_ARTIFACT_VASE_02 },
		{ "BP_Treasure_Artifact_Proxy_box_02_a_C",					SOT::ActorType::TREASURE_ARTIFACT_BOX_01 },
		{ "BP_Treasure_Artifact_Proxy_DVR_Common_C",				SOT::ActorType::TREASURE_ARTIFACT_DVR_COMMON },
	};

	SOT *game()
	{
		return &_game;
	}

	bool SOT::init()
	{
		if (!this->_process.attach(access_mask)) return false;
		this->_process_base = static_cast<char *>(this->_process.get_module("SoTGame.exe")._base);
		if (!this->_process_base) return false;
		if (!sdk::init(&this->_process)) return false;
		return true;
	}

	hacklib::Process *SOT::process()
	{
		return &this->_process;
	}

	sdk::UWorld SOT::world()
	{
		return this->_process.read_memory<sdk::UWorld>(_process_base + offsets::GWorld);
	}

	void *SOT::names()
	{
		return this->_process.read_memory<void *>(_process_base + offsets::GNames);
	}

	sdk::Matrix3x3 create_view_matrix(const sdk::Vector3 &rotation)
	{
		sdk::Vector3 rotation_rads = rotation * (pi / 180);
		float sp = std::sinf(rotation_rads._x);
		float cp = std::cosf(rotation_rads._x);
		float sy = std::sinf(rotation_rads._y);
		float cy = std::cosf(rotation_rads._y);
		float sr = std::sinf(rotation_rads._z);
		float cr = std::cosf(rotation_rads._z);

		sdk::Matrix3x3 result{ };
		result[0][0] = cp * cy;
		result[0][1] = cp * sy;
		result[0][2] = sp;
		result[1][0] = sr * sp * cy - cr * sy;
		result[1][1] = sr * sp * sy + cr * cy;
		result[1][2] = -sr * cp;
		result[2][0] = -(cr * sp * cy + sr * sy);
		result[2][1] = cy * sr - cr * sp * sy;
		result[2][2] = cr * cp;
		return result;
	}

	//https://github.com/DougTheDruid/SoT-ESP-Framework/blob/main/helpers.py#L71-L161
	bool SOT::world_to_screen(const sdk::FMinimalViewInfo &camera_pov, sdk::Vector3 &position, sdk::Vector2 *out)
	{
		auto temp = create_view_matrix(camera_pov.rotation());
		const auto axis_x = sdk::Vector3{ temp[0][0], temp[0][1], temp[0][2] };
		const auto axis_y = sdk::Vector3{ temp[1][0], temp[1][1], temp[1][2] };
		const auto axis_z = sdk::Vector3{ temp[2][0], temp[2][1], temp[2][2] };
		const auto delta = position - camera_pov.location();
		const auto dot_products = sdk::Vector3{ delta.dot(axis_y), delta.dot(axis_z), delta.dot(axis_x) };
		if (dot_products._z < 0.1f) return false;
		const sdk::Vector2 screen_center{ 1920.0f / 2, 1080.0f / 2 };
		const auto magic = screen_center._x / std::tanf(camera_pov.fov() * pi / 360.0f) / dot_products._z;
		out->_x = screen_center._x + dot_products._x * magic;
		out->_y = screen_center._y - dot_products._y * magic;
		return true;
	}

	std::string SOT::get_actor_name(int id)
	{
		const auto chunk_offset = (id / 0x4000) * 8;
		const auto chunk_index_offset = (id % 0x4000) * 8;
		const auto name_chunk = this->_process.read_memory<void *>(static_cast<char *>(this->names()) + chunk_offset);
		const auto name_ptr = this->_process.read_memory<void *>(static_cast<char *>(name_chunk) + chunk_index_offset);
		char name_text[68];
		this->_process.read_memory(static_cast<char *>(name_ptr) + 0x10, name_text, sizeof(name_text));
		name_text[67] = '\0';
		return std::string{ name_text };
	}

	SOT::ActorType SOT::get_actor_type(int id)
	{
		if (this->_actor_id_map.count(id)) return this->_actor_id_map[id];
		const std::string name = this->get_actor_name(id);
		if (_actor_name_map.count(name)) this->_actor_id_map[id] = _actor_name_map.at(name);
		else this->_actor_id_map[id] = SOT::ActorType::UNKNOWN;
		return this->_actor_id_map[id];
	}
}