/*
 * HDU - Hardware Depth Unprojector C library implementation
 *
 * Copyright 2020 (C) Bartosz Meglicki <meglickib@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "hdu.h"

#include <stdio.h> //fprintf
#include <stdlib.h> //malloc

struct hdu
{
	float ppx;
	float ppy;
	float fx;
	float fy;
	float depth_unit;
};

struct hdu *hdu_init(float ppx, float ppy, float fx, float fy, float depth_unit)
{
	struct hdu *h;

	if( ( h = (struct hdu*)malloc(sizeof(struct hdu))) == NULL )
	{
		fprintf(stderr, "hdu: not enough memory for hdu\n");
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

void hdu_close(struct hdu *h)
{
	if(h == NULL)
		return;

	free(h);
}

void hdu_unproject(const struct hdu *h, const struct hdu_depth *depth, struct hdu_point_cloud *pc)
{
	const int pc_size = pc->size;
	int points=0;
	float d;
	const float max_d = 0.19f;

	for(int r=0;r<depth->height;++r)
		for(int c=0;c<depth->width && points < pc_size;++c)
		{
			if( (d = depth->data[r * depth->stride / 2 + c] * h->depth_unit) < max_d )
				continue;

			pc->data[points][0] = d * (c - h->ppx) / h->fx;
			pc->data[points][1] = -d * (r - h->ppy) / h->fy;
			pc->data[points][2] = d;

			//for explanation see:
			//https://github.com/bmegli/unity-network-hardware-video-decoder/issues/11#issuecomment-591970124
			pc->colors[points] = depth->colors[r/2 * depth->stride + (r % 2) * depth->width  + c + 1 - c % 2];

			++points;
		}

	pc->used = points;
	return;
}
