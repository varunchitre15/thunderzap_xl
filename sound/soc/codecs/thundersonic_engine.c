/*
 * Copyright © 2014, Varun Chitre "varun.chitre15" <varun.chitre15@gmail.com>
 *
 * Sound control engine for WCD9304
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

#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <linux/mfd/wcd9xxx/wcd9304_registers.h>

#define ENGINE_VERSION  1
#define ENGINE_VERSION_SUB 5

#define REG_HSGAIN_DEF 18
#define REG_HSGAIN_BOOSTED 0

extern struct snd_soc_codec *tz_codec_pointer;

unsigned int sitar_read(struct snd_soc_codec *codec, unsigned int reg);
int sitar_write(struct snd_soc_codec *codec, unsigned int reg, unsigned int value);
static int is_boosted = 0;

static ssize_t speaker_boost_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        return sprintf(buf, "Current boost level: %u\nMin:0 Max:8", sitar_read(tz_codec_pointer, SITAR_A_CDC_RX1_VOL_CTL_B2_CTL));

}

static ssize_t speaker_boost_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	unsigned int val;
	sscanf(buf, "%u", &val);
	if (val>8)
	{
	pr_info("[thundersonic-engine] Too much gain value can damage your speakers: Reverting to safer value 8\n");
	val=8;
	}
    sitar_write(tz_codec_pointer, SITAR_A_CDC_RX1_VOL_CTL_B2_CTL, val);
	return count;
}

static ssize_t headphone_boost_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	int status;
	sscanf(buf, "%u", &status);
	if(status==1)
	{
	sitar_write(tz_codec_pointer, SITAR_A_RX_HPH_L_GAIN, REG_HSGAIN_BOOSTED);
	sitar_write(tz_codec_pointer, SITAR_A_RX_HPH_R_GAIN, REG_HSGAIN_BOOSTED);
	pr_info("[thundersonic-engine] Headphone boost enabled\n");
	is_boosted=1;
	}
	else if(status==0)
	{
	sitar_write(tz_codec_pointer, SITAR_A_RX_HPH_L_GAIN, REG_HSGAIN_DEF);
	sitar_write(tz_codec_pointer, SITAR_A_RX_HPH_R_GAIN, REG_HSGAIN_DEF);
	pr_info("[thundersonic-engine] Headphone boost disabled\n");
	is_boosted=0;
	}
	else
	{
	pr_info("Invalid choice: 1 for boost, 0 for unboost");
	}
	return count;
}

static ssize_t headphone_boost_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	if(is_boosted==1)
	return sprintf(buf, "Current status:boosted");
	else
	return sprintf(buf, "Current status:unboosted");
}

static ssize_t thundersonic_version_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "version: %u.%u\n", ENGINE_VERSION, ENGINE_VERSION_SUB);
}


static struct kobj_attribute speaker_boost_attribute =
	__ATTR(speaker_boost,
		0666,
		speaker_boost_show,
		speaker_boost_store);

static struct kobj_attribute headphone_boost_attribute =
	__ATTR(headphone_boost,
		0666,
		headphone_boost_show,
		headphone_boost_store);

static struct kobj_attribute thundersonic_version_attribute =
	__ATTR(engine_version,
		0444,
		thundersonic_version_show, NULL);

static struct attribute *thundersonic_engine_attrs[] =
	{
		&speaker_boost_attribute.attr,
		&headphone_boost_attribute.attr,
		&thundersonic_version_attribute.attr,
		NULL,
	};

static struct attribute_group sound_control_attr_group =
	{
		.attrs = thundersonic_engine_attrs,
	};

static struct kobject *sound_control_kobj;

static int sound_control_init(void)
{
	int sysfs_result;
	printk(KERN_DEBUG "[%s]\n",__func__);

	sound_control_kobj =
		kobject_create_and_add("thundersonic_engine", kernel_kobj);

	if (!sound_control_kobj) {
		pr_err("%s Interface create failed!\n",
			__FUNCTION__);
		return -ENOMEM;
        }

	sysfs_result = sysfs_create_group(sound_control_kobj,
			&sound_control_attr_group);

	if (sysfs_result) {
		pr_info("%s sysfs create failed!\n", __FUNCTION__);
		kobject_put(sound_control_kobj);
	}
	return sysfs_result;
}

static void sound_control_exit(void)
{
	if (sound_control_kobj != NULL)
		kobject_put(sound_control_kobj);
}

module_init(sound_control_init);
module_exit(sound_control_exit);
MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Varun Chitre <varun.chitre15@gmail.com>");
MODULE_DESCRIPTION("ThunderSonic Sound Engine - A control driver for WCD9304 sound card");
