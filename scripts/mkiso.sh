#!/bin/bash
set -e

if [ $# -ne 2 ]
then
  echo "usage: mkiso.sh kernel_file iso_file"
  exit 1
fi

ROOT_DIR="target/iso"
BOOT_DIR="${ROOT_DIR}/boot"
GRUB_DIR="${BOOT_DIR}/grub"
GRUB_CFG="${GRUB_DIR}/grub.cfg"

KERNEL=$1
TARGET=$2

KERNEL_BASENAME=`basename $KERNEL`

mkdir -p $GRUB_DIR
cp $KERNEL $BOOT_DIR

cat > $GRUB_CFG <<EOF
set timeout=0
set default=0
menuentry "Baojuan OS" {
  multiboot2 /boot/${KERNEL_BASENAME}
}
EOF

grub-mkrescue --output=$TARGET $ROOT_DIR
