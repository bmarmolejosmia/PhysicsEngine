#include <irrlicht.h>

#include "Physics/World/PhysicsWorld.hpp"
#include "Physics/Visuals/DebugPhysicsRenderer.hpp"

using namespace irr;
using namespace physics;

int main()
{
    // ------------------------------------------------------------
    // Irrlicht setup
    // ------------------------------------------------------------
    IrrlichtDevice* device = createDevice(
        video::EDT_OPENGL,
        core::dimension2du(1280, 720));

    if (!device)
    {
        return 1;
    }

    device->setWindowCaption(L"Physics Engine - Phase C Test");

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* sceneManager = device->getSceneManager();

    scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNodeFPS();
    camera->setPosition(Vector3(0.0f, 2.0f, -6.0f));
    device->getCursorControl()->setVisible(false);

    // ------------------------------------------------------------
    // Physics setup
    // ------------------------------------------------------------
    PhysicsWorld physicsWorld;

    // Ground (static)
    Rigidbody groundBody;
    groundBody.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    groundBody.SetMass(0.0f);

    // Falling sphere (dynamic)
    Rigidbody fallingBody;
    fallingBody.SetPosition(Vector3(0.0f, 5.0f, 0.0f));
    fallingBody.SetMass(1.0f);
 
    physicsWorld.AddRigidbody(&groundBody);
    physicsWorld.AddRigidbody(&fallingBody);

    // ------------------------------------------------------------
    // Colliders
    // ------------------------------------------------------------
    Collider groundCollider(&groundBody, ShapeType::Box);
    groundCollider.Box().halfSize = Vector3(5.0f, 0.5f, 5.0f);

    Collider fallingCollider(&fallingBody, ShapeType::Sphere);
    fallingCollider.Sphere().radius = 0.5f;

    physicsWorld.AddCollider(&groundCollider);
    physicsWorld.AddCollider(&fallingCollider);

    // ------------------------------------------------------------
    // Debug renderer
    // ------------------------------------------------------------
    DebugPhysicsRenderer debugRenderer(sceneManager);
    debugRenderer.AddRigidbody(&groundBody);
    debugRenderer.AddRigidbody(&fallingBody);
    debugRenderer.AddCollider(&groundCollider);
    debugRenderer.AddCollider(&fallingCollider);

    // ------------------------------------------------------------
    // Timing
    // ------------------------------------------------------------
    u32 previousTime = device->getTimer()->getTime();

    // ------------------------------------------------------------
    // Main loop
    // ------------------------------------------------------------
    while (device->run())
    {
        const u32 currentTime = device->getTimer()->getTime();
        const float deltaTime =
            (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        // Single authoritative physics call
        physicsWorld.StepSimulation(deltaTime);

        debugRenderer.Sync();

        driver->beginScene(true, true, video::SColor(255, 30, 30, 30));
        sceneManager->drawAll();
        driver->endScene();
    }

    device->drop();
    return 0;
}



/*
#include <irrlicht.h>

int main()
{
	irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2du(1024, 768), 32, false, false, false);

	if (!device) { return 1; }

	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();

	while (device->run())
	{
		driver->beginScene(true, true, irr::video::SColor(255, 125, 125, 255));
		smgr->drawAll();
		driver->endScene();
	}

	device->drop();
	return 0;
}
*/