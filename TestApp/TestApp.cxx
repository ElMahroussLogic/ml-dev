#include <MLCoreGraphicsContext.hxx>

int main(int argc, char const *argv[])
{
    MLCoreGraphicsContext* context = CGRequestContext(0, false);

    context->Move(10, 100).FontSize(50).Text("New OS...");
    context->Move(10, 150).FontSize(50).Text("Graphics Stack...");

    context->WriteAs("TestApp.png");

    CGReleaseContext(context);
    return 0;
}
