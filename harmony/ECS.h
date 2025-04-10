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

	class System
	{
	public:
		const str_hash mSystemHash;
		System(const str_hash& systemHash) : mSystemHash(systemHash) {}
		System(const String& systemName) : mSystemHash(HashString(systemName)) {}

		/// <summary>
		/// Initialize callbacks and operations 
		/// for component data which interacts with this sytem
		/// </summary>
		/// <param name="s"></param>
		virtual void Init(Scene& s) = 0;

		/// <summary>
		/// Remove callbacks
		/// </summary>
		/// <param name="s"></param>
		virtual void Cleanup(Scene& s) = 0;
		
		/// <summary>
		/// Return JSON representing the system state
		/// </summary>
		/// <param name="s">Scene to serialize</param>
		/// <returns>JSON representing the systems serializable state for all entities</returns>
		virtual Json Serialize(Scene& s) = 0;

		/// <summary>
		/// Given some json, deserialize and create appropriate components for a 
		/// collection of entities
		/// </summary>
		/// <param name="s"></param>
		/// <param name="sceneJson"></param>
		virtual void Deserialize(Scene& s, Json sceneJson) = 0;


		/// <summary>
		/// Serialize all components on a given entity for this systems
		/// managed components
		/// </summary>
		/// <param name="s"></param>
		/// <param name="e"></param>
		/// <returns></returns>
		virtual Json SerializeEntity(Scene& s, Entity& e) = 0;

		/// <summary>
		/// Given some json, deserialize and create appropriate components for a 
		/// single entity
		/// </summary>
		/// <param name="s">Scene to deserialize into</param>
		/// <param name="e">Entity to deserialize into</param>
		/// <param name="sceneJson">JSON to be deserialized</param>
		virtual void DeserializeEntity(Scene& s, Entity& e, Json sceneJson) = 0;

		static String GetEntityIdAsString(Entity& e);
		static uint64 GetEntityIdFromString(const String& entity);
	};



}