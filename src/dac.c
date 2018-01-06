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

#include "dac.h"
#include "tasks.h"
#include "dev/twi.h"

// DAC structure with settings
struct dac_t *dac = NULL;

void DAC_init(void)
{
    // create DAC structure
    dac = (struct dac_t*)malloc(sizeof(struct dac_t));

    // zero-fill
    memset(dac, 0, sizeof(struct dac_t));

    // power-up mode
    PORTB |= _BV(4);

    // default values
    dac->ak4490.acks = 1;
    dac->ak4490.dif = 3; // 24-bit I2S compatible
    dac->ak4490.rstn = 1; // normal Operation

    // default attenuation
    dac->ak4490.latt = 0xff;
    dac->ak4490.ratt = 0xff;

    // de-emphasis response - initial value is "01" (OFF)
    dac->ak4490.dem = 1;

    // sampling speed control - hex speed mode 768kHz ("101")
    //dac->ak4490.dfs0 = 1;
    //dac->ak4490.dfs1 = 0;
    //dac->ak4490.dfs2 = 1;
    // sampling speed control - normal speed mode 30kHz - 54kHz ("000")
    dac->ak4490.dfs0 = 0;
    dac->ak4490.dfs1 = 0;
    dac->ak4490.dfs2 = 0;

    // update device
    dac->mustUpdateDevice = TRUE;

    // listen to input
    Button01_join(DAC_onFilterChange);

    // create private tasks
    Tasks_create(100, TASK_REPEAT, DAC_updateDevice, NULL);
}

void DAC_updateDevice(void)
{
    if(dac->mustUpdateDevice) {
        // TWI status
        uint8_t result = 0;

        if((result = TWI_start(AK4490_ADDR))) {
            TWI_transmit(0);

            // transfer whole structure
            for(int8_t i = 0; i < sizeof(struct ak4490_t); i++)
                TWI_transmit(*((uint8_t*)&dac->ak4490 + i));

            TWI_stop();
        }

        // led indicator
        if(result)
            PORTD |= _BV(2);

        // no need to update anymore
        dac->mustUpdateDevice = FALSE;
    }
}

void DAC_onFilterChange(enum Buttonstate_t state)
{
    uint8_t filter = dac->ak4490.sd << 1 | dac->ak4490.slow;
    if(++filter > 3)
        filter = 0;

    dac->ak4490.sd = (filter & 0x02) == 0x02;
    dac->ak4490.slow = (filter & 0x01) == 0x01;

    // update device
    dac->mustUpdateDevice = TRUE;
}
