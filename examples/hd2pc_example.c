/*
 * HD2PC - Hardware Depth to Point Cloud example
 *
 * Copyright 2020 (C) Bartosz Meglicki <meglickib@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "../hd2pc.h"

#include <stdio.h>

const float PPX=421.353;
const float PPY=240.93;
const float FX=426.768;
const float FY=426.768;
const float DEPTH_UNIT=0.0001;

void print_point_cloud(const struct hd2pc_point_cloud *pc);

int main(int argc, char **argv)
{

	struct hd2pc *h;

	if( (h = hd2pc_init(PPX, PPY, FX, FY, DEPTH_UNIT)) == NULL )
	{
		fprintf(stderr, "failed to initizlize hd2pc\n");
		return 1;
	}

	//dummy depth map data (middle value)
	uint16_t v = UINT16_MAX/2;
	uint16_t depth_data[4] = {v, v, v, v};

	//pass here pointer to your real data and its size, stride
	struct hd2pc_depth depth = {depth_data, 2, 2, 2*2};

	//placeholder for output point cloud data
	float3 point_data[4];
	struct hd2pc_point_cloud pc = {point_data, 4, 0};

	//unproject the depth map to point cloud
	hd2pc_unproject(h, &depth, &pc);

	//here just print the result point cloud
	print_point_cloud(&pc);

	hd2pc_close(h);

	return 0;
}

void print_point_cloud(const struct hd2pc_point_cloud *pc)
{
	printf("Point cloud: %d points\n", pc->used);

	for(int p=0;p<pc->size;++p)
		printf("%d: [%f, %f, %f]\n", p, pc->data[p][0], pc->data[p][1], pc->data[p][2]);
}
