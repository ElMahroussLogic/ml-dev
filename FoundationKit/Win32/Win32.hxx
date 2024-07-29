/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>

#ifdef _WIN32
#include <Windows.h>
#include <CommCtrl.h>
#include <commdlg.h>

#define INIT_COM ML_MUST_PASS(SUCCEEDED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
#define FINI_COM CoUninitialize()

#define ML_EXEC(PATH) 	 ::ShellExecuteA(nullptr, "open", PATH, nullptr, nullptr, SW_SHOWNORMAL)
#endif // _WIN32
