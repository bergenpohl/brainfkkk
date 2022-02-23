#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define OPERATIONS 2048

uint8_t	*loopForward(register uint8_t *args) {
	register uint16_t others = 0;
	
	args++;
	while (*args != ']' || others) {
		switch (*args) {
			case '[':
				others++;
				break;
			case ']':
				others--;
				break;
			default:
				break;
		}
		args++;
	}
	return (args);
}

uint8_t	*loopBackward(register uint8_t *args) {
	register uint16_t others = 0;
	
	args--;
	while (*args != '[' || others) {
		switch (*args) {
			case ']':
				others++;
				break;
			case '[':
				others--;
				break;
			default:
				break;
		}
		args--;
	}
	return (args);
}

void	bf(register uint8_t *args) {
	register uint8_t *ptr = (uint8_t *)malloc(sizeof(uint8_t) * OPERATIONS);
	register uint8_t *t = ptr;
	register uint16_t i = 0;
	
	while (i < OPERATIONS) {
		ptr[i] = 0;
		++i;
	}
	while (*args) {
		switch (*args) {
			case '>':
				ptr++;
				break;
			case '<':
				ptr--;
				break;
			case '+':
				(*ptr)++;
				break;
			case '-':
				(*ptr)--;
				break;
			case '.':
				write(1, ptr, 1);
				break;
			case '[':
				if (!(*ptr)) args = loopForward(args);
				break;
			case ']':
				if (*ptr) args = loopBackward(args);
				break;
			default:
				break;
		}
		args++;
	}
	free(t);
}

int	main(int argc, char **argv) {
	if (argc == 2) bf((uint8_t *)(argv[1]));
	return (0);
}
