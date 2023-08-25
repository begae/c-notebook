#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Usage: ./a.out filename\n");
		return -1;
	}

	char* id_input = malloc(20);
	char* pw_input = malloc(20);
	char* fline = malloc(150);
	char* sysout = malloc(150);

	printf("Enter id: ");
	char* input_ok = fgets(id_input, 20, stdin);
	int id_len = strlen(id_input) - 1;
	
	FILE* file = fopen(argv[1], "r");
	if (!file) return -1;

	char* read_ok = fgets(fline, 150, file);
 	
	bool found = false;
	while (read_ok) {
		if (strncmp(fline, id_input, id_len) == 0) {
			if (*(fline + id_len) == '$') {
					found = true;
					break;
			}
		}
		read_ok = fgets(fline, 150, file);
	}

	printf("Enter pw: ");
	input_ok = fgets(pw_input, 20, stdin);
	int pw_len = strlen(pw_input) - 1;
	
	if (!found) {
		printf("Something went wrong.\n");
		return 1;
	}

	char command[100] = "mkpasswd -m sha-512 -S ";
	strncat(command, fline + id_len + 3, 16);
	strcat(command, " \0");
	strncat(command, pw_input, pw_len);

	FILE* pipe = popen(command, "r");
	if (!pipe) return -1;

	char* pipe_ok = fgets(sysout, 150, pipe);
	int result = strcmp(sysout + 30, fline + id_len + 30);

	free(id_input);
	free(pw_input);
	free(sysout);
	free(fline);
	
	fclose(file);
	pclose(pipe);
	
	if (result == 0) {
		printf("Welcome back.\n");
		return 0;
	}

	printf("Something went wrong.\n");
	return 1;
}
