#!/bin/bash
VG=2
for pv in $(cat pvs.txt); do
vgcreate sapdata${VG}vg $pv
VG=$(($VG +1))
done
