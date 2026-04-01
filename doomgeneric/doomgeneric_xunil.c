#include "doomkeys.h"

#include "doomgeneric.h"

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

// static unsigned char convertToDoomKey(unsigned int key)
// {
// 	switch (key)
// 	{
//     case XK_Return:
// 		key = KEY_ENTER;
// 		break;
//     case XK_Escape:
// 		key = KEY_ESCAPE;
// 		break;
//     case XK_Left:
// 		key = KEY_LEFTARROW;
// 		break;
//     case XK_Right:
// 		key = KEY_RIGHTARROW;
// 		break;
//     case XK_Up:
// 		key = KEY_UPARROW;
// 		break;
//     case XK_Down:
// 		key = KEY_DOWNARROW;
// 		break;
//     case XK_Control_L:
//     case XK_Control_R:
// 		key = KEY_FIRE;
// 		break;
//     case XK_space:
// 		key = KEY_USE;
// 		break;
//     case XK_Shift_L:
//     case XK_Shift_R:
// 		key = KEY_RSHIFT;
// 		break;
// 	default:
// 		key = tolower(key);
// 		break;
// 	}

// 	return key;
// }

// static void addKeyToQueue(int pressed, unsigned int keyCode)
// {
// 	unsigned char key = convertToDoomKey(keyCode);

// 	unsigned short keyData = (pressed << 8) | key;

// 	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
// 	s_KeyQueueWriteIndex++;
// 	s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
// }

void DG_Init()
{

}


void DG_DrawFrame()
{

}

void DG_SleepMs(uint32_t ms)
{
    // usleep (ms * 1000);
}

uint32_t DG_GetTicksMs()
{
    // struct timeval  tp;
    // struct timezone tzp;

    // gettimeofday(&tp, &tzp);

    // return (tp.tv_sec * 1000) + (tp.tv_usec / 1000); /* return milliseconds */
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	// if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
	// {
	// 	//key queue is empty

	// 	return 0;
	// }
	// else
	// {
	// 	unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
	// 	s_KeyQueueReadIndex++;
	// 	s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

	// 	*pressed = keyData >> 8;
	// 	*doomKey = keyData & 0xFF;

	// 	return 1;
	// }
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
