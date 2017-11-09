#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/hardirq.h>
#include <linux/debugfs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wade Mealing");
MODULE_DESCRIPTION("Just a test, nothing serious, just for fun!");

static ssize_t target_read_write(struct file *f, const char __user *buf,
		size_t count, loff_t *off)
{

    /* Yes i realise this is cheeky, but its encouragement :*) */
    return -EAGAIN;
}


/* Handles to the files we will create */
static struct dentry *target_root, *target_de;

/* Structs telling the kernel how to handle writes to our files. */
static const struct file_operations bug_fops = {
	.write = target_read_write,
};

/*
 * To clean up our module, we just remove the two files and the
 * directory.
 */
static void cleanup_debugfs(void) {
	if (target_de) debugfs_remove(target_de);
	if (target_root) debugfs_remove(target_root);
}

/*
 * This function is called at module load time, and creates the
 * directory in debugfs and the two files.
 */
static int __init skeleton_init(void)
{

	target_root = debugfs_create_dir("skeleton_bug", NULL);
        
	if (!target_root) {
		printk(KERN_ERR "skeleton_bug: creating root dir failed\n");
		return -ENODEV;
	}

	/*
	 * Create the file that we're going to have a buggy write on.
	 * structs defined above so that the kernel knows how to
	 * handle writes to them, and set the permissions to be
	 * writable by anyone.
	 */
	target_de = debugfs_create_file("target", 0222, target_root,
				      NULL, &bug_fops);

	if (!target_de)
		goto out_err;

	return 0;
out_err:
	cleanup_debugfs();

	return -ENODEV;
}



static void skeleton_cleanup(void) {
    cleanup_debugfs();
    printk( KERN_INFO "Cleaning up skeleton-demo-module\n");
}

/* register entry/exit points for module */
module_init(skeleton_init);
module_exit(skeleton_cleanup);
