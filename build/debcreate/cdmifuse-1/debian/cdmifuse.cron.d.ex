#
# Regular cron jobs for the cdmifuse package
#
0 4	* * *	root	[ -x /usr/bin/cdmifuse_maintenance ] && /usr/bin/cdmifuse_maintenance
