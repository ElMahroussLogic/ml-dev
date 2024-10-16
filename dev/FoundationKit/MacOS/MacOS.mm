/* -------------------------------------------

    Copyright ZKA Technologies

------------------------------------------- */

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#include <FoundationKit/MLURL.hxx>

extern "C" int MLAlertBox(const MLChar* title, const MLChar* msg, const MLChar* link_provider)
{
    NSAlert* alert = [[NSAlert alloc] init];
    alert.alertStyle = NSAlertStyleCritical;
    alert.messageText = [NSString stringWithUTF8String:msg];
    alert.informativeText = [NSString stringWithUTF8String:title];

    [alert addButtonWithTitle: @"Ok"];
    [alert addButtonWithTitle: @"Close"];
    [alert addButtonWithTitle: @"Help..."];

    NSModalResponse response = [alert runModal];

    while (response == 1002)
    {
        ML_EXEC("-a 'Help Viewer'");
        response = [alert runModal];
    }

    [alert release];

    return response == 1000;
}
