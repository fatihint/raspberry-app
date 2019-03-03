#include "gpioIOCounter.h"
#include "gpioDIO.h"
#include "gpioTypes.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int gpioCount() {
	
	printf("0");
	int port = atoi(getenv("GPIO_IN"));
	printf("1");
	int value = GPIORead(port);
	printf("2");
	int count = atoi(getenv("GPIO_COUNT"));
	printf("3");

	if(!count) {
		count = value;
	} else {
		count += value;
	}

	setenv("GPIO_COUNT",count,0);

	return count;
}
