#pragma once
#include "base/Painter.hpp"
#include <box2d/box2d.h>
#include <iostream>

class World {
public:
	World() {}
	~World() {
		if (worldId.index1 != 0) {
			b2DestroyWorld(worldId);
		}
	}

	explicit World(b2Vec2 v) {
		worldDef = b2DefaultWorldDef();
		worldDef.gravity = v;
		worldId = b2CreateWorld(&worldDef);
	}

	void Init(b2Vec2 gravity) {
		if (worldId.index1 != 0) {
			b2DestroyWorld(worldId);
		}

		worldDef = b2DefaultWorldDef();
		worldDef.gravity = gravity;
		worldId = b2CreateWorld(&worldDef);
	}

    bool isValid(){
        return b2World_IsValid(worldId);
    }

	World(const World& w) = delete;
	World(World&& w) = delete;
	World& operator=(const World& other) = delete;
	World& operator=(World&& other) = delete;

	b2WorldDef& getDefinition() { return worldDef; }
	const b2WorldDef& getDefinition() const { return worldDef; }

	explicit operator b2WorldId() const { return worldId; }
	b2WorldId getId() { return worldId; }

private:
	b2WorldDef worldDef;
	b2WorldId worldId;
};
