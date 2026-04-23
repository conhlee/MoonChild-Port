#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#define _IN_MAIN
#include "framewrk/frm_int.hpp"

#include "moonchild/mc.hpp"
#include "moonchild/globals.hpp"
#include "moonchild/prefs.hpp"
#include "wii_audio.h"
#include "wii_game.h"
#include "wii_movie_player.h"
#include "wii_util.h"

static void* xfb = NULL;
static GXRModeObj* rmode = NULL;

extern s32 __STM_Init();
extern void __exception_closeall();
extern s32 __IOS_ShutdownSubsystems();

MoviePlayer *moviePlayer = nullptr;

#define GAME_WIDTH 640
#define GAME_HEIGHT 480

uint8_t *pixelBuffer = nullptr;
int pixelBufferPitch = 0;

bool poll_pad()
{
	WPAD_ScanPads();

	u32 buttonsDown = WPAD_ButtonsDown(0);
	u32 buttonsUp = WPAD_ButtonsUp(0);

	if (buttonsDown & WPAD_BUTTON_HOME)
		return true;

	if (buttonsDown & WPAD_BUTTON_RIGHT)
        framework_EventHandle(FW_KEYDOWN, (int)prefs->upkey);
    if (buttonsUp & WPAD_BUTTON_RIGHT)
        framework_EventHandle(FW_KEYUP, (int)prefs->upkey);
    
    if (buttonsDown & WPAD_BUTTON_LEFT)
        framework_EventHandle(FW_KEYDOWN, (int)prefs->downkey);
    if (buttonsUp & WPAD_BUTTON_LEFT)
        framework_EventHandle(FW_KEYUP, (int)prefs->downkey);
    
    if (buttonsDown & WPAD_BUTTON_DOWN)
        framework_EventHandle(FW_KEYDOWN, (int)prefs->leftkey);
    if (buttonsUp & WPAD_BUTTON_DOWN)
        framework_EventHandle(FW_KEYUP, (int)prefs->leftkey);
    
    if (buttonsDown & WPAD_BUTTON_UP)
        framework_EventHandle(FW_KEYDOWN, (int)prefs->rightkey);
    if (buttonsUp & WPAD_BUTTON_UP)
        framework_EventHandle(FW_KEYUP, (int)prefs->rightkey);

    if (buttonsDown & WPAD_BUTTON_2)
        framework_EventHandle(FW_KEYDOWN, (int)prefs->shootkey);
    if (buttonsUp & WPAD_BUTTON_2)
        framework_EventHandle(FW_KEYUP, (int)prefs->shootkey);
	
	return false;
}

void blit_screen()
{
	VIDEO_WaitVSync();
}

void run_game_tick()
{
	if (moviePlayer && moviePlayer->isPlaying())
		moviePlayer->update(pixelBuffer, GAME_WIDTH, GAME_HEIGHT, pixelBufferPitch);
    else
		gameTick(pixelBuffer, GAME_WIDTH, GAME_HEIGHT, pixelBufferPitch);
}

int main(int argc, char **argv)
{
	VIDEO_Init();
	WPAD_Init();

	rmode = VIDEO_GetPreferredMode(NULL);
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_BLACK);
	VIDEO_SetBlack(false);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if (rmode->viTVMode & VI_NON_INTERLACE)
		VIDEO_WaitVSync();
	
	__STM_Init();
	//SYS_STDIO_Report(true);

	pixelBufferPitch = GAME_WIDTH * 4;
	pixelBuffer = new uint8_t[pixelBufferPitch * GAME_HEIGHT];
	memset(pixelBuffer, 0, pixelBufferPitch * GAME_HEIGHT);

	moviePlayer = new MoviePlayer();

	initMoonChild(pixelBuffer, GAME_WIDTH, GAME_HEIGHT, moviePlayer);
	while (1)
	{
		if (poll_pad())
			break;
		run_game_tick();
		blit_screen();
	}

	return 0;
}
