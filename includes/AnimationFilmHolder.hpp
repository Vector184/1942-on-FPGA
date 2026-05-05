#ifndef AnimationFilmHolder_hpp
#define AnimationFilmHolder_hpp

#include "../includes/includes.h"
#include "../includes/AnimationFilm.hpp"
#include <stdint.h>

class AnimationFilmHolder{
private:
    typedef std::map<std::string, AnimationFilm*> Films;
    Films _films;
    //BitmapLoader _bitmaps;
    static AnimationFilmHolder*  _holder; //singleton
  
    AnimationFilmHolder (void);
    ~AnimationFilmHolder();
public:
    void AddHardwareAnimationFilm(const uint8_t* tileIndexes, unsigned count, string id);
    void AddHardwareAnimationFilm(const uint8_t* tileIndexes, const uint8_t* attributes, unsigned count, string id);

    //static const AnimationFilmHolder& Get(void);
    static AnimationFilmHolder* Get (void){
        if (!_holder)
            _holder = new AnimationFilmHolder();
        return _holder;
    }
    
    void    LoadHardwareFilms(void);
    static void    CleanUp(void);
    AnimationFilm* GetFilm(const std::string id) ;
};
#endif
