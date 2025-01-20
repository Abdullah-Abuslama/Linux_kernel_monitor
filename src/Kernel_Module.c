// File: Kernel_Module.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdullah Abuslama");
MODULE_DESCRIPTION("Kernel Internals Monitor");

static struct proc_dir_entry *proc_entry;

// Structure to hold kernel statistics
struct kernel_stats {
    unsigned long total_ram;
    unsigned long free_ram;
    unsigned long proc_count;
    unsigned long cpu_total;
    unsigned long cpu_idle;
};

static int stats_show(struct seq_file *m, void *v)
{
    struct kernel_stats stats;
    struct sysinfo si;
    struct task_struct *task;
    
    // Get memory information
    si_meminfo(&si);
    stats.total_ram = si.totalram * PAGE_SIZE;
    stats.free_ram = si.freeram * PAGE_SIZE;
    
    // Count processes
    stats.proc_count = 0;
    for_each_process(task) {
        stats.proc_count++;
    }
    
    // Get basic CPU statistics
    stats.cpu_total = jiffies;
    stats.cpu_idle = 0;  // We'll implement this differently
    
    // Write data to seq_file
    seq_printf(m, "%lu %lu %lu %lu %lu\n",
               stats.total_ram,
               stats.free_ram,
               stats.proc_count,
               stats.cpu_total,
               stats.cpu_idle);
    
    return 0;
}

static int stats_open(struct inode *inode, struct file *file)
{
    return single_open(file, stats_show, NULL);
}

static const struct proc_ops stats_ops = {
    .proc_open = stats_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init kernel_monitor_init(void)
{
    proc_entry = proc_create("kernel_monitor", 0444, NULL, &stats_ops);
    if (!proc_entry) {
        return -ENOMEM;
    }
    printk(KERN_INFO "Kernel monitor module loaded\n");
    return 0;
}

static void __exit kernel_monitor_exit(void)
{
    proc_remove(proc_entry);
    printk(KERN_INFO "Kernel monitor module unloaded\n");
}

module_init(kernel_monitor_init);
module_exit(kernel_monitor_exit);