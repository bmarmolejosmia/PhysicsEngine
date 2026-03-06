/*
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

    scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNodeFPS(0,100.0f,0.1f);
    camera->setPosition(Vector3(0.0f, 5.0f, -6.0f));
    //device->getCursorControl()->setVisible(false);

    scene::ISceneNode* floor = sceneManager->addCubeSceneNode();
    floor->setPosition(Vector3(0.0f, 0.0f, 0.0f));
    floor->setScale(Vector3(50.0f, 1.0f, 50.0f));
    floor->setMaterialFlag(video::EMF_WIREFRAME, true);

    // ------------------------------------------------------------
    // Physics setup
    // ------------------------------------------------------------
    PhysicsWorld physicsWorld;

    // Ground (static)
    
    Rigidbody groundBody;
    groundBody.SetPosition(Vector3(floor->getPosition()));
    groundBody.SetMass(0.0f);

    // Falling sphere (dynamic)
    Rigidbody fallingBody;
    fallingBody.SetPosition(Vector3(0.0f, 5.0f, 0.0f));
    fallingBody.SetMass(1.0f);

    Rigidbody cameraBody;
    cameraBody.SetPosition(camera->getPosition());
    cameraBody.SetMass(1.0f);

    physicsWorld.AddRigidbody(&groundBody);
    physicsWorld.AddRigidbody(&fallingBody);
    physicsWorld.AddRigidbody(&cameraBody);

    // ------------------------------------------------------------
    // Colliders
    // ------------------------------------------------------------
    Collider groundCollider(&groundBody, ShapeType::Box);
    groundCollider.Box().halfSize = Vector3(floor->getScale().X / 2, floor->getScale().Y / 2, floor->getScale().Z / 2);

    Collider fallingCollider(&fallingBody, ShapeType::Sphere);
    fallingCollider.Sphere().radius = 0.5f;

    Collider cameraCollider(&cameraBody, ShapeType::Sphere);
    cameraCollider.Sphere().radius = 1.0f;

    physicsWorld.AddCollider(&groundCollider);
    physicsWorld.AddCollider(&fallingCollider);
    physicsWorld.AddCollider(&cameraCollider);

    // ------------------------------------------------------------
    // Debug renderer
    // ------------------------------------------------------------
    DebugPhysicsRenderer debugRenderer(sceneManager);
    debugRenderer.AddRigidbody(&groundBody, floor);
    debugRenderer.AddRigidbody(&fallingBody);
    debugRenderer.AddRigidbody(&cameraBody, camera);
    debugRenderer.AddCollider(&groundCollider);
    debugRenderer.AddCollider(&fallingCollider);
    debugRenderer.AddCollider(&cameraCollider);

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
*/



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
/*
*/