/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#pragma once

#ifdef __APPLE__

#define ML_EXEC(PATH) 	 std::system((std::string("open ") + PATH).c_str())

#endif
