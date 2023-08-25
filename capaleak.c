#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Usage: ./a.out /bin/bash\n");
		return -1;
	}

	printf("ls -l\n");
	system("ls -l");
	printf("ls -l /etc/zzz\n");
	system("ls -l /etc/zzz");

	printf("Opening file with setuid privilege...\n");
	int fd = open("/etc/zzz", "O_RDWR" && "O_APPEND");
	if (fd == -1) {
		printf("Couldn't open /etc/zzz\n");
		return -1;
	}

	printf("File opened, fd is %d\n", fd);

	printf("Disabling setuid privilege...\n");
	setuid(getuid());
	
	printf("Entering new shell process with opened fd...\n");
	printf("Try echo something to the fd,\n");
	printf("then check if /etc/zzz has changed, after exit.\n");
	system(argv[1]);

	return 0;
}
