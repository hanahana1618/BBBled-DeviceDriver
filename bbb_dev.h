#ifndef BBB_DEV_H
#define BBB_DEV_H


#include <linux/init.h>           // macro  __init __exit
#include <linux/module.h>       
#include <linux/device.h>        
#include <linux/errno.h>
#include <linux/kernel.h>        
#include <linux/fs.h>             // file system in Linux
#include <asm/uaccess.h>  
#include <linux/mutex.h>  
#include "McodeMod.h" 

//Blinking the LED includes
#include <delay.h>
#include <string.h>
#include <types.h>
#include <linux/kdev_t.h> 
#include <linux/ioport.h>
#include <linux/highmem.h>
#include <linux/pfn.h>
#include <linux/version.h>
#include <linux/ioctl.h>
#include <net/sock.h>
#include <net/tcp.h>


//#include file with the Morse Code equivalences

#define  DEVICE_NAME "BBB_dev"    
#define  CLASS_NAME  "BBB" 

MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Ivette Prieto Castro");    
MODULE_DESCRIPTION("Linux device driver for the B^3 in order to flash the LEDs in Morse Code");  
MODULE_VERSION("0.1");  

//define listing for the LEDs to turn on
#define GPIO1_START_ADDR 0x4804C000
#define GPIO1_END_ADDR   0x4804e000
#define GPIO1_SIZE (GPIO1_END_ADDR - GPIO1_START_ADDR)

#define GPIO_SETDATAOUT 0x194
#define GPIO_CLEARDATAOUT 0x190
#define USR3 (1<<24)
#define USR0 (1<<21)

#define USR_LED USR0
#define LED0_PATH "/sys/class/leds/beaglebone:green:usr0"



//funcs for LEDs to blink
void BBBremoveTrigger(void);
void BBBstartHeartbeat(void);
void BBBledOn(void);
void BBBledOff(void);

//variables for the device driver
static int major = 0;                 
static char message[256] = {0};
static short sizeMssg = 0;            
static struct class*  BBBledClass  = NULL; 
static struct device* BBBledDevice = NULL; 
static DEFINE_MUTEX(BBBledMutex);  //mutex unlocked by default

//static variables declared for the LED mapping, notice they are static
static volatile void *gpio_addr;
static volatile unsigned int *gpio_setdataout_addr;
static volatile unsigned int *gpio_cleardataout_addr;

 
//file declarations for the device driver
static int dev_open(struct inode *, struct file *);
//static ssize_t dev_read(struct file *, char *, size_t, loff_t *); //display to LEDs
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);  //get strings from the user to be displayed in Morse Code
static int dev_release(struct inode *, struct file *);
//return something to the LEDs in order to display Morse code
static int dev_display();

//LED func and others
ssize_t write_vaddr_disk(void *, size_t);
int setup_disk(void);
void cleanup_disk(void);
static void disable_dio(void);

static struct file * f = NULL;
static int reopen = 0;
static char *filepath = 0;
static char fullFileName[1024];
static int dio = 0;

static char *name = "hello";   ///< An example LKM argument -- default value is "world"

//does this go in the header file
module_param(name, charp, S_IRUGO);
///< Param desc. charp = char ptr, S_IRUGO can be read/not changed

MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");  ///< parameter descript


#endif