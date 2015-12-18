/*
 * Copyright (c) 2015, Chuck Coffing
 * OcherBook is released under the GPLv3.  See COPYING.
 */

#include "ocher/Container.h"
#include "ocher/device/Battery.h"
#include "ocher/device/Device.h"
#include "ocher/device/Filesystem.h"
#include "ocher/settings/Options.h"
#include "ocher/settings/Settings.h"
#include "ocher/ux/Controller.h"
#include "ocher/ux/PowerSaver.h"
#include "ocher/ux/Renderer.h"
#include "ocher/ux/fb/FontEngine.h"
#include "ocher/ux/fb/FrameBuffer.h"


Container g_container;

Container::Container() :
    loop(0),
    device(0),
    battery(0),
    filesystem(0),
    settings(0),
    powerSaver(0),
    uxController(0),
    frameBuffer(0),
    fontEngine(0),
    renderer(0)
{
}

Container::~Container()
{
    delete uxController;
    delete battery;
    delete filesystem;
    delete settings;
    delete powerSaver;
    delete loop;
    delete device;
#ifdef UX_FB  // TODO:  Does this belong on UxControllerFb?  no one else would use it.
    delete frameBuffer;
    delete fontEngine;
#endif
    delete renderer;

}

// wire
// unwire
// destroy
