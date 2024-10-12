/* -------------------------------------------

    Copyright ZKA Technologies

------------------------------------------- */

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

extern "C" int MLAlertBox(const char* title, const char* msg)
{
    NSAlert* alert = [[NSAlert alloc] init];
    alert.alertStyle = NSAlertStyleCritical;
    alert.messageText = [NSString stringWithUTF8String:msg];
    alert.informativeText = [NSString stringWithUTF8String:title];
    [alert runModal];

    [alert release];

    return 0;
}
