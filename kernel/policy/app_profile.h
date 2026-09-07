#ifndef __KSU_H_APP_PROFILE
#define __KSU_H_APP_PROFILE

#include "uapi/app_profile.h"
#include "linux/init.h"

// This flag doubles as the full "KSU disabled for this process tree" switch:
// fork-inherited via thread_info.flags, irreversible. When set, escape_with_
// root_profile() aborts, is_manager()/is_allow_uid() are always false, every
// supercall ioctl returns -EPERM, the reboot magic fd-install is skipped, and
// setresuid no longer installs/caches anything.
#ifdef CONFIG_64BIT
#define TIF_KSU_DISABLE_ESCAPE_WITH_ROOT 63
// bit 62 is taken by TIF_PROC_NON_PRIVILEGE (kernel/feature/sucompat.h)
#else
#define TIF_KSU_DISABLE_ESCAPE_WITH_ROOT 31
// bit 30 is taken by TIF_PROC_NON_PRIVILEGE (kernel/feature/sucompat.h)
#endif

// Escalate current process to root with the appropriate profile
int escape_with_root_profile(void);

void disable_seccomp(void);
void escape_to_root_for_init(void);

void __init ksu_app_profile_init(void);

#endif
