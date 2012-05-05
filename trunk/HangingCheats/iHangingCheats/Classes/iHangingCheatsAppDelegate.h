//
//  iHangingCheatsAppDelegate.h
//  iHangingCheats
//
//  Created by h5nc on 12-5-4.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class HGEGLView;

@interface iHangingCheatsAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    HGEGLView *glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet HGEGLView *glView;

@end

