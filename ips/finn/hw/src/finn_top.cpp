/*
 * Fred hardware accelerator stub.
 *
 * Copyright (C) 2019, Marco Pagani, ReTiS Lab.
 * <marco.pag(at)outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
*/

#include "finn_top.hpp"
#include "top.hpp"

void finn_top(args_t *id, args_t args[ARGS_SIZE], data_t *mem_in, data_t *mem_out)
{
#pragma HLS INLINE
	// AXI Lite control bus
	#pragma HLS INTERFACE s_axilite port=return bundle=ctrl_bus
	#pragma HLS INTERFACE s_axilite port=id bundle=ctrl_bus
	#pragma HLS INTERFACE s_axilite port=args bundle=ctrl_bus

	// AXI Master memory ports
	#pragma HLS INTERFACE m_axi port=mem_in offset=slave bundle=mem_bus
	#pragma HLS INTERFACE s_axilite port=mem_in bundle=ctrl_bus
	#pragma HLS INTERFACE m_axi port=mem_out offset=slave bundle=mem_bus
	#pragma HLS INTERFACE s_axilite port=mem_out bundle=ctrl_bus

	*id = 100;

	do_compute(mem_in + args[0] / sizeof(data_t), mem_out + args[1] / sizeof(data_t));
}

//void hw_task_1(args_t *id, args_t args[ARGS_SIZE], volatile data_t *mem_in, volatile data_t *mem_out)
//{
//	#pragma HLS DATAFLOW
//
//	// AXI Lite control bus
//	#pragma HLS INTERFACE s_axilite port=return bundle=ctrl_bus
//	#pragma HLS INTERFACE s_axilite port=id bundle=ctrl_bus
//	#pragma HLS INTERFACE s_axilite port=args bundle=ctrl_bus
//
//	// AXI Master memory ports
//	#pragma HLS INTERFACE m_axi port=mem_in offset=slave bundle=mem_bus
//	#pragma HLS INTERFACE s_axilite port=mem_in bundle=ctrl_bus
//	#pragma HLS INTERFACE m_axi port=mem_out offset=slave bundle=mem_bus
//	#pragma HLS INTERFACE s_axilite port=mem_out bundle=ctrl_bus
//
//	hw_mod(id, mem_in, mem_out, args[0], args[1]);
//}

