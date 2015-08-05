//
//  AppDelegate.m
//  App360SDKDemo
//
//  Created by Tran Manh Tuan on 1/29/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import "AppDelegate.h"

#import <App360SDK/App360SDK.h>

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
#error Remove or comment this line after set your application keys
    
    [App360SDK initializeWithApplicationId:<#your-app-id#> clientKey:<#your-app-secret#>];
    
    NSString *deviceId = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
    
    [MOGSessionManager openActiveSessionWithScopeId:deviceId userInfo:nil block:^(MOGSession *session, NSError *error) {
        if (session) {
            //Create appscoped-id session successfully!
            //After session create, you can access info of current user via:
            
            MOGScopedUser *currentUser = [MOGScopedUser getCurrentUser];
            NSLog(@"Scoped-id of current user: %@, come from channel: %@, subChannel: %@", currentUser.scopedId, currentUser.channel, currentUser.subChannel);
        } else {
            
            //Something went wrong! Check error object for more information
            NSLog(@"Create session failed. Error: %@", error.description);
        }
    }];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
