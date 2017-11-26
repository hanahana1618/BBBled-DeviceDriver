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

//#include file with the Morse Code equivalences

#define  DEVICE_NAME "BBBled"    
#define  CLASS_NAME  "BBBdev" 

MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Ivette Prieto Castro");    
MODULE_DESCRIPTION("Linux device driver for the B^3 in order to flash the LEDs in Morse Code");  
MODULE_VERSION("0.1");  


static int major = 0;                 
static char message[256] = {0};
static short sizeMssg = 0;            
static struct class*  BBBledClass  = NULL; 
static struct device* BBBledDevice = NULL; 
static DEFINE_MUTEX(BBBledMutex);  //mutex unlocked by default
 
static int dev_open(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *); //READ to LEDs instead of to the user
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);  //get strings from the user to be displayed in Morse Code
static int dev_release(struct inode *, struct file *);

#endif