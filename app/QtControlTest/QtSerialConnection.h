#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <termios.h>

/*
 */
class CSerialConnection {

	public:
	
		CSerialConnection(char *port);	// Filename of port (e.g. /dev/ttyS0)
		~CSerialConnection();

		void setBaud(speed_t speed);	// From <termios.h> definitions
		void setParity(unsigned char enable, unsigned char even);	//Enable: enabled = not-zero, disabled = 0, even: even = not-zero, odd = 0
		void setStopBits(unsigned char count); // count: 1 = 0,  2 = non-zero
		void setCharSize(unsigned char size); // size = 5, 6, 7 or 8

		void connect(char *port);  // Filename of port (e.g. /dev/ttyS0)
		void disconnect();
		void send(unsigned char *data, int count);
		unsigned char recieve();

		// A variable to keep error codes
		int erroNo;

	private:
	
		// Structure to store settings
		struct termios settings;

		// File name of serial port
		char portName[65];

		// File descriptor of serial port
		int fd;
		int connected;
};

/*
 */
enum ErrorCodes {
	EOK,
	ERROR_OPEN,
	ERROR_CLOSE,
	ERROR_DEVICE_TYPE,
	ERROR_SEND,
	ERROR_ATTRIBUTES_READ,
	ERROR_ATTRIBUTES_WRITE,
	ERROR_BAUDRATE,
	ERROR_INVALID_CHARSIZE,
	ERROR_BUSY
};

#endif /* __SERIAL_H__ */
