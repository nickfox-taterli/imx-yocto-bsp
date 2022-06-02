# Copyright (C) 2016 Freescale Semiconductor
# Copyright 2017-2022 NXP
# Copyright 2018 (C) O.S. Systems Software LTDA.
# Released under the MIT license (see COPYING.MIT for the terms)

DESCRIPTION = "G2D library using i.MX GPU"
LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://COPYING;md5=be5ff43682ed6c57dfcbeb97651c2829" 
DEPENDS = "libgal-imx"
PROVIDES = "virtual/libg2d"

FSLBIN_NAME = "${PN}-${PV}-${TARGET_ARCH}"

SRC_URI = "${FSL_MIRROR}/${FSLBIN_NAME}.bin;name=${TARGET_ARCH};fsl-eula=true"
SRC_URI[aarch64.md5sum] = "b3b3c285796cd5d47841b73c4735e6bd"
SRC_URI[aarch64.sha256sum] = "f2d592d1389be0c16f8dbe6374d480d674c2e31f4195916dbd6baf71473a0e60"
SRC_URI[arm.md5sum] = "82f6a394505bc9d348a35f26cd02bd6a"
SRC_URI[arm.sha256sum] = "96f0213009087de0842740401a67a19d70d5a7ae928843c9c9bee3f8f177b2a0"

S = "${WORKDIR}/${FSLBIN_NAME}"

inherit fsl-eula-unpack

do_install () {
    cp -r -d --no-preserve=ownership ${S}/g2d/* ${D}
    if [ "${libdir}" != "/usr/lib" ]; then
        mv ${D}/usr/lib ${D}${libdir}
    fi
}

INSANE_SKIP:${PN} += "ldflags"

COMPATIBLE_MACHINE = "(imxgpu2d)"
