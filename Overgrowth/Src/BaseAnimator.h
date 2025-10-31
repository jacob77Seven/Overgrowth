#pragma once

#include <string>
class anim;

class StateMachine; // Forward declaration

class IState {
public:
    virtual ~IState() = default;

    // Called when entering the state
    virtual void Enter(StateMachine& sm) = 0;

    // Called every frame/update tick
    virtual void Update(StateMachine& sm, float deltaTime) = 0;

    // Called when exiting the state
    virtual void Exit(StateMachine& sm) = 0;
};


class AnimStateMachine {

};

class BaseAnimator {

};

