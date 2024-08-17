/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

/* Definitions of physical drive number for each drive */
//#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
//#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

#define DEV_SD_CARD		0	//SD Card
#define DEV_SPI_FLASH	1	//SPI FLASH
#define DEV_USB			2	//USB


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	//int result;
	switch (pdrv) {
	case DEV_SD_CARD :
		//result = MMC_disk_status();
		stat = RES_OK;
		// translate the reslut code here
		
		return stat;

	case DEV_SPI_FLASH :
		//result = RAM_disk_status();
		
		// translate the reslut code here
		stat = STA_NOINIT;
		return stat;
		

	case DEV_USB :
		//result = USB_disk_status();

		// translate the reslut code here
		stat = STA_NOINIT;
		return stat;
	}
	
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	//int result;
	switch (pdrv) {
	case DEV_SD_CARD :
		//result = MMC_disk_initialize();
		if(SD_Init() == SD_OK)	//SD卡初始化
		{
			stat = RES_OK;
		}else{
			stat = STA_NOINIT;
		}
		// translate the reslut code here

		return stat;
		
	case DEV_SPI_FLASH :
		//result = RAM_disk_initialize();

		// translate the reslut code here
		stat = STA_NOINIT;
		return stat;

	case DEV_USB :
		//result = USB_disk_initialize();

		// translate the reslut code here
		stat = STA_NOINIT;
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;
	
	switch (pdrv) {
	case DEV_SD_CARD :
		// translate the arguments here

		//result = MMC_disk_read(buff, sector, count);
		
		// translate the reslut code here
		result = SD_ReadDisk(buff, sector, count);
		if(result != 0)
		{
			res = RES_PARERR;
		}else{
			res = RES_OK;
		}
		return res;
		
	case DEV_SPI_FLASH :
		// translate the arguments here

		//result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here
		res = RES_PARERR;
		return res;

	case DEV_USB :
		// translate the arguments here

		//result = USB_disk_read(buff, sector, count);

		// translate the reslut code here
		res = RES_PARERR;
		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;
	switch (pdrv) {
	case DEV_SD_CARD :
		// translate the arguments here

		//result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here
		result = SD_WriteDisk((u8 *)buff, sector, count);
		if(result != 0)
		{
			res = RES_PARERR;
		}else{
			res = RES_OK;
		}
		return res;
	case DEV_SPI_FLASH :
		// translate the arguments here

		//result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here
		res = RES_PARERR;
		return res;

	case DEV_USB :
		// translate the arguments here

		//result = USB_disk_write(buff, sector, count);

		// translate the reslut code here
		res = RES_PARERR;
		return res;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	//int result;

	switch (pdrv) {
	case DEV_SD_CARD :

		// Process of the command for the MMC/SD card
       switch (cmd) {
          /* 扇区数量 */
          case GET_SECTOR_COUNT:
            *(DWORD * )buff = SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize;		
		  break;
          
          /* 扇区大小  */
          case GET_SECTOR_SIZE :
            *(WORD * )buff = SDCardInfo.CardBlockSize;

          break;
          
          /* 同时擦除扇区个数(单位为扇区) */
          case GET_BLOCK_SIZE :
            *(DWORD * )buff = 1;
          break;        
        }
		res = RES_OK;
		return res;
		
	case DEV_SPI_FLASH :

		// Process of the command for the RAM drive
		res = RES_PARERR;
		return res;

	case DEV_USB :

		// Process of the command the USB drive
		res = RES_PARERR;
		return res;
	}

	return RES_PARERR;
}

