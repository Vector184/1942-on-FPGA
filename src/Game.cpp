//
//  Game.cpp
//  1942
//
//  Created by Nikos Xenakis on 29/12/15.
//  Copyright © 2015 Nikos Xenakis. All rights reserved.
//

#include "../includes/Game.hpp"

#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
#include "USB/usb_keyboard.h"
#define GAME_HAS_FPGA_USB 1
#endif

#ifdef GAME_HAS_FPGA_USB
Uint32 Game::_fps_lasttime = 0;
#else
Uint32 Game::_fps_lasttime = SDL_GetTicks(); //the last recorded time.
#endif
Uint32 Game::_fps_current = 0; //the last recorded time.
Uint32 Game::_fps_frames = 0; //frames passed since the last recorded fps.

std::list<unsigned> Game::_powerUpsOfStage;
SDL_Window * Game::_window = 0;
SDL_Renderer * Game::_renderer = 0;
SDL_Event Game::event;
SDL_Event Game::prevEvent;

GameState Game::_gameState = GameState::SINGLEPLAYER_MENU;

//Game Variables
//unsigned Game::_remaining_loops_num = 3;
float Game::_spriteSize = 1;
int Game::_highScore = 0;
int Game::_score = 0;
unsigned long Game::_currTime = 0;

unsigned int Game::_totalEnemies = 0;
unsigned int Game::_deadEnemies  = 0;
//controller
SDL_GameController* Game::_controller = nullptr;

int Game::OnExecute(){

    if(OnInit() == false) {
        return -1;
    }
	//Game Loop
    while ( !isExit()    ){
		setGameTime();

#ifndef GAME_HAS_FPGA_USB
        while (SDL_PollEvent(&event))
            OnEvent();
#endif

        OnUsbKeyboard();
        OnLoop();
        //fpsLoop();
        OnRender();

    }
    OnCleanup();
    return 0;
}

void Game::OnUsbKeyboard() {
#ifdef GAME_HAS_FPGA_USB
    const BYTE USB_KEY_Z = 0x1d;
    const BYTE USB_KEY_X = 0x1b;
    const BYTE USB_KEY_ENTER = 0x28;
    const BYTE USB_KEY_RIGHT = 0x4f;
    const BYTE USB_KEY_LEFT = 0x50;
    const BYTE USB_KEY_DOWN = 0x51;
    const BYTE USB_KEY_UP = 0x52;
    const BYTE USB_MOD_SHIFT = 0x02 | 0x20;

    static BYTE prev_keycode[6] = {0};
    static BYTE prev_mod = 0;

    USBKeyboard_Task();
    const BOOT_KBD_REPORT* report = USBKeyboard_GetReport();

    auto wasPressed = [&](BYTE keycode) {
        for (int i = 0; i < 6; ++i) {
            if (prev_keycode[i] == keycode) {
                return true;
            }
        }
        return false;
    };

    auto isPressed = [&](BYTE keycode) {
        for (int i = 0; i < 6; ++i) {
            if (report->keycode[i] == keycode) {
                return true;
            }
        }
        return false;
    };

    const bool enterPressed = isPressed(USB_KEY_ENTER);
    const bool enterEdge = enterPressed && !wasPressed(USB_KEY_ENTER);
    const bool shiftPressed = (report->mod & USB_MOD_SHIFT) != 0;
    const bool shiftEdge = shiftPressed && ((prev_mod & USB_MOD_SHIFT) == 0);
    const bool specialPressed = isPressed(USB_KEY_X);
    const bool specialEdge = specialPressed && !wasPressed(USB_KEY_X);
    const bool firePressed = isPressed(USB_KEY_Z);
    const bool fireEdge = firePressed && !wasPressed(USB_KEY_Z);

    switch (getState()) {
        case SINGLEPLAYER_MENU:
            if (enterEdge) {
                setState(SINGLEPLAYER_GAME);
            } else if (shiftEdge) {
                setState(MULTIPLAYER_MENU);
            }
            break;
        case MULTIPLAYER_MENU:
            if (enterEdge) {
                setState(MULTIPLAYER_GAME);
            } else if (shiftEdge) {
                setState(SINGLEPLAYER_MENU);
            }
            break;
        case SINGLEPLAYER_GAME:
        case MULTIPLAYER_GAME: {
            SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
            if (superAce && AnimatorHolder::movingEnable && !AnimatorHolder::onManuevuer()) {
                if (isPressed(USB_KEY_LEFT)) {
                    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeft0");
                    if (animator) {
                        animator->start(getGameTime());
                    }
                }
                if (isPressed(USB_KEY_RIGHT)) {
                    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRight0");
                    if (animator) {
                        animator->start(getGameTime());
                    }
                }
                if (isPressed(USB_KEY_UP)) {
                    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorUp0");
                    if (animator) {
                        animator->start(getGameTime());
                    }
                }
                if (isPressed(USB_KEY_DOWN)) {
                    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorDown0");
                    if (animator) {
                        animator->start(getGameTime());
                    }
                }
                if (fireEdge) {
                    superAce->fire();
                }
                if (specialEdge) {
                    superAce->doManeuever();
                }
            }
            break;
        }
        case GAME_OVER:
            if (enterEdge) {
                setState(EXIT);
            }
            break;
        default:
            break;
        }

    for (int i = 0; i < 6; ++i) {
        prev_keycode[i] = report->keycode[i];
    }
    prev_mod = report->mod;
#endif
}

void Game::setGameTime(){
#ifdef GAME_HAS_FPGA_USB
    _currTime += 16;
#else
    _currTime = SDL_GetTicks();
#endif
}

SDL_Window * Game::getWindow(){
    return _window;
}

SDL_Renderer * Game::getRenderer(){
    return _renderer;
}

GameState Game::getState(){
    return Game::_gameState;
}

namespace {
uint32_t resolveBackgroundSpriteId(const char* metadataName)
{
    const SpriteMetadata* metadata = SpriteMetadata_FindByName(metadataName);
    assert(metadata && metadata != SpriteMetadata_Default());
    return metadata->tileIndex;
}
}

uint32_t Game::getBackgroundSpriteId(){
    switch (_gameState) {
        case SINGLEPLAYER_MENU:
        case MULTIPLAYER_MENU:
            return resolveBackgroundSpriteId("STARTING_SCRN");
        case SINGLEPLAYER_GAME:
        case MULTIPLAYER_GAME:
        case PAUSE_MENU: {
            Sprite* superAce = SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
            if (superAce && superAce->getState() == STARTING) {
                return resolveBackgroundSpriteId("LVL_START");
            }
            return resolveBackgroundSpriteId("ROLLING_BKG");
        }
        case GAME_OVER:
            return resolveBackgroundSpriteId("SCORE_BOARD");
        case END_OF_STAGE:
            return resolveBackgroundSpriteId("LVL_END");
        case EXIT:
        default:
            return resolveBackgroundSpriteId("STARTING_SCRN");
    }
}

/*int Game::getRemainingLoops(void){
    return Game::_remaining_loops_num;
}*/

/*void Game::setRemainingLoops(int loops){
    Game::_remaining_loops_num = loops;
}*/
unsigned int Game::getTotalEnemies(){
	return _totalEnemies;
}
unsigned int Game::getDeadEnemies(){
	return _deadEnemies;
}
void Game::setToDeadEnemiesOneMore(){
	++_deadEnemies;
}
void Game::increaceTotalEnemies(){
	_totalEnemies++;
}
void Game::setState(GameState gameState){
    Game::_gameState = gameState;
}

bool Game::isExit(){
    if (_gameState==EXIT) {
        return true;
    }
    return false;
}

float Game::getSpriteSize() {
    return _spriteSize;
}

void Game::setSpriteSize(float s){
    _spriteSize= s;
}

int Game::getHighScore() {
    return _highScore;
}

void Game::setHighScore(int s){
    _highScore = s;
}

int Game::getScore() {
    return _score;
}

void Game::setScore(int s){
    _score = s;
    updateScoreSprite();
    if (_score > _highScore){
        setHighScore(_score);
        updateHighScoreSprite();
    }
}

void Game::updateScoreSprite(){
    std::string score = std::to_string(_score);
     SpriteStringHolder::getSpriteString("score")->changeString(score,20, 30);
}

void Game::updateHighScoreSprite(){
    std::string highScore = std::to_string(_highScore);
    SpriteStringHolder::getSpriteString("highScore")->changeString(highScore,WIN_WIDTH/2 - (int) (highScore.size()*6), 30);
    
    //write _highScore to config json     "highScore": 140

}


bool Game::isMainMenu(){
    if (_gameState==SINGLEPLAYER_MENU || _gameState==MULTIPLAYER_MENU) {
        return true;
    }
    return false;
}

void Game::fpsLoop(){
#ifdef GAME_HAS_FPGA_USB
    return;
#else
    
    Game::_fps_frames++;
	
    if (_fps_lasttime < SDL_GetTicks() - FPS_INTERVAL*1000)
    {
        _fps_lasttime = SDL_GetTicks();
        _fps_current = _fps_frames;
        _fps_frames = 0;
    }
    SpriteStringHolder::getSpriteString("fps")->changeString(std::to_string(_fps_current),WIN_WIDTH -62,30);
#endif
}

unsigned long Game::getGameTime(){
    return _currTime;
}

void Game::setNextPowerUpType(unsigned p){
    assert( p < 7);
    _powerUpsOfStage.push_back(p);
}

unsigned Game::getNextPowerUpType(){

    assert(!_powerUpsOfStage.empty());
    unsigned p = _powerUpsOfStage.front();
    _powerUpsOfStage.pop_front();
    return p;
}
