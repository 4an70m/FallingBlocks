#ifndef __DEFENITIONS_H__
#define __DEFENITIONS_H__

#define TO_PLAY_SCENE_TRANSITION_TIME 	1.0f
#define SPLASH_SCREEN_TRANSITION_LENGTH 2.0f
#define SPLASH_SCREEN_APPEAR_TIME 		2.0f
#define COVER_APPEARANCE_SPEED 			0.5f
#define NUMBER_OF_BLOCKS				7
#define NUMBER_OF_BONUS					5

#define FALLING_BLOCK_GENERATION_TIME	0.50f
#define MIN_FALLING_TIME				10.0f
#define MAX_FALLING_TIME				60.0f

#define MIN_BLOCK_GENERATION_TIME		0.5f
#define MAX_BLOCK_GENERATION_TIME		2.5f

#define MIN_BONUS_TIME					50
#define MAX_BONUS_TIME					150
#define MIN_BONUS_BLOCK_HEALTH			15
#define BONUS_BLOCK_HEALTH_STEP			300
#define POINTS							10

//intro comicses
#define INTRO_PAGE_1 			"SplashIntro/COVER1.png"
#define INTRO_PAGE_2 			"SplashIntro/COVER2.png"
#define INTRO_PAGE_3 			"SplashIntro/COVER3.png"
#define SPLASH_SCREEN			"SplashIntro/Splash.png"
//sprites
#define BOTO_SPRITE_PATH 		"Sprites/Robot.png"
#define COIN					"Sprites/Coin.png"

//blocks
#define BRICK_I 				"Sprites/Bricks/BRICK-I.png"
#define BRICK_J 				"Sprites/Bricks/BRICK-J.png"
#define BRICK_L 				"Sprites/Bricks/BRICK-L.png"
#define BRICK_O 				"Sprites/Bricks/BRICK-O.png"
#define BRICK_S 				"Sprites/Bricks/BRICK-S.png"
#define BRICK_T 				"Sprites/Bricks/BRICK-T.png"
#define BRICK_Z 				"Sprites/Bricks/BRICK-Z.png"
#define MEGABLOCK 				"Sprites/Bricks/BRICK-BIG.png"
#define BONUS_BLOCKS 			"Sprites/Box.png"

#define TAP_PATH				"UI/Tap.png"
#define PAUSE_BUTTON			"UI/PAUSE_BUTTON.png"
#define PAUSE_BUTTON_PRESSED	"UI/PAUSE_BUTTON_PRESSED.png"

//bonus
#define BONUS_FGRAVITY 			"Sprites/Bonus/bonus_gravity.png"
#define BONUS_SPEED 			"Sprites/Bonus/bonus_speed.png"
#define BONUS_SGRAVITY			"Sprites/Bonus/bonus_gravity_slow.png"
#define BONUS_SBOTO 			"Sprites/Bonus/bonus_boto_size.png"
#define BONUS_X2 				"Sprites/Bonus/bonus_points_x2.png"

//bitmasks for collisions
#define BOTO_BITMASK 			0x01
#define BLOCKS_BITMASK 			0x02
#define GROUND_BITMASK 			0x03
#define COIN_BITMASK 			0x05
#define MEGABLOCK_BITMASK		0x04
#define BONUS_BITMASK			0x04

//backgrounds
#define GAME_SCENE_BACKGROUND 	"Backgrounds/game_scene_background.png"
#define GAME_SCENE_GROUND		"Backgrounds/grounds.png"
#define TITLE					"Backgrounds/title.png"
//pause
#define PAUSE_BACKGROUND		"Backgrounds/Pause.png"
#define GAMEOVER_BACKGROUND		"Backgrounds/GameOver.png"
#define BACK_BUTTON				"UI/Pause/pause_back.png"
#define BACK_BUTTON_PRESSED		"UI/Pause/pause_back_pressed.png"
#define MENU_BUTTON				"UI/Pause/pause_menu.png"
#define MENU_BUTTON_PRESSED		"UI/Pause/pause_menu_pressed.png"
#define SOUND_BUTTON			"UI/Pause/pause_music.png"
#define SOUND_BUTTON_PRESSED	"UI/Pause/pause_music_pressed.png"
#define RETRY_BUTTON			"UI/Pause/gameover_retry.png"
#define RETRY_BUTTON_PRESSED	"UI/Pause/gameover_retry_pressed.png"
//UI
#define SKIP_BUTTON 			"UI/SKIP_BUTTON.png"
#define SKIP_BUTTON_PRESSED 	"UI/SKIP_BUTTON_PRESSED.png"

//json
#define BRICK_BODIES			"Json/BRICK_BODIES.json"

//animations
//main menu
#define BOTO_MM_PLIST 			"Sprites/Animations/MainMenu/MainMenuBoto0.plist"
#define BOTO_MM_PNG 			"Sprites/Animations/MainMenu/MainMenuBoto0.png"
#define BOTO_MM_JSON 			"Sprites/Animations/MainMenu/MainMenuBoto.ExportJson"
//moving
#define	BOTO_MOBING_PNG			"Sprites/Animations/MovingBoto/MobingBoto0.png"
#define	BOTO_MOBING_PLIST		"Sprites/Animations/MovingBoto/MobingBoto0.plist"
#define	BOTO_MOBING_JSON		"Sprites/Animations/MovingBoto/MobingBoto.ExportJson"

//zOreders
#define BOTO_ZORDER				2
#define BLOCK_ZORDER			1
#define GROUND_ZORDER			3
#define BACKGROUND_ZORDER		0
#define BUTTONS_ZORDER			5
#define COINS_ZORDER			4
#define PARTICLE_ZORDER			6
#define UI_ZORDER				7

//Opacities
#define OPACITY_225				225
#define OPACITY_178				178
#define OPACITY_127				127

//scales
#define SCALE_07				0.7f
#define SCALE_05				0.5f
#define SCALE_03				0.3f

//music
#define BACKGROUND_MUSIC		"Music/background_music.mp3"
#define COIN_PICKUP				"Music/Effects/coin_pickup.wav"
#define MEGABLOCK_HIT			"Music/Effects/megablock_hit.wav"
#define MEGABLOCK_HIT2			"Music/Effects/megablock_hit2.wav"
#define MEGABLOCK_HIT3			"Music/Effects/megablock_hit3.wav"
#define MEGABLOCK_DESTROYED		"Music/Effects/megablock_destroyed.wav"
#define BLOCK_BREAK				"Music/Effects/block_destroyed.wav"
#define BONUS_PICKUP			"Music/Effects/bonus_pickup.wav"

#endif // __DEFENITIONS_H__
