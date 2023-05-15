#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <termios.h>

static 

int open_serial(const char *dev)
{
    int fd;

    fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0)
        return -1;

    return fd;
}

int set_serial(int fd, int baudrate, int databits, char parity, int stopbits, bool hardflow)
{
    struct termios new_setting;
    struct termios old_setting;

    memset(&new_setting, 0, sizeof(new_setting));
    memset(&old_setting, 0, sizeof(old_setting));

    if (tcgetattr(fd, &old_setting) < 0)
    {
        printf("Failed to get attr\n");
        return -1;
    }

    new_setting.c_cflag |= CLOCAL | CREAD;
    new_setting.c_cflag &= ~CSIZE;

    switch (baudrate)
    {
    case 1200:
        cfsetspeed(&new_setting, B1200);
        break;
    case 2400:
        cfsetspeed(&new_setting, B2400);
        break;
    case 4800:
        cfsetspeed(&new_setting, B4800);
        break;
    case 9600:
        cfsetspeed(&new_setting, B9600);
        break;
    case 19200:
        cfsetspeed(&new_setting, B19200);
        break;
    case 38400:
        cfsetspeed(&new_setting, B38400);
        break;
    case 57600:
        cfsetspeed(&new_setting, B57600);
        break;
    case 115200:
        cfsetspeed(&new_setting, B115200);
        break;
    case 230400:
        cfsetspeed(&new_setting, B230400);
        break;
    case 460800:
        cfsetspeed(&new_setting, B460800);
        break;
    case 921600:
        cfsetspeed(&new_setting, B921600);
        break;
    default:
        fprintf(stderr, "unsupported baudrate\n");
   		return -1;
    }

    switch (databits) {
   	case 5:
   		new_setting.c_cflag |= CS5;
   		break;
   	case 6:
   		new_setting.c_cflag |= CS6;
   		break;
   	case 7:
   		new_setting.c_cflag |= CS7;
   		break;
   	case 8:
   		new_setting.c_cflag |= CS8;
   		break;
   	default:
   		fprintf(stderr, "unsupported data size\n");
   		return -1;
   	}

    switch (parity) {
   	case 'n':
   	case 'N':
   		new_setting.c_cflag &= ~PARENB;    /* Clear parity enable */
   		new_setting.c_iflag &= ~INPCK;     /* Disable input parity check */
   		break;
   	case 'o':
   	case 'O':
   		new_setting.c_cflag |= (PARODD | PARENB); /* Odd parity instead of even */
   		new_setting.c_iflag |= INPCK;     /* Enable input parity check */
   		break;
   	case 'e':
   	case 'E':
   		new_setting.c_cflag |= PARENB;    /* Enable parity */
   		new_setting.c_cflag &= ~PARODD;   /* Even parity instead of odd */
   		new_setting.c_iflag |= INPCK;     /* Enable input parity check */
   		break;
   	case 'm':
   	case 'M':
   		new_setting.c_cflag |= PARENB;    /* Enable parity */
   		new_setting.c_cflag |= CMSPAR;    /* Stick parity instead */
   		new_setting.c_cflag |= PARODD;    /* Even parity instead of odd */
   		new_setting.c_iflag |= INPCK;     /* Enable input parity check */
   		break;
   	case 's':
   	case 'S':
   		new_setting.c_cflag |= PARENB;    /* Enable parity */
   		new_setting.c_cflag |= CMSPAR;    /* Stick parity instead */
   		new_setting.c_cflag &= ~PARODD;   /* Even parity instead of odd */
   		new_setting.c_iflag |= INPCK;     /* Enable input parity check */
   		break;
   	default:
   		fprintf(stderr, "unsupported parity\n");
   		return -1;
   	}

    /* 停止位设置 */
   	switch (stopbits) {
   	case 1:
   		new_setting.c_cflag &= ~CSTOPB;
   		break;
   	case 2:
   		new_setting.c_cflag |= CSTOPB;
   		break;
   	default:
   		perror("unsupported stop bits\n");
   		return -1;
   	}

    if (hardflow)
   		new_setting.c_cflag |= CRTSCTS;
   	else
   		new_setting.c_cflag &= ~CRTSCTS;

    tcflush(fd, TCIOFLUSH);

    if (tcsetattr(fd, TCSANOW, &new_setting) != 0) {
        perror("tcsetattr");
        return -1;
    }

    return 0;
}

int main()
{
    int serial = open_serial("/dev/ttyS3");

    set_serial(serial, 115200, 8, 'n', 1, false);

    write(serial, "Hello world\n", sizeof(char) * 14);

    return 0;
}