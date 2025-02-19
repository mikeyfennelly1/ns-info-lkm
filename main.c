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
}