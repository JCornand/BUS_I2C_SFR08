#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>	
#define master_device "/dev/i2c-1"
//#define I2C_SLAVE "0xFE"

//I2C_slave 0xFE
int main()
{
	int fd;
	//unsigned long int I2C_SLAVE = 0xFE;
	unsigned int address = 0x70;
	unsigned char buffer[1000];
	unsigned char range[2];
	unsigned char meter[2];
	short int val=0;
	unsigned char msb,lsb;

	//
	//ouverture du périphérique maître
	fd=open(master_device, O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd<0)
	{
		printf("L'ouverture du Peripherique Master I2C /dev/i2c a echoue\n");
		exit(0);
	}
	else
	{
		printf("L'ouverture du Peripherique Master I2C /dev/i2c a reussi\n");
		//
		//ouverture du périphérique esclave
		if(ioctl(fd, I2C_SLAVE, address)<0)
		{
			perror("IOCTL");
			printf("Impossible de communiquer avec le périphérique Esclave I2C 0x\n");
			exit(1);
		}
		else{
			printf("Communication avec le peripherique esclave I2C 0x70\n");
		}
	}
	//
	//écriture dans le registre 0
	buffer[0] = 0x00;
	if (write(fd,buffer,1)== -1)
	{
		printf("Error writing to I2C slave\n");
		return -1;
	}
	else
	{
		printf("écriture réussi dans 0x00\n");
	}
	//
	//lecture de la version
	if(read(fd,buffer,1) != 1)
	{
		printf("Unable to read from slave\n");
	}
	else
	{
		printf("Version:%d\n",buffer[0]);
	}
	//configurer le range
	//
	//écriture dans le registre range
	range[0]=0x02;
	range[1]=0x18;
	if (write(fd,range,2)== -1)
	{
		printf("Error writing to I2C slave n1\n");
		return -1;
	}
	else
	{
		printf("écriture réussi range \n");
	}

	//
	//Mesurer en mètre
	meter[0]=0x00;
	meter[1]=0x51;
	if (write(fd,meter,2)== -1)
	{
		printf("Error writing to I2C slave\n");
		return -1;
	}
	else
	{
		printf("écriture réussi pour étape mesure\n");
	}

	sleep(1);
	//
	//lecture de la luminosité
	//écriture dans le registre 0
	buffer[0] = 0x01;
	if (write(fd,buffer,1)== -1)
	{
		printf("Error writing to I2C slave\n");
		return -1;
	}
	else
	{
		printf("écriture réussi dans 0x00\n");
	}
	if(read(fd,buffer,1) != 1)
	{
		printf("Unable to read from slave\n");
	}
	else
	{
		printf("Luminosité:%d\n",buffer[0]);
	}
	
	//
	//lecture mesure msb
	buffer[0]=0x02;
	if (write(fd,buffer,1)!=1)
	{
		printf("Error writing to I2C slave n1\n");
		return -1;
	}
	else
	{
		printf("écriture réussi msb \n");
	}
	if(read(fd,&msb,1) != 1)
	{
		printf("Unable to read from slave\n");
	}
	else
	{
		printf("MSB:%d\n",msb);
	}

	//
	//lecture mesure lsb
	buffer[0]=0x03;
	if (write(fd,buffer,1)!=1)
	{
		printf("Error writing to I2C slave n1\n");
		return -1;
	}
	else
	{
		printf("écriture réussi LSB \n");
	}
	if(read(fd,&lsb,1) != 1)
	{
		printf("Unable to read from slave\n");
	}
	else
	{
		printf("LSB:%d\n",lsb);
	}
	val=(msb<<8)+lsb;
	printf("distance:%d\n",val);
	close(fd);
	exit(0);
}
