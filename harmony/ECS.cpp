#include "ECS.h"

harmony::Entity harmony::Scene::CreateEntity()
{
	auto flecs_entity = mWorld.entity();
	return Entity(flecs_entity);
}

harmony::String harmony::System::GetEntityIdAsString(Entity& e)
{
	// TODO: Need sprintf
	// Utils::ToString(static_cast<uint64>(e.mFlecsHandle.id()));
	return ""; 
}

uint64 harmony::System::GetEntityIdFromString(const String& entity)
{
	return std::stoull(entity.c_str());
}
