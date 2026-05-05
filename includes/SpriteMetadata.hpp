#ifndef SpriteMetadata_hpp
#define SpriteMetadata_hpp

#include "../includes/includes.h"
#include <stdint.h>

struct SpriteMetadata {
    uint8_t tileIndex;
    const char* name;
    uint16_t width;
    uint16_t height;
};

const SpriteMetadata* SpriteMetadata_FindByTileIndex(uint8_t tileIndex);
const SpriteMetadata* SpriteMetadata_FindByName(const std::string& spriteId);
const SpriteMetadata* SpriteMetadata_Resolve(const std::string& spriteId, unsigned frameNo);
const SpriteMetadata* SpriteMetadata_ResolveAnimationFrame(const std::string& spriteId, const std::string& filmId, unsigned frameNo);
const SpriteMetadata* SpriteMetadata_Default(void);

#endif
