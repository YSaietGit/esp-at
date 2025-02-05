下载指导
==========

{IDF_TARGET_MODULE_NAME: default="undefined", esp32="ESP32-WROOM-32", esp32c2="ESP8684-MINI-1", esp32c3="ESP32-C3-MINI-1"}
{IDF_TARGET_FACTORY_BIN: default="undefined", esp32="ESP32-WROOM-32_AT_Bin_V2.2.0.0", esp32c2="ESP32C2-4MB_AT_Bin_V2.5.0.0", esp32c3="ESP32-C3-MINI-1_AT_Bin_V2.3.0.0"}

:link_to_translation:`en:[English]`

本文档以 {IDF_TARGET_MODULE_NAME} 模组为例，介绍如何下载 {IDF_TARGET_MODULE_NAME} 模组对应的 AT 固件，以及如何将固件烧录到模组上，其它 {IDF_TARGET_NAME} 系列模组也可参考本文档。

下载和烧录 AT 固件之前，请确保您已正确连接所需硬件，具体可参考 :doc:`Hardware_connection`。

对于不同系列的模组，AT 默认固件所支持的命令会有所差异。具体可参考 :doc:`/Compile_and_Develop/esp-at_firmware_differences`。

.. _download-at-firmware:

下载 AT 固件
-------------

请按照以下步骤将 AT 固件下载至 PC：

- 前往 :doc:`../AT_Binary_Lists/index`
- 找到您的模组所对应的 AT 固件
- 点击相应链接进行下载

此处，我们下载了 {IDF_TARGET_MODULE_NAME} 对应的 ``{IDF_TARGET_FACTORY_BIN}`` 固件，该固件的目录结构及其中各个 bin 文件介绍如下，其它 {IDF_TARGET_NAME} 系列模组固件的目录结构及 bin 文件也可参考如下介绍：

.. only:: esp32

   .. code-block:: none

      .
      ├── at_customize.bin                 // 二级分区表
      ├── bootloader                       // bootloader
      │   └── bootloader.bin
      ├── customized_partitions            // AT 自定义 bin 文件
      │   └── mfg_nvs.bin                  // 量产 NVS 分区
      ├── download.config                  // 烧录固件的参数
      ├── esp-at.bin                       // AT 应用固件
      ├── esp-at.elf
      ├── esp-at.map
      ├── factory                          // 量产所需打包好的 bin 文件
      │   ├── factory_WROOM-32.bin
      │   └── factory_parameter.log
      ├── flasher_args.json                // 下载参数信息新的格式
      ├── ota_data_initial.bin             // ota data 区初始值
      ├── partition_table                  // 一级分区列表
      │   └── partition-table.bin
      ├── phy_init_data.bin                // phy 初始值信息
      └── sdkconfig                        // AT 固件对应的编译配置

.. only:: esp32c3 or esp32c2

   .. code-block:: none

      .
      ├── at_customize.bin                 // 二级分区表
      ├── bootloader                       // bootloader
      │   └── bootloader.bin
      ├── customized_partitions            // AT 自定义 bin 文件
      │   └── mfg_nvs.bin                  // 量产 NVS 分区
      ├── download.config                  // 烧录固件的参数
      ├── esp-at.bin                       // AT 应用固件
      ├── esp-at.elf
      ├── esp-at.map
      ├── factory                          // 量产所需打包好的 bin 文件
      │   ├── factory_MINI-1.bin
      │   └── factory_parameter.log
      ├── flasher_args.json                // 下载参数信息新的格式
      ├── ota_data_initial.bin             // ota data 区初始值
      ├── partition_table                  // 一级分区列表
      │   └── partition-table.bin
      ├── phy_init_data.bin                // phy 初始值信息
      └── sdkconfig                        // AT 固件对应的编译配置

其中，``download.config`` 文件包含烧录固件的参数：

.. only:: esp32

   .. code-block:: none

      --flash_mode dio --flash_freq 40m --flash_size 4MB
      0x8000 partition_table/partition-table.bin
      0x10000 ota_data_initial.bin
      0xf000 phy_init_data.bin
      0x1000 bootloader/bootloader.bin
      0x100000 esp-at.bin
      0x20000 at_customize.bin
      0x21000 customized_partitions/mfg_nvs.bin

.. only:: esp32c2

   .. code-block:: none

      --flash_mode dio --flash_freq 60m --flash_size 4MB
      0x0 bootloader/bootloader.bin
      0x60000 esp-at.bin
      0x8000 partition_table/partition-table.bin
      0xd000 ota_data_initial.bin
      0xf000 phy_init_data.bin
      0x1e000 at_customize.bin
      0x1F000 customized_partitions/mfg_nvs.bin

.. only:: esp32c3

   .. code-block:: none

      --flash_mode dio --flash_freq 40m --flash_size 4MB
      0x8000 partition_table/partition-table.bin
      0xd000 ota_data_initial.bin
      0xf000 phy_init_data.bin
      0x0 bootloader/bootloader.bin
      0x60000 esp-at.bin
      0x1e000 at_customize.bin
      0x1F000 customized_partitions/mfg_nvs.bin

.. list::

   - ``--flash_mode dio`` 代表此固件采用的 flash dio 模式进行编译；
   :esp32 or esp32c3: - ``--flash_freq 40m`` 代表此固件采用的 flash 通讯频率为 40 MHz；
   :esp32c2: - ``--flash_freq 60m`` 代表此固件采用的 flash 通讯频率为 60 MHz；
   - ``--flash_size 4MB`` 代表此固件适用的 flash 最小为 4 MB；
   :esp32: - ``0x10000 ota_data_initial.bin`` 代表在 ``0x10000`` 地址烧录 ``ota_data_initial.bin`` 文件。
   :esp32c2 or esp32c3: - ``0xd000 ota_data_initial.bin`` 代表在 ``0xd000`` 地址烧录 ``ota_data_initial.bin`` 文件。

.. _flash-at-firmware-into-your-device:

烧录 AT 固件至设备
-------------------

请根据您的操作系统选择对应的烧录方法。

Windows 
^^^^^^^^

开始烧录之前，请下载 `Flash 下载工具 <https://www.espressif.com/zh-hans/support/download/other-tools>`_。更多有关 Flash 下载工具的介绍，请参考压缩包中 ``doc`` 文件夹。

- 打开 Flash 下载工具；
- 选择芯片类型；（此处，我们选择 ``{IDF_TARGET_CFG_PREFIX}``。）
- 根据您的需求选择一种工作模式；（此处，我们选择 ``develop``。)
- 根据您的需求选择一种下载接口；（此处，我们选择 ``uart``。)

.. figure:: ../../_static/download_tool_{IDF_TARGET_PATH_NAME}.png
   :align: center
   :alt: 固件下载配置选择
   :figclass: align-center

   固件下载配置选择

- 将 AT 固件烧录至设备，以下两种方式任选其一：

   - 直接下载打包好的量产固件至 ``0x0`` 地址：勾选 "DoNotChgBin"，使用量产固件的默认配置；

     .. figure:: ../../_static/download_one_bin_{IDF_TARGET_PATH_NAME}.png
        :align: center
        :scale: 70%
        :alt: 下载至单个地址界面图

        下载至单个地址界面图（点击放大）

   - 分开下载多个 bin 文件至不同的地址：根据 ``download.config`` 文件进行配置，请勿勾选 "DoNotChgBin"；

     .. figure:: ../../_static/download_multi_bin_{IDF_TARGET_PATH_NAME}.png
        :align: center
        :scale: 60%
        :alt: 下载至多个地址界面图

        下载至多个地址界面图（点击放大）

为了避免烧录出现问题，请查看开发板的下载接口的 COM 端口号，并从 "COM:" 下拉列表中选择该端口号。有关如何查看端口号的详细介绍请参考 `在 Windows 上查看端口 <https://docs.espressif.com/projects/esp-idf/zh_CN/latest/{IDF_TARGET_PATH_NAME}/get-started/establish-serial-connection.html#windows>`_。 

烧录完成后, 请 `检查 AT 固件是否烧录成功`_。

Linux 或 macOS
^^^^^^^^^^^^^^^

开始烧录之前，请安装 `esptool.py <https://github.com/espressif/esptool>`_。

以下两种方式任选其一，将 AT 固件烧录至设备：

- 分开下载多个 bin 文件至不同的地址：输入以下命令，替换 ``PORTNAME`` 和 ``download.config`` 参数；

  .. code-block:: none

      esptool.py --chip auto --port PORTNAME --baud 115200 --before default_reset --after hard_reset write_flash -z download.config

  将 ``PORTNAME`` 替换成开发板的下载接口名称，若您无法确定该接口名称，请参考 `在 Linux 和 macOS 上查看端口 <https://docs.espressif.com/projects/esp-idf/zh_CN/latest/{IDF_TARGET_PATH_NAME}/get-started/establish-serial-connection.html#linux-macos>`_。

  将 ``download.config`` 替换成该文件里的参数列表。

  以下是将固件烧录至 {IDF_TARGET_MODULE_NAME} 模组输入的命令：

   .. only:: esp32

      .. code-block:: none

         esptool.py --chip auto --port /dev/tty.usbserial-0001 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 4MB 0x8000 partition_table/partition-table.bin 0x10000 ota_data_initial.bin 0xf000 phy_init_data.bin 0x1000 bootloader/bootloader.bin 0x100000 esp-at.bin 0x20000 at_customize.bin 0x21000 customized_partitions/mfg_nvs.bin

   .. only:: esp32c2

      .. code-block:: none

         esptool.py --chip auto --port /dev/tty.usbserial-0001 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 60m --flash_size 4MB 0x0 bootloader/bootloader.bin 0x60000 esp-at.bin 0x8000 partition_table/partition-table.bin 0xd000 ota_data_initial.bin 0xf000 phy_init_data.bin 0x1e000 at_customize.bin 0x1F000 customized_partitions/mfg_nvs.bin

   .. only:: esp32c3

      .. code-block:: none

         esptool.py --chip auto --port /dev/tty.usbserial-0001 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 4MB 0x8000 partition_table/partition-table.bin 0xd000 ota_data_initial.bin 0xf000 phy_init_data.bin 0x0 bootloader/bootloader.bin 0x60000 esp-at.bin 0x1e000 at_customize.bin 0x1F000 customized_partitions/mfg_nvs.bin

- 直接下载打包好的量产固件至 ``0x0`` 地址：输入以下命令，替换 ``PORTNAME`` 和 ``FILEDIRECTORY`` 参数；

  .. code-block:: none

      esptool.py --chip auto --port PORTNAME --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 4MB 0x0 FILEDIRECTORY

  将 ``PORTNAME`` 替换成开发板的下载接口名称，若您无法确定该接口名称，请参考 `在 Linux 和 macOS 上查看端口 <https://docs.espressif.com/projects/esp-idf/zh_CN/latest/{IDF_TARGET_PATH_NAME}/get-started/establish-serial-connection.html#linux-macos>`_。

  将 ``FILEDIRECTORY`` 替换成打包好的量产固件的文件路径，通常情况下，文件路径是 ``factory/XXX.bin``。

  以下是将固件烧录至 {IDF_TARGET_MODULE_NAME} 模组输入的命令：

   .. only:: esp32

      .. code-block:: none

         esptool.py --chip auto --port /dev/tty.usbserial-0001 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 4MB 0x0 factory/factory_WROOM-32.bin

   .. only:: esp32c2

      .. code-block:: none

         esptool.py --chip auto --port /dev/tty.usbserial-0001 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 60m --flash_size 4MB 0x0 factory/factory_MINI-1.bin

   .. only:: esp32c3

      .. code-block:: none

         esptool.py --chip auto --port /dev/tty.usbserial-0001 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 4MB 0x0 factory/factory_MINI-1.bin

烧录完成后，请 `检查 AT 固件是否烧录成功`_。

.. _check-whether-at-works:

检查 AT 固件是否烧录成功
-------------------------

请按照以下步骤检查 AT 固件是否烧录成功：

- 打开串口工具，如 SecureCRT；
- 串口：选择用于发送或接收“AT 命令/响应”的串口（详情请见 :doc:`Hardware_connection`）；
- 波特率：115200；
- 数据位：8；
- 检验位：None；
- 停止位：1；
- 流控：None；
- 输入 "AT+GMR" 命令，并且换行 (CR LF)；

若如下图所示，响应是 ``OK``, 则表示 AT 固件烧录成功。

.. figure:: ../../_static/at_version_{IDF_TARGET_PATH_NAME}.png
   :align: center
   :alt: AT 响应
   :figclass: align-center

   AT 响应

否则，您需要通过以下方式之一检查 {IDF_TARGET_NAME} 设备开机日志：
  
**方法 1：**

- 打开串口工具，如 SecureCRT；
- 串口：选择用于“下载固件/输出日志”的串口，串口详情请参阅 :doc:`Hardware_connection`。
- 波特率：115200；
- 数据位：8；
- 检验位：None；
- 停止位：1；
- 流控：None；
- 直接按开发板的 RST 键，若日志和下面的日志相似，则说明 ESP-AT 固件已经正确初始化了。

**方法 2：**

- 打开两个串口工具，如 SecureCRT；
- 串口：分别选择用于发送或接收“AT 命令/响应”的串口以及用于“下载固件/输出日志”的串口，串口详情请参阅 :doc:`Hardware_connection`。
- 波特率：115200；
- 数据位：8；
- 检验位：None；
- 停止位：1；
- 流控：None；
- 在发送或接收“AT 命令/响应”的串口输入 :ref:`AT+RST <cmd-RST>` 命令，并且换行 (CR LF)，若“下载固件/输出日志”的串口日志和下面的日志相似，则说明 ESP-AT 固件已经正确初始化了。

.. only:: esp32

   {IDF_TARGET_NAME} 开机日志：

   .. code-block:: none

      rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
      configsip: 0, SPIWP:0xee
      clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
      mode:DIO, clock div:2
      load:0x3fff0030,len:5884
      ho 0 tail 12 room 4
      load:0x40078000,len:15844
      load:0x40080400,len:3560
      entry 0x40080604
      I (29) boot: ESP-IDF v5.0-541-g885e501d99-dirty 2nd stage bootloader
      I (29) boot: compile time 08:40:13
      I (29) boot: chip revision: v1.0
      I (34) boot.esp32: SPI Speed      : 40MHz
      I (38) boot.esp32: SPI Mode       : DIO
      I (43) boot.esp32: SPI Flash Size : 4MB
      I (47) boot: Enabling RNG early entropy source...
      I (53) boot: Partition Table:
      I (56) boot: ## Label            Usage          Type ST Offset   Length
      I (64) boot:  0 phy_init         RF data          01 01 0000f000 00001000
      I (71) boot:  1 otadata          OTA data         01 00 00010000 00002000
      I (78) boot:  2 nvs              WiFi data        01 02 00012000 0000e000
      I (86) boot:  3 at_customize     unknown          40 00 00020000 000e0000
      I (93) boot:  4 ota_0            OTA app          00 10 00100000 00180000
      I (101) boot:  5 ota_1            OTA app          00 11 00280000 00180000
      I (108) boot: End of partition table
      I (113) esp_image: segment 0: paddr=00100020 vaddr=3f400020 size=1a854h (108628) map
      I (161) esp_image: segment 1: paddr=0011a87c vaddr=3ff80063 size=00008h (     8) load
      I (161) esp_image: segment 2: paddr=0011a88c vaddr=3ffbdb60 size=04d5ch ( 19804) load
      I (174) esp_image: segment 3: paddr=0011f5f0 vaddr=40080000 size=00a28h (  2600) load
      I (176) esp_image: segment 4: paddr=00120020 vaddr=400d0020 size=11f5c0h (1177024) map
      I (609) esp_image: segment 5: paddr=0023f5e8 vaddr=40080a28 size=1e948h (125256) load
      I (660) esp_image: segment 6: paddr=0025df38 vaddr=400c0000 size=00064h (   100) load
      I (676) boot: Loaded app from partition at offset 0x100000
      I (676) boot: Disabling RNG early entropy source...
      no external 32k oscillator, disable it now.
      at param mode: 1
      AT cmd port:uart1 tx:17 rx:16 cts:15 rts:14 baudrate:115200
      module_name: WROOM-32
      max tx power=78, ret=0
      2.5.0

.. only:: esp32c2

   {IDF_TARGET_NAME} 开机日志:

   .. code-block:: none

      ESP-ROM:esp8684-api2-20220127
      Build:Jan 27 2022
      rst:0x1 (POWERON),boot:0xc (SPI_FAST_FLASH_BOOT)
      SPIWP:0xee
      mode:DIO, clock div:1
      load:0x3fcd6108,len:0x18b0
      load:0x403ae000,len:0x854
      load:0x403b0000,len:0x2724
      entry 0x403ae000
      I (32) boot: ESP-IDF v5.0-dev-5949-g885e501d99-dirty 2nd stage bootloader
      I (32) boot: compile time 11:05:11
      I (32) boot: chip revision: v1.0
      I (36) boot.esp32c2: MMU Page Size  : 64K
      I (41) boot.esp32c2: SPI Speed      : 60MHz
      I (46) boot.esp32c2: SPI Mode       : DIO
      I (50) boot.esp32c2: SPI Flash Size : 4MB
      I (55) boot: Enabling RNG early entropy source...
      I (61) boot: Partition Table:
      I (64) boot: ## Label            Usage          Type ST Offset   Length
      I (71) boot:  0 otadata          OTA data         01 00 0000d000 00002000
      I (79) boot:  1 phy_init         RF data          01 01 0000f000 00001000
      I (86) boot:  2 nvs              WiFi data        01 02 00010000 0000e000
      I (94) boot:  3 at_customize     unknown          40 00 0001e000 00042000
      I (101) boot:  4 ota_0            OTA app          00 10 00060000 001d0000
      I (109) boot:  5 ota_1            OTA app          00 11 00230000 001d0000
      I (116) boot: End of partition table
      I (121) esp_image: segment 0: paddr=00060020 vaddr=3c0e0020 size=288c8h (166088) map
      I (167) esp_image: segment 1: paddr=000888f0 vaddr=3fca6010 size=02c18h ( 11288) load
      I (170) esp_image: segment 2: paddr=0008b510 vaddr=40380000 size=04b08h ( 19208) load
      I (178) esp_image: segment 3: paddr=00090020 vaddr=42000020 size=d444ch (869452) map
      I (378) esp_image: segment 4: paddr=00164474 vaddr=40384b08 size=01508h (  5384) load
      I (382) boot: Loaded app from partition at offset 0x60000
      I (383) boot: Disabling RNG early entropy source...
      at param mode: 1
      AT cmd port:uart1 tx:7 rx:6 cts:5 rts:4 baudrate:115200
      module_name: ESP32C2-4MB
      max tx power=78, ret=0
      3.0.0

.. only:: esp32c3

   {IDF_TARGET_NAME} 开机日志:

   .. code-block:: none

      ESP-ROM:esp32c3-api1-20210207
      Build:Feb  7 2021
      rst:0x1 (POWERON),boot:0xc (SPI_FAST_FLASH_BOOT)
      SPIWP:0xee
      mode:DIO, clock div:2
      load:0x3fcd5820,len:0x16b4
      load:0x403cc710,len:0x970
      load:0x403ce710,len:0x2e90
      entry 0x403cc710
      I (31) boot: ESP-IDF v5.0-541-g885e501d99-dirty 2nd stage bootloader
      I (31) boot: compile time 14:34:08
      I (32) boot: chip revision: v0.3
      I (35) boot.esp32c3: SPI Speed      : 40MHz
      I (40) boot.esp32c3: SPI Mode       : DIO
      I (45) boot.esp32c3: SPI Flash Size : 4MB
      I (49) boot: Enabling RNG early entropy source...
      I (55) boot: Partition Table:
      I (58) boot: ## Label            Usage          Type ST Offset   Length
      I (66) boot:  0 otadata          OTA data         01 00 0000d000 00002000
      I (73) boot:  1 phy_init         RF data          01 01 0000f000 00001000
      I (81) boot:  2 nvs              WiFi data        01 02 00010000 0000e000
      I (88) boot:  3 at_customize     unknown          40 00 0001e000 00042000
      I (95) boot:  4 ota_0            OTA app          00 10 00060000 001d0000
      I (103) boot:  5 ota_1            OTA app          00 11 00230000 001d0000
      I (110) boot: End of partition table
      I (115) esp_image: segment 0: paddr=00060020 vaddr=3c170020 size=3bd30h (245040) map
      I (175) esp_image: segment 1: paddr=0009bd58 vaddr=3fc95400 size=03884h ( 14468) load
      I (178) esp_image: segment 2: paddr=0009f5e4 vaddr=40380000 size=00a34h (  2612) load
      I (181) esp_image: segment 3: paddr=000a0020 vaddr=42000020 size=167a10h (1473040) map
      I (497) esp_image: segment 4: paddr=00207a38 vaddr=40380a34 size=1486ch ( 84076) load
      I (518) esp_image: segment 5: paddr=0021c2ac vaddr=50000000 size=00018h (    24) load
      I (525) boot: Loaded app from partition at offset 0x60000
      I (525) boot: Disabling RNG early entropy source...
      no external 32k oscillator, disable it now.
      at param mode: 1
      AT cmd port:uart1 tx:7 rx:6 cts:5 rts:4 baudrate:115200
      module_name: MINI-1
      max tx power=78, ret=0
      2.5.0
