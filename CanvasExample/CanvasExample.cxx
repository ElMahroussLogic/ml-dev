#include <MLCoreGraphicsContext.hxx>

int main(int argc, char const *argv[])
{
    MLCoreGraphicsContext* context = CGRequestContext(0, false, 1280, 720);

    context->Move(0, 0);
    context->Color(0xFF, 0xFF, 0xFF, 0.2);
    context->Rect(1280, 30, 2);

    context->TextSize(25.0);
    context->Color(0xFF, 0xFF, 0xFF, 1);
    context->Move(5, 22);
    context->Font("SF Pro", false);
    context->Text("Menu");

    context->FlushAs("CanvasExample.png");

    CGReleaseContext(context);

    return 0;
}
