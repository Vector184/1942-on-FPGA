#include "../includes/Sprite.hpp"
#include "../includes/SpritesHolder.hpp"
#include "../includes/AnimatorHolder.h"

Sprite::Sprite(){
    //illegal use
    assert(0);
}

Sprite::Sprite(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm){
   
   // assert( id!="" && frameNo>=0 && type>=0 && type<SpriteType(SPRITE_TYPE_SIZE) && currFilm);
	
	assert(type <= Last_SpriteType);
	assert(type >= 0);
	assert(id != "");
    if (currFilm && !currFilm->hasHardwareFrames()) {
        assert(frameNo < currFilm->getTotalFrames());
    }


    setId(id);
    setCurrFilm(currFilm);
    _logic = {};
    _metadata = SpriteMetadata_FindByName(id);

    _logic.setPoint(point);
    setVisibility(isVisible);
    _logic.type=static_cast<uint8_t>(type);
    setState(STARTING);
    _parent=nullptr;
    
    setFrame(frameNo);
    setDstRect(dstRect);

    this->setUndefeatable(false);
    
    SpritesHolder::add(this);

}

Sprite::~Sprite(){
}

void Sprite::setId(std::string id){
    _spriteId = id;
}
void Sprite::setCurrFilm(AnimationFilm* currFilm){
    _currFilm = currFilm;
}
AnimationFilm* Sprite::getCurrFilm(void) const{
    return  _currFilm;
}

void Sprite::setFrame(unsigned i){
    if (_currFilm && !_currFilm->hasHardwareFrames()) {
        assert(i < _currFilm->getTotalFrames());
    }
	_logic.frameNo = static_cast<uint16_t>(i);
    if (_currFilm && _currFilm->hasHardwareFrames()) {
        _metadata = _currFilm->getFrameMetadata(i);
        setAttributes(_currFilm->getFrameAttributes(i));
    } else if (_currFilm) {
        _metadata = SpriteMetadata_ResolveAnimationFrame(_spriteId, _currFilm->getId(), i);
        setAttributes(0);
    } else {
        _metadata = SpriteMetadata_Resolve(_spriteId, i);
        setAttributes(0);
    }
    setTileIndex(_metadata->tileIndex);
}

unsigned Sprite::getFrame(void) const {
    return _logic.frameNo;
}

void Sprite::setDstRect(SDL_Rect dstRect){
    _logic.setDstRect(dstRect);
}

void Sprite::setDstRectX(int x){
    _logic.x=static_cast<int16_t>(x);
    _logic.syncOamPosition();
}
void Sprite::setDstRectY(int y){
    _logic.y=static_cast<int16_t>(y);
    _logic.syncOamPosition();

}

void Sprite::setUndefeatable(bool flag){
    _logic.undefeatable = flag ? 1 : 0;
}

bool Sprite::isUndefeatable(){
    return _logic.undefeatable != 0;
}

std::string Sprite::getId(void) const{
    return _spriteId;
}

SDL_Rect Sprite::getDstRect(void) const{
    return _logic.getDstRect();
}

void Sprite::changeDstRectX(int dx){
    _logic.x=static_cast<int16_t>(_logic.x + dx);
    _logic.syncOamPosition();
}
void Sprite::changeDstRectY(int dy){
    _logic.y=static_cast<int16_t>(_logic.y + dy);
    _logic.syncOamPosition();
}

void Sprite::setPoint(SDL_Point point){
    _logic.setPoint(point);
}

SDL_Point Sprite::getPoint(){
    return _logic.getPoint();
}

void Sprite::setVisibility (bool v) {
    _logic.visible = v ? 1 : 0;
    setActive(v);
}

bool Sprite::getVisibility (void) const{
    return _logic.visible != 0;
}

SpriteState Sprite::getState(){
    return SpriteState(_logic.state);
}

SpriteType Sprite::getType(){
    return SpriteType(_logic.type);
}

void Sprite::move (int dx, int dy){
    filterMotion(&dx, &dy);
    //basic move logic
    _logic.x=static_cast<int16_t>(_logic.x + dx);
    _logic.y=static_cast<int16_t>(_logic.y + dy);
    _logic.syncOamPosition();
    moveAttached(dx, dy);
}

void Sprite::filterMotion(int* dx, int* dy) const {
    /* default is unfiltered motion */
};

void Sprite::moveAttached (int dx, int dy) {
    for (auto& i : _attached)
        i.second->move(dx,dy);
}

void Sprite::attach (Sprite* s, const std::string& name){
    _attached[name] = s;
    s->_parent = this;
    s->_name = name; 
}

void Sprite::detach(const std::string& name, bool forDestroy){
    
    auto i  (_attached.find(name));
    assert(i != _attached.end());
    auto* s (i->second);
    s->_parent = nullptr;
    s->_name.clear();
    _attached.erase(i);
    if (forDestroy && s->isAlive())
        s->destroySprite();

}

Sprite* Sprite::getAttached(const std::string& name) const{
    auto i  (_attached.find(name));
    return i != _attached.end() ? i->second : nullptr;
}

void Sprite::display(SDL_Renderer* renderer) {
    if (_currFilm) {
        _currFilm->displayFrame(renderer,_logic.getPoint(),_logic.frameNo,_logic.getDstRect());
    }
}

bool Sprite::isOutOfWindow(){
    int x = getDstRect().x;
    int y = getDstRect().y;
    int w = getDstRect().w;
    int h = getDstRect().h;
    int extra_dst = 5;
    
    if( x > -w - extra_dst && y > -h - extra_dst && x < WIN_WIDTH + extra_dst && y < WIN_HEIGHT + extra_dst ){
        return false;
    }

    return true;
}

// TODO :: CollisionCheck body
void Sprite::collisionCheck(Sprite* s){
    assert(this->isAlive());
    assert(s->isAlive());
	
	
	if ((getState() == MANEUVER) || s->getState() == MANEUVER ){
	
		return;
	}

	//if sprites are not visible return
    if( !this->getVisibility() || !s->getVisibility() || !this->isActive() || !s->isActive() ){
        return;
    }
    SDL_Rect thisRect = getCollisionRect();
    SDL_Rect otherRect = s->getCollisionRect();

    //compare metadata hitboxes
	if (
		thisRect.x < otherRect.x + otherRect.w &&
		thisRect.x + thisRect.w > otherRect.x &&
		thisRect.y < otherRect.y + otherRect.h &&
		thisRect.h + thisRect.y > otherRect.y
		)
        notifyCollision(s);
}

SDL_Rect Sprite::getCollisionRect(void) const{
    SDL_Rect rect = getDstRect();
    if (_metadata && _metadata->width > 0 && _metadata->height > 0) {
        rect.w = _metadata->width;
        rect.h = _metadata->height;
    }
    return rect;
}

//collision detection functions
void Sprite::notifyCollision(Sprite* arg){
    assert(arg);
    assert(this->isAlive());
    assert(arg->isAlive());

    Handlers::iterator i = _handlers.begin();
    Handlers::iterator i2;
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
	SuperAce* superAce2 = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce1");
	
	if (superAce2 == this || arg == superAce2){
		if (superAce2->getState() == MANEUVER || superAce2->isUndefeatable()){
			if (arg->getType() != POWER_UPS && this->getType() != POWER_UPS)
				return;
		}
	}

    if( superAce == this || arg == superAce){
        if(superAce->getState()==MANEUVER || superAce->isUndefeatable()){
            if( arg->getType()!=POWER_UPS && this->getType()!=POWER_UPS )
                return;
        }
    }
	
	Sprite* right = superAce->getAttached(RIGHT_FIGHTER);
	Sprite* left = superAce->getAttached(LEFT_FIGHTER);

	
	if (this == right || arg == right || this == left || arg == left){
		if (arg->getType() == POWER_UPS || this->getType() == POWER_UPS){
			//get power up 
		}else if (superAce->isUndefeatable()){	
			return;
		}
	}
    

	
    
    while(i!=_handlers.end()){
        i2=i;
        i2++;
        
        (**i)(this,arg);
            
        i=i2;
    }
}

void Sprite::addCollisionHandler(const CollisionHandler& h){
    _handlers.push_back(h.Clone());
    if( getType() == SUPER_ACE){

        SpriteList* aliens;
        
        aliens = SpritesHolder::getSprites(ALIEN_SHIP);
        
        if (aliens)
            for (SpriteList::iterator it=aliens->begin(); it != aliens->end(); ++it){
                if( ((Sprite*)*it)->isAlive() )
                    CollisionChecker::Register(this,*it);
            }
    }
    if( getType() == ALIEN_SHIP || getType() == POWER_UPS){
        SpriteList* superAce;
        
        superAce = SpritesHolder::getSpritesHolder()->getSprites(SUPER_ACE);
        
        if (superAce)
            for (SpriteList::iterator it=superAce->begin(); it != superAce->end(); ++it){
                if( ((Sprite*)*it)->isAlive() )
                    CollisionChecker::Register(this,*it);
            }
    }
}

void Sprite::clearHandlers(void){
    for(Handlers::const_iterator i = _handlers.begin(); i!=_handlers.end(); ++i ){
        delete *i;
    }
    
    _handlers.clear();

}

void Sprite::setState(SpriteState state){
	assert( (First_SpriteState <= state )&& (state <= Last_SpriteState));
	_logic.state = static_cast<uint8_t>(state);
}

void Sprite::setTileIndex(uint8_t tileIndex){
    _logic.tile_index = tileIndex;
}

uint8_t Sprite::getTileIndex(void) const{
    return _logic.tile_index;
}

void Sprite::setAttributes(uint8_t attributes){
    _logic.attributes = attributes;
}

uint8_t Sprite::getAttributes(void) const{
    return _logic.attributes;
}

void Sprite::setActive(bool active){
    _logic.active = active ? 1 : 0;
}

bool Sprite::isActive(void) const{
    return _logic.active != 0;
}

const InternalSprite& Sprite::getInternalSprite(void) const{
    return _logic;
}

const SpriteMetadata* Sprite::getMetadata(void) const{
    return _metadata;
}

void Sprite::destroySprite(void){
    assert(this->isAlive());
    setActive(false);

    while (!_attached.empty()) {
        detach(_attached.begin()->first, false);
    }

    if (getParent()) {
        getParent()->detach(_name, false);
    }

    //collisions
    CollisionChecker::CancelAll(this);
    clearHandlers();

    //SpritesHolder
    SpritesHolder::getSpritesHolder()->remove(this);
    
    LatelyDestroyable::destroy();
}

Sprite* Sprite::getParent(){
    return _parent;
}
