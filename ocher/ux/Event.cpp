/*
 * Copyright (c) 2015, Chuck Coffing
 * OcherBook is released under the GPLv3.  See COPYING.
 */

#include "ocher/ux/Event.h"
#include "ocher/util/Logger.h"

#include <ev.h>

#define LOG_NAME "ocher.evt"


EventLoop::EventLoop() :
    evLoop(EV_DEFAULT),
    m_epoch(0)
{
}

EventLoop::~EventLoop()
{
}

int EventLoop::run()
{
    Log::debug(LOG_NAME, "ev_run");

    ev_run(evLoop, 0);
    Log::debug(LOG_NAME, "ev_run done");

    return 0;
}

void EventLoop::stop()
{
    ev_break(evLoop, EVBREAK_ALL);
}

void EventLoop::setEpoch()
{
    /* TODO m_epoch = SDL_GetTick() */
}

EventWork::EventWork(EventLoop *loop) :
    Thread("EventWork %p", loop->evLoop),
    m_loop(loop)
{
    ev_async_init(&m_async, notifyCb);
    m_async.data = this;
    ev_async_start(m_loop->evLoop, &m_async);
}

EventWork::~EventWork()
{
}

void EventWork::run()
{
    work();
    ev_async_send(m_loop->evLoop, &m_async);
}

void EventWork::notifyCb(EV_P_ ev_async *w, int revents)
{
    EventWork *self = ((EventWork *)w->data);

    self->notify();
}
