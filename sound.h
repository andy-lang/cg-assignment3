/**********************************************************************
 * Self contained, super dirty, sound playback functionality.
 * Include from anywhere and call playSound(pathToSound)
 *
 * @author 	: Riley Chase
 * @id 		: a1647198
 * @created 	: 2015-05-22
 * @project 	: CG Assignment 3
**********************************************************************/

#ifndef SOUNDPLAYER
#define SOUNDPLAYER

#include <stdlib.h>
#include <string>


/*
 * Play a sound file to the default system speakers.
 * Adapted from Tutorial 4 example.
 *
 * @author 		: Riley Chase
 * @id 			: a1647198
 * @created 		: 2015-05-22
 *
 * @param1 std::string 	: Path to the sound file to be played.
 */
void playSound(std::string path)
{
	std::string execStr = "aplay " + path + " &";
	system(execStr.c_str());
}

#endif // SOUNDPLAYER
