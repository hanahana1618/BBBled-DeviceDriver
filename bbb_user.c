#include "bbb_user.h"

//THIS SHIT DONT WORK EVEN IN A MILLION YEARS
//convert argv[] into a string
//missing fread implementation

//user space program for the BBB LED device driver
int main(void) { //just because CS50 was very annoying about this

	//making sure that the user gives sentence to the device driver
	int fhandler;
	int retWrite;
	char buff[BUFF_LEN];

	//check the arguments are fine
	
	//accessing the LKM
	//FILE *fhandler;
	fhandler = open("/dev/bbb_dev", O_RDWR);

	if (fhandler < 0) {
		printf("Unable to open loadable kernel module BBB_dev. Closing program\n");
		return -2;
	}
	else {
		printf("LKM successfully opened\n");
	}

	printf("Enter string to send to the device driver: ");
	scanf("%[^\n]%*c", buff);
	retWrite = write(fhandler, buff, strlen(buff));
	if (retWrite < 0) {
		printf("Unable to send string to device driver BBB_dev");
		return -3;
	}


	//program ran correctly
	return 0;
}