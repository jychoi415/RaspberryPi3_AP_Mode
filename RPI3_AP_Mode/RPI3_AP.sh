#!/bin/bash
#AP_Mode
if [ "$EUID" -ne 0 ]; then
	echo "Must be root!"
	exit 
fi
apt-get install dnsmasq hostapd

cp AP_dhcpcd /etc/dhcpcd.conf
ifdown wlan0
ifup wlan0

cp AP_interfaces /etc/network/interfaces
service dhcpcd restart

cp hostapd hostapd.conf

func()
{
	echo -n "Insert passwd(more than 7) >> "
	read passwd
}

echo -n "Insert ssid >> "
read ssid
func	#함수 실행

while [ ${#passwd} -lt 8 ]; do		#passwd가 8자리 미만이면
	echo "Password is too short!"
	func
done

sed -e s/^ssid=*/ssid=$ssid/g hostapd.conf > hostapd.conf.tmp
mv hostapd.conf.tmp hostapd.conf
sed -e s/^wpa_passphrase=*/wpa_passphrase=$passwd/g hostapd.conf > hostapd.conf.tmp
mv hostapd.conf.tmp /etc/hostapd/hostapd.conf

#/usr/sbin/hostapd /etc/hostapd/hostapd.conf

cp AP_DAEMON_CONF /etc/default/hostapd
cp AP_dnsmasq /etc/dnsmasq.conf
cp AP_sysctl /etc/sysctl.conf

echo 1 > /proc/sys/net/ipv4/ip_forward

iptables -t nat -A POSTROUTING –o eth0 –j MASQUERADE
iptables –A FORWARD –i eth0 –o wlan0 –m state -- state RELATED,ESTABLISHED –j ACCEPT
iptables –A FORWARD -i wlan0 –o eth0 –j ACCEPT

iptables -t nat -S
iptables -S

sh -c "iptables-save > /etc/iptables.ipv4.nat"

cp AP_iptables /lib/dhcpcd/dhcpcd-hooks/70-ipv4-nat

service hostapd restart
service dnsmasq restart
