//#include <linux/init.h>      // Macros used to mark up functions e.g., __init __exit
//#include <linux/module.h>    // Core header for loading LKMs into the kernel
//#include <linux/kernel.h>    // Contains types, macros, functions for the kernel - printk()
//#include <linux/errno.h>     // error codes
//#include <linux/delay.h>
//#include <linux/string.h>
//#include <linux/types.h>  
//#include <linux/fs.h>
//#include <linux/device.h>









ssize_t write_vaddr_disk(void *, size_t);
int setup_disk(void);
void cleanup_disk(void);
static void disable_dio(void);

static struct file * f = NULL;
static int reopen = 0;
static char *filepath = 0;
static char fullFileName[1024];
static int dio = 0;


module_param(name, charp, S_IRUGO);
///< Param desc. charp = char ptr, S_IRUGO can be read/not changed

MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");  ///< parameter descript


static int __init hello_init(void){
   printk(KERN_INFO "TDR: Hello %s from Test LKM!\n", name);
   gpio_addr = ioremap(GPIO1_START_ADDR, GPIO1_SIZE);
   if(!gpio_addr) {
     printk (KERN_ERR "HI: ERROR: Failed to remap memory for GPIO Bank 1.\n");
   }

   gpio_setdataout_addr   = gpio_addr + GPIO_SETDATAOUT;
   gpio_cleardataout_addr = gpio_addr + GPIO_CLEARDATAOUT;

   BBBremoveTrigger();
   BBBledOn();
   msleep(1000);
   BBBledOff();
   msleep(1000);
   BBBledOn();

   return 0;
}



static void __exit hello_exit(void){
   BBBledOff();
   BBBstartHeartbeat();
   printk(KERN_INFO "TDR: Goodbye %s from the Test LKM!\n", name);
}


module_init(hello_init);
module_exit(hello_exit);


void BBBremoveTrigger(){
   // remove the trigger from the LED
   int err = 0;
  
  strcpy(fullFileName, LED0_PATH);
  strcat(fullFileName, "/");
  strcat(fullFileName, "trigger");
  printk(KERN_INFO "File to Open: %s\n", fullFileName);
  filepath = fullFileName; // set for disk write code
  err = setup_disk();
  err = write_vaddr_disk("none", 4);
  cleanup_disk();
}

void BBBstartHeartbeat(){
   // start heartbeat from the LED
     int err = 0;
  

  strcpy(fullFileName, LED0_PATH);
  strcat(fullFileName, "/");
  strcat(fullFileName, "trigger");
  printk(KERN_INFO "File to Open: %s\n", fullFileName);
  filepath = fullFileName; // set for disk write code
  err = setup_disk();
  err = write_vaddr_disk("heartbeat", 9);
  cleanup_disk();
}

void BBBledOn(){
*gpio_setdataout_addr = USR_LED;
}


void BBBledOff(){
*gpio_cleardataout_addr = USR_LED;
}


static void disable_dio() {
   dio = 0;
   reopen = 1;
   cleanup_disk();
   setup_disk();
}

int setup_disk() {
   mm_segment_t fs;
   int err;

   fs = get_fs();
   set_fs(KERNEL_DS);
	
   if (dio && reopen) {	
      f = filp_open(filepath, O_WRONLY | O_CREAT | O_LARGEFILE | O_SYNC | O_DIRECT, 0444);
   } else if (dio) {
      f = filp_open(filepath, O_WRONLY | O_CREAT | O_LARGEFILE | O_TRUNC | O_SYNC | O_DIRECT, 0444);
   }
	
   if(!dio || (f == ERR_PTR(-EINVAL))) {
      f = filp_open(filepath, O_WRONLY | O_CREAT | O_LARGEFILE | O_TRUNC, 0444);
      dio = 0;
   }
   if (!f || IS_ERR(f)) {
      set_fs(fs);
      err = (f) ? PTR_ERR(f) : -EIO;
      f = NULL;
      return err;
   }

   set_fs(fs);
   return 0;
}

void cleanup_disk() {
   mm_segment_t fs;

   fs = get_fs();
   set_fs(KERNEL_DS);
   if(f) filp_close(f, NULL);
   set_fs(fs);
}

ssize_t write_vaddr_disk(void * v, size_t is) {
   mm_segment_t fs;

   ssize_t s;
   loff_t pos;

   fs = get_fs();
   set_fs(KERNEL_DS);
	
   pos = f->f_pos;
   s = vfs_write(f, v, is, &pos);
   if (s == is) {
      f->f_pos = pos;
   }					
   set_fs(fs);
   if (s != is && dio) {
      disable_dio();
      f->f_pos = pos;
      return write_vaddr_disk(v, is);
   }
   return s;
}


