/*******************************************************************************
*
* (c) 2015 by arvero GmbH
* arvero GmbH
* Winchesterstraße 2
* D-35394 Gießen
*
********************************************************************************
*
* Module      : gpio.h
* Function    : Prototypes for gpio interface
* Author      : Hubert
* Date        : 2015-10-29
*
*******************************************************************************/ 

///////////////
// Prototypes
///////////////
int gpio_isHigh(int gpio_fd);
int gpio_export(unsigned int gpio);
int gpio_unexport(unsigned int gpio);
int gpio_set_dir(unsigned int gpio, unsigned int out_flag);
int gpio_set_value(unsigned int gpio, unsigned int value);
int gpio_get_value(unsigned int gpio, unsigned int *value);
int gpio_set_edge(unsigned int gpio, char *edge);
int gpio_set_active_low(unsigned int gpio, unsigned int mode);
int gpio_fd_open(unsigned int gpio);
int gpio_fd_close(int fd);
