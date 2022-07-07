# i.MX Yocto BSP 使用笔记

------

主要是手上有这个板子,所以就总是想搞点什么,趁着有空就做个最新的Porting吧.

官方源分层:

- **meta-imx**
    - **meta-bsp** updates for meta-freescale, poky, and metaopenembedded layers
    - **meta-sdk** updates for meta-freescale-distros
    - **meta-ml** Machine learning recipes
    - **meta-v2x** V2X recipes only used for i.MX 8DXL
    - **meta-cockpit** Cockpit recipes for i.MX 8QuadMax
- **meta-browser** Provides several browsers.
- **meta-qt6** Provides Qt 6.
- **meta-timesys** Provides Vigiles tools for monitoring and notification of BSP vulnerabilities (CVEs).
- **meta-freescale** Provides support for the base and for i.MX Arm® reference boards.
- **meta-freescale-3rdparty** Provides support for 3rd party and partner boards.
- **meta-openembedded** Collection of layers for the OE-core universe. See layers.openembedded.org
- **meta-freescale-distro** Additional items to aid in development and exercise board capabilities.
- **fsl-community-bsp-base** Often renamed to base. Provides base configuration for FSL Community BSP.

镜像支持:

| 镜像名 | 描述 | 估计大小 | 
| - | - | - |
| core-image-minimal | 最小可启动镜像. | 30 MByte |
| core-image-base | 仅CLI + 全部系统组件. | 60 MByte |
| core-image-sato | Sato GUI Demo | 166 MByte |
| imx-image-core | Wayland Demo | 146 MByte |
| fsl-image-machine-test | 包含测试工具但是无GUI. | 212 MByte |
| imx-image-multimedia | 有GUI支持但是无任何GUI内容. | 158 MByte |
| imx-image-full | 包含QT6和机器学习相关的内容. | 480 MByte |
| fsl-image-mfgtool-initramfs | 用于烧录量产的镜像,仅可引导无功能. | 16 MByte |

图形层支持:

- **fsl-imx-fb** 纯软件实现,没有GPU选这个.
- **fsl-imx-wayland** Wayland实现.
- **fsl-imx-xwayland** Wayland和X11实现.

烧录对应参考(以我的自定义板子举例):

| UUU | 描述 | 运行环境 | 实际文件 | 
| - | - | - | - |
| _flash_fw.bin | 引导 | 烧录 | u-boot.imx-custom-01 |
| _flash.bin | 引导 | 运行 | u-boot.imx-custom-01 |
| _Image | 内核 | 烧录 + 运行 | zImage |
| _board.dtb | 设备树 | 烧录 + 运行 | imx6ul-14x14-evk-custom-01.dtb |
| _initramfs.cpio.gz.uboot | 烧录用文件系统 | 烧录 | fsl-image-mfgtool-initramfs-imx6ulevk.cpio.gz.u-boot |
| _tee | 安全组件 | 运行 | uTee-6ulevk |
| _rootfs.tar.bz2 | 文件系统 | 运行 | core-image-base-imx6ulevk.tar.bz2 |

启动Log参考:

```txt
[    0.000000] Booting Linux on physical CPU 0x0
[    0.000000] Linux version 5.15.5-lts-next+gda8167fa0cd1 (oe-user@oe-host) (arm-poky-linux-gnueabi-gcc (GCC) 11.2.0, GNU ld (GNU Binutils) 2.37.20210721) #1 SMP PREEMPT Mon Mar 7 20:03:59 UTC 2022
[    0.000000] CPU: ARMv7 Processor [410fc075] revision 5 (ARMv7), cr=10c5387d
[    0.000000] CPU: div instructions available: patching division code
[    0.000000] CPU: PIPT / VIPT nonaliasing data cache, VIPT aliasing instruction cache
[    0.000000] OF: fdt: Machine model: Freescale i.MX6 UltraLite Custom Board #1
[    0.000000] Memory policy: Data cache writealloc
[    0.000000] cma: Reserved 32 MiB at 0x8e000000
[    0.000000] Zone ranges:
[    0.000000]   Normal   [mem 0x0000000080000000-0x000000008fffffff]
[    0.000000]   HighMem  empty
[    0.000000] Movable zone start for each node
[    0.000000] Early memory node ranges
[    0.000000]   node   0: [mem 0x0000000080000000-0x0000000083ffffff]
[    0.000000]   node   0: [mem 0x0000000084000000-0x0000000085ffffff]
[    0.000000]   node   0: [mem 0x0000000086000000-0x000000008fffffff]
[    0.000000] Initmem setup node 0 [mem 0x0000000080000000-0x000000008fffffff]
[    0.000000] psci: probing for conduit method from DT.
[    0.000000] psci: PSCIv1.0 detected in firmware.
[    0.000000] psci: Using standard PSCI v0.2 function IDs
[    0.000000] psci: MIGRATE_INFO_TYPE not supported.
[    0.000000] psci: SMC Calling Convention v1.1
[    0.000000] percpu: Embedded 12 pages/cpu s17036 r8192 d23924 u49152
[    0.000000] pcpu-alloc: s17036 r8192 d23924 u49152 alloc=12*4096
[    0.000000] pcpu-alloc: [0] 0
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 64960
[    0.000000] Kernel command line: console=ttymxc0,115200 ubi.mtd=nandrootfs root=ubi0:nandrootfs rootfstype=ubifs mtdparts=gpmi-nand:64m(nandboot),16m(nandkernel),16m(nanddtb),16m(nandtee),-(nandrootfs)
[    0.000000] Dentry cache hash table entries: 32768 (order: 5, 131072 bytes, linear)
[    0.000000] Inode-cache hash table entries: 16384 (order: 4, 65536 bytes, linear)
[    0.000000] mem auto-init: stack:off, heap alloc:off, heap free:off
[    0.000000] Memory: 173644K/262144K available (12288K kernel code, 1339K rwdata, 4284K rodata, 1024K init, 429K bss, 55732K reserved, 32768K cma-reserved, 0K highmem)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] rcu: Preemptible hierarchical RCU implementation.
[    0.000000] rcu:     RCU event tracing is enabled.
[    0.000000] rcu:     RCU restricting CPUs from NR_CPUS=4 to nr_cpu_ids=1.
[    0.000000]  Trampoline variant of Tasks RCU enabled.
[    0.000000] rcu: RCU calculated value of scheduler-enlistment delay is 10 jiffies.
[    0.000000] rcu: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=1
[    0.000000] NR_IRQS: 16, nr_irqs: 16, preallocated irqs: 16
[    0.000000] random: get_random_bytes called from start_kernel+0x484/0x650 with crng_init=0
[    0.000000] Switching to timer-based delay loop, resolution 41ns
[    0.000003] sched_clock: 32 bits at 24MHz, resolution 41ns, wraps every 89478484971ns
[    0.000055] clocksource: mxc_timer1: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 79635851949 ns
[    0.002515] Console: colour dummy device 80x30
[    0.002632] Calibrating delay loop (skipped), value calculated using timer frequency.. 48.00 BogoMIPS (lpj=240000)
[    0.002688] pid_max: default: 32768 minimum: 301
[    0.003037] Mount-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
[    0.003088] Mountpoint-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
[    0.004892] CPU: Testing write buffer coherency: ok
[    0.005460] CPU0: update cpu_capacity 1024
[    0.005513] CPU0: thread -1, cpu 0, socket 0, mpidr 80000000
[    0.007160] Setting up static identity map for 0x80100000 - 0x80100060
[    0.007509] rcu: Hierarchical SRCU implementation.
[    0.008466] smp: Bringing up secondary CPUs ...
[    0.008511] smp: Brought up 1 node, 1 CPU
[    0.008543] SMP: Total of 1 processors activated (48.00 BogoMIPS).
[    0.008575] CPU: All CPU(s) started in SVC mode.
[    0.009507] devtmpfs: initialized
[    0.023502] VFP support v0.3: implementor 41 architecture 2 part 30 variant 7 rev 5
[    0.024115] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.024195] futex hash table entries: 256 (order: 2, 16384 bytes, linear)
[    0.027083] pinctrl core: initialized pinctrl subsystem
[    0.029728] NET: Registered PF_NETLINK/PF_ROUTE protocol family
[    0.047470] DMA: preallocated 256 KiB pool for atomic coherent allocations
[    0.050589] thermal_sys: Registered thermal governor 'step_wise'
[    0.050953] cpuidle: using governor menu
[    0.051343] CPU identified as i.MX6UL, silicon rev 1.1
[    0.076097] vdd3p0: supplied by regulator-dummy
[    0.077180] cpu: supplied by regulator-dummy
[    0.078637] vddsoc: supplied by regulator-dummy
[    0.101787] No ATAGs?
[    0.101933] hw-breakpoint: found 5 (+1 reserved) breakpoint and 4 watchpoint registers.
[    0.101975] hw-breakpoint: maximum watchpoint size is 8 bytes.
[    0.104357] imx6ul-pinctrl 20e0000.pinctrl: initialized IMX pinctrl driver
[    0.106921] imx mu driver is registered.
[    0.107720] imx rpmsg driver is registered.
[    0.144256] Kprobes globally optimized
[    0.182351] vgaarb: loaded
[    0.184067] SCSI subsystem initialized
[    0.184599] libata version 3.00 loaded.
[    0.185259] usbcore: registered new interface driver usbfs
[    0.185413] usbcore: registered new interface driver hub
[    0.185546] usbcore: registered new device driver usb
[    0.187923] i2c i2c-0: IMX I2C adapter registered
[    0.189154] i2c i2c-1: IMX I2C adapter registered
[    0.189781] mc: Linux media interface: v0.10
[    0.189902] videodev: Linux video capture interface: v2.00
[    0.190207] pps_core: LinuxPPS API ver. 1 registered
[    0.190240] pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
[    0.190303] PTP clock support registered
[    0.193671] MIPI CSI2 driver module loaded
[    0.193831] Advanced Linux Sound Architecture Driver Initialized.
[    0.195619] Bluetooth: Core ver 2.22
[    0.195780] NET: Registered PF_BLUETOOTH protocol family
[    0.195809] Bluetooth: HCI device and connection manager initialized
[    0.195856] Bluetooth: HCI socket layer initialized
[    0.195890] Bluetooth: L2CAP socket layer initialized
[    0.195954] Bluetooth: SCO socket layer initialized
[    0.197113] clocksource: Switched to clocksource mxc_timer1
[    0.197597] VFS: Disk quotas dquot_6.6.0
[    0.197790] VFS: Dquot-cache hash table entries: 1024 (order 0, 4096 bytes)
[    0.219226] NET: Registered PF_INET protocol family
[    0.219580] IP idents hash table entries: 4096 (order: 3, 32768 bytes, linear)
[    0.221237] tcp_listen_portaddr_hash hash table entries: 512 (order: 0, 6144 bytes, linear)
[    0.221351] TCP established hash table entries: 2048 (order: 1, 8192 bytes, linear)
[    0.221441] TCP bind hash table entries: 2048 (order: 2, 16384 bytes, linear)
[    0.221548] TCP: Hash tables configured (established 2048 bind 2048)
[    0.221755] UDP hash table entries: 256 (order: 1, 8192 bytes, linear)
[    0.221847] UDP-Lite hash table entries: 256 (order: 1, 8192 bytes, linear)
[    0.222244] NET: Registered PF_UNIX/PF_LOCAL protocol family
[    0.223659] RPC: Registered named UNIX socket transport module.
[    0.223720] RPC: Registered udp transport module.
[    0.223743] RPC: Registered tcp transport module.
[    0.223766] RPC: Registered tcp NFSv4.1 backchannel transport module.
[    0.226000] PCI: CLS 0 bytes, default 64
[    0.227191] hw perfevents: enabled with armv7_cortex_a7 PMU driver, 5 counters available
[    0.229843] OPTEE busfreq Supported
[    0.230255] Bus freq driver module loaded
[    0.232498] Initialise system trusted keyrings
[    0.233636] workingset: timestamp_bits=14 max_order=16 bucket_order=2
[    0.249430] NFS: Registering the id_resolver key type
[    0.249531] Key type id_resolver registered
[    0.249559] Key type id_legacy registered
[    0.249793] nfs4filelayout_init: NFSv4 File Layout Driver Registering...
[    0.249830] nfs4flexfilelayout_init: NFSv4 Flexfile Layout Driver Registering...
[    0.249925] jffs2: version 2.2. (NAND) © 2001-2006 Red Hat, Inc.
[    0.251199] fuse: init (API version 7.34)
[    0.487437] Key type asymmetric registered
[    0.487500] Asymmetric key parser 'x509' registered
[    0.487700] io scheduler mq-deadline registered
[    0.487740] io scheduler kyber registered
[    0.507669] imx-sdma 20ec000.sdma: Direct firmware load for imx/sdma/sdma-imx6q.bin failed with error -2
[    0.507745] imx-sdma 20ec000.sdma: Falling back to sysfs fallback for: imx/sdma/sdma-imx6q.bin
[    0.511875] mxs-dma 1804000.dma-apbh: initialized
[    0.518936] 2020000.serial: ttymxc0 at MMIO 0x2020000 (irq = 29, base_baud = 5000000) is a IMX
[    1.302208] printk: console [ttymxc0] enabled
[    1.308967] imx-uart 21ec000.serial: no RTS control, disabling rs485
[    1.315540] 21ec000.serial: ttymxc2 at MMIO 0x21ec000 (irq = 64, base_baud = 5000000) is a IMX
[    1.326756] imx sema4 driver is registered.
[    1.365650] brd: module loaded
[    1.384733] loop: module loaded
[    1.390042] imx ahci driver is registered.
[    1.395434] SPI driver mtd_dataflash has no spi_device_id for atmel,at45
[    1.402281] SPI driver mtd_dataflash has no spi_device_id for atmel,dataflash
[    1.413427] nand: device found, Manufacturer ID: 0x2c, Chip ID: 0xda
[    1.419915] nand: Micron MT29F2G08ABAEAWP
[    1.423950] nand: 256 MiB, SLC, erase size: 128 KiB, page size: 2048, OOB size: 64
[    1.432991] Bad block table found at page 131008, version 0x01
[    1.439677] Bad block table found at page 130944, version 0x01
[    1.445985] 5 cmdlinepart partitions found on MTD device gpmi-nand
[    1.452258] Creating 5 MTD partitions on "gpmi-nand":
[    1.457383] 0x000000000000-0x000004000000 : "nandboot"
[    1.464143] mtdblock: MTD device 'nandboot' is NAND, please consider using UBI block devices instead.
[    1.479274] 0x000004000000-0x000005000000 : "nandkernel"
[    1.485759] mtdblock: MTD device 'nandkernel' is NAND, please consider using UBI block devices instead.
[    1.509251] 0x000005000000-0x000006000000 : "nanddtb"
[    1.515542] mtdblock: MTD device 'nanddtb' is NAND, please consider using UBI block devices instead.
[    1.539248] 0x000006000000-0x000007000000 : "nandtee"
[    1.545499] mtdblock: MTD device 'nandtee' is NAND, please consider using UBI block devices instead.
[    1.569243] 0x000007000000-0x000010000000 : "nandrootfs"
[    1.576755] mtdblock: MTD device 'nandrootfs' is NAND, please consider using UBI block devices instead.
[    1.599249] gpmi-nand 1806000.nand-controller: driver registered.
[    1.611075] libphy: Fixed MDIO Bus: probed
[    1.616564] CAN device driver interface
[    1.837942] pps pps0: new PPS source ptp0
[    1.844711] libphy: fec_enet_mii_bus: probed
[    1.854383] fec 20b4000.ethernet eth0: registered PHC device 0
[    2.077936] pps pps1: new PPS source ptp1
[    2.085349] fec 2188000.ethernet eth1: registered PHC device 1
[    2.092918] usbcore: registered new interface driver r8152
[    2.098674] usbcore: registered new interface driver lan78xx
[    2.104468] usbcore: registered new interface driver asix
[    2.110049] usbcore: registered new interface driver ax88179_178a
[    2.116255] usbcore: registered new interface driver cdc_ether
[    2.122301] usbcore: registered new interface driver smsc95xx
[    2.128223] usbcore: registered new interface driver net1080
[    2.133991] usbcore: registered new interface driver cdc_subset
[    2.140072] usbcore: registered new interface driver zaurus
[    2.145759] usbcore: registered new interface driver MOSCHIP usb-ethernet driver
[    2.153361] usbcore: registered new interface driver cdc_ncm
[    2.159094] ehci_hcd: USB 2.0 'Enhanced' Host Controller (EHCI) Driver
[    2.165645] ehci-pci: EHCI PCI platform driver
[    2.170373] usbcore: registered new interface driver usb-storage
[    2.182348] SPI driver ads7846 has no spi_device_id for ti,tsc2046
[    2.188771] SPI driver ads7846 has no spi_device_id for ti,ads7843
[    2.194990] SPI driver ads7846 has no spi_device_id for ti,ads7845
[    2.201242] SPI driver ads7846 has no spi_device_id for ti,ads7873
[    2.213625] snvs_rtc 20cc000.snvs:snvs-rtc-lp: registered as rtc0
[    2.219927] snvs_rtc 20cc000.snvs:snvs-rtc-lp: setting system clock to 1970-01-01T01:02:56 UTC (3776)
[    2.229589] i2c_dev: i2c /dev entries driver
[    2.242221] Bluetooth: HCI UART driver ver 2.3
[    2.246721] Bluetooth: HCI UART protocol H4 registered
[    2.251976] Bluetooth: HCI UART protocol BCSP registered
[    2.257441] Bluetooth: HCI UART protocol LL registered
[    2.262691] Bluetooth: HCI UART protocol Three-wire (H5) registered
[    2.269102] Bluetooth: HCI UART protocol Marvell registered
[    2.274830] usbcore: registered new interface driver btusb
[    2.282402] sdhci: Secure Digital Host Controller Interface driver
[    2.288712] sdhci: Copyright(c) Pierre Ossman
[    2.293091] sdhci-pltfm: SDHCI platform and OF driver helper
[    2.301352] sdhci-esdhc-imx 2190000.mmc: Got CD GPIO
[    2.310852] usbcore: registered new interface driver usbhid
[    2.316477] usbhid: USB HID core driver
[    2.329218] optee: probing for conduit method.
[    2.333734] optee: revision 3.15 (807629a0)
[    2.334532] optee: dynamic shared memory is enabled
[    2.345040] optee: initialized driver
[    2.367592] mmc0: SDHCI controller on 2190000.mmc [2190000.mmc] using ADMA
[    2.375475] NET: Registered PF_LLC protocol family
[    2.382086] NET: Registered PF_INET6 protocol family
[    2.390210] Segment Routing with IPv6
[    2.393989] In-situ OAM (IOAM) with IPv6
[    2.398294] sit: IPv6, IPv4 and MPLS over IPv4 tunneling driver
[    2.405792] NET: Registered PF_PACKET protocol family
[    2.411052] can: controller area network core
[    2.415794] NET: Registered PF_CAN protocol family
[    2.420802] can: raw protocol
[    2.423813] can: broadcast manager protocol
[    2.428150] can: netlink gateway - max_hops=1
[    2.433115] Bluetooth: RFCOMM TTY layer initialized
[    2.438423] Bluetooth: RFCOMM socket layer initialized
[    2.443652] Bluetooth: RFCOMM ver 1.11
[    2.447603] Bluetooth: BNEP (Ethernet Emulation) ver 1.3
[    2.452948] Bluetooth: BNEP filters: protocol multicast
[    2.458262] Bluetooth: BNEP socket layer initialized
[    2.463255] Bluetooth: HIDP (Human Interface Emulation) ver 1.2
[    2.469252] Bluetooth: HIDP socket layer initialized
[    2.474656] lib80211: common routines for IEEE802.11 drivers
[    2.480460] lib80211_crypt: registered algorithm 'NULL'
[    2.480485] lib80211_crypt: registered algorithm 'WEP'
[    2.480502] lib80211_crypt: registered algorithm 'CCMP'
[    2.480518] lib80211_crypt: registered algorithm 'TKIP'
[    2.480612] Key type dns_resolver registered
[    2.511031] Registering SWP/SWPB emulation handler
[    2.516311] Loading compiled-in X.509 certificates
[    2.561486] imx_usb 2184000.usb: No over current polarity defined
[    2.582591] random: fast init done
[    2.748646] ci_hdrc ci_hdrc.1: EHCI Host Controller
[    2.753725] ci_hdrc ci_hdrc.1: new USB bus registered, assigned bus number 1
[    2.787348] ci_hdrc ci_hdrc.1: USB 2.0 started, EHCI 1.00
[    2.793842] usb usb1: New USB device found, idVendor=1d6b, idProduct=0002, bcdDevice= 5.15
[    2.802337] usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    2.810175] usb usb1: Product: EHCI Host Controller
[    2.815488] usb usb1: Manufacturer: Linux 5.15.5-lts-next+gda8167fa0cd1 ehci_hcd
[    2.822955] usb usb1: SerialNumber: ci_hdrc.1
[    2.828610] hub 1-0:1.0: USB hub found
[    2.832542] hub 1-0:1.0: 1 port detected
[    2.840438] imx_thermal 20c8000.anatop:tempmon: Industrial CPU temperature grade - max:105C critical:100C passive:95C
[    2.852712] ubi0: default fastmap pool size: 55
[    2.858593] ubi0: default fastmap WL pool size: 27
[    2.863425] ubi0: attaching mtd4
[    3.511010] ubi0: scanning is finished
[    3.526478] ubi0: attached mtd4 (name "nandrootfs", size 144 MiB)
[    3.532745] ubi0: PEB size: 131072 bytes (128 KiB), LEB size: 126976 bytes
[    3.539697] ubi0: min./max. I/O unit sizes: 2048/2048, sub-page size 2048
[    3.546516] ubi0: VID header offset: 2048 (aligned 2048), data offset: 4096
[    3.553858] ubi0: good PEBs: 1148, bad PEBs: 4, corrupted PEBs: 0
[    3.560286] ubi0: user volume: 1, internal volumes: 1, max. volumes count: 128
[    3.567569] ubi0: max/mean erase counter: 2/1, WL threshold: 4096, image sequence number: 2821213695
[    3.576727] ubi0: available PEBs: 0, total reserved PEBs: 1148, PEBs reserved for bad PEB handling: 36
[    3.586143] ubi0: background thread "ubi_bgt0d" started, PID 86
[    3.593032] cfg80211: Loading compiled-in X.509 certificates for regulatory database
[    3.606498] cfg80211: Loaded X.509 cert 'sforshee: 00b28ddf47aef9cea7'
[    3.613691] platform regulatory.0: Direct firmware load for regulatory.db failed with error -2
[    3.622831] ALSA device list:
[    3.625832]   No soundcards found.
[    3.629471] platform regulatory.0: Falling back to sysfs fallback for: regulatory.db
[    3.638959] UBIFS (ubi0:0): Mounting in unauthenticated mode
[    3.728657] UBIFS (ubi0:0): UBIFS: mounted UBI device 0, volume 0, name "nandrootfs", R/O mode
[    3.737449] UBIFS (ubi0:0): LEB size: 126976 bytes (124 KiB), min./max. I/O unit sizes: 2048 bytes/2048 bytes
[    3.747773] UBIFS (ubi0:0): FS size: 139038720 bytes (132 MiB, 1095 LEBs), max 1106 LEBs, journal size 6983680 bytes (6 MiB, 55 LEBs)
[    3.760147] UBIFS (ubi0:0): reserved for root: 4952683 bytes (4836 KiB)
[    3.766794] UBIFS (ubi0:0): media format: w5/r0 (latest is w5/r0), UUID F6481E8E-DF6B-463C-8DB1-065E877C64CD, small LPT model
[    3.780757] VFS: Mounted root (ubifs filesystem) readonly on device 0:15.
[    3.789027] devtmpfs: mounted
[    3.794584] Freeing unused kernel image (initmem) memory: 1024K
[    3.801192] Run /sbin/init as init process
[    3.805314]   with arguments:
[    3.805324]     /sbin/init
[    3.805335]   with environment:
[    3.805346]     HOME=/
[    3.805354]     TERM=linux
[    4.300770] systemd[1]: System time before build time, advancing clock.
[    4.431681] systemd[1]: systemd 249 running in system mode (-PAM -AUDIT -SELINUX -APPARMOR +IMA -SMACK +SECCOMP -GCRYPT -GNUTLS -OPENSSL +ACL +BLKID -CURL -ELFUTILS -FIDO2 -IDN2 -IDN -IPTC +KMOD -LIBCRYPTSETUP +LIBFDISK -PCRE2 -PWQUALITY -P11KIT -QRENCODE -BZIP2 -LZ4 -XZ -ZLIB +ZSTD -XKBCOMMON +UTMP +SYSVINIT default-hierarchy=hybrid)
[    4.465604] systemd[1]: Detected architecture arm.
[    4.528408] systemd[1]: Hostname set to <imx6ulevk>.
[    4.545926] random: systemd: uninitialized urandom read (16 bytes read)
[    4.552899] systemd[1]: Initializing machine ID from random generator.
[    4.563658] systemd[1]: Installed transient /etc/machine-id file.
[    6.369313] systemd[1]: Queued start job for default target Multi-User System.
[    6.391814] random: systemd: uninitialized urandom read (16 bytes read)
[    6.452835] systemd[1]: Created slice Slice /system/getty.
[    6.487741] random: systemd: uninitialized urandom read (16 bytes read)
[    6.501536] systemd[1]: Created slice Slice /system/modprobe.
[    6.537624] random: systemd: uninitialized urandom read (16 bytes read)
[    6.551480] systemd[1]: Created slice Slice /system/serial-getty.
[    6.597850] systemd[1]: Created slice User and Session Slice.
[    6.641604] systemd[1]: Started Dispatch Password Requests to Console Directory Watch.
[    6.689865] systemd[1]: Started Forward Password Requests to Wall Directory Watch.
[    6.728777] systemd[1]: Reached target Path Units.
[    6.758708] systemd[1]: Reached target Remote File Systems.
[    6.798020] systemd[1]: Reached target Slice Units.
[    6.828886] systemd[1]: Reached target Swaps.
[    6.868052] systemd[1]: Listening on RPCbind Server Activation Socket.
[    6.909063] systemd[1]: Reached target RPC Port Mapper.
[    6.955288] systemd[1]: Listening on Syslog Socket.
[    6.989868] systemd[1]: Listening on initctl Compatibility Named Pipe.
[    7.095885] systemd[1]: Condition check resulted in Journal Audit Socket being skipped.
[    7.107862] systemd[1]: Listening on Journal Socket (/dev/log).
[    7.151697] systemd[1]: Listening on Journal Socket.
[    7.192494] systemd[1]: Listening on Network Service Netlink Socket.
[    7.233902] systemd[1]: Listening on udev Control Socket.
[    7.270894] systemd[1]: Listening on udev Kernel Socket.
[    7.313181] systemd[1]: Listening on User Database Manager Socket.
[    7.350588] systemd[1]: Condition check resulted in Huge Pages File System being skipped.
[    7.377589] systemd[1]: Mounting POSIX Message Queue File System...
[    7.418523] systemd[1]: Mounting Kernel Debug File System...
[    7.447500] systemd[1]: Condition check resulted in Kernel Trace File System being skipped.
[    7.491608] systemd[1]: Mounting Temporary Directory /tmp...
[    7.564365] systemd[1]: Starting Create List of Static Device Nodes...
[    7.631421] systemd[1]: Starting Load Kernel Module configfs...
[    7.692185] systemd[1]: Starting Load Kernel Module drm...
[    7.759237] systemd[1]: Starting Load Kernel Module fuse...
[    7.815524] systemd[1]: Starting RPC Bind...
[    7.876787] systemd[1]: Starting File System Check on Root Device...
[    7.904925] systemd[1]: systemd-journald.service: unit configures an IP firewall, but the local system does not support BPF/cgroup firewalling.
[    7.918448] systemd[1]: (This warning is only shown for the first unit using IP firewalling.)
[    7.979140] systemd[1]: Starting Journal Service...
[    8.016670] systemd[1]: Condition check resulted in Load Kernel Modules being skipped.
[    8.070796] systemd[1]: Starting Apply Kernel Variables...
[    8.149444] systemd[1]: Starting Coldplug All udev Devices...
[    8.229185] systemd[1]: Starting Setup Virtual Console...
[    8.360705] systemd[1]: Started RPC Bind.
[    8.385076] random: crng init done
[    8.388524] random: 6 urandom warning(s) missed due to ratelimiting
[    8.399317] systemd[1]: Mounted POSIX Message Queue File System.
[    8.424997] systemd[1]: Mounted Kernel Debug File System.
[    8.479460] systemd[1]: Mounted Temporary Directory /tmp.
[    8.524372] systemd[1]: Finished Create List of Static Device Nodes.
[    8.582512] systemd[1]: modprobe@configfs.service: Deactivated successfully.
[    8.622630] systemd[1]: Finished Load Kernel Module configfs.
[    8.680748] systemd[1]: modprobe@drm.service: Deactivated successfully.
[    8.717889] systemd[1]: Finished Load Kernel Module drm.
[    8.741144] systemd[1]: modprobe@fuse.service: Deactivated successfully.
[    8.787706] systemd[1]: Finished Load Kernel Module fuse.
[    8.847829] systemd[1]: Finished File System Check on Root Device.
[    8.907812] systemd[1]: Finished Apply Kernel Variables.
[    8.967840] systemd[1]: Finished Setup Virtual Console.
[    9.038819] systemd[1]: Mounting FUSE Control File System...
[    9.112533] systemd[1]: Mounting Kernel Configuration File System...
[    9.213782] systemd[1]: Starting Remount Root and Kernel File Systems...
[    9.273685] systemd[1]: Started Journal Service.
[    9.474670] UBIFS (ubi0:0): background thread "ubifs_bgt0_0" started, PID 122
[    9.764766] systemd-journald[111]: Received client request to flush runtime journal.
[   16.793137] caam-snvs 20cc000.caam-snvs: violation handlers armed - init state
[   17.207472] SMSC LAN8710/LAN8720 20b4000.ethernet-1:01: attached PHY driver (mii_bus:phy_addr=20b4000.ethernet-1:01, irq=POLL)
[   17.262974] caam 2140000.crypto: device ID = 0x0a16030000000000 (Era 8)
[   17.361277] caam 2140000.crypto: job rings = 2, qi = 0
[   17.827508] SMSC LAN8710/LAN8720 20b4000.ethernet-1:00: attached PHY driver (mii_bus:phy_addr=20b4000.ethernet-1:00, irq=POLL)
[   19.367634] fec 20b4000.ethernet eth0: Link is Up - 100Mbps/Full - flow control rx/tx
[   19.375568] IPv6: ADDRCONF(NETDEV_CHANGE): eth0: link becomes ready
[   19.682542] caam algorithms registered in /proc/crypto
[   19.693478] caam 2140000.crypto: caam pkc algorithms registered in /proc/crypto
[   19.705167] caam 2140000.crypto: registering rng-caam
[   19.729450] Device caam-keygen registered
[   64.487824] cfg80211: failed to load regulatory.db
[   64.532426] imx-sdma 20ec000.sdma: firmware found.
[   64.541349] imx-sdma 20ec000.sdma: loaded firmware 3.6
```

