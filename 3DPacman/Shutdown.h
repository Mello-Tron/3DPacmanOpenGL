#ifndef SHUTDOWN_H
#define SHUTDOWN_H

void OnShutdown()
{
	// release the textures on the graphics card
	go_skybox.cleanup();

	//Edit: Patrick H. 4/17
	//floor1.cleanup();
	//for (int i = 0; i < walls.size(); i++) {
	//	walls[i]->cleanup();
	//}
	ground.cleanup();
	wall.cleanup();
	myTree.cleanup();
	myDonald.cleanup();
	myDonaldClose.cleanup();
}

#endif