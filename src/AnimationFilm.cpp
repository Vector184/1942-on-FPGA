#include "../includes/AnimationFilm.hpp"

//TODO ChangeMasked Blit to  SLD Blit
void AnimationFilm::displayFrame(SDL_Renderer* renderer, const SDL_Point point, unsigned frameNo, SDL_Rect dstRect) const{

#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
    (void)renderer;
    (void)point;
    (void)frameNo;
    (void)dstRect;
#else
    if (_hardwareFrames.empty() == false || !_texture) {
        return;
    }
	SDL_RenderCopyEx(renderer, _texture, &(_boxes[frameNo]), &dstRect, _degrees, &point, SDL_FLIP_NONE);
#endif
}

unsigned AnimationFilm::getTotalFrames(void) const{
    if (!_hardwareFrames.empty()) {
        return (unsigned)_hardwareFrames.size();
    }
    return (unsigned)_boxes.size();
}

SDL_Texture* AnimationFilm::getTexture(void) const  {
#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
    return nullptr;
#else
    return _texture;
#endif
}

const std::string AnimationFilm::getId (void) const {
    return _id;
}

const SDL_Rect  AnimationFilm ::getFrameBox(unsigned frameNo) const{
    if (!_hardwareFrames.empty()) {
        const SpriteMetadata* metadata = getFrameMetadata(frameNo);
        return {0, 0, metadata->width, metadata->height};
    }
    assert(_boxes.size() > frameNo);
    return _boxes[frameNo];
}

bool AnimationFilm::hasHardwareFrames(void) const{
    return !_hardwareFrames.empty();
}

const SpriteMetadata* AnimationFilm::getFrameMetadata(unsigned frameNo) const{
    if (_hardwareFrames.empty()) {
        return SpriteMetadata_Default();
    }

    return _hardwareFrames[frameNo % _hardwareFrames.size()].metadata;
}

uint8_t AnimationFilm::getFrameAttributes(unsigned frameNo) const{
    if (_hardwareFrames.empty()) {
        return 0;
    }

    return _hardwareFrames[frameNo % _hardwareFrames.size()].attributes;
}

void AnimationFilm::setDegrees(int d){
    _degrees =d;
}
AnimationFilm::AnimationFilm(SDL_Texture* texture ,vector<SDL_Rect> boxes ,string id){
    _texture=texture;
    _boxes=boxes;
    _id=id;
    _degrees = 0;
}

AnimationFilm::AnimationFilm(vector<const SpriteMetadata*> hardwareFrames, string id){
    _texture = nullptr;
    for (vector<const SpriteMetadata*>::const_iterator it = hardwareFrames.begin(); it != hardwareFrames.end(); ++it) {
        HardwareFrame frame = { *it, 0 };
        _hardwareFrames.push_back(frame);
    }
    _id = id;
    _degrees = 0;
}

AnimationFilm::AnimationFilm(vector<HardwareFrame> hardwareFrames, string id){
    _texture = nullptr;
    _hardwareFrames = hardwareFrames;
    _id = id;
    _degrees = 0;
}
