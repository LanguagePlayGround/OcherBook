#ifndef OCHER_UX_HOMEACTIVITY_H
#define OCHER_UX_HOMEACTIVITY_H

#include "ocher/ux/Activity.h"


class HomeActivity : public Panel
{
public:
    HomeActivity(Controller* c);
    ~HomeActivity();

    Rect draw(Pos* pos);

    int evtKey(struct OcherKeyEvent*);
    int evtMouse(struct OcherMouseEvent*);

protected:
    void onAttached();
    void onDetached();

    Controller* m_controller;

    float coverRatio;
#define NUM_CLUSTER_BOOKS 5
    Rect books[NUM_CLUSTER_BOOKS];
    Rect shortlist[5];
    Rect m_browseLabel;
};

#endif
