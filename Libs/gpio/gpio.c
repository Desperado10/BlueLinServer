/*******************************************************************************
*
* Module      : gpio.c
* Function    : GPIO interface functions
* Author      : Hubert
* Date        : 2015-12-26
*
*******************************************************************************/

#include <stdio.h>  // for snprintf()
#include <string.h> // for strlen()
#include <unistd.h> // for write(), close(), read()
#include <fcntl.h>  // for open()
#include <poll.h>   // for poll()
#include "gpio.h"

/****************************************************************
* Macros
****************************************************************/

#define CHECK_FD(fd) if(fd < 0) \
                       return fd;

/****************************************************************
* Defines
****************************************************************/
 
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF        64
#define HIGH           1
#define LOW            0


/****************************************************************
 * gpio_isHigh
 ****************************************************************/

int gpio_isHigh(int gpio_fd)
{
  char buf;
  int retval;
  struct pollfd fdset[1] = {};

  fdset[0].fd     = gpio_fd;
  fdset[0].events = POLLPRI; // Wait for state change

  if((retval = poll(fdset, 1, -1)) <= 0)
  {
    printf("\nError: poll() failed!\n");
    return LOW;
  }

  if(fdset[0].revents & POLLPRI)
  {
    if(read(fdset[0].fd, &buf, 1) < 0)
    {
      printf("Error: read() failed when getting gpio state!\n");
      return LOW;
    }

    if(buf == 48) /* ASCII 48 == Decimal 0 */
      return LOW;
    else
      return HIGH;
  }

  if(fdset[0].revents & POLLERR)
  {
    printf("Error: return event of poll() is POLLERR\n");
    return LOW;
  }

  if(fdset[0].revents & POLLHUP)
  {
    printf("Error: return event of poll() is POLLHUP\n");
    return LOW;
  }

  if(fdset[0].revents & POLLNVAL)
  {
    printf("Error: return event of poll() is POLLNVAL\n");
    return LOW;
  }

  printf("poll() comes back without setting return event?!\n");
  return LOW;
}

/****************************************************************
 * gpio_export
 ****************************************************************/

int gpio_export(unsigned int gpio)
{
  int fd, len;
  char buf[MAX_BUF];

  fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
  CHECK_FD(fd);

  len = snprintf(buf, sizeof(buf), "%u", gpio);
  write(fd, buf, len);
  close(fd);

  return 0;
}

/****************************************************************
 * gpio_unexport
 ****************************************************************/

int gpio_unexport(unsigned int gpio)
{
  int fd, len;
  char buf[MAX_BUF];

  fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
  CHECK_FD(fd);

  len = snprintf(buf, sizeof(buf), "%u", gpio);
  write(fd, buf, len);
  close(fd);
  return 0;
}

/****************************************************************
 * gpio_set_dir
 ****************************************************************/

int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
  int fd;
  char buf[MAX_BUF];

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%u/direction", gpio);

  fd = open(buf, O_WRONLY);
  CHECK_FD(fd);

  if(out_flag)
    write(fd, "out", 4);
  else
    write(fd, "in", 3);

  close(fd);
  return 0;
}

/****************************************************************
 * gpio_set_value
 ****************************************************************/

int gpio_set_value(unsigned int gpio, unsigned int value)
{
  int fd;
  char buf[MAX_BUF];

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%u/value", gpio);

  fd = open(buf, O_WRONLY);
  CHECK_FD(fd);

  if(value)
    write(fd, "1", 2);
  else
    write(fd, "0", 2);

  close(fd);
  return 0;
}

/****************************************************************
 * gpio_get_value
 ****************************************************************/

int gpio_get_value(unsigned int gpio, unsigned int *value)
{
  int fd;
  char ch;
  char buf[MAX_BUF];

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%u/value", gpio);

  fd = open(buf, O_RDONLY);
  CHECK_FD(fd);

  read(fd, &ch, 1);

  if(ch != '0')
    *value = HIGH;
  else
    *value = LOW;

  close(fd);
  return 0;
}


/****************************************************************
 * gpio_set_edge
 ****************************************************************/

int gpio_set_edge(unsigned int gpio, char *edge)
{
  int fd;
  char buf[MAX_BUF];

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%u/edge", gpio);

  fd = open(buf, O_WRONLY);
  CHECK_FD(fd);

  write(fd, edge, strlen(edge) + 1); 
  close(fd);
  return 0;
}

/****************************************************************
 * gpio_set_active_low
 ****************************************************************/

int gpio_set_active_low(unsigned int gpio, unsigned int mode)
{
  int fd;
  char buf[MAX_BUF];

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%u/active_low", gpio);

  fd = open(buf, O_WRONLY);
  CHECK_FD(fd);

  if(mode)
    write(fd, "1", 2);
  else
    write(fd, "0", 2);

  close(fd);
  return 0; 
}

/****************************************************************
 * gpio_fd_open
 ****************************************************************/

int gpio_fd_open(unsigned int gpio)
{
  int fd;
  char buf[MAX_BUF];

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%u/value", gpio);

  fd = open(buf, O_RDONLY | O_NONBLOCK );
  CHECK_FD(fd);

  return fd;
}

/****************************************************************
 * gpio_fd_close
 ****************************************************************/

int gpio_fd_close(int fd)
{
  return close(fd);
}
