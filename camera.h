#ifdef __cplusplus
extern "C"
{
#endif

#include "videodev.h"
#include <string.h>
typedef unsigned short      WORD;      /* WORD (无符号短整型) */
typedef unsigned long       DWORD;     /* DOUBLE WORD (无符号长整形)*/


void *CreateCameraContext();
void DestoryCameraCotext(void* v4l2ctx);

int OpenCamera(void* v4l2ctx, char *pname);
void CloseCamera(void* v4l2ctx);
void getV4l2FrameParam(void* v4l2ctx);
int StartCamera(void* v4l2ctx, int *width, int *height, int Fps);
void StopCamera(void* v4l2ctx);

int CameraGetOneFrame(void*  v4l2ctx, struct v4l2_buffer *buffer);
void CameraReturnOneFame(void* v4l2ctx, struct v4l2_buffer *buffer);

#ifdef __cplusplus
}
#endif
