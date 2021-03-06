
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "typedef.h"
#include "focusmotor.h"
//#include "fzlensmotor.h"
#define ZOOM_MOTOR      1
#define FOCUS_MOTOR             2
#define MAX_ZOOM                        1300 
#define MAX_FOCUS                       3300 

#if defined _TI_DM365
DWORD g_dwMotorSpeed[4] = {0x10000, 0x11940, 0x23280, 0x34BC0};
#elif defined _MOZART
DWORD g_dwMotorSpeed[4] = {1000000, 333333, 666666, 999999}; // 10ms, 3ms, 6ms, 9ms
#endif 

void PrintHelp(char *pcProgramName)
{
	printf("Usage:\n"
		"%s WalkSteps(-w 1~2000) OverRun?(-o)\n\n", pcProgramName);
}

int main(int argc, char *argv[])
{
    //unsigned char buf[MOTOR_BUF_LEN];
	int fd, iRet, i, ch;
	int zoom_fd, focus_fd;
	int iDevice;
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
	ioctl(zoom_fd, MOTOR_WALK_STEPS, MAX_ZOOM);
	ioctl(focus_fd, MOTOR_SET_BACKWARD);
	ioctl(focus_fd, MOTOR_WALK_STEPS, MAX_FOCUS);
	/*
	while ((ch = getopt(argc, argv, "w:o")) != -1)
	{
		switch(ch)
		{	
		case 'w':
			dwWalkSteps = atoi(optarg);
			printf(">>> Walk Steps:%d \n", dwWalkSteps);
			break;
		case 'o':
			bOverRun = TRUE;
			break;
		default:
			PrintHelp(argv[0]);
			return -1;
			break;
		}
	}
	if (argc < 3)
	{
		PrintHelp(argv[0]);
		return -1;
	}
	*/
	do
	{
		//ioctl(fd, MOTOR_TURN_OFF);
		printf("\n===================== Motor Test ====================== \n");
		printf("[Device zoom:1 focus:2][Position zoom:0~%d focus:0~%d]\n",MAX_ZOOM,MAX_FOCUS);
		scanf("%d %d",&iDevice,&dwPosition);

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
		
		ioctl(fd, MOTOR_SET_SPEED, 0x1D4C0);
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
		iRet = ioctl(fd, MOTOR_WALK_STEPS, abs(sdwWalkSteps));
		//ioctl(fd, MOTOR_TURN_OFF);
		printf("Current Zoom:%d  Focus:%d\n", dwCurrentZoom, dwCurrentFocus);
		//sleep(2);

		/*
		printf("===================== Motor Speed Test ====================== \n");
		printf(">>>>>>>> Slow !\n");
		ioctl(fd, MOTOR_SET_SPEED, g_dwMotorSpeed[3]);
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps);
		sleep(1);
		printf(">>>>>>>> Medium !\n");
		ioctl(fd, MOTOR_SET_SPEED, g_dwMotorSpeed[2]);
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps);
		sleep(1);
		printf(">>>>>>>> Fast !\n");
		ioctl(fd, MOTOR_SET_SPEED, g_dwMotorSpeed[1]);
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps);
		sleep(1);
		printf(">>>>>>>> Medium !\n");
		ioctl(fd, MOTOR_SET_SPEED, g_dwMotorSpeed[2]);
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps);
		sleep(1);
		printf(">>>>>>>> Slow !\n");
		ioctl(fd, MOTOR_SET_SPEED, g_dwMotorSpeed[3]);
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps);
		sleep(2);
		printf("===================== Motor Walk Step Test ====================== \n");
		printf(">>>>>>>> Step Test !!\n");
		ioctl(fd, MOTOR_SET_SPEED, g_dwMotorSpeed[1]);
		ioctl(fd, MOTOR_SET_FORWARD);
		printf(">>>>>>>> Short !\n");
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps * 5);
		ioctl(fd, MOTOR_SET_BACKWARD);
		printf(">>>>>>>> Medium !\n");
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps * 10);
		ioctl(fd, MOTOR_SET_FORWARD);
		printf(">>>>>>>> Long !\n");
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps * 5);
		printf(">>>>>>>> Step Test !!\n");
		printf("===================== Motor Stop Test ====================== \n");
		sleep(2);
		ioctl(fd, MOTOR_SET_BACKWARD);
		printf(">>>>>>>> Start !\n");
		iRet = ioctl(fd, MOTOR_WALK_STEPS, dwWalkSteps * 10);
		sleep(1);
		ioctl(fd, MOTOR_WALK_STEPS_CLR); 
		printf(">>>>>>>> Stop !\n");
		printf("===================== Motor System Info ====================== \n");
		ioctl(fd, MOTOR_SYS_LOG_LIST, 1);
		printf("===================== Motor Testing End ====================== \n");
		sleep(3);
		*/
	}while(!bEnd);

	close(fd);
	return 0;
}
