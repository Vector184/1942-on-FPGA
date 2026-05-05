#include "../includes/AnimationHolder.h"
#include "../includes/CppGameData.hpp"

AnimationHolder* AnimationHolder::_holder = 0;//singleton

AnimationHolder::AnimationHolder(){
}

AnimationHolder::~AnimationHolder(){
}

AnimationHolder* AnimationHolder::getAnimationHolder(){
    if(!_holder){
        _holder = new AnimationHolder();
    }
    return _holder;
}

void AnimationHolder::cleanUp(void){
    _holder->~AnimationHolder();
    _holder = NULL;
}

void AnimationHolder::add(Animation* anim){
    AnimationHolder::getAnimationHolder()->_map[anim->getId()]=anim;
}

Animation* AnimationHolder::getAnimation(animid_t str){
    if (AnimationHolder::getAnimationHolder()->_map[str] == nullptr){
        cout << "Error: Animation is not in map with animations !" << endl;
    }
    return AnimationHolder::getAnimationHolder()->_map[str];
}

void AnimationHolder::LoadFromCppData(void){
    for (size_t i = 0; i < CppGameData::kMovingAnimationCount; ++i) {
        const CppGameData::MovingAnimationData& data = CppGameData::kMovingAnimations[i];
        add(new MovingAnimation(data.dx, data.dy, data.delay, data.continuous, data.id));
    }

    for (size_t i = 0; i < CppGameData::kTickAnimationCount; ++i) {
        const CppGameData::TickAnimationData& data = CppGameData::kTickAnimations[i];
        add(new TickAnimation(data.id, data.delay, data.repetitions));
    }

    for (size_t i = 0; i < CppGameData::kMovingPathAnimationCount; ++i) {
        const CppGameData::MovingPathAnimationData& data = CppGameData::kMovingPathAnimations[i];
        std::list<PathEntry> paths;

        for (size_t j = 0; j < data.pathCount; ++j) {
            const CppGameData::PathEntryData& entry = data.paths[j];
            PathEntry pathEntry;
            pathEntry._visibility = entry.visibility;
            pathEntry._dx = entry.dx;
            pathEntry._dy = entry.dy;
            pathEntry._frame = entry.frame;
            pathEntry._delay = entry.delay;
            paths.push_back(pathEntry);
        }

        add(new MovingPathAnimation(paths, data.id, data.continuous));
    }
}

void AnimationHolder::Load(const std::string& cataloge){
    (void)cataloge;
    LoadFromCppData();
}

void AnimationHolder::LoadMovingPathAnim(const std::string& cataloge, int n){
    (void)cataloge;
    (void)n;
}
