#include <lib.h>

static char *path = "/lib/a";

int main() {
	/*int fd = open(path, O_RDONLY);
	if (fd < 0) {
		user_panic("failed to open %s, return value: %d", path, fd);
	}*/
	char buf[16]="hello world!";
	//int len = read(fd, buf, sizeof(buf) - 1);
	//buf[len] = '\0';
	debugf("File content: hello world!\n");
	//close(fd);
	return 0;
}
