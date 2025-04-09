#pragma once
#include "STL.h"
#include "Json.h"
#define FLECS_USE_OS_ALLOC
#include "flecs.h"
#include "flecs/addons/cpp/flecs.hpp"

namespace harmony
{
	class Entity
	{
	public:
		flecs::entity mFlecsHandle;
		Entity(const flecs::entity& e) : mFlecsHandle(e) {}

		void Destroy() { mFlecsHandle.destruct(); }

		template<typename _Ty, typename... Args>
		_Ty& AddComponent(Args &&...args)
		{
			mFlecsHandle.add<_Ty>(eastl::forward<Args>(args) ...);
			return *mFlecsHandle.get_mut<_Ty>();
		}

		template<typename _Ty>
		_Ty& GetComponent()
		{
			return *mFlecsHandle.get_mut<_Ty>();
		}
	};

	class Scene
	{
	public:
		flecs::world	mWorld;
		String			mName;

		Scene() : mName("Default Scene Name") {};
		Scene(const String& sceneName) : mName(sceneName) {}

		Entity	CreateEntity();
	};

	/// <summary>
	/// One system -> many scenes.
	/// </summary>
	class System
	{
	public:
		const str_hash mSystemHash;
		System(const str_hash& systemHash) : mSystemHash(systemHash) {}
		System(const String& systemName) : mSystemHash(HashString(systemName)) {}

		virtual void Init(Scene& s) = 0;
		virtual void Update(Scene& s) = 0;
		virtual void Render(Scene& s) = 0;
		virtual void Cleanup(Scene& s) = 0;
		
		virtual Json Serialize(Scene& s) = 0;
		virtual void Deserialize(Scene& s, Json sceneJson) = 0;

		virtual Json SerializeEntity(Scene& s, Entity& e) = 0;
		virtual void DeserializeEntity(Scene& s, Entity& e, Json sceneJson) = 0;

		static String GetEntityIdAsString(Entity& e);
		static uint64 GetEntityIdFromString(const String& entity);
	};



}