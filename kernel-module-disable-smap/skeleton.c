#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/hardirq.h>
#include <linux/debugfs.h>
#include <asm/paravirt.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wade Mealing");
MODULE_DESCRIPTION("Disable SMAP");

static long cr4_prev, cr4_next;


static int __init skeleton_init(void) {

  
  printk (KERN_INFO "Your systems SMAP will be disabled!!");
  
  cr4_prev = __read_cr4();

  cr4_next = cr4_prev & ~(X86_CR4_SMEP);

  printk (KERN_INFO "CR4 was temporarily changed from %lx to %lx\n", cr4_prev, cr4_next);  

  __write_cr4(cr4_next);

  return 0;

}

static void skeleton_cleanup(void) {

  /* Attempt to re-enable SMEP */

  __write_cr4(cr4_prev);
  printk( KERN_INFO "Cleaning up skeleton-demo-module\n");
  
}

/* register entry/exit points for module */
module_init(skeleton_init);
module_exit(skeleton_cleanup);
