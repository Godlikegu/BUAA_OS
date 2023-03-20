void sprintf_1_check() {
	int len;
	char str[100];
	len = sprintf(str, "%d\n", 12321);
	printk("%s",str[0]);
	printk("%s",str);
	len = sprintf(str, "%c\n", 97);
	printk("%s",str);
}

void mips_init() {
	sprintf_1_check();
	halt();
}
