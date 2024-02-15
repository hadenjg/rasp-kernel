#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/timekeeping.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <asm/atomic.h>

#define GPIO_TRIGGER (26)
#define GPIO_ECHO (6)

struct cdev *hc_sr04_cdev;
int drv_major = 0;
int gpio_irq_number;

wait_queue_head_t wait_for_echo;
volatile int condition_echo;

volatile ktime_t ktime_start, ktime_end;

// there should be 60ms between measurements
ktime_t ktime_last_measurement;

atomic_t opened = ATOMIC_INIT(-1);

//only one thread of execution shall reaad at the same time since a read triggers hw measurement
DEFINE_SEMAPHORE(read_semaphore);

static irqreturn_t gpio_echo_irq_handler(int irq, void *dev_id)
{
  int gpio_value;
  gpio_value = gpio_get_value(GPIO_ECHO);

  //rising edge start time
  if(gpio_value == 1)
  {
    ktime_start = ktime_get();
  }
  //falling edge 
  else if(gpio_value == 0)
  {
    ktime_end = ktime_get();

    condition_echo = 1;
    wake_up_interruptible(&wait_for_echo);
  }

  return IRQ_HANDLED;
}