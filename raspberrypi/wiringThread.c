#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>
#include <linux/input.h>
#include <softTone.h>

#define CDS 0
#define LED 1
#define SW 5
#define SPKR 6
#define TOTAL 32

int note[] = {
	391, 391, 440, 440, 391, 391, 329.63, 329.63,\
	391, 391, 329.63, 329.63, 293.66, 293.66, 293.66, 0,\
	391, 391, 440, 440, 391, 391, 329.63, 329.63,\
	391, 329.63, 293.66, 329.63, 261.63, 261.63, 261.63, 0
};

int light_fd, alarm_fd;
void *lightFunc(void *arg) {
	while (1) {
		// no light
		if (digitalRead(CDS) == LOW) {
			light_fd = 0;
			digitalWrite(LED, HIGH);
		} else { // light
			light_fd = 1;
			digitalWrite(LED, LOW);
		}
	}
	return NULL;
}

void *musicFunc(void *arg) {
	softToneCreate(SPKR);
	while (1) {
		int i = 0;
		while (alarm_fd && light_fd) {
			if (i == 32)
				i = 0;
			softToneWrite(SPKR, note[i]);
			delay(280);
			i++;
		}
		softToneWrite(SPKR, 0);
	}
	return NULL;
}

void *alarmFunc(void *arg) {
	while (1) {
		if (digitalRead(SW) == LOW) {
			if (alarm_fd)
				alarm_fd = 0;
			else alarm_fd = 1;
		}
		delay(10);
	}
	return NULL;
}

int main(int argc, char **argv) {
	wiringPiSetup();
	pinMode(CDS, INPUT);
	pinMode(LED, OUTPUT);
	pinMode(SW, INPUT);
	pinMode(SPKR, OUTPUT);

	pthread_t ptLight, ptMusic, ptAlarm;
	
	pthread_create(&ptLight, NULL, lightFunc, NULL);
	pthread_create(&ptMusic, NULL, musicFunc, NULL);
	pthread_create(&ptAlarm, NULL, alarmFunc, NULL);
	
	printf("start\n");
	while (1) {
	}
	return 0;
};
