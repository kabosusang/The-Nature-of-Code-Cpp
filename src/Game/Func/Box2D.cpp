#include "Game/Func/Box2D.hpp"
#include "base/Painter.hpp"
#include "box2d/box2d.h"
#include "box2d/collision.h"
#include "box2d/types.h"

// 只声明变量，不初始化
b2WorldDef worldDef;
b2WorldId worldId;

b2BodyDef groundBodyDef;
b2BodyId groundId;

b2Polygon groundBox;
b2ShapeDef groundShapeDef;

// 动态物体定义
b2BodyDef dynamicBodyDef;
b2BodyId dynamicBodyId;
b2Polygon dynamicBox;
b2ShapeDef dynamicShapeDef;

void LiveWorld_Init() {
	auto& canvas = Canvas::getInstance();

	// 1. 先初始化世界定义
	worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, -10.0f };

	// 2. 创建世界
	worldId = b2CreateWorld(&worldDef);

	// 3. 初始化地面物体定义
	groundBodyDef = b2DefaultBodyDef();
	groundBox = b2MakeBox(50.0f, 10.0f);
	groundShapeDef = b2DefaultShapeDef();

	// 4. 创建地面（在屏幕底部）
	b2Vec2 groundWorldPos = coordPixelsToWorld({
			canvas.GetWindowW() / 2.0f,
			canvas.GetWindowH() - 50.0f // 距离底部50像素
	});
	groundBodyDef.position = groundWorldPos;

	// 5. 先创建地面物体
	groundId = b2CreateBody(worldId, &groundBodyDef);

	// 6. 然后添加形状
	b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

	// 7. 初始化动态物体定义
	dynamicBodyDef = b2DefaultBodyDef();
	dynamicBox = b2MakeBox(5.0f, 5.0f);
	dynamicShapeDef = b2DefaultShapeDef();

	// 8. 创建动态物体（在屏幕中心）
	b2Vec2 centerWorldPos = coordPixelsToWorld({ canvas.GetWindowW() / 2.0f,
			canvas.GetWindowH() / 2.0f });

	dynamicBodyDef.position = centerWorldPos;
	dynamicBodyDef.type = b2_dynamicBody; // 设置为动态物体

	// 9. 先创建动态物体
	dynamicBodyId = b2CreateBody(worldId, &dynamicBodyDef);

	// 10. 设置物理属性（重要！动态物体必须有密度）
	dynamicShapeDef.density = 1.0f; // 设置密度
	//dynamicShapeDef.friction = 0.3f; // 设置摩擦系数

	// 11. 然后添加形状
	b2CreatePolygonShape(dynamicBodyId, &dynamicShapeDef, &dynamicBox);
}
void LiveWorld() {
	auto& painter = Painter::getInstance();
	// 物理世界步进（每秒60帧）
	float timeStep = 1.0f / 60.0f;
	b2World_Step(worldId, timeStep, 8);

	// 获取动态物体的位置并转换为屏幕坐标
	b2Transform dynamicTransform = b2Body_GetTransform(dynamicBodyId);
	b2Vec2 screenPos = coordWorldToPixels(dynamicTransform.p);

	// 这里可以添加渲染代码
	painter.DrawRect(screenPos.x, screenPos.y, 5, 5, White);
}
