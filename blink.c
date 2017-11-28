//#include <linux/init.h>      // Macros used to mark up functions e.g., __init __exit
//#include <linux/module.h>    // Core header for loading LKMs into the kernel
//#include <linux/kernel.h>    // Contains types, macros, functions for the kernel - printk()
//#include <linux/errno.h>     // error codes
//#include <linux/delay.h>
//#include <linux/string.h>
//#include <linux/types.h>  
//#include <linux/fs.h>
//#include <linux/device.h>


static int __init hello_init(void){
   

   return 0;
}



static void __exit hello_exit(void){
   BBBledOff();
   BBBstartHeartbeat();
   printk(KERN_INFO "TDR: Goodbye %s from the Test LKM!\n", name);
}


module_init(hello_init);
module_exit(hello_exit);


