#include "../includes/AnimationFilmHolder.hpp"
#include <iostream>
#include <string>

AnimationFilmHolder *AnimationFilmHolder::_holder = 0;

AnimationFilmHolder::AnimationFilmHolder (void){}

AnimationFilmHolder::~AnimationFilmHolder(){ CleanUp(); }

namespace {
std::string normalizeHardwareFilmId(const std::string& id)
{
    if (id == "Super.Ace.1942.Scaled" || id == "Super.Ace.1942" || id == "Super.Ace" || id == "sideFighters") {
        return "SUPERACE";
    }
    if (id == "SuperAceLand") {
        return "SUPERACE_LAND";
    }
    if (id == "min_gray_plane" || id == "grey_medium_planes_2") {
        return "QING";
    }
    if (id == "green_jet") {
        return "FUKUSUKE";
    }
    if (id == "mini_green_one_eng" || id == "gray_jet") {
        return "KURODEN";
    }
    if (id == "red_plane") {
        return "KURODEN_KAI";
    }
    if (id == "green_double_engine" || id == "mini_grey_double_engine") {
        return "BVD";
    }
    if (id == "green_medium_plane" || id == "grey_medium_plane") {
        return "SHORYU";
    }
    if (id == "green_medium_triple") {
        return "RAIZAN";
    }
    if (id == "bigGreen" || id == "bigGrey" || id == "deathStarFilm") {
        return "DAIHIRYU_LARGE";
    }
    if (id == "bullets") {
        return "BULLET_SUPERACE";
    }
    if (id == "enemyBullets") {
        return "BULLET_ENEMY";
    }
    if (id == "powerUps") {
        return "POWER_UP";
    }
    if (id == "explosion") {
        return "EXPLOSION_ENEMY";
    }
    if (id == "superAceExplosion") {
        return "EXPLOSION_SUPERACE";
    }
    if (id == "scores") {
        return "SCORE";
    }
    return id;
}

void addHardwareFilms(AnimationFilmHolder* holder)
{
    const uint8_t hflip = 0x40;
    const uint8_t vflip = 0x80;
    const uint8_t hvflip = hflip | vflip;

    static const uint8_t superAce[] = {28, 29, 30, 31, 32, 39, 40, 41, 40, 39, 32, 31, 30, 29, 28};
    static const uint8_t superAceLand[] = {3};
    static const uint8_t sideFighters[] = {3};
    static const uint8_t qing[] = {36};
    static const uint8_t kuroden[] = {0, 1, 2, 4, 5};
    static const uint8_t kurodenSide[] = {6, 7, 9};
    static const uint8_t kurodenKai[] = {12,14, 8,15,16};
    static const uint8_t bvd[] = {18};
    static const uint8_t fukusuke[] = {21};
    static const uint8_t shoryu[] = {34};
    static const uint8_t raizan[] = {37};
    static const uint8_t daihiryuLarge[] = {129};

    static const uint8_t kurodenFlipUp[] = {0, 1, 2, 4, 5};
    static const uint8_t kurodenSideRight[] = {6, 7, 9};
    static const uint8_t kurodenSideLeft[] = {6, 7, 9};
    static const uint8_t kurodenSideLeftAttrs[] = {hflip, hflip, hflip};
    static const uint8_t kurodenKaiRightFlipLeft[] = {12, 14, 8, 15, 16};
    static const uint8_t kurodenKaiLeftFlipRight[] = {12, 14, 8, 15, 16};
    static const uint8_t kurodenKaiLeftFlipRightAttrs[] = {hflip, hflip, hflip, hflip, hflip};
    static const uint8_t kurodenKaiRotatingClockwise[] = {12, 10, 11, 10, 12};
    static const uint8_t kurodenKaiRotatingClockwiseAttrs[] = {0, 0, 0, hflip, hflip};
    static const uint8_t kurodenKaiRotatingCounterclockwise[] = {12, 10, 11, 10, 12};
    static const uint8_t kurodenKaiRotatingCounterclockwiseAttrs[] = {hflip, hflip, 0, 0, 0};

    static const uint8_t fukusukeSideRight[] = {21, 23, 24, 25, 26};
    static const uint8_t fukusukeSideLeft[] = {21, 23, 24, 25, 26};
    static const uint8_t fukusukeSideLeftAttrs[] = {hflip, hflip, hflip, hflip, hflip};
    static const uint8_t fukusukeDown[] = {21};
    static const uint8_t fukusukeUp[] = {21};
    static const uint8_t fukusukeUpAttrs[] = {vflip};
    static const uint8_t fukusukeDownright[] = {20};
    static const uint8_t fukusukeRight[] = {22};
    static const uint8_t fukusukeLeft[] = {22};
    static const uint8_t fukusukeLeftAttrs[] = {hflip};
    static const uint8_t fukusukeDownleft[] = {20};
    static const uint8_t fukusukeDownleftAttrs[] = {hflip};
    static const uint8_t fukusukeTopright[] = {20};
    static const uint8_t fukusukeToprightAttrs[] = {vflip};
    static const uint8_t fukusukeTopleft[] = {20};
    static const uint8_t fukusukeTopleftAttrs[] = {hvflip};

    static const uint8_t bvdDownright[] = {17};
    static const uint8_t bvdDown[] = {18};
    static const uint8_t bvdRight[] = {19};
    static const uint8_t bvdDownleft[] = {17};
    static const uint8_t bvdDownleftAttrs[] = {hflip};
    static const uint8_t bvdUp[] = {18};
    static const uint8_t bvdUpAttrs[] = {vflip};
    static const uint8_t bvdLeft[] = {19};
    static const uint8_t bvdLeftAttrs[] = {hflip};
    static const uint8_t bvdTopleft[] = {17};
    static const uint8_t bvdTopleftAttrs[] = {hvflip};
    static const uint8_t bvdTopright[] = {17};
    static const uint8_t bvdToprightAttrs[] = {vflip};

    static const uint8_t shoryuDown[] = {34};
    static const uint8_t shoryuDownright[] = {33};
    static const uint8_t shoryuRight[] = {35};
    static const uint8_t shoryuLeft[] = {35};
    static const uint8_t shoryuLeftAttrs[] = {hflip};
    static const uint8_t shoryuDownleft[] = {33};
    static const uint8_t shoryuDownleftAttrs[] = {hflip};
    static const uint8_t shoryuUp[] = {34};
    static const uint8_t shoryuUpAttrs[] = {vflip};
    static const uint8_t shoryuTopright[] = {35};
    static const uint8_t shoryuToprightAttrs[] = {vflip};
    static const uint8_t shoryuTopleft[] = {25};
    static const uint8_t shoryuTopleftAttrs[] = {hvflip};

    static const uint8_t playerBullets[] = {44};
    static const uint8_t enemyBullets[] = {46};
    static const uint8_t powerUps[] = {65};
    static const uint8_t enemyExplosion[] = {66, 67, 68, 69, 70};
    static const uint8_t largeEnemyExplosion[] = {56, 57, 58, 59, 60, 61, 62, 63, 64};
    static const uint8_t playerExplosion[] = {42, 43, 49, 50, 51, 52, 53};
    static const uint8_t scores[] = {91};

    holder->AddHardwareAnimationFilm(superAce, sizeof(superAce) / sizeof(superAce[0]), "SUPERACE");
    holder->AddHardwareAnimationFilm(superAceLand, sizeof(superAceLand) / sizeof(superAceLand[0]), "SUPERACE_LAND");
    holder->AddHardwareAnimationFilm(sideFighters, sizeof(sideFighters) / sizeof(sideFighters[0]), "SIDE_FIGHTER");
    holder->AddHardwareAnimationFilm(qing, sizeof(qing) / sizeof(qing[0]), "QING");
    holder->AddHardwareAnimationFilm(kuroden, sizeof(kuroden) / sizeof(kuroden[0]), "KURODEN");
    holder->AddHardwareAnimationFilm(kurodenSide, sizeof(kurodenSide) / sizeof(kurodenSide[0]), "KURODEN_SIDE");
    holder->AddHardwareAnimationFilm(kurodenKai, sizeof(kurodenKai) / sizeof(kurodenKai[0]), "KURODEN_KAI");
    holder->AddHardwareAnimationFilm(bvd, sizeof(bvd) / sizeof(bvd[0]), "BVD");
    holder->AddHardwareAnimationFilm(fukusuke, sizeof(fukusuke) / sizeof(fukusuke[0]), "FUKUSUKE");
    holder->AddHardwareAnimationFilm(shoryu, sizeof(shoryu) / sizeof(shoryu[0]), "SHORYU");
    holder->AddHardwareAnimationFilm(raizan, sizeof(raizan) / sizeof(raizan[0]), "RAIZAN");
    holder->AddHardwareAnimationFilm(daihiryuLarge, sizeof(daihiryuLarge) / sizeof(daihiryuLarge[0]), "DAIHIRYU_LARGE");

    holder->AddHardwareAnimationFilm(kurodenFlipUp, sizeof(kurodenFlipUp) / sizeof(kurodenFlipUp[0]), "kuroden_flip_up");
    holder->AddHardwareAnimationFilm(kurodenSideRight, sizeof(kurodenSideRight) / sizeof(kurodenSideRight[0]), "kurodenSide_right");
    holder->AddHardwareAnimationFilm(kurodenSideLeft, kurodenSideLeftAttrs, sizeof(kurodenSideLeft) / sizeof(kurodenSideLeft[0]), "kurodenSide_left");
    holder->AddHardwareAnimationFilm(kurodenKaiRightFlipLeft, sizeof(kurodenKaiRightFlipLeft) / sizeof(kurodenKaiRightFlipLeft[0]), "kurodenKai_right_flip_left");
    holder->AddHardwareAnimationFilm(kurodenKaiLeftFlipRight, kurodenKaiLeftFlipRightAttrs, sizeof(kurodenKaiLeftFlipRight) / sizeof(kurodenKaiLeftFlipRight[0]), "kurodenKai_left_flip_right");
    holder->AddHardwareAnimationFilm(kurodenKaiRotatingClockwise, kurodenKaiRotatingClockwiseAttrs, sizeof(kurodenKaiRotatingClockwise) / sizeof(kurodenKaiRotatingClockwise[0]), "kurodenKai_rotating_clockwise");
    holder->AddHardwareAnimationFilm(kurodenKaiRotatingCounterclockwise, kurodenKaiRotatingCounterclockwiseAttrs, sizeof(kurodenKaiRotatingCounterclockwise) / sizeof(kurodenKaiRotatingCounterclockwise[0]), "kurodenKai_rotating_counterclockwise");

    holder->AddHardwareAnimationFilm(fukusukeSideRight, sizeof(fukusukeSideRight) / sizeof(fukusukeSideRight[0]), "fukusuke_side_right");
    holder->AddHardwareAnimationFilm(fukusukeSideLeft, fukusukeSideLeftAttrs, sizeof(fukusukeSideLeft) / sizeof(fukusukeSideLeft[0]), "fukusuke_side_left");
    holder->AddHardwareAnimationFilm(fukusukeDown, sizeof(fukusukeDown) / sizeof(fukusukeDown[0]), "fukusuke_down");
    holder->AddHardwareAnimationFilm(fukusukeUp, fukusukeUpAttrs, sizeof(fukusukeUp) / sizeof(fukusukeUp[0]), "fukusuke_up");
    holder->AddHardwareAnimationFilm(fukusukeDownright, sizeof(fukusukeDownright) / sizeof(fukusukeDownright[0]), "fukusuke_downright");
    holder->AddHardwareAnimationFilm(fukusukeRight, sizeof(fukusukeRight) / sizeof(fukusukeRight[0]), "fukusuke_right");
    holder->AddHardwareAnimationFilm(fukusukeLeft, fukusukeLeftAttrs, sizeof(fukusukeLeft) / sizeof(fukusukeLeft[0]), "fukusuke_left");
    holder->AddHardwareAnimationFilm(fukusukeDownleft, fukusukeDownleftAttrs, sizeof(fukusukeDownleft) / sizeof(fukusukeDownleft[0]), "fukusuke_downleft");
    holder->AddHardwareAnimationFilm(fukusukeTopright, fukusukeToprightAttrs, sizeof(fukusukeTopright) / sizeof(fukusukeTopright[0]), "fukusuke_topright");
    holder->AddHardwareAnimationFilm(fukusukeTopleft, fukusukeTopleftAttrs, sizeof(fukusukeTopleft) / sizeof(fukusukeTopleft[0]), "fukusuke_topleft");

    holder->AddHardwareAnimationFilm(bvdDownright, sizeof(bvdDownright) / sizeof(bvdDownright[0]), "BVD_downright");
    holder->AddHardwareAnimationFilm(bvdDown, sizeof(bvdDown) / sizeof(bvdDown[0]), "BVD_down");
    holder->AddHardwareAnimationFilm(bvdRight, sizeof(bvdRight) / sizeof(bvdRight[0]), "BVD_right");
    holder->AddHardwareAnimationFilm(bvdDownleft, bvdDownleftAttrs, sizeof(bvdDownleft) / sizeof(bvdDownleft[0]), "BVD_downleft");
    holder->AddHardwareAnimationFilm(bvdUp, bvdUpAttrs, sizeof(bvdUp) / sizeof(bvdUp[0]), "BVD_up");
    holder->AddHardwareAnimationFilm(bvdLeft, bvdLeftAttrs, sizeof(bvdLeft) / sizeof(bvdLeft[0]), "BVD_left");
    holder->AddHardwareAnimationFilm(bvdTopleft, bvdTopleftAttrs, sizeof(bvdTopleft) / sizeof(bvdTopleft[0]), "BVD_topleft");
    holder->AddHardwareAnimationFilm(bvdTopright, bvdToprightAttrs, sizeof(bvdTopright) / sizeof(bvdTopright[0]), "BVD_topright");

    holder->AddHardwareAnimationFilm(shoryuDown, sizeof(shoryuDown) / sizeof(shoryuDown[0]), "shoryu_down");
    holder->AddHardwareAnimationFilm(shoryuDownright, sizeof(shoryuDownright) / sizeof(shoryuDownright[0]), "shoryu_downright");
    holder->AddHardwareAnimationFilm(shoryuRight, sizeof(shoryuRight) / sizeof(shoryuRight[0]), "shoryu_right");
    holder->AddHardwareAnimationFilm(shoryuLeft, shoryuLeftAttrs, sizeof(shoryuLeft) / sizeof(shoryuLeft[0]), "shoryu_left");
    holder->AddHardwareAnimationFilm(shoryuDownleft, shoryuDownleftAttrs, sizeof(shoryuDownleft) / sizeof(shoryuDownleft[0]), "shoryu_downleft");
    holder->AddHardwareAnimationFilm(shoryuUp, shoryuUpAttrs, sizeof(shoryuUp) / sizeof(shoryuUp[0]), "shoryu_up");
    holder->AddHardwareAnimationFilm(shoryuTopright, shoryuToprightAttrs, sizeof(shoryuTopright) / sizeof(shoryuTopright[0]), "shoryu_topright");
    holder->AddHardwareAnimationFilm(shoryuTopleft, shoryuTopleftAttrs, sizeof(shoryuTopleft) / sizeof(shoryuTopleft[0]), "shoryu_topleft");

    holder->AddHardwareAnimationFilm(playerBullets, sizeof(playerBullets) / sizeof(playerBullets[0]), "BULLET_SUPERACE");
    holder->AddHardwareAnimationFilm(enemyBullets, sizeof(enemyBullets) / sizeof(enemyBullets[0]), "BULLET_ENEMY");
    holder->AddHardwareAnimationFilm(powerUps, sizeof(powerUps) / sizeof(powerUps[0]), "POWER_UP");
    holder->AddHardwareAnimationFilm(enemyExplosion, sizeof(enemyExplosion) / sizeof(enemyExplosion[0]), "EXPLOSION_ENEMY");
    holder->AddHardwareAnimationFilm(largeEnemyExplosion, sizeof(largeEnemyExplosion) / sizeof(largeEnemyExplosion[0]), "EXPLOSION_LARGE_ENEMY");
    holder->AddHardwareAnimationFilm(playerExplosion, sizeof(playerExplosion) / sizeof(playerExplosion[0]), "EXPLOSION_SUPERACE");
    holder->AddHardwareAnimationFilm(scores, sizeof(scores) / sizeof(scores[0]), "SCORE");
}
}

void AnimationFilmHolder::LoadHardwareFilms(void){
    addHardwareFilms(this);
}

void AnimationFilmHolder::AddHardwareAnimationFilm(const uint8_t* tileIndexes, unsigned count, string id){
    assert(tileIndexes);
    assert(count > 0);

    vector<const SpriteMetadata*> frames;
    for (unsigned i = 0; i < count; ++i) {
        const SpriteMetadata* metadata = SpriteMetadata_FindByTileIndex(tileIndexes[i]);
        assert(metadata && metadata != SpriteMetadata_Default());
        frames.push_back(metadata);
    }

    AnimationFilm* film = new AnimationFilm(frames, id);
    Films::iterator existing = _films.find(id);
    if (existing != _films.end()) {
        delete existing->second;
    }
    _films[id] = film;
    assert(_films[id] != nullptr);
}

void AnimationFilmHolder::AddHardwareAnimationFilm(const uint8_t* tileIndexes, const uint8_t* attributes, unsigned count, string id){
    assert(tileIndexes);
    assert(attributes);
    assert(count > 0);

    vector<AnimationFilm::HardwareFrame> frames;
    for (unsigned i = 0; i < count; ++i) {
        const SpriteMetadata* metadata = SpriteMetadata_FindByTileIndex(tileIndexes[i]);
        assert(metadata && metadata != SpriteMetadata_Default());
        AnimationFilm::HardwareFrame frame = { metadata, attributes[i] };
        frames.push_back(frame);
    }

    AnimationFilm* film = new AnimationFilm(frames, id);
    Films::iterator existing = _films.find(id);
    if (existing != _films.end()) {
        delete existing->second;
    }
    _films[id] = film;
    assert(_films[id] != nullptr);
}

void AnimationFilmHolder::CleanUp(void){
    AnimationFilmHolder* h = Get();

    for(Films::iterator i =h->_films.begin(); i!= h->_films.end(); ++i)
        delete(i->second);
    h->_films.clear();
}

AnimationFilm* AnimationFilmHolder::GetFilm(const std::string id) {
    
    Films::const_iterator i = _films.find(id);
    if (i == _films.end()) {
        i = _films.find(normalizeHardwareFilmId(id));
    }
    
    return i != _films.end() ? i->second : ( AnimationFilm*) 0;
	//return _films[id];
}
