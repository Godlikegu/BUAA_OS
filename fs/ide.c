/*
 * operations on IDE disk.
 */

#include "serv.h"
#include <drivers/dev_disk.h>
#include <lib.h>
#include <mmu.h>

// Overview:
//  read data from IDE disk. First issue a read request through
//  disk register and then copy data from disk buffer
//  (512 bytes, a sector) to destination array.
//
// Parameters:
//  diskno: disk number.
//  secno: start sector number.
//  dst: destination for data read from IDE disk.
//  nsecs: the number of sectors to read.
//
// Post-Condition:
//  Panic if any error occurs. (you may want to use 'panic_on')
//
// Hint: Use syscalls to access device registers and buffers.
// Hint: Use the physical address and offsets defined in 'include/drivers/dev_disk.h':
//  'DEV_DISK_ADDRESS', 'DEV_DISK_ID', 'DEV_DISK_OFFSET', 'DEV_DISK_OPERATION_READ',
//  'DEV_DISK_START_OPERATION', 'DEV_DISK_STATUS', 'DEV_DISK_BUFFER'
void ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs) {
	u_int begin = secno * BY2SECT;
	u_int end = begin + nsecs * BY2SECT;

	for (u_int off = 0; begin + off < end; off += BY2SECT) {
		uint32_t temp = diskno;
		u_int cur_offset = begin + off;
		/* Exercise 5.3: Your code here. (1/2) */
		uint32_t op = DEV_DISK_OPERATION_READ;
		if (syscall_write_dev(&temp,DEV_DISK_ADDRESS + DEV_DISK_ID,sizeof(uint32_t))!=0){
			panic_on("ide_read panic");
		}
		if (syscall_write_dev(&cur_offset,DEV_DISK_ADDRESS + DEV_DISK_OFFSET,sizeof(uint32_t))!=0){
			panic_on("ide_read panic");
		}
		if (syscall_write_dev(&op,DEV_DISK_ADDRESS + DEV_DISK_START_OPERATION,sizeof(uint32_t))!=0){
			panic_on("ide_read panic");
		}
		uint32_t isOk;
		if (syscall_read_dev(&isOk,DEV_DISK_ADDRESS + DEV_DISK_STATUS,sizeof(uint32_t))!=0){
			panic_on("ide_read panic");
		}
		if (!isOk){
			panic_on("ide_read panic");
		}
		if (syscall_read_dev((uint32_t)(dst + off),DEV_DISK_ADDRESS + DEV_DISK_BUFFER,BY2SECT)!=0){
			panic_on("ide_read panic");
		}
	}
}

// Overview:
//  write data to IDE disk.
//
// Parameters:
//  diskno: disk number.
//  secno: start sector number.
//  src: the source data to write into IDE disk.
//  nsecs: the number of sectors to write.
//
// Post-Condition:
//  Panic if any error occurs.
//
// Hint: Use syscalls to access device registers and buffers.
// Hint: Use the physical address and offsets defined in 'include/drivers/dev_disk.h':
//  'DEV_DISK_ADDRESS', 'DEV_DISK_ID', 'DEV_DISK_OFFSET', 'DEV_DISK_BUFFER',
//  'DEV_DISK_OPERATION_WRITE', 'DEV_DISK_START_OPERATION', 'DEV_DISK_STATUS'
void ide_write(u_int diskno, u_int secno, void *src, u_int nsecs) {
	u_int begin = secno * BY2SECT;
	u_int end = begin + nsecs * BY2SECT;

	for (u_int off = 0; begin + off < end; off += BY2SECT) {
		uint32_t temp = diskno;
		u_int cur_offset = begin + off;
		/* Exercise 5.3: Your code here. (2/2) */
		uint32_t op = DEV_DISK_OPERATION_WRITE;
		if (syscall_write_dev(&temp,DEV_DISK_ADDRESS + DEV_DISK_ID,sizeof(uint32_t))!=0){
			panic_on("ide_read panic");
		}
		if (syscall_write_dev(&cur_offset,DEV_DISK_ADDRESS + DEV_DISK_OFFSET,sizeof(uint32_t))!=0){
			panic_on("ide_read panic");
		}
		if (syscall_write_dev((uint32_t)(src + off),DEV_DISK_ADDRESS + DEV_DISK_BUFFER,BY2SECT)!=0){
			panic_on("ide_read panic");
		}
		if (syscall_write_dev(&op,DEV_DISK_ADDRESS + DEV_DISK_START_OPERATION,sizeof(uint32_t))!=0){
			panic_on("ide_read panic");
		}
		uint32_t isOk;
		if (syscall_read_dev(&isOk,DEV_DISK_ADDRESS + DEV_DISK_STATUS,sizeof(uint32_t))!=0){
			panic_on("ide_read panic");
		}
		if (!isOk){
			panic_on("ide_read panic");
		}
	}
}
