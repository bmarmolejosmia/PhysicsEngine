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