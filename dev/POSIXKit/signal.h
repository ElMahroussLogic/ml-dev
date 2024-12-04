/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

#include <sys/signal.h>
#include <sys/_pthread/_pthread_t.h>

namespace posix
{
	ML_EXTERN_C int kill(pid_t, int);
	ML_EXTERN_C int killpg(pid_t, int);
	ML_EXTERN_C int pthread_kill(pthread_t, int);
	ML_EXTERN_C int pthread_sigmask(int, const sigset_t*, sigset_t*);
	ML_EXTERN_C int sigaction(int, const struct sigaction* __restrict, struct sigaction* __restrict);
	ML_EXTERN_C int sigaddset(sigset_t*, int);
	ML_EXTERN_C int sigaltstack(const stack_t* __restrict, stack_t* __restrict);
	ML_EXTERN_C int sigdelset(sigset_t*, int);
	ML_EXTERN_C int sigemptyset(sigset_t*);
	ML_EXTERN_C int sigfillset(sigset_t*);
	ML_EXTERN_C int sighold(int);
	ML_EXTERN_C int sigignore(int);
	ML_EXTERN_C int siginterrupt(int, int);
	ML_EXTERN_C int sigismember(const sigset_t*, int);
	ML_EXTERN_C int sigpause(int);
	ML_EXTERN_C int sigpending(sigset_t*);
	ML_EXTERN_C int sigprocmask(int, const sigset_t* __restrict, sigset_t* __restrict);
	ML_EXTERN_C int sigrelse(int);
} // namespace posix