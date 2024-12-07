/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLApplication.h>

#include <sstream>
#include <cstdarg>
#include <cstdio>

#include <chrono>
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>

#define ML_PRINTF ::printf

/// @brief MLLog advanced print function.
ML_IMPORT void MLLog(const char* format, ...)
{
	std::time_t end_time =
		std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::string formatted_time = std::ctime(&end_time);
	formatted_time.pop_back();

	auto appName = MLApplication::shared().getAppName();

	va_list va;
	va_start(va, format);

	long index = 0UL;

	std::string fmtStr = format;

	while (fmtStr[index] != 0)
	{
		if (fmtStr[index] == '%')
		{
			if (fmtStr[index + 1] == '$')
			{
				MLString* object = va_arg(va, MLString*);

				std::string stlString = object->asConstBytes();

				fmtStr.replace(index, 2, stlString);
			}
			if (fmtStr[index + 1] == '@')
			{
				MLObject* object = va_arg(va, MLObject*);

				std::string stlString = object->toString().asConstBytes();

				fmtStr.replace(index, 2, stlString);
			}
			else if (fmtStr[index + 1] == 's')
			{
				char* msgLog = va_arg(va, char*);
				fmtStr.replace(index, 2, msgLog);
			}
			else if (fmtStr[index + 1] == 'n')
			{
				std::string msgLog;
				msgLog.push_back(va_arg(va, MLInteger));

				fmtStr.replace(index, 2, msgLog);
			}
			else if (fmtStr[index + 1] == 'r')
			{
				char buf[64] = {0};
				snprintf(buf, 64, "%lf", va_arg(va, MLReal));

				fmtStr.replace(index, 2, buf);
			}
			else if (fmtStr[index + 1] == 'x')
			{
				MLInteger64 numberInsideVarArg = va_arg(va, MLInteger64);

				std::stringstream ss;
				ss << std::hex << numberInsideVarArg;

				std::string hexString = ss.str();

				fmtStr.replace(index, 2, hexString);
			}
			else if (fmtStr[index + 1] == 'c')
			{
				char charInside = va_arg(va, int);

				fmtStr.replace(index, 2, 1, charInside);
			}
			else if (fmtStr[index + 1] == 'd')
			{
				MLInteger64 numberInsideVarArg = va_arg(va, MLInteger64);

				fmtStr.replace(index, 2, std::to_string(numberInsideVarArg));
			}
			else if (fmtStr[index + 1] == 'b')
			{
				bool boolInsideVarArg = va_arg(va, int);

				fmtStr.replace(index, 2, boolInsideVarArg ? "YES" : "NO");
			}
			else if (fmtStr[index + 1] == 0)
			{
				++index;
				continue;
			}
		}

		++index;
	}

	va_end(va);

	ML_PRINTF("%s [ %s ] : %s\n", formatted_time.c_str(), appName.asBytes(), fmtStr.c_str());

	appName.dispose();
}
