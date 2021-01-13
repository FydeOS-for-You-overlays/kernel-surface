/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#ifndef __MTK_MDP3_M2M_H__
#define __MTK_MDP3_M2M_H__

#include <media/v4l2-ctrls.h>
#include "mtk-mdp3-core.h"
#include "mtk-mdp3-vpu.h"
#include "mtk-mdp3-regs.h"

#define MDP_MAX_CTRLS	10

struct mdp_m2m_ctrls {
	struct v4l2_ctrl	*hflip;
	struct v4l2_ctrl	*vflip;
	struct v4l2_ctrl	*rotate;
};

struct mdp_m2m_ctx {
	u32				id;
	struct mdp_dev			*mdp_dev;
	struct v4l2_fh			fh;
	struct v4l2_ctrl_handler	ctrl_handler;
	struct mdp_m2m_ctrls		ctrls;
	struct v4l2_m2m_ctx		*m2m_ctx;
	struct mdp_vpu_ctx		vpu;
	struct work_struct		work;
	u32				frame_count;

	struct mdp_frameparam		curr_param;
};

int mdp_m2m_device_register(struct mdp_dev *mdp);
void mdp_m2m_device_unregister(struct mdp_dev *mdp);
void mdp_m2m_job_finish(struct mdp_m2m_ctx *ctx);

#endif  /* __MTK_MDP3_M2M_H__ */

