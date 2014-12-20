#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>

#define DRIVER_NAME "BeagleBone_Driver"

static dev_t Hardware_ID;
static struct class *DevClass;
static struct cdev theCdev;

static struct file_operations fops = {
  .owner = THIS_MODULE
};

int __init buf_init(void){
  printk(KERN_INFO "Driver installed.\n");

  int errNo = 0;
  errNo = alloc_chrdev_region(&Hardware_ID,0,1,DRIVER_NAME);

  if(errNo != 0){
    printk("Driver exists already");
    return errNo;
  }

  DevClass = class_create(THIS_MODULE, DRIVER_NAME);

  if(device_create(DevClass,NULL,Hardware_ID,NULL,DRIVER_NAME) == (struct device*)ERR_PTR){
    printk(KERN_ALERT"Failed to create beaglebone driver");
    return -1;
  }

  cdev_init(&theCdev, &fops);

  errNo = cdev_add(&theCdev,Hardware_ID,1);
  if(errNo != 0){
    printk(KERN_ALERT"Failed to create driver allocation");
    return -1;
  }
  return 0;
}

void __exit buf_exit(void){
  printk(KERN_INFO "Uninstall driver.\n");
  cdev_del(&theCdev);

  device_destroy(DevClass,Hardware_ID);
  class_destroy(DevClass);

  unregister_chrdev_region(Hardware_ID,1);
}

module_init(buf_init);
module_exit(buf_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anthony Legault-Cesta, Christopher Lariviere");
MODULE_DESCRIPTION("BeagleBone Driver");
