#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/wait.h>
#define BUFF_SIZE 17
MODULE_LICENSE("Dual BSD/GPL");

dev_t my_dev_id;
static struct class *my_class;
static struct device *my_device;
static struct cdev *my_cdev;

unsigned char fifo[BUFF_SIZE];
int hex_or_dec = 16;
int glava = 0;
int rep = 0;
int broj_ispisa = 1;
int endRead = 0;
int broj_clanova = 0;

//DECLARE_WAIT_QUEUE_HEAD(readQ);
//DECLARE_WAIT_QUEUE_HEAD(writeQ);

int fifo_open(struct inode *pinode, struct file *pfile);
int fifo_close(struct inode *pinode, struct file *pfile);
ssize_t fifo_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset);
ssize_t fifo_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset);

struct file_operations my_fops =
{
	.owner = THIS_MODULE,
	.open = fifo_open,
	.read = fifo_read,
	.write = fifo_write,
	.release = fifo_close,
};


int fifo_open(struct inode *pinode, struct file *pfile)
{
		printk(KERN_INFO "Succesfully opened fifo\n");
		return 0;
}

int fifo_close(struct inode *pinode, struct file *pfile)
{
		printk(KERN_INFO "Succesfully closed fifo\n");
		return 0;
}

ssize_t fifo_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	int ret;
	char buff[BUFF_SIZE];
	long int len = 0;
	int i;
	if (endRead)
	{
		endRead = 0;
		return 0;
	}

	//wait_event_interruptible(readQ, !(glava == rep));

	for(i = 0; i < broj_ispisa; ++i)
	{
		if(glava == rep)
		{
			printk(KERN_INFO "Fifo je prazan.\n");
			endRead = 1;
		}
		else
		{
			if(hex_or_dec == 10)
			{
				len = scnprintf(buff, BUFF_SIZE, "%d ", fifo[rep]);
				ret = copy_to_user(buffer, buff, len);
				printk(KERN_INFO "Uspjesno procitan broj: %d", fifo[rep]);
			}
			else
			{
				len = scnprintf(buff, BUFF_SIZE, "%d ", fifo[rep]);
				ret = copy_to_user(buffer, buff, len);
				printk(KERN_INFO "Uspjesno procitan broj %x", fifo[rep]);
			}
			rep = (rep + 1) % BUFF_SIZE;
			--broj_clanova;

			if(ret)
				return -EFAULT;

			//printk(KERN_INFO "Succesfully read\n");
			endRead = 1;
		}
	}

	printk(KERN_INFO "Trenutno stanje bafera je: %d\n", broj_clanova);

	//wake_up_interruptible(&writeQ);

	return 1;
}

ssize_t fifo_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	char buff[50];
	int ret;
	char *p;
	unsigned int z;
	ret = copy_from_user(buff, buffer, length);
	if(ret)
		return -EFAULT;

	buff[length-1] = '\0';
	p = buff;
	//wait_event_interruptible(writeQ, ((glava + 1) % BUFF_SIZE) == rep);

	if(!strncmp("num=", buff, 4))
	{
		sscanf(buff, "num=%d", &broj_ispisa);
		printk(KERN_INFO "Broj ispisa clanova promjenjen na: %d\n", broj_ispisa);
	}
	else if(!strcmp("hex", buff))
	{
		hex_or_dec = 16;
		printk(KERN_INFO "Ispis u hex.\n");
	}
	else if(!strcmp("dec", buff))
	{
		hex_or_dec = 10;
		printk(KERN_INFO "Ispis u dec.\n");
	}
	else
	{
		while(1)
		{
			sscanf(p, "%x,", &z);
			if(((glava + 1) % BUFF_SIZE) == rep)
			{
				printk(KERN_WARNING "Fifo je pun\n");
				break;
			}
			else
			{
				fifo[glava] = z;
				glava = (glava + 1) % BUFF_SIZE;
				++broj_clanova;
				printk(KERN_INFO "Uspjesno upisan broj %d u bafer\n", z);

				while(p[0] != ',' && p[0] != '\0')
					++p;
				if(*p == ',')
					++p;
				else
					break;
			}
		}
	}
	//wake_up_interruptible(&readQ);

	printk(KERN_INFO "Trenutno stanje bafera je: %d\n", broj_clanova);

	return length;
}

static int __init fifo_init(void)
{
   	int ret = 0;
	int i=0;

	//Initialize array
	for (i = 0; i < 16; ++i)
		fifo[i] = 0;

   ret = alloc_chrdev_region(&my_dev_id, 0, 1, "fifo");
   if (ret){
      printk(KERN_ERR "failed to register char device\n");
      return ret;
   }
   printk(KERN_INFO "char device region allocated\n");

   my_class = class_create(THIS_MODULE, "fifo_class");
   if (my_class == NULL){
      printk(KERN_ERR "failed to create class\n");
      goto fail_0;
   }
   printk(KERN_INFO "class created\n");

   my_device = device_create(my_class, NULL, my_dev_id, NULL, "fifo");
   if (my_device == NULL){
      printk(KERN_ERR "failed to create device\n");
      goto fail_1;
   }
   printk(KERN_INFO "device created\n");

	my_cdev = cdev_alloc();
	my_cdev->ops = &my_fops;
	my_cdev->owner = THIS_MODULE;
	ret = cdev_add(my_cdev, my_dev_id, 1);
	if (ret)
	{
     		printk(KERN_ERR "failed to add cdev\n");
		goto fail_2;
	}
   printk(KERN_INFO "cdev added\n");
   printk(KERN_INFO "Hello world\n");

   return 0;

   fail_2:
      device_destroy(my_class, my_dev_id);
   fail_1:
      class_destroy(my_class);
   fail_0:
      unregister_chrdev_region(my_dev_id, 1);
   return -1;
}

static void __exit fifo_exit(void)
{
   cdev_del(my_cdev);
   device_destroy(my_class, my_dev_id);
   class_destroy(my_class);
   unregister_chrdev_region(my_dev_id, 1);
   printk(KERN_INFO "Goodbye, cruel world\n");
}

module_init(fifo_init);
module_exit(fifo_exit);
