/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLString.hxx>

const MLString MLObject::toString()
{
	const auto max_json_len = 255;

	MLString toStrObj = MLString(max_json_len);
	toStrObj += "[{'name': 'MLObject'}]";

	return toStrObj;
}

const void MLObject::encode(MLCodec* output)
{
	ML_UNUSED(output);
}

const void MLObject::decode(MLCodec* output)
{
	ML_UNUSED(output);
}
