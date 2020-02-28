/*
 * HDU - Hardware Depth Unprojector example
 *
 * Copyright 2020 (C) Bartosz Meglicki <meglickib@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "../hdu.h"

#include <stdio.h>

const float PPX=421.353;
const float PPY=240.93;
const float FX=426.768;
const float FY=426.768;
const float DEPTH_UNIT=0.0001;

const uint16_t P010LE_MAX = 0xFFC0; //in binary 10 ones followed by 6 zeroes

void print_point_cloud(const struct hdu_point_cloud *pc);

int main(int argc, char **argv)
{

	struct hdu *h;

	if( (h = hdu_init(PPX, PPY, FX, FY, DEPTH_UNIT)) == NULL )
	{
		fprintf(stderr, "failed to initizlize hdu\n");
		return 1;
	}

	//dummy depth map data (middle value)
	uint16_t v = UINT16_MAX/2;
	//dummy color value (middle value)
	uint16_t c = P010LE_MAX/2;

	uint16_t depth_data[4] = {v, v, v, v};

	//only every second horizontal color (greyscale) value is encoded, see
	//https://github.com/bmegli/unity-network-hardware-video-decoder/issues/11#issuecomment-591970124
	uint16_t color_data[2] = {c, c};

	//pass here pointer to your real data and its size, stride
	struct hdu_depth depth = {depth_data, (uint8_t*)color_data, 2, 2, 2*2};

	//placeholder for output point cloud data
	float3 point_data[4];
	color32 point_color_data[4];
	struct hdu_point_cloud pc = {point_data, point_color_data, 4, 0};

	//unproject the depth map to point cloud
	hdu_unproject(h, &depth, &pc);

	//here just print the result point cloud
	print_point_cloud(&pc);

	hdu_close(h);

	return 0;
}

void print_point_cloud(const struct hdu_point_cloud *pc)
{
	printf("Point cloud: %d points\n", pc->used);

	for(int p=0;p<pc->size;++p)
		printf("%d: [%f, %f, %f] - color %d\n", p, pc->data[p][0], pc->data[p][1], pc->data[p][2], pc->colors[p]);
}
