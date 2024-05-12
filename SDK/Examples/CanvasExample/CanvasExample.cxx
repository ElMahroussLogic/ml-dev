/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SystemLabs B.V
 */

#include <MLCoreGraphicsContext.hxx>
#include <MLString.hxx>
#include <string.h>

int main(int argc, char const* argv[])
{
	MLCoreGraphicsContext* context = CGRequestContext(0, false, 1000, 666);

	context->Start();

	context->Image("rsrc://CanvasBackground.png", 1000, 666, 0, 0);

	context->Color(.2, .2, .2, 0.499);
	context->Move(50.0, 100.0);
	context->Rectangle(90, 324, 0);
	context->Blur(400, 90, 324);

	context->Color(.2, .2, .2, 1);
	context->Stroke(0.5);

	context->Color(.2, .2, .2, 1);
	context->Move(140.0, 100.0);
	context->Rectangle(500, 324, 0);

	context->Color(.2, .2, .2, 1);
	context->Stroke(0.5);

	context->WriteTo("rsrc://CanvasExample.png");

	context->End();

	CGReleaseContext(context);

	return 0;
}
