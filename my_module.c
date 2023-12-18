#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/time.h>

MODULE_AUTHOR("Present Mykhailo Potapenko");
MODULE_DESCRIPTION("Lab1 test kernel module");
MODULE_LICENSE("MIT");

#define MSG_PREF "TEST: "

static int print_time(struct seq_file *m, void *v) {
    struct timespec64 now;
    ktime_get_real_ts64(&now);

    struct tm timeinfo;
    time64_to_tm(now.tv_sec, 0, &timeinfo);

    // Додаємо зсув часового поясу (2 години для прикладу, ви можете змінити це значення)
    timeinfo.tm_hour += 2;

    seq_printf(m, "Current time: %04d-%02d-%02d %02d:%02d:%02d.%09ld\n",
               timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
               timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, now.tv_nsec);
    return 0;
}

static int time_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, print_time, NULL);
}

static const struct proc_ops time_proc_ops = {
    .proc_open = time_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init time_module_init(void) {
    proc_create_data("my_module_time", 0, NULL, &time_proc_ops, NULL);
    return 0;
}

static void __exit time_module_exit(void) {
    remove_proc_entry("my_module_time", NULL);
    printk(KERN_ERR MSG_PREF "Hasta la vista, Kernel!\n");
}

module_init(time_module_init);
module_exit(time_module_exit);