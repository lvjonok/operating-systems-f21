#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
	char* keyboard_path = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
	FILE* keyboard_events = fopen(keyboard_path, "r");
	struct input_event input;
	while (1) {
		fread(&input, sizeof(struct input_event), 1,  keyboard_events);
		// we want to handle events on keyboard
		if (input.type != EV_KEY) continue;
		
		// input.value now contains the key we pressed

		if (input.value	== 0) {
			printf("RELEASED %#x (%d)\n", input.code, input.code);
		} else if (input.value == 1) {
			printf("PRESSED %#x (%d)\n", input.code, input.code);
		}
	}
}
