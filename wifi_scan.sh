#!/bin/sh

while true
do
    NETWORK_LIST=`wpa_cli scan_r | grep WPA | awk '{print $5}'`
    for NET in $NETWORK_LIST
    do
        echo $NET
    done

    sleep 1
done