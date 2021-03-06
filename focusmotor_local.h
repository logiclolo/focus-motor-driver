/*
*******************************************************************************
* $Header: $
*
*  Copyright (c) 2000-2010 VIVOTEK Inc. All rights reserved.
*
*  +-----------------------------------------------------------------+
*  | THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY ONLY BE USED |
*  | AND COPIED IN ACCORDANCE WITH THE TERMS AND CONDITIONS OF SUCH  |
*  | A LICENSE AND WITH THE INCLUSION OF THE THIS COPY RIGHT NOTICE. |
*  | THIS SOFTWARE OR ANY OTHER COPIES OF THIS SOFTWARE MAY NOT BE   |
*  | PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY OTHER PERSON. THE   |
*  | OWNERSHIP AND TITLE OF THIS SOFTWARE IS NOT TRANSFERRED.        |
*  |                                                                 |
*  | THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT   |
*  | ANY PRIOR NOTICE AND SHOULD NOT BE CONSTRUED AS A COMMITMENT BY |
*  | VIVOTEK INC.                                                    |
*  +-----------------------------------------------------------------+
*
* $History: $
*/

/*!
*******************************************************************************
* Copyright 2000-2010 VIVOTEK, Inc. All rights reserved.
*
* \file
* focusmotor_local.h
*
* \brief
* Local header file of focus motor control driver
*
* \date
* 2010/12/21
*
* \author
* James Ye (reference piris driver written by Evan Huang)
*
*******************************************************************************
*/

/* ============================================================================= */
#ifndef _FOCUSMOTOR_LOCAL_H_
#define _FOCUSMOTOR_LOCAL_H_

#define MOTOR_DRIVER_VERSION		"1.0.2.0"
/* ============================================================================= */
#define MOTOR_MAJOR_DEFAULT		182 //241
#define MOTOR_VFS_INTERFACE		"focusmotor"
#define MOTOR_SYSLOG_ID			"[FocusMotor]:"
#define MOTOR_TIMER_NUM			3
#define MOTOR_TIMER_SPEED_NUM		3
#define MOTOR_LOG_DATE_TIME      	"2012/06/14 17:15:00"
/* ============================================================================= */
#if defined (_TI_DM365)
/* DM365 Timer 3 base address, IRQ, Timer interrupt period */
#define MOTOR_TIMER3_BASE		0x01C20800
#define MOTOR_IRQ_TIMER3		IRQ_DM3XX_TINT6
#define MOTOR_OFF_DEFERRED_TIME	5
#elif defined (_MOZART)
/* MOZART Timer base address, IRQ, Timer interrupt period */
#define MOTOR_TIMER_BASE		TMRC_MMR_BASE
#define MOTOR_TIMER_CTRL		(MOTOR_TIMER_BASE + 0x04)
#define MOTOR_TIMER_COUT		(MOTOR_TIMER_BASE + 0x30)
#define MOTOR_TIMER_RELOAD		(MOTOR_TIMER_BASE + 0x34)
#define MOTOR_IRQ_TIMER3		TMRC_TM3_IRQ_NUM
#define MOTOR_TIMER_PERIOD		((APB_CLK)/HZ) // APB_CLK:100000000 HZ:100 Default: period: 10 ms

#define MOTOR_MOZART_WRITE(addr,value)	(*((volatile unsigned long *)(addr)) = value)
#define MOTOR_MOZART_READ(addr)		(*((volatile unsigned long *)(addr)))
#else
#error "!!<< Error Error >>!! Please define _TI_DM365 or _MOZART platform first !!"
#endif 

#if defined (_I2C_MODE)
#define MOTOR_I2C_CLIENT_PCA9536_ADDRESS	0x41
#define MOTOR_I2C_CLIENT_OUTPORT_REG		0x01
#define MOTOR_I2C_CLIENT_CONFIG_REG		0x03
#elif defined (_GPIO_MODE)

#define MOTOR_ENABLE_PIN			73
#define MOTOR_GPIO_PIN_NUM_1			74
#define MOTOR_GPIO_PIN_NUM_2			75
#else
#error "!!<< Error Error >>!! Please define _I2C_MODE or _GPIO_MODE platform first !!"	
#endif

#define MOTOR_BUF_LEN	16

#endif // _FOCUSMOTOR_LOCAL_H_
