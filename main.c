#include "camera.h"
#include "V4L2.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define __DEBUG__

void SaveOneFram(void* v4l2ctx,int times)
{
	FILE* fp =NULL;
	V4L2_CONTEXT* V4l2_Context = (V4L2_CONTEXT*) v4l2ctx;
	char filename[40];
	int cnt = V4l2_Context->mBufferCnt;
	int length = V4l2_Context->mMapMem.length;
	sprintf(filename, "/mnt/sdcard/steve/raw1_%d.jpg",times);
	fp = fopen(filename, "wb+");
	if (fp > 0) {
		fwrite((char*)((V4L2_CONTEXT*)v4l2ctx)->mMapMem.mem[V4l2_Context->mBufferCnt], 1,length,fp);
		fclose(fp);
		printf("Write success mjpeg data to %s",filename);
	} else {
		printf("Create %s failed(%d, %s)",filename,fp, strerror(errno));
	}
}
void main()
{
	int ret = 0;
	void * v4l2ctx = NULL;
	int height = 720;
	int width = 1280;
	int fps = 30;
	int times = 0;
	unsigned char *Frame_Buffer;      
	
	Frame_Buffer = (unsigned char *) malloc(sizeof(unsigned char)*height*width*3);

	v4l2ctx = CreateCameraContext();
#ifdef __DEBUG__
	printf("CrateCameractx finish!!\n");
#endif
	struct v4l2_buffer buff;


	memset(&buff, 0, sizeof(struct v4l2_buffer));
#ifdef __DEBUG__
	printf("Before OPEN Camera in main!\n");
#endif
	
	ret = OpenCamera(v4l2ctx, "/dev/video5");
	if (0 != ret)
	{
		perror("Can't open Camera!\n");
	}
#ifdef __DEBUG__
	printf("After OPEN Camera in main!\n");
#endif
	StartCamera(v4l2ctx, &width, &height, fps);
#ifdef __DEBUG__
	printf("After startcamera in main!\n");
#endif
   while(times != 20){
	CameraGetOneFrame(v4l2ctx, &buff);
#ifdef __DEBUG__
	printf("After CameraGetOneFram in main!\n");
#endif
	//int cnt = ((V4L2_CONTEXT*)v4l2ctx)->mBufferCnt;
	//int length = ((V4L2_CONTEXT*)v4l2ctx)->mMapMem.length;
	//memcpy(Jpeg_Buffer, ((V4L2_CONTEXT*)v4l2ctx)->mMapMem.mem[cnt], length);
#ifdef __DEBUG__
	//printf("the buff legth is %d !!\nthe buffcnt is %d!!\n",length, cnt);
#endif

	SaveOneFram(v4l2ctx,times);
	CameraReturnOneFame(v4l2ctx, &buff);
	times++;
}
#ifdef __DEBUG__
	printf("Before StopCamera in main!\n");
#endif
	StopCamera(v4l2ctx);
#ifdef __DEBUG__
	printf("Before CloseCameraDevice in main!\n");
#endif
	CloseCamera(v4l2ctx);
	DestoryCameraCotext(v4l2ctx);

	v4l2ctx = NULL;
	free(Frame_Buffer);
	//free(Jpeg_Buffer);

//	return 0;

}
