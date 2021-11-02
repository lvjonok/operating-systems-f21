dd if=/dev/zero of=lofs.img bs=1M count=50
losetup -a
mkfs.ext4 ./lofs.img
sudo losetup -fP lofs.img
losetup -a
mkdir lofsdisk
sudo mount -o loop /dev/loop0 ./lofsdisk
