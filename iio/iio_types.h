/***************************************************************************//**
 *   @file   iio_types.h
 *   @brief  Header file for iio_types
 *   @author Cristian Pop (cristian.pop@analog.com)
********************************************************************************
 * Copyright 2013(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#ifndef IIO_TYPES_H_
#define IIO_TYPES_H_

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

/******************************************************************************/
/*************************** Types Declarations *******************************/
/******************************************************************************/

/**
 * @struct iio_ch_info
 * @brief Structure holding channel attributess.
 */
struct iio_ch_info {
	/** Channel number */
	int16_t ch_num;
	/** Channel type: input/output */
	bool ch_out;
};

/**
 * @struct iio_attribute
 * @brief Structure holding pointers to show and store functions.
 */
struct iio_attribute {
	/** Attribute name */
	const char *name;
	/** Show function pointer */
	ssize_t (*show)(void *device, char *buf, size_t len,
			const struct iio_ch_info *channel);
	/** Store function pointer */
	ssize_t (*store)(void *device, char *buf, size_t len,
			 const struct iio_ch_info *channel);
};

/**
 * @struct iio_channel
 * @brief Structure holding attributes of a channel.
 */
struct iio_channel {
	/** channel name */
	char *name;
	/** list of attributes */
	struct iio_attribute **attributes;
	/** if true, the channel is an output channel */
	bool ch_out;
};

/**
 * @struct iio_device
 * @brief Structure holding channels and attributes of a device.
 */
struct iio_device {
	/** Device name */
	const char *name;
	/** Device number of channels */
	uint16_t num_ch;
	/** List of channels */
	struct iio_channel **channels;
	/** List of attributes */
	struct iio_attribute **attributes;
};

/**
 * @struct iio_server_ops
 * @brief iio interface for server read/write operations
 */
struct iio_server_ops {
	/** Read from from a peripheral device (UART, USB, NETWORK) */
	ssize_t (*read)(char *buf, size_t len);
	/** Write to a peripheral device (UART, USB, NETWORK) */
	ssize_t (*write)(const char *buf, size_t len);
};

#endif /* IIO_TYPES_H_ */
