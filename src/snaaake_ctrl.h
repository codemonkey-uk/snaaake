//
//  snaaake_ctrl.h
//  SNAAAKE
//
//  Created by Thaddaeus Frogley on 25/07/2014.
//  Copyright (c) 2014 Thaddaeus Frogley. All rights reserved.
//

#ifndef SNAAAKE_snaaake_ctrl_h
#define SNAAAKE_snaaake_ctrl_h

#include "CApp.h"
#include "InputLatch.h"

#include <deque>

class SnakeApp;

class SnakeController
{
public:
    // for input handling forwarded from the app
    // TODO: should be registered with app as input observer
    virtual void OnEvent(SDL_Event* Event)=0;
    virtual CApp::Point GetDirection(CApp::Point currentDirection)=0;
    virtual void Reset()=0;
    virtual void Update(const SnakeApp* pApp)=0;
    virtual ~SnakeController(){}
};

class SnakePlayerController : public SnakeController
{
public:
    // for input handling forwarded from the app
    // TODO: should be registered with app as input observer
    void OnEvent(SDL_Event* Event);
    CApp::Point GetDirection(CApp::Point currentDirection);
    void Reset();
    void Update(const SnakeApp* pApp);
    
private:
    InputLatch mInputLatch;
    std::deque< CApp::Point > mEvents;
};

class SnakeAIController : public SnakeController
{
public:
    SnakeAIController() : mDir(0,0) {}
    // for input handling forwarded from the app
    // TODO: should be registered with app as input observer
    void OnEvent(SDL_Event* Event);
    CApp::Point GetDirection(CApp::Point currentDirection);
    void Reset();
    void Update(const SnakeApp* pApp);
    
private:
    CApp::Point mDir;
};


#endif //SNAAAKE_snaaake_ctrl_h
