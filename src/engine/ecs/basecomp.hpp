#ifndef BASECOMP
#define BASECOMP

#include "ecstypes.hpp"

namespace fr::ecs {
	struct BaseComponent {
		BaseComponent() = default;
		~BaseComponent() = default;

		inline const EntityID GetID() const { return entityID; }

	private:
		EntityID entityID = -1;
		friend class EntityManager;
	};
}

#endif