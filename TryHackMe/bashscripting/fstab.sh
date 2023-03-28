#!/bin/bash

LV=1

for i in $(cat devices.txt); do
echo $i/sapdata${LV}lv          /db2/CRP/sapdata${LV}           xfs     defaults 1 2
LV=$(($LV +1))
done
