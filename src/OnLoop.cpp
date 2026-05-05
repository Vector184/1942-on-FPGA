#include "../includes/Game.hpp"

void Game::destructionManagerOnLoop(){
    DestructionManager::commit();
}

void Game::AIOnLoop(){
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    assert(superAce);
    
    if(superAce->getState() == IN_COLUSION ){
        setState(GAME_OVER);
        return;
    }

    static int i = 0;

    if(i % 50000 ==0){
        AnimatorHolder::getAnimatorHolder()->updateAllGreyPlaneAnimations();
        
        static bool right = true;
        static bool left = true;
		
        if(superAce->getAttached(RIGHT_FIGHTER) && right){

            right = AnimatorHolder::updateSideFighterAnimation(RIGHT_FIGHTER);
        }
        if(superAce->getAttached(LEFT_FIGHTER) && left){
            left = AnimatorHolder::updateSideFighterAnimation(LEFT_FIGHTER);
        }
    }
    }
    
void Game::GameOnLoop(){

    // AI
    Game::AIOnLoop();
    
    //collision checker
    CollisionChecker::Check();
    
    //check sprites and animators for delete if is out of window
    SpritesHolder::checkSpritesForDelete();
    AnimatorHolder::checkAnimatorsForDelete();
    
    //progress animators
    AnimatorHolder::progress(getGameTime());

    //free all sprites/animators that were safely detached during this frame
    destructionManagerOnLoop();
}

void Game::gameOver(){
    static bool firstTime = true;
    //assert(0);
    if( firstTime ){
        updateHighScoreJson("config.json");
        AnimatorHolder::pauseAnimators();
        
        SpriteStringHolder::getSpriteString("game")->setVisibility(true);
        SpriteStringHolder::getSpriteString("over")->setVisibility(true);
        
        SpriteStringHolder::getSpriteString("press")->setVisibility(true);
        SpriteStringHolder::getSpriteString("space")->setVisibility(true);
        SpriteStringHolder::getSpriteString("for")->setVisibility(true);
        SpriteStringHolder::getSpriteString("exit2")->setVisibility(true);
        
        SpriteStringHolder::getSpriteString("startingReadyLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("startingPlayerLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("numberOne")->setVisibility(false);
        firstTime = false;
        
        //Game::cleanUpHolders();
        //setState(SINGLEPLAYER_MENU);
    }else{
        //assert(0);
    }
}

void Game::OnLoop() {
    switch (_gameState) {
        case SINGLEPLAYER_MENU:
            break;
        case MULTIPLAYER_MENU:
            break;
        case SINGLEPLAYER_GAME:{
            GameOnLoop();
            break;
        }
        case MULTIPLAYER_GAME:{
            GameOnLoop();
            break;
        }
        case EXIT:
            break;
		case PAUSE_MENU:
			break;
        case GAME_OVER:{
            gameOver();
            break;
        }
        default:
            break;
    }
    
}
