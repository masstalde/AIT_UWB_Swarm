#pragma once

#include "uart_interface.h"

#include "mavlink_bridge/mavlink/v10/uwb/mavlink.h"

namespace ait {

class MAVLinkBridge {
    UART_Interface* _uart;
    mavlink_system_t _mavlink_system;
    // TODO: Is this int?
    mavlink_channel_t _mavlink_channel;
    mavlink_message_t _recv_msg;
    mavlink_status_t _recv_status;
    int _packet_drops;

public:
    MAVLinkBridge(UART_Interface* uart, mavlink_channel_t mavlink_channel = MAVLINK_COMM_0, uint8_t sysid = 1, uint8_t compid = MAV_COMP_ID_UART_BRIDGE);

    void setSysId(uint8_t sysid) {
        _mavlink_system.sysid = sysid;
    }

    uint8_t getSysId() const {
        return _mavlink_system.sysid;
    }

    void setCompId(uint8_t compid) {
        _mavlink_system.compid = compid;
    }

    uint8_t getCompId() const {
        return _mavlink_system.compid;
    }

    void sendMessage(const mavlink_message_t& msg);

    bool tryReceiveMessage();

    const mavlink_message_t& getLastReceivedMessage();

protected:
    void sendBuffer(const uint8_t* buf, uint16_t len);
};

}
