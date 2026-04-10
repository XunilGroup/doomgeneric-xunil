#include "doomkeys.h"
#include "../../../libxunil/include/keyboard.h"
#include <complex.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "doomgeneric.h"

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static xunil_kbd_event_t s_kbdevent_queue[8];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};

int gettimeofday(struct timeval *tv, struct timezone *tz);
int draw_buffer(uint32_t *buffer, uint32_t width, uint32_t height);
useconds_t sleep_ms(uint32_t ms);

static unsigned char convertToDoomKey(unsigned int key, uint32_t unicode)
{
	switch (key)
	{
        case RETURN:
    		key = KEY_ENTER;
    		break;
        case ESCAPE:
    		key = KEY_ESCAPE;
    		break;
        case ARROW_LEFT:
    		key = KEY_LEFTARROW;
    		break;
        case ARROW_RIGHT:
    		key = KEY_RIGHTARROW;
    		break;
        case ARROW_UP:
    		key = KEY_UPARROW;
    		break;
        case ARROW_DOWN:
    		key = KEY_DOWNARROW;
    		break;
        case L_CONTROL:
        case R_CONTROL:
    		key = KEY_FIRE;
    		break;
        case SPACEBAR:
    		key = KEY_USE;
    		break;
        case L_SHIFT:
        case R_SHIFT:
    		key = KEY_RSHIFT;
    		break;
    	default:
            key = unicode;
    		break;
	}

	return key;
}

static void addKeyToQueue(int pressed, unsigned int keyCode, uint32_t unicode)
{
	unsigned char key = convertToDoomKey(keyCode, unicode);

	unsigned short keyData = (pressed << 8) | key;

	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
	s_KeyQueueWriteIndex++;
	s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

void DG_Init()
{
    memset(s_KeyQueue, 0, KEYQUEUE_SIZE * sizeof(unsigned short));
}

void fill_kbd_buffer() {
    int to_read;

    to_read = kbd_read(s_kbdevent_queue, 8);

    if (to_read <= 0) {
        return;
    }

    xunil_kbd_event_t current_event;

    for (int i = 0; i < to_read; i++) {
        current_event = s_kbdevent_queue[i];
        addKeyToQueue(current_event.state, current_event.key, current_event.unicode);
    }
}

void DG_DrawFrame()
{
    draw_buffer(DG_ScreenBuffer, DOOMGENERIC_RESX, DOOMGENERIC_RESY);
    fill_kbd_buffer();
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
