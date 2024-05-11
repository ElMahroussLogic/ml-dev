/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SystemLabs B.V
 */

#include <MLCoreGraphicsContext.hxx>
#include <MLString.hxx>

int main(int argc, char const* argv[])
{
	MLCoreGraphicsContext* context = CGRequestContext(0, false, 1000, 666);

	context->Image("./CanvasBackground.png", 1000, 666, 0, 0);

	context->Move(0, 0);
	context->Color(0xFF, 0xFF, 0xFF, 0.2);
	context->Rectangle(1000, 40, 0);
	context->GaussianBlur(1000.0, 1000, 40);
	context->Color(0x00, 0x00, 0x00, 0.6);
	context->Stroke(2.0);

	context->TextSize(15.0);
	context->Color(0x00, 0x00, 0x00, 1);
	context->Move(25, 25);
	context->Font("Chicago", true);
	context->Text("WindowServer");

	context->Color(0xFF, 0xFF, 0xFF, 0.2);
	context->Move(50.0, 100.0);
	context->Rectangle(500, 400, 0);
	context->GaussianBlur(1000.0, 500, 400);
	context->Color(0x00, 0x00, 0x00, 0.6);
	context->Stroke(2.0);

	context->FlushAs("CanvasExample.png");

	MLLog("%s: %s\n", context->toString().asConstBytes(), "first canvas drawn.");

	CGReleaseContext(context);

	return 0;
}
