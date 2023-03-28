#!/bin/bash
VG=2
LV=2

for i in $(cat lvs.txt); do
lvcreate -l +100%FREE -n sapdata${LV}lv sapdata${VG}vg
VG=$(($VG +1))
LV=$(($LV +1))
done
