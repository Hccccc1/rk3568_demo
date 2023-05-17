killall wpa_supplicant

echo -e "ctrl_interface=/var/run/wpa_supplicant \n
ctrl_interface_group=0 \n
update_config=1 \n
\n
network={ \n
        ssid=\"HChenPC\" \n
        psk=\"asd135790\" \n
}" > /usrdata/wpa_supplicant.conf

wpa_supplicant -B -Dnl80211 -iwlan0 -c /usrdata/wpa_supplicant.conf