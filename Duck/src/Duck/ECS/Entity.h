#pragma once

//component files
#include "Duck/Audio/AudioComponent.h"
#include "Duck/Ghost/JiangShi.h"

//standard lib
#include <stdint.h>
#include <bitset>
#include <queue>
#include <array>
#include <map>
#include <set>
#include <memory>
#include <any>
#include <cassert>



namespace Duck
{

	using Entity = uint32_t;
	using ComponentType = uint8_t;

	const Entity MAX_ENTITIES = 5000;
	const ComponentType MAX_COMPONENTS = 32;

	using Signature = std::bitset<MAX_COMPONENTS>;

	//events
	using EventId = std::uint32_t;
	using ParamId = std::uint32_t;

	class EntityManager
	{
	public:
		EntityManager()
		{
			for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				m_AvailableEntities.push(entity);
			}
		}

		Entity CreateEntity()
		{
			Entity id = m_AvailableEntities.front();
			m_AvailableEntities.pop();
			++mLivingEntityCount;

			return id;
		}

		void DestroyEntity(Entity entity)
		{
			m_Signatures[entity].reset();
			m_AvailableEntities.push(entity);
			--mLivingEntityCount;
		}

		void SetSignature(Entity entity, Signature signature)
		{
			m_Signatures[entity] = signature;
		}

		Signature GetSignature(Entity entity)
		{
			return m_Signatures[entity];
		}

	private:
		std::queue<Entity> m_AvailableEntities{};
		std::array<Signature, MAX_ENTITIES> m_Signatures{};
		uint32_t mLivingEntityCount{};
	};


	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};


	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:

		void InsertData(Entity entity, T component)
		{
			assert(m_EntityToIndexMap.find(entity) == m_EntityToIndexMap.end() && "Component added more than once.");

			// Put new entry at end
			size_t newIndex = m_Size;
			m_EntityToIndexMap[entity] = newIndex;
			m_IndexToEntityMap[newIndex] = entity;
			m_ComponentArray[newIndex] = component;
			++m_Size;
		}

		void RemoveData(Entity entity)
		{
			assert(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end() && "Removing non-existent component.");

			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
			size_t indexOfLastElement = m_Size - 1;
			m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

			// Update map to point to moved spot
			Entity entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
			m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			m_EntityToIndexMap.erase(entity);
			m_IndexToEntityMap.erase(indexOfLastElement);

			--m_Size;
		}

		T& GetData(Entity entity)
		{
			return m_ComponentArray[m_EntityToIndexMap[entity]];
		}

		void EntityDestroyed(Entity entity) override
		{
			if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			{
				RemoveData(entity);
			}
		}

	private:
		std::array<T, MAX_ENTITIES> m_ComponentArray{};
		std::map<Entity, size_t> m_EntityToIndexMap{};
		std::map<size_t, Entity> m_IndexToEntityMap{};
		size_t m_Size{0};
	};


	class ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();

			m_ComponentTypes.insert({ typeName, m_NextComponentType });
			m_ComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			++m_NextComponentType;
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(T).name();

			return m_ComponentTypes[typeName];
		}

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			GetComponentArray<T>()->RemoveData(entity);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			return GetComponentArray<T>()->GetData(entity);
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : m_ComponentArrays)
			{
				auto const& component = pair.second;

				component->EntityDestroyed(entity);
			}
		}

	private:
		std::map<const char*, ComponentType> m_ComponentTypes{};
		std::map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays{};
		ComponentType m_NextComponentType{};


		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
		}
	};

	class System
	{
	public:
		std::set<Entity> m_Entities;
	};

	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			auto system = std::make_shared<T>();
			m_Systems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			m_Signatures.insert({ typeName, signature });
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : m_Systems)
			{
				auto const& system = pair.second;


				system->m_Entities.erase(entity);
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			for (auto const& pair : m_Systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = m_Signatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->m_Entities.insert(entity);
				}
				else
				{
					system->m_Entities.erase(entity);
				}
			}
		}

	private:
		std::map<const char*, Signature> m_Signatures{};
		std::map<const char*, std::shared_ptr<System>> m_Systems{};
	};

	class Coordinator
	{
	public:
		void Init()
		{
			m_ComponentManager = std::make_unique<ComponentManager>();
			m_EntityManager = std::make_unique<EntityManager>();
			m_SystemManager = std::make_unique<SystemManager>();
		}


		// Entity methods
		Entity CreateEntity()
		{
			return m_EntityManager->CreateEntity();
		}

		void DestroyEntity(Entity entity)
		{
			m_EntityManager->DestroyEntity(entity);

			m_ComponentManager->EntityDestroyed(entity);

			m_SystemManager->EntityDestroyed(entity);
		}


		// Component methods
		template<typename T>
		void RegisterComponent()
		{
			m_ComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			m_ComponentManager->AddComponent<T>(entity, component);

			auto signature = m_EntityManager->GetSignature(entity);
			signature.set(m_ComponentManager->GetComponentType<T>(), true);
			m_EntityManager->SetSignature(entity, signature);

			m_SystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			m_ComponentManager->RemoveComponent<T>(entity);

			auto signature = m_EntityManager->GetSignature(entity);
			signature.set(m_ComponentManager->GetComponentType<T>(), false);
			m_EntityManager->SetSignature(entity, signature);

			m_SystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& getComponent(Entity entity)
		{
			return m_ComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return m_ComponentManager->GetComponentType<T>();
		}


		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return m_SystemManager->RegisterSystem<T>();
		}

		template<typename T>
		std::unique_ptr<T> GetSystems()
		{
			return m_SystemManager;
		}

		template<typename T>
		void SetSystemSignature(Signature signature)
		{
			m_SystemManager->SetSignature<T>(signature);
		}

	private:
		std::unique_ptr<ComponentManager> m_ComponentManager;
		std::unique_ptr<EntityManager> m_EntityManager;
		std::unique_ptr<SystemManager> m_SystemManager;
	};


	extern DUCK_API Coordinator ecs;
}