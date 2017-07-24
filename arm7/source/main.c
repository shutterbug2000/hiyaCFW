/*---------------------------------------------------------------------------------

default ARM7 core

Copyright (C) 2005 - 2010
	Michael Noland (joat)
	Jason Rogers (dovoto)
	Dave Murphy (WinterMute)

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1.	The origin of this software must not be misrepresented; you
	must not claim that you wrote the original software. If you use
	this software in a product, an acknowledgment in the product
	documentation would be appreciated but is not required.

2.	Altered source versions must be plainly marked as such, and
	must not be misrepresented as being the original software.

3.	This notice may not be removed or altered from any source
	distribution.

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "RocketLauncher.h"	// RocketLauncher payload

/*
const unsigned char AES_IV[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, };
const unsigned char AES_MAC[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, };

const unsigned char AES_KEY0_NORMAL[] = { 0x98,0xEE,0x80,0x80,0x00,0x6C,0xB4,0xF6,0x3A,0xC2,0x6E,0x62,0xF9,0xEC,0x34,0xAD, };
const unsigned char AES_KEY0_X[] = { 0x4E,0x69,0x6E,0x74,0x65,0x6E,0x64,0x6F,0x20,0x44,0x53,0x00,0x01,0x23,0x21,0x00, };
const unsigned char AES_KEY0_Y[] = { 0xEC,0x07,0x00,0x00,0x34,0xE2,0x94,0x7C,0xC3,0x0E,0x81,0x7C,0xEC,0x07,0x00,0x00, };

const unsigned char AES_KEY1_NORMAL[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, };
const unsigned char AES_KEY1_X[] = { 0x4A,0x00,0x00,0x4E,0x4E,0x00,0x00,0x4A,0x73,0x7A,0x2C,0xC0,0x22,0x21,0x09,0x05, };
const unsigned char AES_KEY1_Y[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, };

const unsigned char AES_KEY2_NORMAL[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, };
const unsigned char AES_KEY2_X[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, };
const unsigned char AES_KEY2_Y[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, };

const unsigned char AES_KEY3_NORMAL[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, };
const unsigned char AES_KEY3_X[] = { 0x22,0x21,0x09,0x05,0x24,0x48,0xE7,0x21,0x1C,0x51,0x7B,0xEE,0x01,0x31,0x20,0x08, };
const unsigned char AES_KEY3_Y[] = { 0x76,0xDC,0xB9,0x0A,0xD3,0xC4,0x4D,0xBD,0x1D,0xDD,0x2D,0x20,0x00,0x00,0x00,0x00, };

#define REG_AES_CNT (*((vu32*)0x4004400))
#define REG_AES_BLKCNT (*((vu32*)0x4004404))
#define REG_AES_WRFIFO (*((vu32*)0x4004408))

#define REG_AES_IV 0x4004420
#define REG_AES_MAC 0x4004430
#define AES_KEY_SIZE 0x10

#define REG_AES_KEY0_NORMAL 0x4004440
#define REG_AES_KEY0_X 0x4004450
#define REG_AES_KEY0_Y 0x4004460

#define REG_AES_KEY1_NORMAL 0x4004470
#define REG_AES_KEY1_X 0x4004480
#define REG_AES_KEY1_Y 0x4004490

#define REG_AES_KEY2_NORMAL 0x40044A0
#define REG_AES_KEY2_X 0x40044B0
#define REG_AES_KEY2_Y 0x40044C0

#define REG_AES_KEY3_NORMAL 0x40044D0
#define REG_AES_KEY3_X 0x40044E0
#define REG_AES_KEY3_Y 0x40044F0

#define REG_NDMA_00 (*((vu32*)0x4004100))
#define REG_NDMA_01 (*((vu32*)0x4004104))
#define REG_NDMA_02 (*((vu32*)0x4004108))
#define REG_NDMA_03 (*((vu32*)0x400410C))
#define REG_NDMA_04 (*((vu32*)0x4004110))
#define REG_NDMA_05 (*((vu32*)0x4004114))
#define REG_NDMA_06 (*((vu32*)0x4004118))
#define REG_NDMA_07 (*((vu32*)0x400411C))
#define REG_NDMA_08 (*((vu32*)0x4004120))
#define REG_NDMA_09 (*((vu32*)0x4004124))
#define REG_NDMA_11 (*((vu32*)0x4004128))
#define REG_NDMA_12 (*((vu32*)0x400412C))
#define REG_NDMA_13 (*((vu32*)0x4004130))
#define REG_NDMA_14 (*((vu32*)0x4004134))
#define REG_NDMA_15 (*((vu32*)0x4004138))
#define REG_NDMA_16 (*((vu32*)0x400413C))
#define REG_NDMA_17 (*((vu32*)0x4004140))
#define REG_NDMA_18 (*((vu32*)0x4004144))
#define REG_NDMA_19 (*((vu32*)0x4004148))
#define REG_NDMA_20 (*((vu32*)0x400414C))
#define REG_NDMA_21 (*((vu32*)0x4004150))
#define REG_NDMA_22 (*((vu32*)0x4004154))
#define REG_NDMA_23 (*((vu32*)0x4004158))
#define REG_NDMA_24 (*((vu32*)0x400415C))
#define REG_NDMA_25 (*((vu32*)0x4004160))
#define REG_NDMA_26 (*((vu32*)0x4004164))
#define REG_NDMA_27 (*((vu32*)0x4004168))
#define REG_NDMA_28 (*((vu32*)0x400416C))
#define REG_NDMA_29 (*((vu32*)0x4004170))


void AES_INIT() {

	// REG_AES_CNT = 0x80000000;
	
	memcpy((u32*)REG_AES_IV, (u32*)AES_IV, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_MAC, (u32*)AES_MAC, AES_KEY_SIZE);

	memcpy((u32*)REG_AES_KEY0_X, (u32*)AES_KEY0_X, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_KEY0_Y, (u32*)AES_KEY0_Y, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_KEY0_NORMAL, (u32*)AES_KEY0_NORMAL, AES_KEY_SIZE);

	memcpy((u32*)REG_AES_KEY1_X, (u32*)AES_KEY1_X, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_KEY1_Y, (u32*)AES_KEY1_Y, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_KEY1_NORMAL, (u32*)AES_KEY1_NORMAL, AES_KEY_SIZE);

	memcpy((u32*)REG_AES_KEY2_X, (u32*)AES_KEY2_X, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_KEY2_Y, (u32*)AES_KEY2_Y, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_KEY2_NORMAL, (u32*)AES_KEY2_NORMAL, AES_KEY_SIZE);

	memcpy((u32*)REG_AES_KEY3_X, (u32*)AES_KEY3_X, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_KEY3_Y, (u32*)AES_KEY3_Y, AES_KEY_SIZE);
	memcpy((u32*)REG_AES_KEY3_NORMAL, (u32*)AES_KEY3_NORMAL, AES_KEY_SIZE);
	
	REG_AES_CNT = 0x01000000;
	REG_AES_BLKCNT = 0x0000000;
	// REG_AES_WRFIFO = 0x0000000;
}

void initNDMA7() {

	REG_NDMA_00 = 0x00000000;
	REG_NDMA_01 = 0x00000000;
	REG_NDMA_02 = 0x00000000;
	REG_NDMA_03 = 0x00000000;
	REG_NDMA_04 = 0x00000000;
	REG_NDMA_05 = 0x00000000;
	REG_NDMA_06 = 0x00000000;
	REG_NDMA_07 = 0x00000000;
	REG_NDMA_08 = 0x00000000;
	REG_NDMA_09 = 0x00000000;
	REG_NDMA_11 = 0x00000000;
	REG_NDMA_12 = 0x00000000;
	REG_NDMA_13 = 0x00000000;
	REG_NDMA_14 = 0x00000000;
	REG_NDMA_15 = 0x00000000;
	REG_NDMA_16 = 0x00000000;
	REG_NDMA_17 = 0x00000000;
	REG_NDMA_18 = 0x00000000;
	REG_NDMA_19 = 0x00000000;
	REG_NDMA_20 = 0x00000000;
	REG_NDMA_21 = 0x00000000;
	REG_NDMA_22 = 0x00000000;
	REG_NDMA_23 = 0x00000000;
	REG_NDMA_24 = 0x00000000;
	REG_NDMA_25 = 0x00000000;
	REG_NDMA_26 = 0x00000000;
	REG_NDMA_27 = 0x00000000;
	REG_NDMA_28 = 0x00000000;
	REG_NDMA_29 = 0x00000000;
 
}
*/

unsigned int * SCFG_EXT=(unsigned int*)0x4004008;

void VcountHandler() { inputGetAndSend(); }

//---------------------------------------------------------------------------------
void RocketLauncher() {
//---------------------------------------------------------------------------------
	memcpy((u32*)0x02800000,payload_RocketLauncher,payload_RocketLauncher_len);
	i2cWriteRegister(0x4A, 0x70, 0x01);		// Bootflag = Warmboot/SkipHealthSafety
	i2cWriteRegister(0x4A, 0x11, 0x01);		// Reboot to RocketLauncher
}

int main(void) {

	irqInit();
	
	readUserSettings();

	initClockIRQ();

	fifoInit();

	SetYtrigger(80);

	installSystemFIFO();
	
	irqSet(IRQ_VCOUNT, VcountHandler);

	irqEnable( IRQ_VBLANK | IRQ_VCOUNT | IRQ_NETWORK );

	fifoSendValue32(FIFO_USER_01, *SCFG_EXT);
	fifoSendValue32(FIFO_USER_02, 1);

	// Reset AES keys to what bootloader expects
	// AES_INIT();
	// initNDMA7();

	while (1) {
		if(fifoCheckValue32(FIFO_USER_03)) {
			i2cWriteRegister(0x4A, 0x70, 0x00);	// Bootflag = Softboot
		} else {
			i2cWriteRegister(0x4A, 0x70, 0x01);	// Bootflag = Warmboot/SkipHealthSafety
		}

		if(fifoCheckValue32(FIFO_USER_08)) {
			RocketLauncher();
		}
		swiWaitForVBlank();
	}
}

