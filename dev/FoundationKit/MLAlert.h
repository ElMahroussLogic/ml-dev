/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

class MLAlert final ML_OBJECT
{
public:
	explicit MLAlert();
	~MLAlert() override;

	int	 runErrorModal(const MLChar* title, const MLChar* format, ...);
	bool runModal(const MLChar* title, const MLChar* format, ...);
	bool runModal(const MLChar* message);

	const MLString toString() override;
};
