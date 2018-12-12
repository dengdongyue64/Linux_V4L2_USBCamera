#include "camera.h"
#include "V4L2.h"
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define NUM_BUFFERNUM 4
#define BMP "/home/plg/image.bmp"
#define YUV "/home/plg/image_yuv.yuv"
unsigned char TESTBUF[240 * 320*4];
#define __DEBUG__

void *CreateCameraContext()
{
	void* v4l2_context = CreamV4l2Context(); 
	return v4l2_context;
}
void DestoryCameraCotext(void* v4l2ctx)
{
	DestoryV4l2Context(v4l2ctx);
}

int OpenCamera(void* v4l2ctx, char *pname)
{
	return OpenCameraDevice(v4l2ctx, pname);
}

void CloseCamera(void* v4l2ctx)
{
	CloseCameraDevice(v4l2ctx);
}

int StartCamera(void* v4l2ctx, int *width, int *height, int Fps)
{
	int ret = -1;
	int buffernum = NUM_BUFFERNUM;
	struct v4l2_streamparm params;
	params.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	params.parm.capture.capturemode = V4L2_MODE_VIDEO;
	params.parm.capture.timeperframe.denominator = Fps;
	params.parm.capture.timeperframe.numerator = 1;

	//setV4l2FrameParam(v4l2ctx, params);
	getV4l2FrameParam(v4l2ctx);
	setV4l2DeviceParam(v4l2ctx, width, height);

	V4l2ReqBuffer(v4l2ctx, &buffernum);

	V4l2MapBuffer(v4l2ctx);

	StarStreaming(v4l2ctx);

	return 0;
}
void StopCamera(void* v4l2ctx)
{
	StopStream(v4l2ctx);
#ifdef __DEBUG__
	printf("had stopstream ! \n");
#endif
	V4l2StopMapBuffer(v4l2ctx);
}

int CameraGetOneFrame(void*  v4l2ctx, struct v4l2_buffer *buffer)
{
	int ret;

	struct v4l2_buffer buff;
	memset(&buff, 0, sizeof(struct v4l2_buffer));

	ret = GetFrame(v4l2ctx, &buff);
	if (-1 == ret)
	{
		perror("it's can't get frame in camera.c CameraGetOneFramne!");
		return ret;
	}

	memcpy(buffer, &buff, sizeof(struct v4l2_buffer));
	return 0;
}


void CameraReturnOneFame(void* v4l2ctx, struct v4l2_buffer *buffer)
{
	ReturnFrame(v4l2ctx, buffer);
}







