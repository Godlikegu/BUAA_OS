#include <types.h>
#include <print.h>

static void print_char(char*,char, int, int);
static void print_str( char*,const char *, int, int);
static void print_num(char*,unsigned long, int, int, int, int, char, int);
static void* memcpy(void*,const void*,size_t);
static void *memset(void*, int, size_t);
static size_t strlen(const char*);
static char *strcpy(char *, const char *);



void *memcpy(void *dst, const void *src, size_t n) {
	void *dstaddr = dst;
	void *max = dst + n;

	if (((u_long)src & 3) != ((u_long)dst & 3)) {
		while (dst < max) {
			*(char *)dst++ = *(char *)src++;
		}
		return dstaddr;
	}

	while (((u_long)dst & 3) && dst < max) {
		*(char *)dst++ = *(char *)src++;
	}

	// copy machine words while possible
	while (dst + 4 <= max) {
		*(uint32_t *)dst = *(uint32_t *)src;
		dst += 4;
		src += 4;
	}

	// finish the remaining 0-3 bytes
	while (dst < max) {
		*(char *)dst++ = *(char *)src++;
	}
	return dstaddr;
}

void *memset(void *dst, int c, size_t n) {
	void *dstaddr = dst;
	void *max = dst + n;
	u_char byte = c & 0xff;
	uint32_t word = byte | byte << 8 | byte << 16 | byte << 24;

	while (((u_long)dst & 3) && dst < max) {
		*(u_char *)dst++ = byte;
	}

	// fill machine words while possible
	while (dst + 4 <= max) {
		*(uint32_t *)dst = word;
		dst += 4;
	}

	// finish the remaining 0-3 bytes
	while (dst < max) {
		*(u_char *)dst++ = byte;
	}
	return dstaddr;
}

size_t strlen(const char *s) {
	int n;

	for (n = 0; *s; s++) {
		n++;
	}

	return n;
}

char *strcpy(char *dst, const char *src) {
	char *ret = dst;

	while ((*dst++ = *src++) != 0) {
	}

	return ret;
}

const char *strchr(const char *s, int c) {
	for (; *s; s++) {
		if (*s == c) {
			return s;
		}
	}
	return 0;
}

int strcmp(const char *p, const char *q) {
	while (*p && *p == *q) {
		p++, q++;
	}

	if ((u_int)*p < (u_int)*q) {
		return -1;
	}

	if ((u_int)*p > (u_int)*q) {
		return 1;
	}

	return 0;
}

int sprintf(char *buf, const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	int len;
	char res[100];
	char c;
	const char *s;
	long num;
	char temps[100];
	int width;
	int long_flag; // output is long (rather than int)
	int neg_flag;  // output is negative
	int ladjust;   // output is left-aligned
	char padc;     // padding char
	memset(res,0,100);
	memset(temps,0,100);
	for (;;) {
		/* scan for the next '%' */
		/* Exercise 1.4: Your code here. (1/8) */
		unsigned int i=0;
		char * curfmt = fmt; /*exist some problem*/
		while (*curfmt != '%' && *curfmt != '\0'){
			curfmt ++;
		}
		/* flush the string found so far */
		/* Exercise 1.4: Your code here. (2/8) */
		len = strlen(res);
		memcpy(res+len, fmt, curfmt-fmt);

		fmt = curfmt;
		/* check "are we hitting the end?" */
		/* Exercise 1.4: Your code here. (3/8) */
		if (*fmt == '\0'){
			buf = res;
			return strlen(buf);
		}
		/* we found a '%' */
		/* Exercise 1.4: Your code here. (4/8) */
		++fmt;
		/* check format flag */
		/* Exercise 1.4: Your code here. (5/8) */
		padc = ' ';
		ladjust = 0;
		if (*fmt == '-'){
			ladjust = 1;
			fmt++;
		}
		if (*fmt == '0'){
			padc = '0';
			fmt++;
		}
		/* get width */
		/* Exercise 1.4: Your code here. (6/8) */
		width = 0;
		if (*fmt >= '0' && *fmt <= '9'){
			width = width * 10 + (*fmt-'0');
			fmt++;
		}
		/* check for long */
		/* Exercise 1.4: Your code here. (7/8) */
		if (*fmt == 'l'){
			long_flag = 1;
			fmt++;
		}
		neg_flag = 0;
		switch (*fmt) {
		case 'b':
			if (long_flag) {
				num = va_arg(ap, long int);
			} else {
				num = va_arg(ap, int);
			}
			print_num(temps,num, 2, 0, width, ladjust, padc, 0);
			len = strlen(res);
			strcpy(res+len,temps);
			break;
	
		case 'd':
		case 'D':
			if (long_flag) {
				num = va_arg(ap, long int);
			} else {
				num = va_arg(ap, int);
			}
			/*
			 * Refer to other parts (case 'b', case 'o', etc.) and func 'print_num' to
			 * complete this part. Think the differences between case 'd' and the
			 * others. (hint: 'neg_flag').
			 */
			/* Exercise 1.4: Your code here. (8/8) */
			if (num < 0){
				neg_flag = 1;
				num = -num;
			}
			print_num(temps,num, 10, neg_flag, width, ladjust, padc, 0);
			len = strlen(res);
			strcpy(res+len,temps);
			break;

		case 'o':
		case 'O':
			if (long_flag) {
				num = va_arg(ap, long int);
			} else {
				num = va_arg(ap, int);
			}
			print_num( temps,num, 8, 0, width, ladjust, padc, 0);
			len = strlen(res);
			strcpy(res+len,temps);
			break;

		case 'u':
		case 'U':
			if (long_flag) {
				num = va_arg(ap, long int);
			} else {
				num = va_arg(ap, int);
			}
			
			print_num(temps, num, 10, 0, width, ladjust, padc, 0);
			len = strlen(res);
			strcpy(res+len,temps);
			break;

		case 'x':
			if (long_flag) {
				num = va_arg(ap, long int);
			} else {
				num = va_arg(ap, int);
			}
			print_num(temps, num, 16, 0, width, ladjust, padc, 0);
			len = strlen(res);
			strcpy(res+len,temps);
			break;

		case 'X':
			if (long_flag) {
				num = va_arg(ap, long int);
			} else {
				num = va_arg(ap, int);
			}
			print_num(temps, num, 16, 0, width, ladjust, padc, 1);
			len = strlen(res);
			strcpy(res+len,temps);
			break;

		case 'c':
			c = (char)va_arg(ap, int);
			print_char( temps,c, width, ladjust);
			len = strlen(res);	
			strcpy(res+len,temps);	
			break;

		case 's':
			s = (char *)va_arg(ap, char *);
			print_str(temps,s, width, ladjust);
			len = strlen(res);
			strcpy(res+len,temps);
			break;

		case '\0':
			fmt--;
			break;

		default:
			/* output this char as it is */
			//out(data, fmt, 1);
			len = strlen(buf);
			buf[len]=*fmt;
		}
		fmt++;
	}







va_end(ap);


}


void print_char(char* buf, char c, int length, int ladjust) {
	int i;
	memset(buf,0,100);
	if (length < 1) {
		length = 1;
	}
	const char space = ' ';
	if (ladjust) {
		//out(data, &c, 1);
		buf[0]=c;
		for (i = 1; i < length; i++) {
			//out(data, &space,1);
			buf[i]=' ';
		}
	} else {
		for (i = 0; i < length - 1; i++) {
			//out(data, &space, 1);
			buf[i]=' ';
		}
		//out(data, &c, 1);
		buf[i]=c;
	}
}

void print_str( char* buf, const char *s, int length, int ladjust) {
	int i;
	int len = 0;
	const char *s1 = s;
	char temps[length+70];
	memset(buf,'\0',100);
	memset(temps,'\0',length+70);
	while (*s1++) {
		len++;
	}
	if (length < len) {
		length = len;
	}

	if (ladjust) {
		//out(data, s, len);
		strcpy(buf,s);
		for (i = len; i < length; i++) {
			//out(data, " ", 1);
			buf[i] = ' ';
		}
	} else {
		for (i = 0; i < length - len; i++) {
			//out(data, " ", 1);
			buf[i]=' ';
		}
		strcpy(temps, s);
		strcpy(buf+i,s);
	}
}

void print_num(char* buf, unsigned long u, int base, int neg_flag, int length,
	       int ladjust, char padc, int upcase) {
	/* algorithm :
	 *  1. prints the number from left to right in reverse form.
	 *  2. fill the remaining spaces with padc if length is longer than
	 *     the actual length
	 *     TRICKY : if left adjusted, no "0" padding.
	 *		    if negtive, insert  "0" padding between "0" and number.
	 *  3. if (!ladjust) we reverse the whole string including paddings
	 *  4. otherwise we only reverse the actual string representing the num.
	 */

	int actualLength = 0;
	memset(buf,'\0',100);
	char *p = buf;
	int i;

	do {
		int tmp = u % base;
		if (tmp <= 9) {
			*p++ = '0' + tmp;
		} else if (upcase) {
			*p++ = 'A' + tmp - 10;
		} else {
			*p++ = 'a' + tmp - 10;
		}
		u /= base;
	} while (u != 0);

	if (neg_flag) {
		*p++ = '-';
	}

	/* figure out actual length and adjust the maximum length */
	actualLength = p - buf;
	if (length < actualLength) {
		length = actualLength;
	}

	/* add padding */
	if (ladjust) {
		padc = ' ';
	}
	if (neg_flag && !ladjust && (padc == '0')) {
		for (i = actualLength - 1; i < length - 1; i++) {
			buf[i] = padc;
		}
		buf[length - 1] = '-';
	} else {
		for (i = actualLength; i < length; i++) {
			buf[i] = padc;
		}
	}

	/* prepare to reverse the string */
	int begin = 0;
	int end;
	if (ladjust) {
		end = actualLength - 1;
	} else {
		end = length - 1;
	}

	/* adjust the string pointer */
	while (end > begin) {
		char tmp = buf[begin];
		buf[begin] = buf[end];
		buf[end] = tmp;
		begin++;
		end--;
	}
}


