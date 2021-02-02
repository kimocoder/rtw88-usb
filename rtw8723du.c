// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#include <linux/module.h>
#include <linux/usb.h>
#include "main.h"
#include "rtw8723du.h"

static const struct usb_device_id rtw_8723du_id_table[] = {
	/*
	 * ULLI :
	 * ID found in rtw8822bu sources
	 */
	{ USB_DEVICE_AND_INTERFACE_INFO(RTW_USB_VENDOR_ID_REALTEK,
					0xD723,
					0xff, 0xff, 0xff),
	  .driver_info = (kernel_ulong_t)&(rtw8723d_hw_spec) }, /* 8723DU 1*1 */
	{ },
};
MODULE_DEVICE_TABLE(usb, rtw_8723du_id_table);

static struct rtw_module_param rtw8723du_mod_params = {
	.disable_idle = true,
	.disable_ps = true,
};

module_param_named(disable_idle, rtw8723du_mod_params.disable_idle, bool, 0444);
module_param_named(disable_ps, rtw8723du_mod_params.disable_ps, bool, 0644);

MODULE_PARM_DESC(disable_idle, "mac80211 power save: (default 1)");
MODULE_PARM_DESC(disable_ps, "mac80211 idle: (default 1)");

static int rtw8723du_probe(struct usb_interface *intf,
			    const struct usb_device_id *id)
{
	return rtw_usb_probe(intf, id, &rtw8723du_mod_params);
}

static struct usb_driver rtw_8723du_driver = {
	.name = "rtw_8723du",
	.id_table = rtw_8723du_id_table,
	.probe = rtw8723du_probe,
	.disconnect = rtw_usb_disconnect,
};
module_usb_driver(rtw_8723du_driver);

MODULE_AUTHOR("Hans Ulli Kroll <linux@ulli-kroll.de>");
MODULE_DESCRIPTION("Realtek 802.11n wireless 8723du driver");
MODULE_LICENSE("Dual BSD/GPL");
