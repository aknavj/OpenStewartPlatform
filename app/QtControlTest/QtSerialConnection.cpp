#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "QtSerialConnection.h"

/*
 */
CSerialConnection::CSerialConnection(char *port) {
	connect(port);
}

/*
 */
CSerialConnection::~CSerialConnection() {
	disconnect();
}

/*
 */
void CSerialConnection::connect(char *port) {

	if(strlen(port) > 64) {
		erroNo = ERROR_DEVICE_TYPE;
		return;
	}

	if(!connected) {

		strcpy(portName, port);
		fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
		
		if(fd < 0) {
			erroNo = ERROR_OPEN;
		} else{
			if(!isatty(fd)) {
				erroNo = ERROR_DEVICE_TYPE;
				close(fd);
			} else{
				if(tcgetattr(fd, &settings) < 0) {
					erroNo = ERROR_ATTRIBUTES_READ;
					close(fd);
				} else{
					fcntl(fd, F_SETFL, 0);
					memset(&settings, 0, sizeof(settings));
					connected = 1;
					erroNo = EOK;
				}
			}
		}
	} else {
		erroNo = ERROR_BUSY;
	}
}

/*
 */
void CSerialConnection::setBaud(speed_t speed) {
	
	erroNo = EOK;
	switch(speed) {
		case 1200: cfsetspeed(&settings, B1200); break;
		case 1800: cfsetspeed(&settings, B1800); break;
		case 2400: cfsetspeed(&settings, B2400); break;
		case 4800: cfsetspeed(&settings, B4800); break;
		case 9600: cfsetspeed(&settings, B9600); break;
		case 19200: cfsetspeed(&settings, B19200); break;
		case 38400: cfsetspeed(&settings, B38400); break;
		case 57600: cfsetspeed(&settings, B57600); break;
		case 115200: cfsetspeed(&settings, B115200); break;
		case 230400: cfsetspeed(&settings, B230400); break;
		case 460800: cfsetspeed(&settings, B460800); break;
		case 500000: cfsetspeed(&settings, B500000); break;
		case 576000: cfsetspeed(&settings, B576000); break;
		case 921600: cfsetspeed(&settings, B921600); break;
		case 1000000: cfsetspeed(&settings, B1000000); break;
		case 1152000: cfsetspeed(&settings, B1152000); break;
		case 1500000: cfsetspeed(&settings, B1500000); break;
		case 2000000: cfsetspeed(&settings, B2000000); break;
		case 2500000: cfsetspeed(&settings, B2500000); break;
		case 3000000: cfsetspeed(&settings, B3000000); break;
		case 3500000: cfsetspeed(&settings, B3500000); break;
		case 4000000: cfsetspeed(&settings, B4000000); break;
		default: erroNo = ERROR_BAUDRATE; return;
	}

	if(tcsetattr(fd, TCSANOW, &settings) < 0) {
		erroNo = ERROR_ATTRIBUTES_WRITE;
	} else {
		erroNo = EOK;
	}
}

/*
 */
void CSerialConnection::setParity(unsigned char enable, unsigned char even) {

	if(enable) {
		if(even) {
			settings.c_cflag |= PARENB;
			settings.c_cflag &= ~PARODD;
		} else{
			settings.c_cflag |= PARENB | PARODD;
		}
	} else{
		settings.c_cflag &= ~(PARENB | PARODD);
	}

	if(tcsetattr(fd, TCSANOW, &settings) < 0) {
		erroNo = ERROR_ATTRIBUTES_WRITE;
	} else {
		erroNo = EOK;
	}

}

/*
 */
void CSerialConnection::setStopBits(unsigned char count) {
	if(count) {
		settings.c_cflag &= ~CSTOPB;
	} else {
		settings.c_cflag |= CSTOPB;
	}

	if(tcsetattr(fd, TCSANOW, &settings) < 0) {
		erroNo = ERROR_ATTRIBUTES_WRITE;
	} else {
		erroNo = EOK;
	}

}

/*
 */
void CSerialConnection::setCharSize(unsigned char size) {
	settings.c_cflag &= ~CSIZE;
	erroNo = EOK;
	
	switch(size) {
		case 5 : settings.c_cflag |= CS5; break;
		case 6 : settings.c_cflag |= CS6; break;
		case 7 : settings.c_cflag |= CS7; break;
		case 8 : settings.c_cflag |= CS8; break;
		default: erroNo = ERROR_INVALID_CHARSIZE; return;
	}

	if(tcsetattr(fd, TCSANOW, &settings) < 0) {
		erroNo = ERROR_ATTRIBUTES_WRITE;
	} else {
		erroNo = EOK;
	}
}

/*
 */
void CSerialConnection::disconnect() {
	if(fd != -1) {
		if(close(fd) < 0) {
			erroNo = ERROR_CLOSE;
		} else {
			fd = -1;
			erroNo = EOK;
			connected = 0;
		}
	}
}

/*
 */
void CSerialConnection::send(unsigned char *data, int count) {

	int n = write(fd, data, count);

	if (n < 0) {
		erroNo = ERROR_SEND;
	}

}

/*
 */
unsigned char CSerialConnection::recieve() {
	unsigned char result;
	read(fd, &result, 1);
	return result;
}


