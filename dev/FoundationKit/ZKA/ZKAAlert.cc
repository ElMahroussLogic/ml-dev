/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/ZKA/ZKA.h>
#include <CFKit/CFRef.h>

/// @brief Launches an alert box from the API.
/// @param title title of dialog.
/// @param msg message of dialog.
/// @return which option was selected.
ML_EXTERN_C MLInteger MLAlertBox(const char* title, const char* msg, const char* link_provider)
{
	CFKit::CFRef ref_dlg = CFKit::CFRefBuilder::Grab("IBAlertObject");

	if (ref_dlg == nullptr) return -1;

	auto ret = ref_dlg->Execute(ref_dlg, title, msg, link_provider);
	ref_dlg->Dispose();

	return ret;
}
