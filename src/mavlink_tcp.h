/****************************************************************************
 *
 * Copyright (C) 2017  Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>

#include <mavlink.h>

#include "pollable.h"

#define SYSTEM_ID_MAIN 100

class Mavlink_TCP : public Pollable {
public:
	virtual ~Mavlink_TCP();

	int init(const char *ip, unsigned long port, uint8_t system_id);

	void handle_read() override;
	bool handle_canwrite() override;

	void highres_imu_msg_subscribe(void (*callback)(const mavlink_highres_imu_t *msg, void *data), const void *data);

	int optical_flow_rad_msg_write(mavlink_optical_flow_rad_t *msg);
private:
	struct sockaddr_in _sockaddr;

	void _handle(mavlink_message_t *msg);

	void (*_highres_imu_msg_callback)(const mavlink_highres_imu_t *msg, void *data) = NULL;
	const void *_highres_imu_msg_callback_data;

	uint8_t _system_id;
	const uint8_t _component_id = 1;
};
