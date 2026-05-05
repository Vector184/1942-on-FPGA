#include "../includes/SpriteAlphaNum.hpp"

SpriteAlphaNum::SpriteAlphaNum(char c,int point_x, int point_y):
Sprite(string(1,c),0,{point_x,point_y,9,13},{point_x,point_y},true,GAME_INFO,AnimationFilmHolder::Get()->GetFilm(string(1, c)))
{
    setId(string(1,c));
    _c = c;
    AnimationFilmHolder* animationHolder=  AnimationFilmHolder::Get(); 

    _logic.type = GAME_INFO;
    
    setDstRect({point_x, point_y, 9, 13});
    
    setVisibility(true);
    setFrame(0);
    
    setPoint({point_x, point_y});
    _currFilm = animationHolder->GetFilm(string(1, c));
}
char SpriteAlphaNum::getChar(void) const{
    return _c;
}
void SpriteAlphaNum::setChar(char c){
    AnimationFilmHolder* animationHolder=  AnimationFilmHolder::Get();
    AnimationFilm* currFilm = animationHolder->GetFilm(string(1, c));
    setCurrFilm(currFilm);
}
