#ifndef BECOME_DAEMON_H
#define BECOME_DAEMON_H

#define BD_NO_CHDIR
#define BD_NO_CLOSE_FILES
#define BD_NO_REOPEN_STD_FDS

#define BD_NO_UMASK0

#define BD_MAX_CLOSE 8192

int becomeDaemon(int flags);

#endif
