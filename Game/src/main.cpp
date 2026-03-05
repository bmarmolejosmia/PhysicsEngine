#include <irrlicht.h>

#include "Physics/World/PhysicsWorld.hpp"
#include "Physics/Rigidbody/Rigidbody.hpp"
#include "Physics/Collision/Collider.hpp"
#include "Physics/Collision/Broadphase.hpp"
#include "Physics/Collision/Narrowphase.hpp"
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

    device->setWindowCaption(L"Physics Engine Debug View");

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* sceneManager = device->getSceneManager();

    irr::scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNodeFPS();
    camera->setPosition(Vector3(0, 1, -3));
    device->getCursorControl()->setVisible(false);

    // ------------------------------------------------------------
    // Physics setup
    // ------------------------------------------------------------
    PhysicsWorld physicsWorld;

    Rigidbody groundBody;
    groundBody.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    groundBody.SetMass(0.0f); // static

    Rigidbody fallingBody;
    fallingBody.SetPosition(Vector3(0.0f, 5.0f, 0.0f));
    fallingBody.SetMass(1.0f);

    physicsWorld.AddRigidbody(&groundBody);
    physicsWorld.AddRigidbody(&fallingBody);

    Collider groundCollider(&groundBody, ShapeType::Box);
    groundCollider.Box().halfSize = Vector3(5.0f, 0.5f, 5.0f);

    Collider fallingCollider(&fallingBody, ShapeType::Sphere);
    fallingCollider.Sphere().radius = 0.5f;

    std::vector<Collider*> colliders;
    colliders.push_back(&groundCollider);
    colliders.push_back(&fallingCollider);

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

        physicsWorld.StepSimulation(deltaTime);

        // Broadphase + Narrowphase (for now just to exercise the pipeline)
        std::vector<CollisionPair> collisionPairs;
        Broadphase::ComputeCollisionPairs(colliders, collisionPairs);

        std::vector<Contact> contacts;
        Narrowphase::GenerateContacts(collisionPairs, contacts);

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