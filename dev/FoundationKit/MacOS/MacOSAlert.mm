/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#include <FoundationKit/Foundation.h>

#define ML_EXEC(PATH) system(PATH)

int MLAlertBox(const MLChar* title, const MLChar* msg, const MLChar* link_provider)
{
    NSAlert* alert = [[NSAlert alloc] init];
    alert.alertStyle = NSAlertStyleCritical;
    alert.messageText = [NSString stringWithUTF8String:title];
    alert.informativeText = [NSString stringWithUTF8String:msg];

    [alert addButtonWithTitle: @"Ok"];
    [alert addButtonWithTitle: @"Close"];
    [alert addButtonWithTitle: @"Help..."];

    NSModalResponse response = [alert runModal];

    while (response == 1002)
    {
        ML_EXEC("open -a 'Help Viewer'");
        response = [alert runModal];
    }

    [alert release];

    return response == 1000;
}
