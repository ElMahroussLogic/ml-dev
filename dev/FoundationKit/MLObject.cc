/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

const MLString MLObject::toString()
{
	const auto max_json_len = 255;

	MLString toStrObj = MLString(max_json_len);
	toStrObj += "[{'name': 'MLObject'}]";

	return toStrObj;
}

const void MLObject::encode(MLCoder* output)
{
	ML_UNUSED(output);
}

const void MLObject::decode(MLCoder* output)
{
	ML_UNUSED(output);
}