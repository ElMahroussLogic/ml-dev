/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

#include <_types.h>
#include <sys/unistd.h>
#include <sys/_types/_gid_t.h>
#include <sys/_types/_intptr_t.h>
#include <sys/_types/_off_t.h>
#include <sys/_types/_pid_t.h>

namespace posix
{
	ML_EXTERN_C int				dup(int);
	ML_EXTERN_C int				dup2(int, int);
	ML_EXTERN_C int				execl(const char* __path, const char* __arg0, ...);
	ML_EXTERN_C int				execle(const char* __path, const char* __arg0, ...);
	ML_EXTERN_C int				execv(const char* __path, char* const* __argv);
	ML_EXTERN_C int				execve(const char* __file, char* const* __argv, char* const* __envp);
	ML_EXTERN_C int				execvp(const char* __file, char* const* __argv);
	ML_EXTERN_C pid_t			fork(void);
	ML_EXTERN_C long			fpathconf(int, int);
	ML_EXTERN_C char*			getcwd(char*, size_t);
	ML_EXTERN_C gid_t			getegid(void);
	ML_EXTERN_C uid_t			geteuid(void);
	ML_EXTERN_C gid_t			getgid(void);
	ML_EXTERN_C int execlp(const char* __file, const char* __arg0, ...);
} // namespace posix