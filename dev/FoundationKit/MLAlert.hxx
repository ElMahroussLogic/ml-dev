/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLString.hxx>

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
