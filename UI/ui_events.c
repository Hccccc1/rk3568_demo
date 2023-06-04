// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.4
// Project name: SquareLine_Project

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "SDL2/SDL_thread.h"
#include "ui.h"

#define MAX_GPIO_NUMS 20

struct gpio_indicator
{
	char *name;
	uint16_t num;
} gpios[] = {
	{.name = "OUT_5V0_EN", .num = 88},
	{.name = "VCC_5V0_EN", .num = 89},
	{.name = "K1B", .num = 90},
	{.name = "K1A", .num = 91},
	{.name = "K2A", .num = 92},
	{.name = "K2B", .num = 93},
	{.name = "K3A", .num = 94},
	{.name = "K3B", .num = 151},
	{.name = "K4A", .num = 152},
	{.name = "K5A", .num = 153},
	{.name = "IO_ID1_OUT", .num = 154},
	{.name = "IO_ID0_OUT", .num = 32},
	{.name = "SWIO1_CPU", .num = 503},
	{.name = "SWIO2_CPU", .num = 504},
	{.name = "SWIO3_CPU", .num = 505},
	{.name = "SWIO4_CPU", .num = 506},
	{.name = "SWIO5_CPU", .num = 507},
	{.name = "SWIO6_CPU", .num = 508},
	{.name = "SWIO7_CPU", .num = 509},
	{.name = "SWIO8_CPU", .num = 510},
};

#define TCP_TEST

static int tcp_create_and_connect(const char *ip_addr, uint32_t port)
{
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		perror("Socket create");
		return -1;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_addr.s_addr = inet_addr(ip_addr);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	socklen_t len = sizeof(addr);

	if (connect(fd, (struct sockaddr *)&addr, len) < 0)
	{
		perror("connect failed");
		goto out_close_socket;
	}

	return fd;

out_close_socket:
	close(fd);
	return -1;
}

static int tcp_create_and_listen(uint16_t port)
{
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		perror("Socket create");
		return -1;
	}

	struct sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		goto out_close_socket;
	}

	if (listen(fd, 5) < 0)
	{
		perror("listen");
		goto out_close_socket;
	}

	return fd;

out_close_socket:
	close(fd);

	return -1;
}

static int tcp_write(int socket_fd, const char *w_buf, uint16_t buf_len)
{
	return write(socket_fd, w_buf, buf_len);
}

static int tcp_read(int socket_fd, char *r_buf, uint16_t buf_len)
{
	return read(socket_fd, r_buf, buf_len);
}

static int udp_create_socket(uint16_t my_port)
{
	int fd;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		perror("udp socket");
		return -1;
	}

	struct sockaddr_in my_addr;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(my_port);
	my_addr.sin_family = AF_INET;

	if (bind(fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
	{
		perror("udp bind");
		goto out_close_socket;
	}

	printf("%s %d\n", inet_ntoa(my_addr.sin_addr), ntohs(my_addr.sin_port));

	return fd;

out_close_socket:
	close(fd);

	return -1;
}

static int udp_recv_from(int socket_fd, const char *ip_addr, uint16_t port, void *recv_buf, uint16_t buf_len)
{
	struct sockaddr_in from_addr;
	socklen_t len = sizeof(from_addr);

	from_addr.sin_addr.s_addr = inet_addr(ip_addr);
	from_addr.sin_port = htons(port);
	from_addr.sin_family = AF_INET;

	return recvfrom(socket_fd, recv_buf, buf_len, 0, (struct sockaddr *)&from_addr, &len);
}

static int udp_send_to(int socket_fd, const char *ip_addr, uint16_t port, const void *send_buf, uint16_t buf_len)
{
	struct sockaddr_in to_addr;

	to_addr.sin_addr.s_addr = inet_addr(ip_addr);
	to_addr.sin_port = htons(port);
	to_addr.sin_family = AF_INET;

	return sendto(socket_fd, send_buf, buf_len, 0, (struct sockaddr *)&to_addr, sizeof(to_addr));
}

void serial_open_clicked(lv_event_t *e)
{
	int serial_fd;
	char port_name[64] = {0};
	char buf[128] = {0};
	serial_widgets_t *widgets = lv_event_get_user_data(e);
	struct termios new_settings, old_settings;

	lv_dropdown_get_selected_str(widgets->port_select, port_name, sizeof(port_name));

	serial_fd = open(port_name, O_RDWR | O_NOCTTY | O_NDELAY);
	if (serial_fd < 0)
	{
		LV_LOG_ERROR("Failed to open serial");
		return;
	}

	memset(&new_settings, 0, sizeof(new_settings));
	memset(&old_settings, 0, sizeof(old_settings));

	if (tcgetattr(serial_fd, &old_settings) < 0)
	{
		LV_LOG_ERROR("Failed to get serial attr\n");
		goto out_close_serial;
	}

	new_settings.c_cflag |= CLOCAL | CREAD;
	new_settings.c_cflag &= ~CSIZE;

	lv_dropdown_get_selected_str(widgets->baudrate_select, buf, sizeof(buf));
	uint32_t baudrate = strtoul(buf, NULL, 0);

	switch (baudrate)
	{
	case 1200:
		cfsetspeed(&new_settings, B1200);
		break;
	case 2400:
		cfsetspeed(&new_settings, B2400);
		break;
	case 4800:
		cfsetspeed(&new_settings, B4800);
		break;
	case 9600:
		cfsetspeed(&new_settings, B9600);
		break;
	case 19200:
		cfsetspeed(&new_settings, B19200);
		break;
	case 38400:
		cfsetspeed(&new_settings, B38400);
		break;
	case 57600:
		cfsetspeed(&new_settings, B57600);
		break;
	case 115200:
		cfsetspeed(&new_settings, B115200);
		break;
	case 230400:
		cfsetspeed(&new_settings, B230400);
		break;
	case 460800:
		cfsetspeed(&new_settings, B460800);
		break;
	case 921600:
		cfsetspeed(&new_settings, B921600);
		break;
	default:
		LV_LOG_ERROR("unsupported baudrate\n");
		goto out_close_serial;
	}

	memset(buf, 0, sizeof(buf));

	lv_dropdown_get_selected_str(widgets->databits_select, buf, sizeof(buf));
	uint32_t databits = strtoul(buf, NULL, 0);
	switch (databits)
	{
	case 5:
		new_settings.c_cflag |= CS5;
		break;
	case 6:
		new_settings.c_cflag |= CS6;
		break;
	case 7:
		new_settings.c_cflag |= CS7;
		break;
	case 8:
		new_settings.c_cflag |= CS8;
		break;
	default:
		LV_LOG_ERROR("unsupported databits\n");
		goto out_close_serial;
	}

	memset(buf, 0, sizeof(buf));

	lv_dropdown_get_selected_str(widgets->databits_select, buf, sizeof(buf));
	char parity = buf[0];
	switch (parity)
	{
	case 'N':
		new_settings.c_cflag &= ~PARENB; /* Clear parity enable */
		new_settings.c_iflag &= ~INPCK;	 /* Disable input parity check */
		break;
	case 'O':
		new_settings.c_cflag |= (PARODD | PARENB); /* Odd parity instead of even */
		new_settings.c_iflag |= INPCK;			   /* Enable input parity check */
		break;
	case 'E':
		new_settings.c_cflag |= PARENB;	 /* Enable parity */
		new_settings.c_cflag &= ~PARODD; /* Even parity instead of odd */
		new_settings.c_iflag |= INPCK;	 /* Enable input parity check */
		break;
	case 'M':
		new_settings.c_cflag |= PARENB; /* Enable parity */
		new_settings.c_cflag |= CMSPAR; /* Stick parity instead */
		new_settings.c_cflag |= PARODD; /* Even parity instead of odd */
		new_settings.c_iflag |= INPCK;	/* Enable input parity check */
		break;
	case 'S':
		new_settings.c_cflag |= PARENB;	 /* Enable parity */
		new_settings.c_cflag |= CMSPAR;	 /* Stick parity instead */
		new_settings.c_cflag &= ~PARODD; /* Even parity instead of odd */
		new_settings.c_iflag |= INPCK;	 /* Enable input parity check */
		break;
	default:
		LV_LOG_ERROR("unsupported parity\n");
		goto out_close_serial;
	}

	memset(buf, 0, sizeof(buf));
	lv_dropdown_get_selected_str(widgets->stopbits_select, buf, sizeof(buf));
	uint32_t stopbits = strtoul(buf, NULL, 0);

	switch (stopbits)
	{
	case 1:
		new_settings.c_cflag &= ~CSTOPB;
		break;
	case 2:
		new_settings.c_cflag |= CSTOPB;
		break;
	default:
		perror("unsupported stop bits\n");
		return;
	}

	memset(buf, 0, sizeof(buf));
	lv_dropdown_get_selected_str(widgets->hardflow_select, buf, sizeof(buf));

	if (!strcmp(buf, "true"))
		new_settings.c_cflag |= CRTSCTS;
	else
		new_settings.c_cflag &= ~CRTSCTS;

	tcflush(serial_fd, TCIOFLUSH);

	if (tcsetattr(serial_fd, TCSANOW, &new_settings) != 0)
	{
		LV_LOG_ERROR("setattr failed\n");
		goto out_close_serial;
	}

	widgets->serial_fd = serial_fd;

	return;

out_close_serial:
	close(serial_fd);

	return;
}

void serial_send_clicked(lv_event_t *e)
{
	// Your code here
	serial_widgets_t *widgets = lv_event_get_user_data(e);

	// write(serial_widgets->serial_fd, )

	if (widgets->serial_fd > 0)
	{
		const char *buf = lv_textarea_get_text(widgets->send_text);
		write(widgets->serial_fd, buf, strlen(buf));
	}
	else
	{
		LV_LOG_WARN("Serial not connected\n");
	}
}

void backlight_value_changed(lv_event_t *e)
{
	lv_obj_t *slider = lv_event_get_target(e);
	lv_obj_t *label = lv_event_get_user_data(e);
	char buf[64];
	int32_t value = lv_slider_get_value(slider);
	lv_snprintf(buf, sizeof(buf), "%d%%", value);
	lv_label_set_text(label, buf);
	lv_obj_align_to(label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

	lv_snprintf(buf, sizeof(buf), "echo %u > /sys/class/backlight/backlight/brightness", (uint32_t)0xff * value / 100);

	LV_LOG_WARN("execute %s\n", buf);

	// system(buf);
}

void wifi_scan_clicked(lv_event_t *e)
{
	uint16_t ssid_index = 0;
	char *p_n, *p_ssid_start, *p_ssid_end;
	FILE *fp;
	char buf[BUFSIZ] = {0}, ssid_buf[128] = {0};
	wifi_widgets_t *widgets = lv_event_get_user_data(e);

	if (lv_obj_has_state(widgets->wifi_switch, LV_STATE_CHECKED))
	{
		if ((fp = popen("wpa_cli scan", "r")) == NULL)
		{
			LV_LOG_ERROR("Failed to scan wifi");
			return;
		}

		while (fgets(buf, sizeof(buf), fp) != NULL)
		{
			if (strstr(buf, "Selected interface") != NULL)
				continue;

			if (strstr(buf, "OK") != NULL)
			{
				LV_LOG_ERROR("close fp and return\n");
				pclose(fp);
				return;
			}
		}

		pclose(fp);

		fp = popen("wpa_cli scan_r", "r");
		if (!fp)
		{
			LV_LOG_ERROR("Failed to get scan result\n");
			return;
		}

		memset(buf, 0, sizeof(buf));
		lv_dropdown_clear_options(widgets->ssid_select);

		while (fgets(buf, BUFSIZ, fp) != NULL)
		{
			if (strstr(buf, "bssid") != 0 || strstr(buf, "Selected interface") != 0)
				continue;

			if ((p_n = strstr(buf, "\n")) != NULL)
			{
				p_ssid_end = p_n - 1;
				while (*p_n != '\t')
					p_n--;

				p_ssid_start = p_n; //'\t'
				strncpy(ssid_buf, (p_ssid_start + 1), (p_ssid_end - p_ssid_start));
			}

			// printf("ssid: %u -> %s\n", ssid_index - 1, ssid_buf[ssid_index - 1]);

			lv_dropdown_add_option(widgets->ssid_select, ssid_buf, ssid_index);
			ssid_index++;
		}

		pclose(fp);
	}
}

void wifi_connect_clicked(lv_event_t *e)
{
	FILE *fp;
	const char *set_ssid = "wpa_cli -i wlan0 set_network 0 ssid ";
	const char *set_password = "wpa_cli -i wlan0 set_network 0 psk ";
	char buf[128] = {0};
	char *cmd = NULL;
	wifi_widgets_t *widgets = lv_event_get_user_data(e);

	if (lv_obj_has_state(widgets->wifi_switch, LV_STATE_CHECKED))
	{

		cmd = (char *)malloc(sizeof(char) * 128);

		lv_dropdown_get_selected_str(widgets->ssid_select, buf, sizeof(buf));

		strcat(cmd, set_ssid);
		strcat(cmd, "'\"");
		strcat(cmd, buf);
		strcat(cmd, "\"'");
		LV_LOG_INFO("%s\n", cmd);

		if ((fp = popen(cmd, "r")) == NULL)
		{
			LV_LOG_ERROR("set ssid failed\n");
			return;
		}

		while (fgets(buf, sizeof(buf), fp) != NULL)
		{
			if (strstr(buf, "FAIL") != NULL)
			{
				LV_LOG_ERROR("Failed to set ssid\n");
				pclose(fp);
				return;
			}
		}
		pclose(fp);

		memset(buf, 0, sizeof(buf));
		memset(cmd, 0, sizeof(char) * 128);

		lv_dropdown_get_selected_str(widgets->password_text, buf, sizeof(buf));

		strcat(cmd, set_password);
		strcat(cmd, "'\"");
		strcat(cmd, buf);
		strcat(cmd, "\"'");
		LV_LOG_INFO("%s\n", cmd);

		if ((fp = popen(cmd, "r")) == NULL)
		{
			LV_LOG_ERROR("Set psk failed\b");
			return;
		}

		while (fgets(buf, sizeof(buf), fp) != NULL)
		{
			if (strstr(buf, "FAIL") != NULL)
			{
				LV_LOG_ERROR("Failed to set psk\n");
				pclose(fp);
				return;
			}
		}

		pclose(fp);

		free(cmd);
	}
}

void wifi_switch_value_changed(lv_event_t *e)
{
	lv_obj_t *obj = lv_event_get_target(e);

	if (lv_obj_has_state(obj, LV_STATE_CHECKED))
		system("wpa_supplicant -Dnl80211 -iwlan0 -B -c /etc/wpa_supplicant.conf");
	else
		system("killall wpa_supplicant");
}

void eth_send_btn_clicked(lv_event_t *e)
{
	enum
	{
		TCPClient,
		TCPServer,
		UDP
	} cur_selection;
	
	eth_widgets_t *widgets = lv_event_get_user_data(e);
	
	char *w_buf = lv_textarea_get_text(widgets->send_text);
	char *r_ip = NULL;
	char *r_port = NULL;

	if (widgets->is_connected) {

		cur_selection = lv_dropdown_get_selected(widgets->protocol_select);
		switch (cur_selection)
		{
		case TCPClient:
			tcp_write(widgets->socket_fd, w_buf, strlen(w_buf));
			break;
		case TCPServer:
			tcp_write(widgets->server_fd, w_buf, strlen(w_buf));
			break;
		case UDP:
			r_ip = lv_textarea_get_text(widgets->r_ip_text);
			r_port = lv_textarea_get_text(widgets->r_port_text);

			udp_send_to(widgets->socket_fd, r_ip, strtoul(r_port, NULL, 0), w_buf, strlen(w_buf));

			break;
		default:
			break;
		}
	}
}

static int tcp_client_thread(void *data)
{
	char buf[BUFSIZ] = {0};
	eth_widgets_t *widgets = (eth_widgets_t *)data;

	while (1) {
		if (tcp_read(widgets->socket_fd, buf, BUFSIZ) < 0)
		{
			LV_LOG_ERROR("Failed to read");
			return 1;
		}

		lv_textarea_add_text(widgets->recv_text, buf);
		memset(buf, 0, sizeof(buf));
	}

	return 0;
}

static int tcp_server_thread(void *data)
{
	int connfd, ret;
	eth_widgets_t *widgets = (eth_widgets_t *)data;
	char buf[BUFSIZ] = {0};

	while (1) 
	{

		if ((connfd = accept(widgets->socket_fd, (struct sockaddr*)NULL, NULL)) == -1) {
			LV_LOG_ERROR("accept server socket\n");
			return -1;
		}
		
		ret = tcp_read(connfd, buf, BUFSIZ);
		if (ret < 0)
		{
			LV_LOG_ERROR("Failed to read from server\n");
			close(connfd);
			return -1;
		}

		if (strncmp(buf, "quit", sizeof(char)*5) == 0) {
			close(connfd);
			return -1;
		}

		lv_textarea_set_text(widgets->recv_text, buf);
		memset(buf, 0, sizeof(buf));
	}

	return 0;
}

static int udp_thread(void *data)
{
	char buf[BUFSIZ] = {0};
	eth_widgets_t *widgets = (eth_widgets_t *)data;

	char *r_ip = lv_textarea_get_text(widgets->r_ip_text);
	char *r_port = lv_textarea_get_text(widgets->r_port_text);

	while (1)
	{
		if (udp_recv_from(widgets->socket_fd, r_ip, strtoul(r_port, NULL, 0), buf, BUFSIZ) < 0)
		{
			LV_LOG_ERROR("Failed to recv from UDP\n");
			return -1;
		}

		lv_textarea_set_text(widgets->recv_text, buf);
	}

	return 0;
}

void eth_connect_btn_clicked(lv_event_t *e)
{
	int fd;
	enum
	{
		TCPClient,
		TCPServer,
		UDP
	} cur_selection;
	eth_widgets_t *widgets = lv_event_get_user_data(e);

	if (!widgets->is_connected)
	{

		char *r_ip = lv_textarea_get_text(widgets->r_ip_text);
		char *r_port = lv_textarea_get_text(widgets->r_port_text);
		char *l_port = lv_textarea_get_text(widgets->l_port_text);

		cur_selection = lv_dropdown_get_selected(widgets->protocol_select);
		switch (cur_selection)
		{
		case TCPClient:
			if ((fd = tcp_create_and_connect(r_ip, strtoul(r_port, NULL, 0))) < 0)
			{
				LV_LOG_ERROR("Failed to create tcp client\n");
				widgets->socket_fd = 0;
				widgets->is_connected = 0;
				return;
			}

			widgets->socket_fd = fd;
			widgets->is_connected = 1;

			SDL_CreateThread(tcp_client_thread, "tcp_client_read", widgets);

			break;
		case TCPServer:
			if ((fd = tcp_create_and_listen(strtoul(l_port, NULL, 0))) < 0)
			{
				LV_LOG_ERROR("Failed to create tcp server\n");
				widgets->socket_fd = 0;
				widgets->is_connected = 0;
				return;
			}

			widgets->socket_fd = fd;
			widgets->is_connected = 1;

			SDL_CreateThread(tcp_server_thread, "tcp_server_read", widgets);

			break;
		case UDP:
			if ((fd = udp_create_socket(strtoul(l_port, NULL, 0))) < 0)
			{
				LV_LOG_ERROR("Failed to create UDP socket\n");
				widgets->socket_fd = 0;
				widgets->is_connected = 0;
			}

			widgets->socket_fd = fd;
			widgets->is_connected = 1;

			SDL_CreateThread(udp_thread, "udp_thread", widgets);

			break;
		default:
			return;
		}
	}
}

void eth_shutdown_btn_clicked(lv_event_t *e)
{
	eth_widgets_t *widgets = lv_event_get_user_data(e);

	if (widgets->is_connected) {
		close(widgets->socket_fd);
		widgets->is_connected = 0;
	}
}

void gpio_get_value(gpio_control_t *widgets)
{
	int i;
	char buf[128] = {0};
	char *export_cmd = "echo %u > /sys/class/gpio/export";
	char *direction_cmd = "echo in > /sys/class/gpio/gpio%u/direction";
	char *get_cmd = "cat /sys/class/gpio/gpio%u/value";
	FILE *fp = NULL;

	lv_dropdown_get_selected_str(widgets->gpio_select, buf, sizeof(buf));

	for (i = 0; i < MAX_GPIO_NUMS; i++)
	{
		if (strcmp(buf, gpios[i].name) == 0)
			break;
	}

	sprintf(buf, export_cmd, gpios[i].num);
	system(buf);
	memset(buf, 0, sizeof(buf));

	sprintf(buf, direction_cmd, gpios[i].num);
	system(buf);
	memset(buf, 0, sizeof(buf));

	sprintf(buf, get_cmd, gpios[i].num);

	fp = popen(buf, "r");
	if (!fp)
		return;

	memset(buf, 0, sizeof(buf));

	while (fgets(buf, sizeof(buf), fp) != NULL)
		;

	lv_dropdown_set_selected(widgets->gpio_value, strtoul(buf, NULL, 0));
}

void gpio_set_value(gpio_control_t *widgets)
{
	int i;
	char buf[128] = {0};
	char *export_cmd = "echo %u > /sys/class/gpio/export";
	char *direction_cmd = "echo out > /sys/class/gpio/gpio%u/direction";
	char *set_cmd = "echo %u > /sys/class/gpio/gpio%u/value";

	lv_dropdown_get_selected_str(widgets->gpio_select, buf, sizeof(buf));

	for (i = 0; i < MAX_GPIO_NUMS; i++)
	{
		if (strcmp(buf, gpios[i].name) == 0)
			break;
	}

	sprintf(buf, export_cmd, gpios[i].num);
	system(buf);
	memset(buf, 0, sizeof(buf));

	sprintf(buf, direction_cmd, gpios[i].num);
	system(buf);
	memset(buf, 0, sizeof(buf));

	sprintf(buf, set_cmd, lv_dropdown_get_selected(widgets->gpio_value), gpios[i].num);
	system(buf);
}