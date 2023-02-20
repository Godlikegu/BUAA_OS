#include <blib.h>

size_t strlen(const char *s) {
	size_t cnt = 0;
	while (*s){
		cnt++;
		s++;
	}
	return cnt;
}

char *strcpy(char *dst, const char *src) {
	char *res = dst;
	while (*src) {
		*dst++ = *src++;
	}
	*dst = '\0';
	return res;
}

char *strncpy(char *dst, const char *src, size_t n) {
	char *res = dst;
	while (*src && n--) {
		*dst++ = *src++;
	}
	*dst = '\0';
	return res;
}

char *strcat(char *dst, const char *src) {
	char *res = dst;
	while (*res){
		res++;
	}
	while (*src){
		*res++ = *src++;
	}
	*res = '\0';
	return dst;

}

int strcmp(const char *s1, const char *s2) {
	while (*s1 || *s2){
		if (*s1 != *s2) {
			return *s1 - *s2;
		}
		if (*s1 == 0) {
			break;
		}
		s1++;
		s2++;
	}
	return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
	while (n--) {
		if (*s1 != *s2) {
			return *s1 - *s2;
		}
		if (*s1 == 0) {
			break;
		}
		s1++;
		s2++;
	}
	return 0;
}

void *memset(void *s, int c, size_t n) {
	int *ss = (int *)s;
	for (int i = 0; i < n; i++) {
		ss[i] = c;
	}
	return s;
}

void *memcpy(void *out, const void *in, size_t n) {
	char *csrc = (char *)in;
	char *cdest = (char *)out;
	for (int i = 0; i < n; i++) {
		cdest[i] = csrc[i];
	}
	return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
	int * ss1 = (int *)s1;
	int * ss2 = (int *)s2;
	for (int i = 0; i < n; i++) {
		if (ss1[i]!=ss2[i]){
			return *ss1 - *ss2;
		}
	}
	return 0;
}
