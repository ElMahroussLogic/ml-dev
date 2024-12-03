/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

const MLString MLObject::toString()
{
	const auto max_json_len = 255;

	MLString toStrObj = MLString(max_json_len);
	toStrObj += "['ClassName': 'MLObject']";

	return toStrObj;
}

const void MLObject::encode(MLCoder* output)
{
    if (!output)
        return;

	*output = output->encode(this);
}

const void MLObject::decode(MLCoder* output)
{
    if (!output)
        return;

	*output = output->decode(this);
}
