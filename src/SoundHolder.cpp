#include "../includes/SoundHolder.hpp"

#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
#define GAME_HAS_FPGA_USB 1
#endif

SoundHolder* SoundHolder::holder = nullptr;
bool SoundHolder::_mute = false;
Mix_Music* SoundHolder::_gameplayMusic = nullptr;
Mix_Music* SoundHolder::_propellerSound = nullptr;
//constructor
SoundHolder::SoundHolder(){
    
}

//destructor
SoundHolder::~SoundHolder(){
    soundMap.clear();
}

SoundHolder* SoundHolder::getSoundHolder(){
    if(!holder){
        holder = new SoundHolder();
    }
    return holder;
}

void SoundHolder::initSounds(){
#ifdef GAME_HAS_FPGA_USB
    (void)SoundHolder::getSoundHolder();
    return;
#else
    SoundHolder* sh = SoundHolder::getSoundHolder();
    SoundMap::const_iterator it = sh->soundMap.begin();
	Mix_Chunk*propeller, *gunshot, *explosion;


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("SDL MIXER Error: %s \n", SDL_GetError());
    }
    
	SoundHolder::addSound("gunshot", (gunshot= Mix_LoadWAV((string(SOUNDS_PATH) + string("gunshot.wav")).c_str()) ) );
    SoundHolder::addSound("soundTrack", Mix_LoadWAV(  (string(SOUNDS_PATH) + string("Soundtrack.ogg")).c_str()  ));
	SoundHolder::addSound("explosion", explosion = Mix_LoadWAV((string(SOUNDS_PATH) + string("explosion.wav")).c_str()));
	SoundHolder::addSound("PowerUp", Mix_LoadWAV((string(SOUNDS_PATH) + string("PowerUp.ogg")).c_str()));
	SoundHolder::addSound("i_will_never_die",Mix_LoadWAV((string(SOUNDS_PATH) + string("i_will_never_die.ogg")).c_str()));
	
	
	
	SoundHolder::addSound("propeller", (propeller = Mix_LoadWAV((string(SOUNDS_PATH) + string("propeller_with_starting_sound_4_29.ogg")).c_str())));
	Mix_VolumeChunk(propeller, MIX_MAX_VOLUME / 3);
	Mix_VolumeChunk(gunshot, MIX_MAX_VOLUME / 3);
	Mix_VolumeChunk(explosion, MIX_MAX_VOLUME / 3);

	_gameplayMusic = Mix_LoadMUS((string(SOUNDS_PATH) + string("gameplay.ogg")).c_str());
	//_propellerSound = Mix_LoadMUS((string(SOUNDS_PATH) + string("propeller.ogg")).c_str());
	
    while(it != sh->soundMap.end()){
        if( !(*it).second ){
            printf("Could not load %s : %s \n",(*it).first.c_str() ,Mix_GetError());
        }
        it++;
    }

#endif
}

void SoundHolder::addSound(string id, Mix_Chunk* sound){
    SoundHolder::getSoundHolder()->soundMap[ id ] = sound;
}

Mix_Chunk* SoundHolder::getSound(string id){
    return SoundHolder::getSoundHolder()->soundMap[ id ];
}

void SoundHolder::cleanUp(){
#ifdef GAME_HAS_FPGA_USB
    if (holder) {
        holder->soundMap.clear();
    }
    return;
#else
    SoundMap::const_iterator it = SoundHolder::getSoundHolder()->soundMap.begin();
    SoundMap::const_iterator it2;

    while(it!=SoundHolder::getSoundHolder()->soundMap.end()){
        (*it).second->~Mix_Chunk();
        it++;
    }
    Mix_Quit();
#endif
}

void SoundHolder::playSound(string id){
#ifdef GAME_HAS_FPGA_USB
    (void)id;
#else
    if(!getMute())
        Mix_PlayChannel(-1, SoundHolder::getSound(id) , 0);
#endif
}

int SoundHolder::playMusic(){
#ifdef GAME_HAS_FPGA_USB
    return 0;
#else
	if (!getMute())
		return Mix_PlayMusic(_gameplayMusic, -1);
    return 0;
#endif
}

void SoundHolder::setMute(bool m ){
    _mute = m;
}
bool SoundHolder::getMute(){
    return _mute;
}
void SoundHolder::pauseSounds(){
#ifndef GAME_HAS_FPGA_USB
	Mix_PauseMusic();
	Mix_Pause(-1);
#endif
}
void SoundHolder::resumeSounds(){
#ifndef GAME_HAS_FPGA_USB
	Mix_ResumeMusic();
	Mix_Resume(-1);
#endif
}
