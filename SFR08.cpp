#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#define master_device /dev/i2c-1
//I2C_slave 0xFE
int main()
{
	int fd;
	unsigned int address = 0XFE;
	unsigned char buffer[1000];
	unsigned int count;


	//
	//ouverture du périphérique maître
	fd=open(master_device, O_RDWR);
	if(fd<0){
		cout<<"L'ouverture du Peripherique Master I2C"<<master_device<<"a echoue"end;
		exit(0);
	}
	else{
		cout<<"L'ouverture du Peripherique Master I2C"<<master_device<<"a reussi"endl;
		//
		//ouverture du périphérique esclave
		if(ioctl(fd,I2C_SLAVE,I2C_slave,address)<0){
			cout<<"Impossible de communiquer avec le périphérique Esclave I2C 0x"<<hex<<int(address)<<endl;
			exit(1);
		}
		else{
			cout<<"Communication avec le peripherique esclave I2C 0x"<<hex<<int(address)<<"Etablie"<<endl;
		}
	}
	//
	//écriture dans le registre 0
	if (write(fd,buffer,count)!=count){
		cout<<"Error writing to I2C slave"<<endl;
		return -1;
	}
	close(fd);
	exit(0);
}