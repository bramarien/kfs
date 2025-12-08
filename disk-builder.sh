#!/bin/bash
set -e

IMAGE="disk.img"
SIZE_MB=10
MNT_POINT="mnt"

dd if=/dev/zero of="$IMAGE" bs=1M count="$SIZE_MB"

LOOPDEV=$(losetup --find --show --partscan "$IMAGE")

echo ',,83,*' | sfdisk "$LOOPDEV"
partx -u "$LOOPDEV"

mkfs.ext2 "${LOOPDEV}p1"

mkdir -p "$MNT_POINT"
mount "${LOOPDEV}p1" "$MNT_POINT"

mkdir -p "$MNT_POINT/boot"
grub-install \
  --target=i386-pc \
  --boot-directory="$MNT_POINT/boot" \
  --install-modules="normal multiboot biosdisk part_msdos ext2" \
  --themes= \
  --fonts= \
  "$LOOPDEV"

cp boot/kernel.elf "$MNT_POINT/boot"
cp boot/grub/grub.cfg "$MNT_POINT/boot/grub"

umount "$MNT_POINT"
losetup -d "$LOOPDEV"
rm -rf "$MNT_POINT"
chmod 666 "$IMAGE"

echo "Disk image created successfully: $IMAGE"
