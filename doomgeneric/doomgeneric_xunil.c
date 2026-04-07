#include "doomkeys.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "doomgeneric.h"

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};

int gettimeofday(struct timeval *tv, struct timezone *tz);
int draw_buffer(uint32_t *buffer, uint32_t width, uint32_t height);
useconds_t sleep_ms(uint32_t ms);

static unsigned char convertToDoomKey(unsigned int key)
{
	// switch (key)
	// {
 //    case XK_Return:
	// 	key = KEY_ENTER;
	// 	break;
 //    case XK_Escape:
	// 	key = KEY_ESCAPE;
	// 	break;
 //    case XK_Left:
	// 	key = KEY_LEFTARROW;
	// 	break;
 //    case XK_Right:
	// 	key = KEY_RIGHTARROW;
	// 	break;
 //    case XK_Up:
	// 	key = KEY_UPARROW;
	// 	break;
 //    case XK_Down:
	// 	key = KEY_DOWNARROW;
	// 	break;
 //    case XK_Control_L:
 //    case XK_Control_R:
	// 	key = KEY_FIRE;
	// 	break;
 //    case XK_space:
	// 	key = KEY_USE;
	// 	break;
 //    case XK_Shift_L:
 //    case XK_Shift_R:
	// 	key = KEY_RSHIFT;
	// 	break;
	// default:
	// 	key = tolower(key);
	// 	break;
	// }

	return key;
}

static void addKeyToQueue(int pressed, unsigned int keyCode)
{
	unsigned char key = convertToDoomKey(keyCode);

	unsigned short keyData = (pressed << 8) | key;

	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
	s_KeyQueueWriteIndex++;
	s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

void DG_Init()
{
    memset(s_KeyQueue, 0, KEYQUEUE_SIZE * sizeof(unsigned short));
}


void DG_DrawFrame()
{
    draw_buffer(DG_ScreenBuffer, DOOMGENERIC_RESX, DOOMGENERIC_RESY);
}

void DG_SleepMs(uint32_t ms)
{
    sleep_ms (ms);
}

uint32_t DG_GetTicksMs()
{
    struct timeval  tp;
    struct timezone tzp;

    gettimeofday(&tp, &tzp);

    return (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
	{
		//key queue is empty

		return 0;
	}
	else
	{
		unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
		s_KeyQueueReadIndex++;
		s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

		*pressed = keyData >> 8;
		*doomKey = keyData & 0xFF;

		return 1;
	}
}

void DG_SetWindowTitle(const char * title)
{

}

int main(int argc, char **argv)
{
    doomgeneric_Create(argc, argv);

    while(1)
    {
      doomgeneric_Tick();
    }

    return 0;
}
