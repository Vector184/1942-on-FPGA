#include "../includes/Game.hpp"
#include "../includes/MovingAnimation.h"
#include "../includes/CppGameData.hpp"

#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
#include "USB/usb_keyboard.h"
#define GAME_HAS_FPGA_USB 1
#endif

bool Game::OnInit(){
    USBKeyboard_Init();
    InitGame();
    return true;
}

void Game::InitGame(){
    
    InitData();

#ifndef GAME_HAS_FPGA_USB
    SoundHolder::initSounds();
#endif

    LoadGameInfo("config.json");
    
    InitGameInfo();
    
    Background::initBackgroundObjects();

    AnimatorHolder::startTimeTickAnimators();

}

void Game::InitGamePad(){
    _controller = nullptr;
}


bool Game::InitWindow(){
    _window = nullptr;
    return true;
}

bool Game::InitRenderer(){
    _renderer = nullptr;
    return true;
}

bool Game::InitData(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;

    AnimationFilmHolder* anFh = AnimationFilmHolder::Get();
    anFh->LoadHardwareFilms();

    SpritesHolder::Load("sprites.json");

    AnimationHolder* anh = AnimationHolder::getAnimationHolder();
    anh->LoadFromCppData();
    AnimatorHolder::getAnimatorHolder()->LoadFromCppData();
    return true;
}

void    Game::LoadGameInfo (const std::string& cataloge){
    (void)cataloge;
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    superAce->setSuperAceLives(CppGameData::kGameConfig.superAceLives);
    superAce->setSuperAceLoops(CppGameData::kGameConfig.superAceLoops);

    SuperAce* superAce2 = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce1");
    superAce2->setSuperAceLives(CppGameData::kGameConfig.superAceLives);
    superAce2->setSuperAceLoops(CppGameData::kGameConfig.superAceLoops);

    _highScore = CppGameData::kGameConfig.highScore;
    _spriteSize = CppGameData::kGameConfig.spriteSize;
    SoundHolder::setMute(CppGameData::kGameConfig.mute);
    for (size_t i = 0; i < CppGameData::kGameConfig.powerUpCount; i++) {
        unsigned u = CppGameData::kGameConfig.powerUps[i];
        assert(u < 7 );
        setNextPowerUpType(u);
    }
}

void Game::updateHighScoreJson(const std::string& cataloge){
    (void)cataloge;
}

bool Game::InitGameInfo(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;

    SpriteStringHolder::addSpriteString("scoreString", new SpriteString("SCORE",20,10));
    SpriteStringHolder::addSpriteString("highString", new SpriteString("HIGH",(WIN_WIDTH/2)-56,10));
    SpriteStringHolder::addSpriteString("highScoreString", new SpriteString("SCORE",(WIN_WIDTH/2)-6,10));

    //SpriteStringHolder::addSpriteString("fpsString", new SpriteString("FPS",WIN_WIDTH-62,10));
    //SpriteStringHolder::addSpriteString("fps", new SpriteString("0000",WIN_WIDTH-62,30));

    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    std::string remainingLoopsString = "";
    for(int i = 0; i < superAce->getSuperAceLoops(); i++){
       remainingLoopsString += "R";
	}

    std::string remainingLivesString = "";
    for(int i = 0; i < superAce->getSuperAceLives(); i++){
        remainingLivesString += "L";
    }

    string score = std::to_string(_score);
    string highScore = std::to_string(_highScore);

    SpriteStringHolder::addSpriteString("press", new SpriteString( "PRESS", (WIN_WIDTH/2)- 106 ,410) );
    SpriteStringHolder::addSpriteString("space", new SpriteString( "ENTER", (WIN_WIDTH/2) - 36 ,410) );
    SpriteStringHolder::addSpriteString("for", new SpriteString( "FOR", (WIN_WIDTH/2)+ 29 ,410) );
    SpriteStringHolder::addSpriteString("exit2", new SpriteString( "EXIT", (WIN_WIDTH/2)+ 69 ,410) );
    SpriteStringHolder::getSpriteString("press")->setVisibility(false);
    SpriteStringHolder::getSpriteString("space")->setVisibility(false);
    SpriteStringHolder::getSpriteString("for")->setVisibility(false);
    SpriteStringHolder::getSpriteString("exit2")->setVisibility(false);

    SpriteStringHolder::addSpriteString("game", new SpriteString( "GAME", (WIN_WIDTH/2)- 60 ,110) );
    SpriteStringHolder::getSpriteString("game")->setVisibility(false);
    SpriteStringHolder::addSpriteString("over", new SpriteString( "OVER", (WIN_WIDTH/2) ,110) );
    SpriteStringHolder::getSpriteString("over")->setVisibility(false);
    SpriteStringHolder::addSpriteString("score", new SpriteString( score , 20 ,30) );
    SpriteStringHolder::addSpriteString("highScore", new SpriteString( highScore , WIN_WIDTH/2 - (int) (highScore.size()*6), 30) );
    SpriteStringHolder::addSpriteString("remainingLoops", new SpriteString(remainingLoopsString, WIN_WIDTH - superAce->getSuperAceLoops()*12 -5, WIN_HEIGHT - 15) );
    SpriteStringHolder::addSpriteString("remainingLives", new SpriteString(remainingLivesString, /*WIN_WIDTH - superAce->getSuperAceLives()*12*/ 5, WIN_HEIGHT - 15) );
    SpriteStringHolder::getSpriteString("remainingLoops")->setVisibility(true);
    SpriteStringHolder::addSpriteString("startingReadyLogo", new SpriteString("READY", (WIN_WIDTH / 2)-40, WIN_HEIGHT / 2) );
    SpriteStringHolder::addSpriteString("startingPlayerLogo", new SpriteString("PLAYER", (WIN_WIDTH / 2)-40, (WIN_HEIGHT / 2)+20) );
    SpriteStringHolder::addSpriteString("numberOne", new SpriteString("1", (WIN_WIDTH / 2)+32, (WIN_HEIGHT / 2)+20) );

    SpriteStringHolder::addSpriteString("exit", new SpriteString("EXIT", (WIN_WIDTH / 2 -(5*6)), (WIN_HEIGHT / 2 - 20) ) );
    SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
    SpriteStringHolder::addSpriteString("pause", new SpriteString("RESUME", (WIN_WIDTH / 2 -(5*6)), (WIN_HEIGHT / 2) ) );
    SpriteStringHolder::getSpriteString("pause")->setVisibility(false);

    SpriteStringHolder::addSpriteString("shootingString", new SpriteString("SHOOTING", (WIN_WIDTH / 2) - 150, (WIN_HEIGHT / 2)) );
    SpriteStringHolder::getSpriteString("shootingString")->setVisibility(false);
    SpriteStringHolder::addSpriteString("downString", new SpriteString("DOWN", (WIN_WIDTH / 2)-40, (WIN_HEIGHT / 2)) );
    SpriteStringHolder::getSpriteString("downString")->setVisibility(false);
    SpriteStringHolder::addSpriteString("shootingDownPercent", new SpriteString("0%", (WIN_WIDTH / 2) + 40, (WIN_HEIGHT / 2)) );
    SpriteStringHolder::getSpriteString("shootingDownPercent")->setVisibility(false);
    SpriteStringHolder::addSpriteString("endingBonusString", new SpriteString("BONUS", (WIN_WIDTH / 2) -70, (WIN_HEIGHT / 2)+70) );
    SpriteStringHolder::getSpriteString("endingBonusString")->setVisibility(false);
    SpriteStringHolder::addSpriteString("pointsString", new SpriteString("PTS", (WIN_WIDTH / 2) +5, (WIN_HEIGHT / 2)+95) );
    SpriteStringHolder::getSpriteString("pointsString")->setVisibility(false);
    SpriteStringHolder::addSpriteString("points", new SpriteString("10000", (WIN_WIDTH / 2)-90, (WIN_HEIGHT / 2) + 95) );
    SpriteStringHolder::getSpriteString("points")->setVisibility(false);
    SpriteStringHolder::addSpriteString("letterR", new SpriteString("R*", (WIN_WIDTH / 2) - 90, (WIN_HEIGHT / 2)+135) );
    SpriteStringHolder::getSpriteString("letterR")->setVisibility(false);
    SpriteStringHolder::addSpriteString("1000Points", new SpriteString("1000", (WIN_WIDTH / 2) - 60, (WIN_HEIGHT / 2) + 135) );
    SpriteStringHolder::getSpriteString("1000Points")->setVisibility(false);
    SpriteStringHolder::addSpriteString("equals", new	SpriteString("=", (WIN_WIDTH / 2) + 15, (WIN_HEIGHT / 2) + 135) );
    SpriteStringHolder::getSpriteString("equals")->setVisibility(false);

	SpriteStringHolder::addSpriteString("LastPoints", new SpriteString("3000", (WIN_WIDTH / 2) + 50, (WIN_HEIGHT / 2) + 135));
	SpriteStringHolder::getSpriteString("LastPoints")->setVisibility(false);

	SpriteStringHolder::addSpriteString("pointsString2", new SpriteString("PTS", (WIN_WIDTH / 2) + 100, (WIN_HEIGHT / 2) + 135));
	SpriteStringHolder::getSpriteString("pointsString2")->setVisibility(false);

    return true;
}
