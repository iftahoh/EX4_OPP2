#pragma once
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
const unsigned int TEXTURE_PATH_SIZE = 4;
const unsigned int SOUND_SIZE = 4;
const int MenuButtonSize = 3;
const std::string MenuInfo = ("Game Instructions:\n\n"
	"Welcome to our version of Xionx !\n\n"
	"- Use the Arrow keys to move your character\n"
	"- Press ESC to return to the main menu\n\n"
	"Good luck!");

const std::string RESOURCES_TEXTURE_PATH[TEXTURE_PATH_SIZE] = { "start", "info","exit", "MenuBackground"  };

const std::string RESOURCES_TEXTURE_NAME[TEXTURE_PATH_SIZE] = { "start" , "info", "exit",  "background" };




enum symbleObjects {
	PLAYER = '/',
	GUARD = '!',
	WALL = '#'
};

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};