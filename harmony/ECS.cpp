#include "ECS.h"

harmony::Entity harmony::Scene::CreateEntity()
{
	auto flecs_entity = mWorld.entity();
	return Entity(flecs_entity);
}
