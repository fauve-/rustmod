#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/slab.h> 


char __morestack[1024];

//prototype for our rust fn
extern void rust_main(void);


//something terrible has happened
void abort(void){
  BUG();
}

//provide a malloc to rust's core crate
void *malloc(size_t s){
  return kmalloc(s, GFP_KERNEL);
}

//and a free
void free(void *ptr){
  kfree(ptr);
}

//init the module
static int rustmod_init(void){
  printk(KERN_INFO "we've initted rustmod\n");
  rust_main();
  return 0;
}

//and for when we wanna exit
static void rustmod_exit(void){
  printk(KERN_INFO "rustmod has left the building\n");
}

module_init(rustmod_init);
module_exit(rustmod_exit);

MODULE_LICENSE("MIT");
