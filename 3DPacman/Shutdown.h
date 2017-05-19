#ifndef SHUTDOWN_H
#define SHUTDOWN_H

void OnShutdown()
{
	// release the textures on the graphics card
	go_skybox.cleanup();

	ground.cleanup();
	wall.cleanup();
	myDot.cleanup();
	myDonald.cleanup();
	myDonald2.cleanup();
	myDonald3.cleanup();
	myDonald4.cleanup();
	myDonaldClose.cleanup();
	screenPic.cleanup();
}

#endif