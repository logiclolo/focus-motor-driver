
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "typedef.h"
#include "focusmotor.h"

#define ZOOM_MOTOR 	1
#define FOCUS_MOTOR	2
#define MAX_ZOOM	766
#define MAX_FOCUS	1849
#define SLOW_SPEED	3 
#define MEDIUM_SPEED 	2
#define FAST_SPEED 	1

int main(int argc, char *argv[])
{
	int iRet, fd, zoom_fd, focus_fd, iDevice;
	DWORD dwDevType, dwWalkSteps, dwMotorSpeed, dwPosition, dwCurrentZoom=0, dwCurrentFocus=0;
	SDWORD sdwWalkSteps;
	BOOL bEnd = FALSE;
	struct timeval tv;
    
	focus_fd = open("/dev/focusmotor", O_WRONLY);
    	if (focus_fd < 0) {
        	printf("Failed to open focus device\n");
        	return -1;
    	}
	zoom_fd = open("/dev/zoommotor", O_WRONLY);
    	if (zoom_fd < 0) {
        	printf("Failed to open zoom device\n");
        	return -1;
    	}

	ioctl(zoom_fd, MOTOR_SET_BACKWARD);
	ioctl(zoom_fd, MOTOR_WALK_STEPS_BLOCK, MAX_ZOOM);
	//ioctl(focus_fd, MOTOR_SET_BACKWARD);
	//ioctl(focus_fd, MOTOR_WALK_STEPS_BLOCK, MAX_FOCUS);
	//sleep(5);	
		printf("\n===================== Motor Test ====================== \n");
/*	ioctl(focus_fd, MOTOR_SET_FORWARD);
	iRet = ioctl(focus_fd, MOTOR_WALK_STEPS_BLOCK, 1800);
	printf("iRet:%d\n", iRet);
	ioctl(focus_fd, MOTOR_SET_BACKWARD);
	iRet = ioctl(focus_fd, MOTOR_WALK_STEPS_BLOCK, 1500);
	printf("iRet:%d\n", iRet);
*/
	ioctl(zoom_fd, MOTOR_SET_FORWARD);
	iRet = ioctl(zoom_fd, MOTOR_WALK_STEPS_BLOCK, 800);
	printf("iRet:%d\n", iRet);
	ioctl(zoom_fd, MOTOR_SET_BACKWARD);
	iRet = ioctl(zoom_fd, MOTOR_WALK_STEPS_BLOCK, 800);
	printf("iRet:%d\n", iRet);

	sleep(1);
	//printf("Current Zoom:%d  Focus:%d iRet:%d\n", dwCurrentZoom, dwCurrentFocus, iRet);
/*	
	do
	{
		printf("\n===================== Motor Test ====================== \n");
		printf("[Device zoom:1 focus:2][Position zoom:0~%d focus:0~%d]\n",MAX_ZOOM, MAX_FOCUS);
		scanf("%d %d",&iDevice, &dwPosition);

		switch (iDevice)
		{
			case ZOOM_MOTOR:
				fd = zoom_fd;
				dwPosition = (dwPosition <= MAX_ZOOM)?dwPosition : MAX_ZOOM; 
				sdwWalkSteps = dwPosition - dwCurrentZoom;
				dwCurrentZoom = dwPosition;
				break;
			case FOCUS_MOTOR:
				fd = focus_fd;
				dwPosition = (dwPosition <= MAX_FOCUS)?dwPosition : MAX_FOCUS;
				sdwWalkSteps = dwPosition - dwCurrentFocus;
				dwCurrentFocus = dwPosition;
				break;
			default:
				return 0;
		}
		
		ioctl(fd, MOTOR_SET_SPEED, MEDIUM_SPEED);
		printf("steps=%d\n",sdwWalkSteps);
		if ( sdwWalkSteps >= 0 )
		{
			printf(">>>>>>>> Forward !\n");	
			ioctl(fd, MOTOR_SET_FORWARD);
		}
		else
		{
			printf(">>>>>>>> Backward !\n");	
			ioctl(fd, MOTOR_SET_BACKWARD);
		}
		iRet = ioctl(fd, MOTOR_WALK_STEPS_BLOCK, abs(sdwWalkSteps));
		printf("Current Zoom:%d  Focus:%d iRet:%d\n", dwCurrentZoom, dwCurrentFocus, iRet);
		sleep(1);
		
	}while(!bEnd);
*/
	close(fd);
	return 0;
}
