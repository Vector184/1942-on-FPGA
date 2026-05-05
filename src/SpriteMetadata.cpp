#include "../includes/SpriteMetadata.hpp"
#include <stdio.h>

static const SpriteMetadata UNKNOWN_METADATA = {255, "UNKNOWN", 0, 0};

static const SpriteMetadata SPRITE_METADATA[] = {
    {0, "KURODEN_1", 16, 16},
    {1, "KURODEN_2", 16, 16},
    {2, "KURODEN_3", 16, 8},
    {3, "SUPERACE_LAND", 16, 8},
    {4, "KURODEN_4", 16, 16},
    {5, "KURODEN_5", 16, 16},
    {6, "KURODEN_6", 16, 16},
    {7, "KURODEN_7", 8, 16},
    {8, "KURODEN_KAI_1", 8, 16},
    {9, "KURODEN_8", 16, 16},
    {10, "KURODEN_KAI_2", 16, 16},
    {11, "KURODEN_KAI_3", 16, 16},
    {12, "KURODEN_KAI_4", 16, 16},
    {13, "KURODEN_KAI_5", 16, 16},
    {14, "KURODEN_KAI_6", 16, 16},
    {15, "KURODEN_KAI_7", 16, 16},
    {16, "KURODEN_KAI_8", 16, 16},
    {17, "BVD_1", 16, 16},
    {18, "BVD_2", 16, 16},
    {19, "BVD_3", 16, 16},
    {20, "FUKUSUKE_1", 16, 16},
    {21, "FUKUSUKE_2", 16, 16},
    {22, "FUKUSUKE_3", 16, 16},
    {23, "FUKUSUKE_4", 16, 16},
    {24, "FUKUSUKE_5", 8, 16},
    {25, "FUKUSUKE_6", 16, 16},
    {26, "FUKUSUKE_7", 16, 16},
    {27, "DAIHIRYU_SMALL", 24, 16},
    {28, "SUPERACE_1", 24, 16},
    {29, "SUPERACE_2", 24, 16},
    {30, "SUPERACE_3", 24, 8},
    {31, "SUPERACE_4", 24, 8},
    {32, "SUPERACE_5", 24, 16},
    {33, "SHORYU_1", 24, 24},
    {34, "SHORYU_2", 24, 24},
    {35, "SHORYU_3", 24, 24},
    {36, "QING_1", 24, 25},
    {37, "RAIZAN_1", 24, 24},
    {38, "DAIHIRYU_MEDIUM", 27, 24},
    {39, "SUPERACE_6", 25, 24},
    {40, "SUPERACE_7", 24, 16},
    {41, "SUPERACE_8", 24, 16},
    {42, "EXPLOSION_SUPERACE_1", 16, 16},
    {43, "EXPLOSION_SUPERACE_2", 16, 16},
    {44, "BULLET_SUPERACE_1", 16, 8},
    {45, "BULLET_SUPERACE_2", 16, 8},
    {46, "BULLET_ENEMY", 8, 8},
    {47, "SCORE_500", 16, 8},
    {48, "SCORE_20000", 24, 8},
    {49, "EXPLOSION_SUPERACE_3", 24, 24},
    {50, "EXPLOSION_SUPERACE_4", 24, 24},
    {51, "EXPLOSION_SUPERACE_5", 24, 24},
    {52, "EXPLOSION_SUPERACE_6", 24, 24},
    {53, "EXPLOSION_SUPERACE_7", 16, 16},
    {54, "BULLET_SUPERACE_3", 8, 8},
    {55, "BULLET_SUPERACE_4", 8, 8},
    {56, "EXPLOSION_ENEMY_1", 24, 24},
    {57, "EXPLOSION_ENEMY_2", 24, 24},
    {58, "EXPLOSION_ENEMY_3", 24, 24},
    {59, "EXPLOSION_ENEMY_4", 24, 24},
    {60, "EXPLOSION_ENEMY_5", 24, 24},
    {61, "EXPLOSION_ENEMY_6", 24, 24},
    {62, "EXPLOSION_ENEMY_7", 24, 24},
    {63, "EXPLOSION_ENEMY_8", 16, 16},
    {64, "EXPLOSION_ENEMY_9", 16, 16},
    {65, "POWER_UP", 16, 16},
    {66, "EXPLOSION_ENEMY_10", 16, 16},
    {67, "EXPLOSION_ENEMY_11", 16, 16},
    {68, "EXPLOSION_ENEMY_12", 16, 16},
    {69, "EXPLOSION_ENEMY_13", 16, 16},
    {70, "EXPLOSION_ENEMY_14", 16, 16},
    {71, "SCORE_1500", 16, 8},
    {72, "SCORE_2000", 16, 8},
    {73, "SCORE_2500", 16, 8},
    {74, "SCORE_3000", 16, 8},
    {75, "SCORE_3500", 16, 8},
    {76, "SCORE_4000", 16, 8},
    {77, "SCORE_4500", 16, 8},
    {78, "SCORE_5000", 16, 8},
    {79, "SCORE_5500", 16, 8},
    {80, "SCORE_6000", 16, 8},
    {81, "SCORE_6500", 16, 8},
    {82, "SCORE_7000", 16, 8},
    {83, "SCORE_7500", 16, 8},
    {84, "SCORE_8000", 16, 8},
    {85, "SCORE_8500", 16, 8},
    {86, "SCORE_9000", 16, 8},
    {87, "SCORE_9500", 16, 8},
    {88, "A", 8, 8},
    {89, "B", 8, 8},
    {90, "C", 8, 8},
    {91, "SCORE_1000", 16, 8},
    {92, "D", 8, 8},
    {93, "E", 8, 8},
    {94, "F", 8, 8},
    {95, "G", 8, 8},
    {96, "H", 8, 8},
    {97, "I", 8, 8},
    {98, "J", 8, 8},
    {99, "K", 8, 8},
    {100, "L", 8, 8},
    {101, "M", 8, 8},
    {102, "N", 8, 8},
    {103, "O", 8, 8},
    {104, "P", 8, 8},
    {105, "R", 8, 8},
    {106, "S", 8, 8},
    {107, "T", 8, 8},
    {108, "U", 8, 8},
    {109, "V", 8, 8},
    {110, "J", 8, 8},
    {111, "W", 8, 8},
    {112, "X", 8, 8},
    {113, "Y", 8, 8},
    {114, "Z", 8, 8},
    {115, "1", 8, 8},
    {116, "2", 8, 8},
    {117, "3", 8, 8},
    {118, "4", 8, 8},
    {119, "5", 8, 8},
    {120, "6", 8, 8},
    {121, "7", 8, 8},
    {122, "8", 8, 8},
    {123, "9", 8, 8},
    {124, "0", 8, 8},
    {125, "-", 8, 8},
    {126, "SPACE", 8, 8},
    {127, "=", 8, 8},
    {128, "%", 8, 8},
    {129, "DAIHIRYU_LARGE", 47, 40},
    {130, "STARTING_SCRN", 256,240},
    {131, "SCORE_BOARD", 256, 240},
    {132,"ROLLING_BKG",256,240},
    {133, "LVL_START", 256, 240},
    {134, "LVL_END",256,240}
};

static bool startsWith(const std::string& value, const char* prefix) {
    return value.find(prefix) == 0;
}

static const SpriteMetadata* findByExactName(const char* name) {
    for (unsigned i = 0; i < sizeof(SPRITE_METADATA) / sizeof(SPRITE_METADATA[0]); ++i) {
        if (std::string(SPRITE_METADATA[i].name) == name) {
            return &SPRITE_METADATA[i];
        }
    }
    return SpriteMetadata_Default();
}

static const SpriteMetadata* findByFamilyFrame(const char* family, unsigned frameNo) {
    char name[40];
    snprintf(name, sizeof(name), "%s_%u", family, frameNo + 1);

    const SpriteMetadata* metadata = findByExactName(name);
    if (metadata != SpriteMetadata_Default()) {
        return metadata;
    }

    snprintf(name, sizeof(name), "%s_1", family);
    metadata = findByExactName(name);
    if (metadata != SpriteMetadata_Default()) {
        return metadata;
    }

    return findByExactName(family);
}

static const SpriteMetadata* findByTileSequence(const uint8_t* sequence, unsigned count, unsigned frameNo) {
    assert(sequence);
    assert(count > 0);
    return SpriteMetadata_FindByTileIndex(sequence[frameNo % count]);
}

static const SpriteMetadata* superAceFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {28, 29, 30, 31, 32, 39, 40, 41, 40, 39, 32, 31, 30, 29, 28};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* kurodenFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {0, 1, 2, 4, 5, 6, 7, 9};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* kurodenSideFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {6, 7, 9};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* kurodenKaiFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {8, 10, 11, 12, 13, 14, 15, 16};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* bvdFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {17, 18, 19, 18};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* fukusukeFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {20, 21, 22, 21};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* shoryuFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {33, 34, 35, 34};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* superAceBulletFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {44, 45, 54, 55};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* enemyExplosionFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68, 69, 70};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* largeEnemyExplosionFrame(unsigned frameNo) {
    static const uint8_t sequence[] = {56, 57, 58, 59, 60, 61, 62, 63, 64};
    return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
}

static const SpriteMetadata* findTextTile(const std::string& spriteId) {
    if (spriteId == " ") {
        return findByExactName("SPACE");
    }
    if (spriteId.size() == 1) {
        return findByExactName(spriteId.c_str());
    }
    return SpriteMetadata_Default();
}

const SpriteMetadata* SpriteMetadata_FindByTileIndex(uint8_t tileIndex) {
    for (unsigned i = 0; i < sizeof(SPRITE_METADATA) / sizeof(SPRITE_METADATA[0]); ++i) {
        if (SPRITE_METADATA[i].tileIndex == tileIndex) {
            return &SPRITE_METADATA[i];
        }
    }
    return SpriteMetadata_Default();
}

const SpriteMetadata* SpriteMetadata_FindByName(const std::string& spriteId) {
    const SpriteMetadata* metadata = findByExactName(spriteId.c_str());
    if (metadata != SpriteMetadata_Default()) {
        return metadata;
    }
    return SpriteMetadata_Resolve(spriteId, 0);
}

const SpriteMetadata* SpriteMetadata_Resolve(const std::string& spriteId, unsigned frameNo) {
    const SpriteMetadata* exactMetadata = findByExactName(spriteId.c_str());
    if (exactMetadata != SpriteMetadata_Default()) {
        return exactMetadata;
    }

    if (startsWith(spriteId, "SUPERACE")) return superAceFrame(frameNo);
    if (startsWith(spriteId, "BULLET_SUPERACE")) return superAceBulletFrame(frameNo);
    if (startsWith(spriteId, "BULLET_ENEMY")) return findByExactName("BULLET_ENEMY");
    if (startsWith(spriteId, "QING")) return findByExactName("QING_1");
    if (startsWith(spriteId, "FUKUSUKE")) return fukusukeFrame(frameNo);
    if (startsWith(spriteId, "KURODEN_SIDE")) return kurodenSideFrame(frameNo);
    if (startsWith(spriteId, "KURODEN_KAI")) return kurodenKaiFrame(frameNo);
    if (startsWith(spriteId, "KURODEN")) return kurodenFrame(frameNo);
    if (startsWith(spriteId, "BVD")) return bvdFrame(frameNo);
    if (startsWith(spriteId, "SHORYU")) return shoryuFrame(frameNo);
    if (startsWith(spriteId, "RAIZAN")) return findByExactName("RAIZAN_1");
    if (startsWith(spriteId, "DAIHIRYU_LARGE")) return findByExactName("DAIHIRYU_LARGE");
    if (startsWith(spriteId, "POWER_UP")) return findByExactName("POWER_UP");
    if (startsWith(spriteId, "EXPLOSION_LARGE_ENEMY")) return largeEnemyExplosionFrame(frameNo);
    if (startsWith(spriteId, "EXPLOSION_ENEMY")) return enemyExplosionFrame(frameNo);
    if (startsWith(spriteId, "SuperAce")) return superAceFrame(frameNo);
    if (spriteId == LEFT_FIGHTER || spriteId == RIGHT_FIGHTER) return superAceFrame(frameNo);
    if (startsWith(spriteId, "spriteSuperAceFire") || startsWith(spriteId, "spriteSideSuperAceFire")) return superAceBulletFrame(frameNo);
    if (startsWith(spriteId, "spriteEnemyFire") || startsWith(spriteId, "spriteEnemySide")) return findByExactName("BULLET_ENEMY");
    if (startsWith(spriteId, "RedJet")) return findByFamilyFrame("QING", frameNo);
    if (startsWith(spriteId, "MiniGreenJet")) return fukusukeFrame(frameNo);
    if (startsWith(spriteId, "MiniGreyJet")) return kurodenFrame(frameNo);
    if (startsWith(spriteId, "MiniGreenOneEng")) return kurodenFrame(frameNo);
    if (startsWith(spriteId, "MiniGreyOneEng")) return kurodenKaiFrame(frameNo);
    if (startsWith(spriteId, "MiniGreenDoubleEng")) return bvdFrame(frameNo);
    if (startsWith(spriteId, "MiniGreyDoubleEng")) return bvdFrame(frameNo);
    if (startsWith(spriteId, "MedGreenDoubleEng")) return shoryuFrame(frameNo);
    if (startsWith(spriteId, "MedGreenTripleEng")) return findByFamilyFrame("RAIZAN", frameNo);
    if (startsWith(spriteId, "MedGreenSingleEng")) return findByFamilyFrame("QING", frameNo);
    if (startsWith(spriteId, "MedGreyDoubleEng")) return shoryuFrame(frameNo);
    if (startsWith(spriteId, "MedGreySingleEng")) return findByFamilyFrame("QING", frameNo);
    if (startsWith(spriteId, "MedGreyTripleEng")) return findByFamilyFrame("RAIZAN", frameNo);
    if (startsWith(spriteId, "BigGreen") || startsWith(spriteId, "BigGrey")) return findByExactName("DAIHIRYU_LARGE");
    if (startsWith(spriteId, "deathStar")) return findByExactName("DAIHIRYU_LARGE");
    if (startsWith(spriteId, "spritePowerUpId")) return findByExactName("POWER_UP");
    if (startsWith(spriteId, "spriteExplosionId")) return enemyExplosionFrame(frameNo);
    if (startsWith(spriteId, "scoreSprite")) {
        if (frameNo == 0) return findByExactName("SCORE_1000");
        if (frameNo == 1) return findByExactName("SCORE_2000");
        if (frameNo == 2) return findByExactName("SCORE_1500");
        return findByExactName("SCORE_1000");
    }

    return findTextTile(spriteId);
}

const SpriteMetadata* SpriteMetadata_ResolveAnimationFrame(const std::string& spriteId, const std::string& filmId, unsigned frameNo) {
    const SpriteMetadata* metadata = SpriteMetadata_Resolve(spriteId, frameNo);
    if (metadata != SpriteMetadata_Default()) {
        return metadata;
    }

    if (filmId == "SUPERACE" || filmId == "SIDE_FIGHTER" || filmId == "Super.Ace.1942.Scaled" || filmId == "Super.Ace.1942" || filmId == "Super.Ace" || filmId == "sideFighters") return superAceFrame(frameNo);
    if (filmId == "QING" || filmId == "red_plane" || filmId == "grey_medium_planes_2") return findByExactName("QING_1");
    if (filmId == "FUKUSUKE" || filmId == "green_jet") return fukusukeFrame(frameNo);
    if (filmId == "KURODEN_SIDE") return kurodenSideFrame(frameNo);
    if (filmId == "KURODEN" || filmId == "mini_green_one_eng" || filmId == "gray_jet") return kurodenFrame(frameNo);
    if (filmId == "KURODEN_KAI" || filmId == "min_gray_plane") return kurodenKaiFrame(frameNo);
    if (filmId == "BVD" || filmId == "green_double_engine" || filmId == "mini_grey_double_engine") return bvdFrame(frameNo);
    if (filmId == "SHORYU" || filmId == "green_medium_plane" || filmId == "grey_medium_plane") return shoryuFrame(frameNo);
    if (filmId == "RAIZAN" || filmId == "green_medium_triple") return findByExactName("RAIZAN_1");
    if (filmId == "DAIHIRYU_LARGE" || filmId == "bigGreen" || filmId == "bigGrey" || filmId == "deathStarFilm") return findByExactName("DAIHIRYU_LARGE");
    if (filmId == "BULLET_SUPERACE" || filmId == "bullets") return superAceBulletFrame(frameNo);
    if (filmId == "BULLET_ENEMY" || filmId == "enemyBullets") return findByExactName("BULLET_ENEMY");
    if (filmId == "POWER_UP" || filmId == "powerUps") return findByExactName("POWER_UP");
    if (filmId == "EXPLOSION_LARGE_ENEMY") return largeEnemyExplosionFrame(frameNo);
    if (filmId == "EXPLOSION_ENEMY" || filmId == "explosion") return enemyExplosionFrame(frameNo);
    if (filmId == "SCORE" || filmId == "scores") {
        static const uint8_t sequence[] = {91, 72, 71};
        return findByTileSequence(sequence, sizeof(sequence) / sizeof(sequence[0]), frameNo);
    }

    return SpriteMetadata_Default();
}

const SpriteMetadata* SpriteMetadata_Default(void) {
    return &UNKNOWN_METADATA;
}
