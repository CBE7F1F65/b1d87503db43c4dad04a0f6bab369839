//
//  iHangingCheatsViewController.h
//  iHangingCheats
//
//  Created by h5nc on 12-5-4.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#include "MainApplicationFunctions.h"

#include "Const.h"

@interface HGEGLView : UIView {
	
@public
	UITouch *touchPoints[TOUCHPOINT_MAX];
    
@private
	
    EAGLContext *context;
    
    GLuint depthRenderbuffer;
    
    NSTimer *loopTimer;
    NSTimeInterval loopInterval;
}

@property NSTimeInterval loopInterval;
- (void)startLoop;
- (void)stopLoop;
- (void)mainLoop;

@end

