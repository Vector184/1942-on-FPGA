
#include "../includes/SuperAce.h"
#include "../includes/EnemyFighter.hpp"
#include "../includes/SpritesHolder.hpp"
#include "../includes/CppGameData.hpp"

#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
#include "HDMI_text_controller/hdmi_text_controller.h"
#endif

namespace {
const uint32_t MAX_OAM_SPRITES = 32;

bool isOamRenderableSprite(const Sprite* sprite)
{
    if (!sprite || !sprite->isAlive() || !sprite->getVisibility() || !sprite->isActive()) {
        return false;
    }

    const SpriteMetadata* metadata = sprite->getMetadata();
    if (!metadata || metadata->tileIndex == 255 || metadata->width == 0 || metadata->height == 0) {
        return false;
    }

    return true;
}
}

SDL_Rect getRandomDestRect(EnemyFighterType e,SDL_Rect dst);
SpritesHolder* SpritesHolder::_holder = 0;

SpritesHolder::SpritesHolder(){
    
    SpriteType type;
    
    for(type=SpriteType(0); type <= SpriteType(SPRITE_TYPE_SIZE); type = SpriteType(type+1)){
        _sprites[type] = new SpriteList();
    }

}

SpritesHolder::~SpritesHolder(){
    for (SpriteByType::iterator it = _sprites.begin(); it != _sprites.end(); ++it) {
        SpriteList* sprites = it->second;
        if (!sprites) {
            continue;
        }

        while (!sprites->empty()) {
            Sprite* sprite = sprites->front();
            if (sprite && sprite->isAlive()) {
                sprite->destroySprite();
            } else {
                sprites->pop_front();
            }
        }

        delete sprites;
    }

    _sprites.clear();
    DestructionManager::commit();
    _holder = nullptr;
}

void SpritesHolder::add(Sprite *s){
    
    assert(s && s->getType()>=0 && s->getType()< SpriteType(SPRITE_TYPE_SIZE) );

    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(s->getType());
    
    assert(h && sl);

    if(s->getType() == ALIEN_SHIP ){
        ;
    }
    
    sl->push_back(s);
    ;
}

void SpritesHolder::remove(Sprite *s){
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(s->getType());
    
    assert(h && sl);
    
    sl->remove(s);
}

Sprite* SpritesHolder::getSprite(SpriteType type, std::string id){

    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(type);
    
    assert(h && sl);
    
    for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
        
        if((*it)->getId().compare(id) == 0)
            return *it;
    }
    
	//cout<<"There is No Sprite with this id"<<std::endl;
    return nullptr;
}

void SpritesHolder::printSprites(SpriteType type){

    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(type);
    
    assert(h && sl);
    
    cout<<endl<<endl;
    for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
        cout<<(*it)->getId()<<endl;
    }
    cout<<endl<<endl;
}

SpritesHolder* SpritesHolder::getSpritesHolder(){
    if (!_holder){
        _holder = new SpritesHolder();
    }
    return _holder;
}

SpriteList * SpritesHolder::getSprites(SpriteType type){
    assert(type>=0 && type<=SpriteType(SPRITE_TYPE_SIZE) );

    SpritesHolder* h = SpritesHolder::getSpritesHolder();

    SpriteByType::const_iterator i = h->_sprites.find(type);
    
    return i != h->_sprites.end() ? i->second : nullptr;
    
}

void SpritesHolder::displaySprites(SDL_Renderer* renderer, SpriteType type){
    assert(type>=0 && type<=SpriteType(SPRITE_TYPE_SIZE) );
    
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(type);
    
    assert(h && sl);
    
    if(!sl){
        return;
    }
    
    for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
        if((*it)->getVisibility() == true){
           (*it)->display(renderer); 
        }
    }
    
}

void SpritesHolder::displayGameSprites(SDL_Renderer* renderer){
    assert(renderer);
    Background::displayTerrain(renderer);
    
    for( SpriteType type = SpriteType(TERRAIN+1); type< SpriteType(SPRITE_TYPE_SIZE); type =SpriteType(type+1) )
        displaySprites(renderer, type);
}

void SpritesHolder::commitFrame(uint32_t backgroundSpriteId){
#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
    const InternalSprite* frame[MAX_OAM_SPRITES];
    uint32_t count = 0;
    SpritesHolder* h = SpritesHolder::getSpritesHolder();

    for (SpriteType type = SpriteType(First_SpriteType); type < SpriteType(SPRITE_TYPE_SIZE) && count < MAX_OAM_SPRITES; type = SpriteType(type + 1)) {
        if (type == TERRAIN) {
            continue;
        }

        SpriteList* sl = h->getSprites(type);
        if (!sl) {
            continue;
        }

        for (SpriteList::const_iterator it = sl->begin(); it != sl->end() && count < MAX_OAM_SPRITES; ++it) {
            Sprite* sprite = *it;
            if (!isOamRenderableSprite(sprite)) {
                continue;
            }

            frame[count++] = &sprite->getInternalSprite();
        }
    }

    ::commitFrame(frame, count, backgroundSpriteId);
#else
    (void)backgroundSpriteId;
#endif
}

void SpritesHolder::cleanUp(void){
    delete SpritesHolder::getSpritesHolder();
}

void    SpritesHolder::Load (const std::string& cataloge/*,SDL_Renderer* _renderer*/){
    (void)cataloge;

    for (size_t i = 0; i < CppGameData::kSpriteCount; ++i) {
        const CppGameData::SpriteInitData& sprite = CppGameData::kSprites[i];
        std::string id = sprite.id;
        unsigned frameNo = sprite.frameNo;
        SDL_Rect destRect = { sprite.x, sprite.y, sprite.w, sprite.h };
        SDL_Point point = { sprite.pointX, sprite.pointY };
        bool isVisible = sprite.visible;
        SpriteType spriteType;
        int st = sprite.spriteType;

        spriteType = SpriteType(st);
        assert( st < SPRITE_TYPE_SIZE );

        AnimationFilm* animationFilm = AnimationFilmHolder::Get()->GetFilm(sprite.animFilmId);
        int repetition = sprite.repetition;
        std::string id2;
        for(int k = 0; k < repetition; ++k){
            id2 = id + std::to_string(k);
            //add Sprite 2 Sprite Holder
            if(spriteType == SpriteType::SUPER_ACE){
                new SuperAce(id2, frameNo, destRect, point, isVisible, spriteType,animationFilm);
            }
            else if(spriteType == SpriteType::ALIEN_SHIP){
                int remainingBullets = sprite.remainingBullets;
                enum EnemyFighterType e = EnemyFighterType(sprite.enemyType);
                
                destRect = getRandomDestRect(e,destRect);
                Game::increaceTotalEnemies();
                new EnemyFighter(id2, frameNo, destRect, point, isVisible, spriteType,animationFilm,e,remainingBullets);
                
            }else if(spriteType == SpriteType::TERRAIN && id2.compare("backgroundSprite0")==0 ){
                new Background(id2, frameNo, destRect, point, isVisible, spriteType,animationFilm);
            }else{
                new Sprite(id2, frameNo, destRect, point, isVisible, spriteType,animationFilm);
            }
            
        }
    }
}


SDL_Rect getRandomDestRect(EnemyFighterType e,SDL_Rect dst){
    switch (e) {
            
        case EnemyFighterType(1):{
            dst.y = rand() % 384 + 92; // random between 92 - 476
            break;}
        case EnemyFighterType(2):{
            dst.y = -dst.h;
            dst.x = rand() % 384 + 192; // random between 192 - 576
            break;}
        case EnemyFighterType(3):{
            dst.y = rand() % 384 + 192; // random between 92 - 376
            break;}
        case EnemyFighterType(4):{
            dst.y = -dst.h;
            dst.x = rand() % 690 + 40; // random between  40 - 730
            break;}
        case EnemyFighterType(5):{
            dst.y = rand() % 384 + 92; // random between 92 - 476
            break;}
        case EnemyFighterType(6):{
            dst.y = -dst.h;
            dst.x = rand() % 384 + 192; // random between 192 - 576
            break;}
        case EnemyFighterType(7):{
            //dst.y = -dst.h;
            dst.x = rand() % 484 + 192; // random between 192 - 676
            break;}
        case EnemyFighterType(8):{
            //dst.y = -dst.h;
            dst.x = rand() % 484 + 192; // random between 192 - 676
            break;}
        /*case EnemyFighterType(9):{
            //dst.y = -dst.h;
            dst.y = rand() % 384 + 192; // random between 192 - 576
            break;}*/
        case EnemyFighterType(10):{
            //dst.y = -dst.h;
            dst.x = rand() % 484 + 192; // random between 192 - 676
            break;}
        case EnemyFighterType(11):{
            //dst.y = -dst.h;
            dst.x = rand() % 484 + 192; // random between 192 - 676
            break;}
        /*case EnemyFighterType(12):{
            //dst.y = -dst.h;
            dst.y = rand() % 384 + 192; // random between 192 - 576
            break;}*/
        
        default:break;
    }
    return dst;
}

void SpritesHolder::checkSpritesForDelete(){
    
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteType type = SUPER_ACE;
    SpriteList* sl = NULL;
    SpriteList::const_iterator it;
    SpriteList::const_iterator it2;

    for(type=SUPER_ACE; type <= GAME_INFO; type = SpriteType(type+1)){
        sl = h->getSprites(type);
        if(sl == nullptr){
            assert(0);
        }

        it=sl->begin();
        
        while(it!=sl->end()){
            it2 = it;
            it2++;
            if( ((*it)->isOutOfWindow() || (*it)->getState() == SpriteState::IN_COLUSION) && ((*it)->getId().compare("SuperAce0") != 0) ){
                (*it)->destroySprite();
            }
            it = it2;
        }
    }
}

bool SpritesHolder::uniqueAliveFromTeam(Sprite* sprite){
    
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* st = h->getSprites(sprite->getType(  ));
   
    
    
    
    
        
    int enemyId,groupId = 0;
    std::size_t found;
    std::string bonusId = sprite->getId();
    std::string s = "RedJetRight";
    std::string g = "RedJetLeft";
    std::string* last = nullptr;
    found = bonusId.find(s);
    if (found == 0){
        bonusId.erase(found, s.length());
        groupId = std::stoi( bonusId )/5;
        last = &s;
    }else {
        found = bonusId.find(g);
        if (found == 0){
            bonusId.erase(found, g.length());
            groupId = std::stoi( bonusId )/5;
            last = &g;
        }else {
            
            assert(0);
        }
    }
    
    if( sprite->getType() == ALIEN_SHIP ){
        
        SpriteList::const_iterator it = st->begin();
        EnemyFighter* enemyFighter = (EnemyFighter*)sprite;
        
        if( enemyFighter->getEnemyFighterType() == RED_PLANE ){
            
            while(it != st->end()){
                enemyFighter = (EnemyFighter*)(*it);
                
                if( enemyFighter->getEnemyFighterType() == RED_PLANE &&  enemyFighter!=sprite ){
                    bonusId = enemyFighter->getId();
                    found = bonusId.find(*last);
                    if (found == 0){
                        bonusId.erase(found, (*last).length());
                        enemyId = std::stoi( bonusId );
                        if( enemyFighter->isAlive() && /*enemyFighter->getVisibility() &&*/ (enemyId >= groupId*5) && (enemyId < (groupId+1)*5) ){
                            return false;
                        }
                    }
                    /*if( enemyFighter->isAlive() && enemyFighter->getVisibility() && (enemyId >= groupId*5) && (enemyId < (groupId+1)*5) ){
                        return false;
                    }*/
                }
                
                ++it;
            }
            
        }
        
    }
    return true;
}


void SpritesHolder::smallAndBigEnemyFireEnable(){
    
    SpriteList* sl = SpritesHolder::getSprites(ALIEN_SHIP);
    SpriteList::const_iterator it = sl->begin();
    EnemyFighter* enemyFighter;
    
    while ( it != sl->end() ){
        enemyFighter = (EnemyFighter*)(*it);
        if( enemyFighter->getEnemyFighterType() != EnemyFighterType(BIG_GREEN) &&
           enemyFighter->getEnemyFighterType() != EnemyFighterType(BIG_GREY)){
            
            enemyFighter->setEnemyFireEnable(true);
            
        }
        ++it;
    }

}
