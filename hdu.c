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
#include <math.h> //fabs

//in binary 10 ones followed by 6 zeroes
static const uint16_t P010LE_MAX = 0xFFC0;

struct hdu
{
	float ppx;
	float ppy;
	float fx;
	float fy;
	float depth_unit;
	float min_depth;
	float max_depth;
};

struct hdu *hdu_init(const struct hdu_config *c)
{
	struct hdu *h;

	if( ( h = (struct hdu*)malloc(sizeof(struct hdu))) == NULL )
	{
		fprintf(stderr, "hdu: not enough memory for hdu\n");
		//errno = ENOMEM;
		return NULL;
	}

	h->ppx = c->ppx;
	h->ppy = c->ppy;
	h->fx = c->fx;
	h->fy = c->fy;
	h->depth_unit = c->depth_unit;
	h->min_depth = c->min_margin;
	h->max_depth = P010LE_MAX * c->depth_unit - c->max_margin;

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
	const color32 default_color = 0xFFFFFFFF;
	const color32 red_color = 0xFF0000FF;
	const color32 blue_color = 0xFFFF0000;
	const float z_move_m = 0.50f / 30.0f;
	const float sqrt3 = sqrt(3);
	const float baseline_m = 0.095;

	int points=0;
	float d;

	for(int r=0;r<depth->height;++r)
		for(int c=0;c<depth->width && points < pc_size;++c)
		{
			if( (d = depth->data[r * depth->depth_stride / 2 + c] * h->depth_unit) <= h->min_depth ||
			     d > h->max_depth)
				continue;

			pc->data[points][0] = d * (c - h->ppx) / h->fx;
			pc->data[points][1] = -d * (r - h->ppy) / h->fy;
			pc->data[points][2] = d;

			const uint32_t *color_line = (uint32_t*)(((uint8_t*)depth->colors) + r * depth->color_stride);
//			pc->colors[points] = depth->colors ? color_line[c] : default_color;

			pc->colors[points] = (d < pc->data[points][0] + z_move_m) ||
			                     (d < baseline_m - pc->data[points][0] + z_move_m ) ?
			                     red_color : color_line[c];

			if(d < fabs(pc->data[points][1]) * sqrt3 + z_move_m)
				pc->colors[points] = blue_color;

			++points;
		}

	pc->used = points;
	return;
}
