.. zephyr:code-sample:: lis2dw12_wakeup
   :name: LIS2DW12_WakeUp

   Detect LIS2DW12 sensor wake-up event

Overview
********

A simple sample that show how to configure LIS2DW12 sensor to
detect a wakeup event and catch a trigger. See `AN5038_url`_ paragraph 5.4
for more info.


Building and Running
********************

This application has been tested on nucleo_h503rb board with a x_nucleo_iks01a3
shield.

.. zephyr-app-commands::
   :zephyr-app: lis2dw12_wakeup
   :host-os: unix
   :board: nucleo_h503rb
   :goals: build flash
   :compact:

To build for another board, change "qemu_x86" above to that board's name.

Sample Output
=============

.. code-block:: console

    wake-up detected

Exit QEMU by pressing :kbd:`CTRL+A` :kbd:`x`.

.. _AN5038_url:
    https://www.st.com/resource/en/application_note/an5038-lis2dw12-alwayson-3axis-accelerometer-stmicroelectronics.pdf

