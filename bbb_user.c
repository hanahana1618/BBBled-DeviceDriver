#include "bbb_user.h"

//THIS SHIT DONT WORK EVEN IN A MILLION YEARS

//user space program for the BBB LED device driver
int main(void) { //just because CS50 was very annoying about this

	int fhandler;
	int retWrite;
	char buff[BUFF_LEN];
	
	//accessing the LKM
	fhandler = open("/dev/BBB_dev", O_RDWR);

	if (fhandler < 0) {
		printf("Unable to open loadable kernel module BBB_dev. Closing program\n");
		return -1;
	}
	else {
		printf("LKM successfully opened\n");
	}

	while (1) {
		printf("Enter quit to exit, or string to send to the device driver: ");
		scanf("%[^\n]%*c", buff);
		if (strcmp(buff, "quit") == 0) {
			break;
		}
		retWrite = write(fhandler, buff, strlen(buff));
		if (retWrite < 0) {
			printf("Unable to send string to device driver BBB_dev");
			return -2;
		}

		printf("Watch science happen now!\n");
	}

	close(fhandler);

	//program ran correctly
	return 0;
}
