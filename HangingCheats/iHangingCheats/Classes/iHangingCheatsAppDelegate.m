//
//  iHangingCheatsAppDelegate.m
//  iHangingCheats
//
//  Created by h5nc on 12-5-4.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "iHangingCheatsAppDelegate.h"
#import "iHangingCheatsViewController.h"
#import "MainApplicationFunctions.h"

@implementation iHangingCheatsAppDelegate

@synthesize window;
@synthesize glView;


- (void)applicationDidFinishLaunching:(UIApplication *)application {
	[[NSFileManager defaultManager] changeCurrentDirectoryPath: [[NSBundle mainBundle] resourcePath]];
	Application_Init();
	[glView startLoop];
	
}


- (void)applicationWillResignActive:(UIApplication *)application {
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
}


- (void)dealloc {
	Application_Quit();
	[window release];
	[glView release];
	[super dealloc];
}

@end

@end

const char * ResourceGetBaseDirectory()
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *basePath = ([paths count]>0) ? [paths objectAtIndex:0] : nil;
	return [basePath UTF8String];}

const char * ResourceGetAppDirectory()
{
	NSString *appPath = [[NSBundle mainBundle]resourcePath];
	return [appPath UTF8String];
}

