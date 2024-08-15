/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/Linux/Linux.hxx>

#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

/// @brief Launches an alert box from the API.
/// @param title title of dialog.
/// @param msg message of dialog.
/// @return which option was selected.
ML_EXTERN_C int MLAlertBox(const char* title, const char* msg)
{
	printf("%s: %s\n", title, msg);

	printf("%s: [ y/Y = yes, n/N = no. ]\n", "choose");

	std::string ln;
	std::getline(std::cin, ln);

	std::transform(ln.begin(), ln.end(), ln.begin(),
				   [](unsigned char c) { return std::tolower(c); });

	if (ln == "y" || ln == "yes")
	{
		return 1;
	}
	else if (ln == "n" || ln == "no")
	{
		return 2;
	}

	return 0;
}
