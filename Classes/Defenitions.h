#ifndef __DEFENITIONS_H__
#define __DEFENITIONS_H__

#define SPLASH_SCREEN_TRANSITION_LENGTH 1.0f
#define SPLASH_SCREEN_APPEAR_TIME 		1.0f
#define COVER_APPEARANCE_SPEED 			0.5f
#define NUMBER_OF_BLOCKS				8
#define BLOCK_GENERATION_TIME			1.0f

//intro comicses
#define INTRO_PAGE_1 			"SplashIntro/COVER1.png"
#define INTRO_PAGE_2 			"SplashIntro/COVER2.png"
#define INTRO_PAGE_3 			"SplashIntro/COVER3.png"

//sprites
#define BOTO_SPRITE_PATH 		"Sprites/Robot.png"
#define TEST_BLOCK 				"Sprites/Box.png"

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

//backgrounds
#define GAME_SCENE_BACKGROUND 	"Backgrounds/game_scene_background.png"

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

#endif // __DEFENITIONS_H__
