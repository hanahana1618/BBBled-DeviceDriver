//CHANGES TO IMPLEMENT
 /*
 * file bbb_dev.c
 * LKM that retrieves a string from the user and flashes it in Morse code on the LEDs at the B^3 for Embedded OS at FIU
 */
 
#include "bbb_dev.h"
#include "McodeMod.h"

static struct file_operations fops = {
   .owner = THIS_MODULE,
   .open = dev_open,
   .write = dev_write,
   .display = dev_display,
   .release = dev_release
};
 
static int __init bbb_dev_init(void) { 
	//save major number
   major = register_chrdev(0, DEVICE_NAME, &fops);
   if (major<0){
      printk(KERN_ALERT "bbb_dev failed to register major number\n");
      return major; 
   }
   printk(KERN_INFO "bbb_dev: registered a major number %d\n", major);
 
   // Register the device class
   bbb_devClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(bbb_devClass)) {           
      unregister_chrdev(major, DEVICE_NAME);
      printk(KERN_ALERT "Failed to register device class. Exiting init\n");
      return PTR_ERR(bbb_devClass);        
   }
   printk(KERN_INFO "bbb_dev: device class registered correctly\n");
 
   // Register the device driver
   bbb_devDevice = device_create(bbb_devClass, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
   if (IS_ERR(bbb_devDevice)) {     //unregister if error
      class_destroy(bbb_devClass);          
      unregister_chrdev(major, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device class\n");
      return PTR_ERR(bbb_devDevice);
   }
   printk(KERN_INFO "bbb_dev: device class created correctly\n"); 

   //lock mutex when the device driver is init
   mutex_init(&bbb_devMutex);

   return 0;
}
 
static int dev_open(struct inode *inodep, struct file *filep){
	//book code: struct dev

   if (!mutex_trylock(&bbb_devMutex)) {
      //print this to user space, not kernel log
      printk("Cannot Access the Device Driver bbb_dev because another process is using it.\n");
      //return something here
      return -EBUSY;
   }

   printk(KERN_INFO "bbb_dev: Device has been successfully opened.\n");
   return 0;
}
 
 //re-implement this whole function so that it sends the info to the LEDs, not the user
//static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
//   printk(KERN_INFO "String from user received");
   

   //return -EFAULT;
//}

static int dev_display() {


   //return 0 on success
   return 0;
}

//read from the user
static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
   sprintf(message, "%s(%zu letters)", buffer, len);   
   sizeMssg = strlen(message);  

   //add code here to send the message to the B^3 to be displayed using the LEDs

   //debugging for the write function             
   printk(KERN_INFO "TestChar: Received %zu characters from the user\n", len);
   return len;
}

 
 //Add here code to release the LEDs after flashing is done
static int dev_release(struct inode *inodep, struct file *filep) {
	//hardware to release code

   //unlock the mutex so that another use can have it
   mutex_unlock(&bbb_devMutex);

   //debugging for make-believe hardware and mutex unlocked
   printk(KERN_INFO "bbb_dev: Device has been successfully closed\n");
   return 0;
}

static void __exit bbb_dev_exit(void) {
   //destroy the mutex so that the next user can have it
   mutex_destroy(&bbb_devMutex);

   //make sure to sign out of the device driver
   device_destroy(bbb_devClass, MKDEV(major, 0));    
   class_unregister(bbb_devClass);                         
   class_destroy(bbb_devClass);                    
   unregister_chrdev(major, DEVICE_NAME);     

   //print out debug message on the kernel log
   printk(KERN_INFO "bbb_dev: Goodbye from the LKM!\n");
}
 
module_init(bbb_dev_init);
module_exit(bbb_dev_exit);