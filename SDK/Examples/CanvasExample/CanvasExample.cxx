/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SoftwareLabs B.V
 */

#include <CoreGraphics.hxx>
#include <MLString.hxx>
#include <string.h>

int main(int argc, char const* argv[])
{
	MLCoreGraphicsContext* context = CGRequestContext(0, 0, 1000, 666);

	context->Start()->Image("rsrc://CanvasBackground.png", 1000, 666, 0, 0);

	context->Image("rsrc://CanvasLetThereBeLight.png", 300, 300, 30, 30);

	context->Color(1.0, 1.0, 1.0, .4)->Move(0.0, 0.0)->Rectangle(1000, 666, 0)->Blur(1666, 1000, 666);
	context->Color(1.0, 1.0, 1.0, 1.0)->Stroke(5.0);

	context->WriteTo("rsrc://CanvasExample.png")->End();

	CGReleaseContext(context);

	return 0;
}
