#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define PRESSED (1)
#define RELEASED (0)

struct shortcut {
	int* sequence;
	int* states;
	int len;	
	char* value;
	char* hint;
};

int main() {
	struct shortcut* cap = (struct shortcut*)malloc(sizeof(struct shortcut) * 1);
	cap->len = 3;
	cap->sequence = (int*)malloc(sizeof(int) * cap->len);
	cap->sequence[0] = KEY_C;
	cap->sequence[1] = KEY_A;
	cap->sequence[2] = KEY_P;
	cap->states = (int*)calloc(0, sizeof(int) * cap->len);
	cap->value = "Get some cappuccino!";
	cap->hint = "cap";

	struct shortcut* pe = (struct shortcut*)malloc(sizeof(struct shortcut) * 1);
	pe->len = 2;
	pe->sequence = (int*)malloc(sizeof(int) * pe->len);
	pe->sequence[0] = KEY_P;
	pe->sequence[1] = KEY_E;
	pe->states = (int*)calloc(0, sizeof(int) * pe->len);
	pe->value = "I passed the Exam!";
	pe->hint = "pe";

	struct shortcut* lev = (struct shortcut*)malloc(sizeof(struct shortcut) * 1);
	lev->len = 3;
	lev->sequence = (int*)malloc(sizeof(int) * lev->len);
	lev->sequence[0] = KEY_L;
	lev->sequence[1] = KEY_E;
	lev->sequence[2] = KEY_V;
	lev->states = (int*)calloc(0, sizeof(int) * lev->len);
	lev->value = "Hello, my name is Lev Kozlov";
	lev->hint = "lev";

	struct shortcut** list_of_shortcuts = malloc(sizeof(struct shortcut*) * 3);
	list_of_shortcuts[0] = cap;
	list_of_shortcuts[1] = pe;
	list_of_shortcuts[2] = lev;

	int AMOUNT_OF_SHORTCUTS = 3;
	printf("Available shortcuts \n");
	for (int i = 0; i < AMOUNT_OF_SHORTCUTS; i++) {
		printf("%s -> %s\n", list_of_shortcuts[i]->hint, list_of_shortcuts[i]->value);
	}

	char* keyboard_path = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
	FILE* keyboard_events = fopen(keyboard_path, "r");
	struct input_event input;
	while (1) {
		fread(&input, sizeof(struct input_event), 1,  keyboard_events);
		// we want to handle events on keyboard
		if (input.type != EV_KEY) continue;

		// we have to use only pressed and released
		if (!(input.value == PRESSED || input.value == RELEASED)) continue;
		
		// input.value now contains the key we pressed
		//
		if (input.value == 2) continue;

		for (int i = 0; i < AMOUNT_OF_SHORTCUTS; i++) {
			struct shortcut* cur_shortcut = list_of_shortcuts[i];
			for (int seq_idx = 0; seq_idx < cur_shortcut->len; seq_idx++) {
				if (cur_shortcut->sequence[seq_idx] == input.code) {
					if (input.value == PRESSED && (seq_idx == 0 || cur_shortcut->states[seq_idx - 1] == PRESSED))
						cur_shortcut->states[seq_idx] = input.value;

					// if we released this key, we broke the streak
					// and release the state of previous keys
					if (input.value == RELEASED) {
						for (int j = seq_idx; j >= 0; j--) {
							cur_shortcut->states[j] = RELEASED;
						}
					}
				}
			}
			if (cur_shortcut->states[cur_shortcut->len - 1] == PRESSED) {
				printf("\n\n%s\n\n", cur_shortcut->value);
				// we completed the shortcut -> release the states
				for (int seq_idx = 0; seq_idx < cur_shortcut->len; seq_idx++) {
					cur_shortcut->states[seq_idx] = RELEASED;
				}
			}
		}
	}
}
