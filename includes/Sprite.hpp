#ifndef Sprite_hpp
#define Sprite_hpp

#include "../includes/includes.h"
#include "../includes/AnimationFilm.hpp"
#include "../includes/LatelyDestroyable.h"
#include "../includes/CollisionChecker.hpp"
#include "../includes/SpriteMetadata.hpp"
#include <stdint.h>

#define SPRITE_TYPE_SIZE 8
#define SPRITE_STATE_SIZE  
class Sprite;

typedef enum SpriteType {
    MAIN_MENU_SINGLEPLAYER = 0,
    MAIN_MENU_MULTIPLAYER = 1,
    TERRAIN = 2,
    SUPER_ACE = 3,
    ALIEN_SHIP = 4,
    POWER_UPS = 5,
    GAME_INFO = 6,
    UNDEFINED = 7 ,
	First_SpriteType = MAIN_MENU_SINGLEPLAYER,
	Last_SpriteType = UNDEFINED

}SpriteType;

typedef enum SpriteState {
    FLYING = 0,
    FIRING = 1,
	MANEUVER = 2,
	STARTING = 3,
    IN_COLUSION = 4,
	ENDING = 5 ,

	First_SpriteState = FLYING,
	Last_SpriteState = ENDING
}SpriteState;

// Compact gameplay state for FPGA ports. Signed coordinates preserve
// off-screen spawns; the uint8_t OAM fields are packed directly for hardware.
struct InternalSprite {
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;
    int16_t pointX;
    int16_t pointY;
    uint16_t frameNo;
    uint8_t oamY;
    uint8_t tile_index;
    uint8_t attributes;
    uint8_t oamX;
    uint8_t visible;
    uint8_t active;
    uint8_t type;
    uint8_t state;
    uint8_t undefeatable;

    static uint8_t toOamCoord(int16_t value) {
        if (value < 0) {
            return 0;
        }
        if (value > 255) {
            return 255;
        }
        return static_cast<uint8_t>(value);
    }

    void syncOamPosition(void) {
        oamX = toOamCoord(x);
        oamY = toOamCoord(y);
    }

    uint32_t packOamEntry(void) const {
        uint8_t packedY = active ? oamY : 255;
        return ((uint32_t)packedY) |
               ((uint32_t)tile_index << 8) |
               ((uint32_t)attributes << 16) |
               ((uint32_t)oamX << 24);
    }

    void setDstRect(SDL_Rect rect) {
        x = static_cast<int16_t>(rect.x);
        y = static_cast<int16_t>(rect.y);
        w = static_cast<int16_t>(rect.w);
        h = static_cast<int16_t>(rect.h);
        syncOamPosition();
    }

    SDL_Rect getDstRect(void) const {
        return { x, y, w, h };
    }

    void setPoint(SDL_Point point) {
        pointX = static_cast<int16_t>(point.x);
        pointY = static_cast<int16_t>(point.y);
    }

    SDL_Point getPoint(void) const {
        return { pointX, pointY };
    }
};

class Sprite : public LatelyDestroyable{
    
public:
    
    class CollisionHandler{
    public:
        virtual void operator()(Sprite* caller, Sprite* arg) const = 0;
        virtual CollisionHandler* Clone(void) const = 0;
        virtual ~CollisionHandler(){};
    };
    
    struct fireHandler : public Sprite::CollisionHandler{
        void operator()(Sprite* bullet,Sprite* arg) const;
        fireHandler* Clone(void) const;
        ~fireHandler();
    };
    
    struct touchHandler : public Sprite::CollisionHandler{
        void operator()(Sprite* aircraft,Sprite* arg) const;
        touchHandler* Clone(void) const;
        ~touchHandler();
    };
    
    struct touchPowerUpHandler : public Sprite::CollisionHandler{
        void operator()(Sprite* powerUp,Sprite* arg) const;
        touchPowerUpHandler* Clone(void) const;
        ~touchPowerUpHandler();
    };
    
protected:
    
    //collision detection variables
    typedef std::list<CollisionHandler*> Handlers;
    Handlers _handlers;
    void notifyCollision(Sprite* arg);
    SDL_Rect getCollisionRect(void) const;
    
    std::string _spriteId;
	SDL_Rect _srcRect;
    InternalSprite _logic;
    const SpriteMetadata* _metadata;
    AnimationFilm* _currFilm;
    
    using Attached = std::map<std::string, Sprite*>;
    Attached _attached;
    Sprite* _parent;
    std::string _name; //inspect this
    void moveAttached(int dx, int dy);
    
    ~Sprite();

    void clearHandlers(void);

public:
    //collision detection functions
    void addCollisionHandler(const CollisionHandler& h);
    
	//setters
	void setState(SpriteState);
    void setId(std::string);
    virtual void setFrame(unsigned  i) ;
    void setVisibility (bool v);
    void setDstRect(SDL_Rect dstRect);
    void setDstRectX(int x);
    void setDstRectY(int y);
    void setCurrFilm(AnimationFilm* currFilm);
    void setUndefeatable(bool flag);
    void setPoint(SDL_Point point);
    void setTileIndex(uint8_t tileIndex);
    void setAttributes(uint8_t attributes);
    void setActive(bool active);
    
    //getters
    std::string getId(void) const;
    unsigned  getFrame(void) const;
    SDL_Rect getDstRect(void) const;
	bool getVisibility (void) const;
    void collisionCheck (Sprite* s);
	SpriteType getType();
	SpriteState getState();
    void changeDstRectX(int dx);
    void changeDstRectY(int dy);
    AnimationFilm* getCurrFilm(void) const;
    Sprite* getParent();
    bool isUndefeatable();
    SDL_Point getPoint();
    uint8_t getTileIndex(void) const;
    uint8_t getAttributes(void) const;
    bool isActive(void) const;
    const InternalSprite& getInternalSprite(void) const;
    const SpriteMetadata* getMetadata(void) const;

	//constructors
    Sprite();
    Sprite(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm);
    
    //basic functionallity
    virtual void move (int dx, int dy);
    
    virtual void filterMotion(int* dx, int* dy) const;
    
    void attach(Sprite* s, const std::string& name);
    
    void detach(const std::string& name, bool forDestroy);
    
    Sprite* getAttached(const std::string& name) const;
    
    virtual void destroySprite(void);
    
    void display (SDL_Renderer* renderer);
    
    bool isOutOfWindow();
  
};

#endif
