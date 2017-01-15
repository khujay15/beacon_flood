#include <iostream>
#include <tins/tins.h>
#include <unistd.h>
#include <memory.h>
using namespace Tins;

//http://www.ktword.co.kr/abbr_view.php?m_temp1=2319&m_search=%BA%F1%C4%DC%C7%C1%B7%B9%C0%D3//

int main()
{
    PacketSender sender("wlx98ded014934e"); //wlan0
    RadioTap radio[2];
    Dot11Beacon beacon;
    beacon.interval(0x0064);
    beacon.timestamp(0x0000003ed11c1181);

    // Make this a broadcast frame. Note that Dot11::BROADCAST
    // is just the same as "ff:ff:ff:ff:ff:ff"
    beacon.addr1(Dot11::BROADCAST);
    // We'll set the source address to some arbitrary address
    beacon.addr2("00:01:02:03:04:05");
    // Set the bssid, to the same one as above
    beacon.addr3(beacon.addr2());

    // Let's add an ssid option
    beacon.ssid("bob_gilgil_mentor_handsome");
    // Our current channel is 8
    beacon.ds_parameter_set(8);
    // This is our list of supported rates:
    beacon.supported_rates({ 1.0f, 5.5f, 11.0f, 6.0f, 9.0f, 12.0f, 18.0f });    // 802.11b + 802.11g bandwidth add!

    // Encryption: we'll say we use WPA2-psk encryption
    beacon.rsn_information(RSNInformation::wpa2_psk());
    radio[0].inner_pdu(beacon);

    Dot11Beacon beacon2;
    beacon2.interval(0x0064);
    beacon2.timestamp(0x0000003ed11c1181);
    beacon2.addr1(Dot11::BROADCAST);
    beacon2.addr2("00:01:02:03:04:06");
    beacon2.addr3(beacon.addr2());
    beacon2.ssid("gilbert_mentor_handsome");
    beacon2.ds_parameter_set(8);
    beacon2.supported_rates({ 1.0f, 5.5f, 11.0f, 6.0f, 9.0f, 12.0f, 18.0f });    // 802.11b + 802.11g bandwidth add!
    beacon2.rsn_information(RSNInformation::wpa2_psk());
    radio[1].inner_pdu(beacon2);



    while(1)
    {
        sender.send(radio[0]);
        sender.send(radio[1]);
        usleep(300);
    }
    return 0;
}

