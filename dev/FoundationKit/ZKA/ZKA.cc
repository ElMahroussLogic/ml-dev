/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/ZKA/ZKA.h>

/** @brief Shows an alert box, with the message and title. */
EXTERN int MLAlertBox(CONST CHAR* title, CONST CHAR* msg, CONST CHAR* link_provider)
{
    ZKA_UNUSED(link_provider);
	return W32MessageBox(W32GetDesktopWindow(), W32_TEXT(msg), W32_TEXT(title),
						 W32_MB_OKCANCEL | W32_MB_ICONINFORMATION) == W32_IDOK;
}
