/*
 * Copyright (c) 2015, Chuck Coffing
 * OcherBook is released under the GPLv3.  See COPYING.
 */

#ifndef OCHER_UX_CDK_BROWSEACTIVITY_H
#define OCHER_UX_CDK_BROWSEACTIVITY_H

#include "ocher/ux/cdk/ActivityCdk.h"


class BrowseActivityCdk : public ActivityCdk {
public:
    BrowseActivityCdk(UxControllerCdk *uxController);

    ~BrowseActivityCdk()
    {
    }

    void onAttached();
    void onDetached();
};


#endif
