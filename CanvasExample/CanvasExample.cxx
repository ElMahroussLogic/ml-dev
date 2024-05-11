/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SystemLabs B.V
 */

#include <MLCoreGraphicsContext.hxx>

int main(int argc, char const *argv[])
{
    MLCoreGraphicsContext* context = CGRequestContext(0, false, 1280, 720);

    context->Move(0, 0);
    context->Color(0xFF, 0xFF, 0xFF, 0.2);
    context->Rectangle(1280, 720, 0);
    context->Blur(100.0);
    context->Color(0xFF, 0xFF, 0xFF, 0.2);

    context->TextSize(15.0);
    context->Color(0xFF, 0xFF, 0xFF, 1);
    context->Move(5, 22);
    context->Font("SF Pro", false);
    context->Text("Install OS.");

    context->FlushAs("CanvasExample.png");

    CGReleaseContext(context);

    MLLog("%s\n", "done.");

    return 0;
}
