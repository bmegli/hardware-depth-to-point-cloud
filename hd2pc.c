/*
 * HD2PC - Hardware Depth to Point Cloud C library implementation
 *
 * Copyright 2020 (C) Bartosz Meglicki <meglickib@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "hd2pc.h"

#include <stdio.h> //fprintf
#include <stdlib.h> //malloc

struct hd2pc
{
	float ppx;
	float ppy;
	float fx;
	float fy;
	float depth_unit;
};

struct hd2pc *hd2pc_init(float ppx, float ppy, float fx, float fy, float depth_unit)
{
	struct hd2pc *h;

	if( ( h = (struct hd2pc*)malloc(sizeof(struct hd2pc))) == NULL )
	{
		fprintf(stderr, "hd2pc: not enough memory for hd2pc\n");
		//errno = ENOMEM;
		return NULL;
	}

	h->ppx = ppx;
	h->ppy = ppy;
	h->fx = fx;
	h->fy = fy;
	h->depth_unit = depth_unit;

	return h;
}

void hd2pc_close(struct hd2pc *h)
{
	if(h == NULL)
		return;

	free(h);
}

void hd2pc_unproject(const struct hd2pc *h, const struct hd2pc_depth *depth, struct hd2pc_point_cloud *pc)
{
	//possibly handle clamp value specially
	int points=0;
	float d;

	for(int r=0;r<depth->height;++r)
		for(int c=0;c<depth->width;++c)
		{
			if(points == pc->size)
				break;

			if( (d = depth->data[r * depth->stride / 2 + c] * h->depth_unit) == 0 )
				continue;

			pc->data[points][0] = d * (c - h->ppx) / h->fx;
			pc->data[points][1] = d * (r - h->ppy) / h->fy;
			pc->data[points][2] = d;

			++points;
		}

	pc->used = points;
	return;
}
