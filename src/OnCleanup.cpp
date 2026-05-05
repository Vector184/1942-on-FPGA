#include "../includes/Game.hpp"

#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
#include "USB/usb_keyboard.h"
#define GAME_HAS_FPGA_USB 1
#endif

void Game::cleanUpHolders(){
    AnimatorHolder::cleanup();
    AnimationHolder::cleanUp();
    SpritesHolder::cleanUp();
    AnimationFilmHolder::CleanUp();
    SoundHolder::cleanUp();

    DestructionManager::commit();
    ;
}

void Game::OnCleanup(){
#ifdef GAME_HAS_FPGA_USB
    cleanUpHolders();
	USBKeyboard_Cleanup();
    return;
#else
	if (_controller != nullptr){
		SDL_GameControllerClose(_controller);
		_controller = nullptr;
	}

    cleanUpHolders();

    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    SDL_Quit();
#endif
}
