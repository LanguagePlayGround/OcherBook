#include "ocher/ux/fb/FrameBuffer.h"


#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

void Rect::unionRect(Rect* r)
{
    if (! valid()) {
        *this = *r;
        return;
    }
    if (! r->valid()) {
        return;
    }
    if (r->x < x)
        x = r->x;
    if (r->y < y)
        y = r->y;
    int x1 = x + w;
    int x2 = r->x + r->w;
    if (x2 > x1)
        w = max(x1, x2) - x;
    int y1 = y + h;
    int y2 = r->y + r->h;
    if (y2 > y1)
        h = max(y1, y2) - y;
}

void Rect::unionRects(Rect* r1, Rect* r2)
{
    if (! r1->valid()) {
        *this = *r2;
        return;
    }
    if (! r2->valid()) {
        *this = *r1;
        return;
    }
    x = min(r1->x, r2->x);
    y = min(r1->y, r2->y);
    int x1 = r1->x + r1->w;
    int x2 = r2->x + r2->w;
    w = max(x1, x2) - x;
    int y1 = r1->y + r1->h;
    int y2 = r2->y + r2->h;
    h = max(y1, y2) - h;
}

void FrameBuffer::line(int x0, int y0, int x1, int y1)
{
#if 0
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
#else
    int sx = 1;
    int sy = 1;
    int dx = x1 - x0;
    int dy = y1 - y0;
    if (x0 > x1) {
        dx = -dx;
        sx = -sx;
    }
    if (y0 > y1) {
        dy = -dy;
        sy = -sy;
    }
#endif
    int err = dx - dy;

    while (1) {
        pset(x0, y0);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = err<<1;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void FrameBuffer::rect(Rect* r)
{
    hline(r->x, r->y, r->x+r->w-1);
    hline(r->x, r->y+r->h-1, r->x+r->w-1);
    vline(r->x, r->y, r->y+r->h-1);
    vline(r->x+r->w-1, r->y, r->y+r->h-1);
}

void FrameBuffer::roundRect(Rect* r, unsigned int radius)
{
    hline(r->x+radius, r->y, r->x+r->w-1-radius);
    hline(r->x+radius, r->y+r->h-1, r->x+r->w-1-radius);
    vline(r->x, r->y+radius, r->y+r->h-1-radius);
    vline(r->x+r->w-1, r->y+radius, r->y+r->h-1-radius);
    if (radius > 1) {
        // TODO
    }
}

void FrameBuffer::blitGlyphs(Glyph** glyphs, Pos* pen, const Rect* clip)
{
    for (unsigned int i = 0; glyphs[i]; ++i) {
        Glyph* g = glyphs[i];
        blit(g->bitmap, pen->x+g->offsetX, pen->y-g->offsetY, g->w, g->h, clip);
        pen->x += g->advanceX;
        pen->y += g->advanceY;
    }
}
