#include "mavlink_bridge.h"

using namespace ait;

MAVLinkBridge::MAVLinkBridge(UART_Interface* uart, mavlink_channel_t mavlink_channel, uint8_t sysid, uint8_t compid)
        : _uart(uart), _mavlink_channel(mavlink_channel), _packet_drops(0) {
    setSysId(sysid);
    setCompId(compid);
}

void MAVLinkBridge::sendMessage(const mavlink_message_t& msg) {
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    sendBuffer(buf, len);
}

void MAVLinkBridge::sendBuffer(const uint8_t* buf, uint16_t len) {
    for (uint16_t i = 0; i < len; ++i) {
        _uart->writeChar(buf[i]);
    }
}

bool MAVLinkBridge::tryReceiveMessage() {
    mavlink_status_t status;
    while (_uart->isCharAvailable()) {
        uint8_t c = _uart->readChar();
        // Try to get a new message
        if (mavlink_parse_char(_mavlink_channel, c, &_recv_msg, &status)) {
            return true;
        }
    }

    // Update packet drops counter
    _packet_drops += _recv_status.packet_rx_drop_count;

    return false;
}

const mavlink_message_t& MAVLinkBridge::getLastReceivedMessage() {
    return _recv_msg;
}
