#
# Regular cron jobs for the raspbed package
#
0 4	* * *	root	[ -x /usr/bin/raspbed_maintenance ] && /usr/bin/raspbed_maintenance
