/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#pragma once

#ifdef __MAHROUSS__
#include <newstd.hxx>

#define ML_ALLOC(SZ)	 NUser::New(SZ)
#define ML_ALLOC_ARR(SZ) NUser::New(SZ)
#define ML_FREE(PTR)	 NUser::Delete(PTR)

#define ML_EXEC(PATH) 	 (NUser::Execute(NURL::FromPath(PATH)) ? 0 : cNUserExecError)
#endif
