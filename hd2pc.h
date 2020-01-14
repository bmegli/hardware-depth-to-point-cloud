/*
 * HD2PC - Hardware Depth to Point Cloud C library
 *
 * Copyright 2020 (C) Bartosz Meglicki <meglickib@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

/**
 ******************************************************************************
 *
 *  \mainpage HD2PC documentation
 *  \see https://github.com/bmegli/hardware-depth-to-point-cloud
 *
 *  \copyright  Copyright (C) 2020 Bartosz Meglicki
 *  \file       hd2pc.h
 *  \brief      Library public interface header
 *
 ******************************************************************************
 */

#ifndef HD2PC_H
#define HD2PC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h> //uint16_t

/** \addtogroup interface Public interface
 *  @{
 */

struct hd2pc;

struct hd2pc_depth
{
	uint16_t *data;
	int width;
	int height;
	int stride;
};

typedef float float3[3];

struct hd2pc_point_cloud
{
	float3 *data;
	int size;
	int used;
};


//NULL on ERROR
struct hd2pc *hd2pc_init(float ppx, float ppy, float fx, float fy, float depth_unit);
void hd2pc_close(struct hd2pc *h);

void hd2pc_unproject(const struct hd2pc *h, const struct hd2pc_depth *depth, struct hd2pc_point_cloud *pc);

/** @}*/

#ifdef __cplusplus
}
#endif

#endif
