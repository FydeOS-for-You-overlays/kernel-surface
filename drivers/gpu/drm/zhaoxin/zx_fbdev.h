#ifndef _H_ZX_FBDEV_H
#define _H_ZX_FBDEV_H
#include "zx_drmfb.h"
#include "zx_device_debug.h"

#define  MAX_RESERVED_VMEM  (3840*2160*4)    //reserved vmem for SW fb

struct zx_fbdev
{
    struct drm_fb_helper helper;
    struct drm_zx_framebuffer *fb;
    int  need_clear;
};

#define to_zx_fbdev(helper) container_of(helper, struct zx_fbdev, helper)


void zx_fbdev_disable_vesa(zx_card_t *zx);
int zx_fbdev_init(zx_card_t *zx);
int zx_fbdev_deinit(zx_card_t *zx);
void zx_fbdev_set_suspend(zx_card_t *zx, int state);
void zx_fbdev_poll_changed(struct drm_device *dev);
#endif
