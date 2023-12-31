SARADC
================

:link_to_translation:`en:[English]`

Beken chip supports get every adc channel value function for user.


ADC API Status
------------------

+--------------------------------------------+---------+---------+--------+
| API                                        | BK7235A | BK7235B | BK7235 |
+============================================+=========+=========+========+
| :cpp:func:`bk_adc_driver_init`             | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_aquire`                  | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_release`                 | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_driver_deinit`           | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_init`	             | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_deinit`                  | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_start`                   | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_stop`                    | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_read_raw`                | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_read`                    | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_register_isr`	     | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_clk`                 | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_channel`             | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_sample_rate`         | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_filter`              | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_steady_time`         | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_sample_cnt`          | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_enable_saturate`         | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_disable_saturate`        | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_saturate`            | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_get_saturate`            | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_config`              | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_set_mode`                | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+
| :cpp:func:`bk_adc_get_mode`                | Y       | Y       | Y      |
+--------------------------------------------+---------+---------+--------+


ADC Channel Number
------------------------

+----------------+---------+---------+--------+
| Capability     | BK7235A | BK7235B | BK7235 |
+================+=========+=========+========+
| Channel Number | 6       | 6       | 6      |
+----------------+---------+---------+--------+

ADC API Reference
---------------------

.. include:: ../../_build/inc/adc.inc

ADC API Typedefs
---------------------
.. include:: ../../_build/inc/adc_types.inc
.. include:: ../../_build/inc/hal_adc_types.inc


