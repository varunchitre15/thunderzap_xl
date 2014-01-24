/*
 * Copyright © 2014, Varun Chitre "varun.chitre15" <varun.chitre15@gmail.com>
 *
 * Kernel header for pm8921-charger Control driver
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
 
#ifndef _LINUX_PM8921_CHG_CTRL_H
#define _LINUX_PM8921_CHG_CTRL_H

extern int mswitch;
extern int usb_curr_val, ac_curr_val;
extern int reg_curr;

#define SUPPLY_TYPE_USB 1
#define SUPPLY_TYPE_AC 2

#endif