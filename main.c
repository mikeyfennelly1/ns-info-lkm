#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/nsproxy.h>
#include <linux/pid.h>

static int pid = 1;
module_param(pid, int, 0644);
MODULE_PARAM_DESC(pid, "Process ID to inspect namespaces.");

static int __init ns_info_init(void)
{
    struct task_struct *task;
    struct nsproxy *ns;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task) {
        pr_err("Process %d not found\n", pid);
        return -ESRCH;
    }

    ns = task->nsproxy;
    if (!ns) {
        pr_err("No namespace proxy found for process %d\n", pid);
        return -EINVAL;
    }

    pr_info("Namespace information for process %d:\n", pid);
    pr_info("Mount namespace inode: %lu\n", ns->mnt_ns->ns.inum);
    pr_info("Network namespace inode: %lu\n", ns->net_ns->ns.inum);
    pr_info("PID namespace inode: %lu\n", ns->pid_ns_for_children->ns.inum);
    pr_info("IPC namespace inode: %lu\n", ns->ipc_ns->ns.inum);
    pr_info("UTS namespace inode: %lu\n", ns->uts_ns->ns.inum);
    pr_info("User namespace inode: %lu\n", task_cred_xxx(task)->user_ns->ns.inum);

    return 0;
}

static void __exit ns_info_exit(void) {
    pr_info("Namespace module exiting\n");
}

module_init(ns_info_init);
module_exit(ns_info_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module to get process namespace information");