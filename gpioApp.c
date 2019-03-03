#include "gpioDIO.h"
#include "stdio.h"
#include "unistd.h"
#include "gpioIOCounter.h"

int main() {
	int step=3;
	int sum = 0;
	while (step--) {

		if (HIGH == GPIORead(17)) {
			printf("Relay ON \n");
			GPIOWrite (27,LOW);
			sleep(3);
			GPIOWrite (27, HIGH);
			printf("Relay OFF \n");
			sum = gpioCount();
			printf("%d", sum);
		}
		sleep(1);

	}
	return 0;
}
