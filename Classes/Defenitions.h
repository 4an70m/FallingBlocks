#ifndef __DEFENITIONS_H__
#define __DEFENITIONS_H__

#define SPLASH_SCREEN_TRANSITION_LENGTH 1.0f
#define SPLASH_SCREEN_APPEAR_TIME 		1.0f
#define COVER_APPEARANCE_SPEED 			0.5f
#define NUMBER_OF_BLOCKS				8
#define BLOCK_GENERATION_TIME			0.50f
#define FALLING_BLOCK_GENERATION_TIME	0.5f
#define MIN_FALLING_TIME				10.0f
#define MAX_FALLING_TIME				60.0f

//intro comicses
#define INTRO_PAGE_1 			"SplashIntro/COVER1.png"
#define INTRO_PAGE_2 			"SplashIntro/COVER2.png"
#define INTRO_PAGE_3 			"SplashIntro/COVER3.png"

//sprites
#define BOTO_SPRITE_PATH 		"Sprites/Robot.png"
#define TEST_BLOCK 				"Sprites/Box.png"
#define COIN					"Sprites/Coin.png"

//blocks
#define BRICK_I 				"Sprites/Bricks/BRICK-I.png"
#define BRICK_J 				"Sprites/Bricks/BRICK-J.png"
#define BRICK_L 				"Sprites/Bricks/BRICK-L.png"
#define BRICK_O 				"Sprites/Bricks/BRICK-O.png"
#define BRICK_S 				"Sprites/Bricks/BRICK-S.png"
#define BRICK_T 				"Sprites/Bricks/BRICK-T.png"
#define BRICK_Z 				"Sprites/Bricks/BRICK-Z.png"
//ToDO: add bonus blocks

//bitmasks for collisions
#define BOTO_BITMASK 			0x01
#define BLOCKS_BITMASK 			0x02
#define GROUND_BITMASK 			0x03
#define COIN_BITMASK 			0x04

//backgrounds
#define GAME_SCENE_BACKGROUND 	"Backgrounds/game_scene_background.png"
#define GAME_SCENE_GROUND		"Backgrounds/grounds.png"

//UI
#define LEFT_BUTTON 			"UI/Controls/left_button.png"
#define LEFT_BUTTON_PRESSED 	"UI/Controls/left_button_pressed.png"
#define RIGHT_BUTTON 			"UI/Controls/right_button.png"
#define RIGHT_BUTTON_PRESSED 	"UI/Controls/right_button_pressed.png"
#define JUMP_BUTTON 			"UI/Controls/jump_button.png"
#define JUMP_BUTTON_PRESSED 	"UI/Controls/jump_button_pressed.png"
#define SKIP_BUTTON 			"UI/SKIP_BUTTON.png"
#define SKIP_BUTTON_PRESSED 	"UI/SKIP_BUTTON_PRESSED.png"

//json
#define BRICK_BODIES			"Json/BRICK_BODIES.json"

//animations
//main menu
#define BOTO_MM_PLIST 			"Sprites/Animations/MainMenu/MainMenuBoto0.plist"
#define BOTO_MM_PNG 			"Sprites/Animations/MainMenu/MainMenuBoto0.png"
#define BOTO_MM_JSON 			"Sprites/Animations/MainMenu/MainMenuBoto.ExportJson"

#endif // __DEFENITIONS_H__
