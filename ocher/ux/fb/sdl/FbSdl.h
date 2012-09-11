#ifndef SDL_FB_H
#define SDL_FB_H

#include "SDL/SDL.h"

#include "ocher/ux/fb/FrameBuffer.h"


class FbSdl : public FrameBuffer
{
public:
    FbSdl();
    virtual ~FbSdl();

    bool init();

    unsigned int height();
    unsigned int width();
    unsigned int dpi();

    void clear();
    void blit(unsigned char *p, int x, int y, int w, int h);
    int update(unsigned int x, unsigned int y, unsigned int w, unsigned int h, bool full=true);

protected:
    int m_sdl;
    SDL_Surface *m_screen;
};

#endif

