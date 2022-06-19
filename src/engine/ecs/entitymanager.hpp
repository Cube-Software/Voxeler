/*
    Fractal Engine - OpenGL 3D Game Engine
    Created by CubeSoftware
    Revised for Voxeler

    -------------------------------
    Copyright (c) 2021-2022 CubeSoftware
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include "ecstypes.hpp"
#include "complist.hpp"
#include "basesystem.hpp"
#include "basecomp.hpp"
#include "compfactory.hpp"

namespace fr::ecs {
	class EntityManager {

	public:		
		~EntityManager() = default;
		EntityManager(const EntityManager&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;

		static EntityManager& Ref() {
			static EntityManager reference;
			return reference;
		}

		void Start() {
			for (auto& system : activeSystems) {
				system->Start();
			}
		}
		
		void Update() {
			for (auto& system : activeSystems) {
				system->Update();
			}
		}

		void Render() {
			for (auto& system : activeSystems) {
				system->Render();
			}
		}

		void ActivateRuntimeSystems() {
			for (auto& system : runtimeSystems) {
				system->Start();
				activeSystems.insert(system);
			}
		}

		void ActivateEditorSystems() {
			for (auto& system : editorSystems) {
				system->Start();
				activeSystems.insert(system);
			}
		}

		void DeactivateRuntimeSystems() {
			for (auto& system : runtimeSystems) {
				system->Stop();
				activeSystems.erase(system);				
			}
		}

		void DeactivateEditorSystems() {
			for (auto& system : editorSystems) {
				system->Stop();
				activeSystems.erase(system);
			}
		}

		const std::set<EntityID>& ActiveEntities() const { return activeEntities; }

		const EntityID AddNewEntity() {
			assert(entityCount < MAX_ENTITY_COUNT && "Entity count limit reached!");
			EntityID entity = availableEntities.front();
			activeEntities.insert(entity);
			availableEntities.pop();
			entityCount++;
			return entity;
		}

		void DestroyEntity(const EntityID entity) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID our of range!");
			entitySignatures.erase(entity);
			for (auto& array : componentArrays) { array->Erase(entity); }
			UpdateEntityTargetSystems(entity);
			entityCount = (entityCount > 0) ? entityCount-- : 0;
			availableEntities.push(entity);
			activeEntities.erase(entity);
		}

		template<typename T, typename... Args>
		void AddComponent(const EntityID entity, Args&&... args) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			assert(entitySignatures[entity].size() < MAX_COMP_COUNT && "Component count limit reached!");
			if (!IsCompListRegistered<T>()) { RegisterCompList<T>();}
			T component(std::forward<Args>(args)...);
			component.entityID = entity;
			entitySignatures[entity].insert(CompType<T>());
			GetCompList<T>()->Insert(&component);
			UpdateEntityTargetSystems(entity);
		}

		template<typename T>
		void AddComponent(const EntityID entity, T component) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			assert(entitySignatures[entity].size() < MAX_COMP_COUNT && "Component count limit reached!");
			if (!IsCompListRegistered<T>()) { RegisterCompList<T>(); }
			component.entityID = entity;
			GetCompList<T>()->Insert(&component);
			entitySignatures[entity].insert(CompType<T>());
			UpdateEntityTargetSystems(entity);
		}

		void AddComponent(const EntityID entity, const char* typeName) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			assert(entitySignatures[entity].size() < MAX_COMP_COUNT && "Component count limit reached!");
			const ComponentTypeID compType = CompFactory.GetTypeID(typeName);
			auto it = std::find_if(componentArrays.begin(), componentArrays.end(),
				[compType](const auto array) { return compType == array->GetDataType(); });
			assert(it != componentArrays.end() && "Component list not registered");
			auto component = CompFactory.CreateComponent(typeName);			
			component->entityID = entity;
			(*it)->Insert(component.get());
			entitySignatures[entity].insert(compType);
			UpdateEntityTargetSystems(entity);
		}
		
		template<typename T>
		void RemoveComponent(const EntityID entity) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			entitySignatures[entity].erase(CompType<T>());
			GetCompList<T>()->Erase(entity);
			UpdateEntityTargetSystems(entity);	
		}

		void RemoveComponent(const EntityID entity, const char* typeName) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");

			const ComponentTypeID compType = CompFactory.GetTypeID(typeName);
			auto it = std::find_if(componentArrays.begin(), componentArrays.end(),
				[compType](const auto array) { return compType == array->GetDataType(); });
			assert(it != componentArrays.end() && "Component list not registered");
			
			(*it)->Erase(entity);
			entitySignatures[entity].erase(compType);
			UpdateEntityTargetSystems(entity);
		}

		template<typename T>
		T& GetComponent(const EntityID entity) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			return  GetCompList<T>()->Get(entity);
		}

		template<typename T>
		const bool HasComponent(const EntityID entity) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range!");
			return (entitySignatures[entity].count(CompType<T>()) > 0);
		}

		template<typename T>
		void AddSystem() {
			auto system = std::make_shared<T>();		
			systems.insert(std::move(system));
		}

		template<typename T>
		void AddRuntimeSystem() {
			auto system = std::make_shared<T>();
			runtimeSystems.insert(std::move(system));
		}

		template<typename T>
		void AddEditorSystem() {
			auto system = std::make_shared<T>();
			editorSystems.insert(std::move(system));
		}

		template<typename T>
		void RegisterCompList() {
			ComponentTypeID compType = CompType<T>();
			auto it = std::find_if(componentArrays.begin(), componentArrays.end(), [compType](const auto array) { return compType == array->GetDataType(); });
			assert(it == componentArrays.end() && "Component list allready registered");
			componentArrays.insert(std::move(std::make_shared<CompList<T>>()));
		}

	private:
		EntityManager() : entityCount(0), componentArrays({}) {
			for (EntityID entity = 0; entity < MAX_ENTITY_COUNT; entity++) {
				availableEntities.push(entity);
			}
		}

		void UpdateEntityTargetSystems(EntityID entity) {
			for (auto system : systems) {
				PushEntityToSystem(entity, system);
			}

			for (auto system : editorSystems) {
				PushEntityToSystem(entity, system, false);
			}

			for (auto system : runtimeSystems) {
				PushEntityToSystem(entity, system, false);
			}
		}

		void PushEntityToSystem(EntityID entity, std::shared_ptr<BaseSystem>& system, bool activateSystem=true) {
			for (auto& compType : system->GetSignature()) {
				if (entitySignatures[entity].count(compType) == 0) {
					system->EraseEntity(entity);
					if (system->IsEmpty() && activeSystems.count(system) > 0) {
						activeSystems.erase(system);						
					}
					return;
				}
			}

			system->PushEntity(entity);
			if (activateSystem && activeSystems.count(system) == 0) {
				activeSystems.insert(system);
			}
		}

		template<typename T>
		bool IsCompListRegistered() {
			ComponentTypeID compType = CompType<T>();
			auto it = std::find_if(componentArrays.begin(), componentArrays.end(),
				[compType](const auto array) { return compType == array->GetDataType(); });
			return (it != componentArrays.end());
		}

		template<typename T>
		std::shared_ptr<CompList<T>> GetCompList() {
			ComponentTypeID compType = CompType<T>();
			auto it = std::find_if(componentArrays.begin(), componentArrays.end(), 
				[compType](const auto array) { return compType == array->GetDataType(); });
			assert(it != componentArrays.end() && "Component list not registered");
			return std::static_pointer_cast<CompList<T>>(*it);
		}

	private:
		EntityID entityCount;
		std::set<EntityID> activeEntities;
		std::queue<EntityID> availableEntities;
		
		// both run & editor
		std::set<std::shared_ptr<BaseSystem>> systems;
		// all active systems
		std::set<std::shared_ptr<BaseSystem>> activeSystems;
		// editor system
		std::set<std::shared_ptr<BaseSystem>> editorSystems;
		// runtime systems
		std::set<std::shared_ptr<BaseSystem>> runtimeSystems;

		std::set<std::shared_ptr<ICompList>> componentArrays;
		std::unordered_map<EntityID, Signature> entitySignatures;
	};

	static EntityManager& Manager = ECS::EntityManager::Ref();
}

#endif