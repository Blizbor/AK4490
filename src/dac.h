/*
 * AK4490 Controller
 * Copyright (c) 2018 Konrad Kusnierz <iryont@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef DAC_H_
#define DAC_H_

#include "pch.h"
#include "const.h"
#include "dev/button.h"

// DAC constant values
#define AK4490_ADDR 32

struct ak4490_t {
    uint8_t rstn : 1;
    uint8_t dif : 3;
    uint8_t _1 : 1;
    uint8_t ecs : 1;
    uint8_t exdf : 1;
    uint8_t acks : 1;
    
    uint8_t smute : 1;
    uint8_t dem : 2;
    uint8_t dfs0 : 1;
    uint8_t dfs1 : 1;
    uint8_t sd : 1;
    uint8_t dzfm : 1;
    uint8_t dzfe : 1;

    uint8_t slow : 1;
    uint8_t sellr : 1;
    uint8_t dzfb : 1;
    uint8_t mono : 1;
    uint8_t dckb : 1;
    uint8_t dcks : 1;
    uint8_t _2 : 1;
    uint8_t dp : 1;

    uint8_t latt;
    uint8_t ratt;

    uint8_t sslow : 1;
    uint8_t dfs2 : 1;
    uint8_t _3 : 1;
    uint8_t _4 : 1;
    uint8_t _5 : 1;
    uint8_t _6 : 1;
    uint8_t invr : 1;
    uint8_t invl : 1;

    uint8_t dsdsel0 : 1;
    uint8_t dsdd : 1;
    uint8_t _7 : 1;
    uint8_t dmre : 1;
    uint8_t dmc : 1;
    uint8_t dmr : 1;
    uint8_t dml : 1;
    uint8_t ddm : 1;

    uint8_t synce : 1;
    uint8_t _8 : 1;
    uint8_t _9 : 1;
    uint8_t _10 : 1;
    uint8_t _11 : 1;
    uint8_t _12 : 1;
    uint8_t _13 : 1;
    uint8_t _14 : 1;

    uint8_t sc : 2;
    uint8_t _15 : 1;
    uint8_t _16 : 1;
    uint8_t _17 : 1;
    uint8_t _18 : 1;
    uint8_t _19 : 1;
    uint8_t _20 : 1;

    uint8_t dsdsel1 : 1;
    uint8_t dsdf : 1;
    uint8_t _21 : 1;
    uint8_t _22 : 1;
    uint8_t _23 : 1;
    uint8_t _24 : 1;
    uint8_t _25 : 1;
    uint8_t _26 : 1;
} __attribute__((packed));

struct dac_t {
	struct ak4490_t ak4490;

	uint8_t mustUpdateDevice;
};

void DAC_init(void);
void DAC_updateDevice(void);
void DAC_onFilterChange(enum Buttonstate_t state);

extern struct dac_t *dac;

#endif
