//
//  AppDelegate.m
//  SNAAAKE
//
//  Created by Thaddaeus Frogley on 13/07/2014.
//  Copyright (c) 2014 Thaddaeus Frogley. All rights reserved.
//

#import "AppDelegate.h"
#import "NSFileManager+DirectoryLocations.h"

#import <AVFoundation/AVFoundation.h>
#import <CoreAudio/CoreAudio.h>

// simple OS X platforms hooks for funcitonality that uses cookies in the browser build

int GetLocalHighScore()
{
    NSString *path = [[NSFileManager defaultManager] applicationSupportDirectory];
    NSString *appFile = [path stringByAppendingPathComponent:@"snaaake.data"];
    NSString *content = [NSString stringWithContentsOfFile:appFile encoding:NSUTF8StringEncoding error:nil];
    
    return [content intValue];
}

void SetLocalHighScore(int d)
{
    NSString *path = [[NSFileManager defaultManager] applicationSupportDirectory];
    NSString *appFile = [path stringByAppendingPathComponent:@"snaaake.data"];
    NSString *noteDataString = [NSString stringWithFormat:@"%d", d];
    [noteDataString writeToFile:appFile atomically:YES];
}

static AVAudioPlayer * Audio = 0;

void PlayMusic()
{
    NSString *soundFilePath = [[NSBundle mainBundle] pathForResource: @"snaaake" ofType: @"mp3"];
    NSURL *fileURL = [[NSURL alloc] initFileURLWithPath: soundFilePath];
    Audio = [[AVAudioPlayer alloc] initWithContentsOfURL: fileURL error: nil];
    
    [Audio setNumberOfLoops:-1];
    [Audio play];
}

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    PlayMusic();
}

@end
