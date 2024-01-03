#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int tsu_counter = 1;

static int tsu_proc_show(struct seq_file *m, void *v) {
    seq_printf(m, "%d\n", tsu_counter);
    tsu_counter = (tsu_counter % 3) + 1;

    return 0;
}

static int tsu_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, tsu_proc_show, NULL);
}

static const struct proc_ops tsu_proc_fops = {
    .proc_open = tsu_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init tsu_init(void) {
    proc_create("tsu", 0, NULL, &tsu_proc_fops);
    pr_info("Welcome to the Tomsk State University\n");
    return 0;
}

static void __exit tsu_exit(void) {
    remove_proc_entry("tsu", NULL);
    pr_info("Tomsk State University forever!\n\n");
}

module_init(tsu_init);
module_exit(tsu_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stepan TSU 2024");
