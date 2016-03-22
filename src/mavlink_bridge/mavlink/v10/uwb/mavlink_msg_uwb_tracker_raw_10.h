// MESSAGE UWB_TRACKER_RAW_10 PACKING

#define MAVLINK_MSG_ID_UWB_TRACKER_RAW_10 180

typedef struct __mavlink_uwb_tracker_raw_10_t
{
 uint64_t timestamp_master_request_1_recv; /*< Timestamp of master request 1 on slave module.*/
 uint64_t timestamp_slave_reply_send; /*< Timestamp of slave reply on slave module.*/
 uint64_t timestamp_master_request_2_recv; /*< Timestamp of master request 2 on slave module.*/
 uint64_t timestamp_master_request_1[10]; /*< Timestamp of master request 1 on tracker modules.*/
 uint64_t timestamp_slave_reply[10]; /*< Timestamp of slave reply on tracker modules.*/
 uint64_t timestamp_master_request_2[10]; /*< Timestamp of master request 2 on tracker modules.*/
 uint8_t num_of_units; /*< Number of UWB units on the tracker.*/
 uint8_t address; /*< Address of UWB tracker.*/
 uint8_t remote_address; /*< Address of remote UWB unit that was used as slave.*/
} mavlink_uwb_tracker_raw_10_t;

#define MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN 267
#define MAVLINK_MSG_ID_180_LEN 267

#define MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_CRC 32
#define MAVLINK_MSG_ID_180_CRC 32

#define MAVLINK_MSG_UWB_TRACKER_RAW_10_FIELD_TIMESTAMP_MASTER_REQUEST_1_LEN 10
#define MAVLINK_MSG_UWB_TRACKER_RAW_10_FIELD_TIMESTAMP_SLAVE_REPLY_LEN 10
#define MAVLINK_MSG_UWB_TRACKER_RAW_10_FIELD_TIMESTAMP_MASTER_REQUEST_2_LEN 10

#define MAVLINK_MESSAGE_INFO_UWB_TRACKER_RAW_10 { \
	"UWB_TRACKER_RAW_10", \
	9, \
	{  { "timestamp_master_request_1_recv", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_uwb_tracker_raw_10_t, timestamp_master_request_1_recv) }, \
         { "timestamp_slave_reply_send", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_uwb_tracker_raw_10_t, timestamp_slave_reply_send) }, \
         { "timestamp_master_request_2_recv", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_uwb_tracker_raw_10_t, timestamp_master_request_2_recv) }, \
         { "timestamp_master_request_1", NULL, MAVLINK_TYPE_UINT64_T, 10, 24, offsetof(mavlink_uwb_tracker_raw_10_t, timestamp_master_request_1) }, \
         { "timestamp_slave_reply", NULL, MAVLINK_TYPE_UINT64_T, 10, 104, offsetof(mavlink_uwb_tracker_raw_10_t, timestamp_slave_reply) }, \
         { "timestamp_master_request_2", NULL, MAVLINK_TYPE_UINT64_T, 10, 184, offsetof(mavlink_uwb_tracker_raw_10_t, timestamp_master_request_2) }, \
         { "num_of_units", NULL, MAVLINK_TYPE_UINT8_T, 0, 264, offsetof(mavlink_uwb_tracker_raw_10_t, num_of_units) }, \
         { "address", NULL, MAVLINK_TYPE_UINT8_T, 0, 265, offsetof(mavlink_uwb_tracker_raw_10_t, address) }, \
         { "remote_address", NULL, MAVLINK_TYPE_UINT8_T, 0, 266, offsetof(mavlink_uwb_tracker_raw_10_t, remote_address) }, \
         } \
}


/**
 * @brief Pack a uwb_tracker_raw_10 message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param num_of_units Number of UWB units on the tracker.
 * @param address Address of UWB tracker.
 * @param remote_address Address of remote UWB unit that was used as slave.
 * @param timestamp_master_request_1_recv Timestamp of master request 1 on slave module.
 * @param timestamp_slave_reply_send Timestamp of slave reply on slave module.
 * @param timestamp_master_request_2_recv Timestamp of master request 2 on slave module.
 * @param timestamp_master_request_1 Timestamp of master request 1 on tracker modules.
 * @param timestamp_slave_reply Timestamp of slave reply on tracker modules.
 * @param timestamp_master_request_2 Timestamp of master request 2 on tracker modules.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_tracker_raw_10_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t num_of_units, uint8_t address, uint8_t remote_address, uint64_t timestamp_master_request_1_recv, uint64_t timestamp_slave_reply_send, uint64_t timestamp_master_request_2_recv, const uint64_t *timestamp_master_request_1, const uint64_t *timestamp_slave_reply, const uint64_t *timestamp_master_request_2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN];
	_mav_put_uint64_t(buf, 0, timestamp_master_request_1_recv);
	_mav_put_uint64_t(buf, 8, timestamp_slave_reply_send);
	_mav_put_uint64_t(buf, 16, timestamp_master_request_2_recv);
	_mav_put_uint8_t(buf, 264, num_of_units);
	_mav_put_uint8_t(buf, 265, address);
	_mav_put_uint8_t(buf, 266, remote_address);
	_mav_put_uint64_t_array(buf, 24, timestamp_master_request_1, 10);
	_mav_put_uint64_t_array(buf, 104, timestamp_slave_reply, 10);
	_mav_put_uint64_t_array(buf, 184, timestamp_master_request_2, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#else
	mavlink_uwb_tracker_raw_10_t packet;
	packet.timestamp_master_request_1_recv = timestamp_master_request_1_recv;
	packet.timestamp_slave_reply_send = timestamp_slave_reply_send;
	packet.timestamp_master_request_2_recv = timestamp_master_request_2_recv;
	packet.num_of_units = num_of_units;
	packet.address = address;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.timestamp_master_request_1, timestamp_master_request_1, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.timestamp_slave_reply, timestamp_slave_reply, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.timestamp_master_request_2, timestamp_master_request_2, sizeof(uint64_t)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_TRACKER_RAW_10;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif
}

/**
 * @brief Pack a uwb_tracker_raw_10 message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param num_of_units Number of UWB units on the tracker.
 * @param address Address of UWB tracker.
 * @param remote_address Address of remote UWB unit that was used as slave.
 * @param timestamp_master_request_1_recv Timestamp of master request 1 on slave module.
 * @param timestamp_slave_reply_send Timestamp of slave reply on slave module.
 * @param timestamp_master_request_2_recv Timestamp of master request 2 on slave module.
 * @param timestamp_master_request_1 Timestamp of master request 1 on tracker modules.
 * @param timestamp_slave_reply Timestamp of slave reply on tracker modules.
 * @param timestamp_master_request_2 Timestamp of master request 2 on tracker modules.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_tracker_raw_10_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t num_of_units,uint8_t address,uint8_t remote_address,uint64_t timestamp_master_request_1_recv,uint64_t timestamp_slave_reply_send,uint64_t timestamp_master_request_2_recv,const uint64_t *timestamp_master_request_1,const uint64_t *timestamp_slave_reply,const uint64_t *timestamp_master_request_2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN];
	_mav_put_uint64_t(buf, 0, timestamp_master_request_1_recv);
	_mav_put_uint64_t(buf, 8, timestamp_slave_reply_send);
	_mav_put_uint64_t(buf, 16, timestamp_master_request_2_recv);
	_mav_put_uint8_t(buf, 264, num_of_units);
	_mav_put_uint8_t(buf, 265, address);
	_mav_put_uint8_t(buf, 266, remote_address);
	_mav_put_uint64_t_array(buf, 24, timestamp_master_request_1, 10);
	_mav_put_uint64_t_array(buf, 104, timestamp_slave_reply, 10);
	_mav_put_uint64_t_array(buf, 184, timestamp_master_request_2, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#else
	mavlink_uwb_tracker_raw_10_t packet;
	packet.timestamp_master_request_1_recv = timestamp_master_request_1_recv;
	packet.timestamp_slave_reply_send = timestamp_slave_reply_send;
	packet.timestamp_master_request_2_recv = timestamp_master_request_2_recv;
	packet.num_of_units = num_of_units;
	packet.address = address;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.timestamp_master_request_1, timestamp_master_request_1, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.timestamp_slave_reply, timestamp_slave_reply, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.timestamp_master_request_2, timestamp_master_request_2, sizeof(uint64_t)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_TRACKER_RAW_10;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif
}

/**
 * @brief Encode a uwb_tracker_raw_10 struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param uwb_tracker_raw_10 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_tracker_raw_10_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_uwb_tracker_raw_10_t* uwb_tracker_raw_10)
{
	return mavlink_msg_uwb_tracker_raw_10_pack(system_id, component_id, msg, uwb_tracker_raw_10->num_of_units, uwb_tracker_raw_10->address, uwb_tracker_raw_10->remote_address, uwb_tracker_raw_10->timestamp_master_request_1_recv, uwb_tracker_raw_10->timestamp_slave_reply_send, uwb_tracker_raw_10->timestamp_master_request_2_recv, uwb_tracker_raw_10->timestamp_master_request_1, uwb_tracker_raw_10->timestamp_slave_reply, uwb_tracker_raw_10->timestamp_master_request_2);
}

/**
 * @brief Encode a uwb_tracker_raw_10 struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uwb_tracker_raw_10 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_tracker_raw_10_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_uwb_tracker_raw_10_t* uwb_tracker_raw_10)
{
	return mavlink_msg_uwb_tracker_raw_10_pack_chan(system_id, component_id, chan, msg, uwb_tracker_raw_10->num_of_units, uwb_tracker_raw_10->address, uwb_tracker_raw_10->remote_address, uwb_tracker_raw_10->timestamp_master_request_1_recv, uwb_tracker_raw_10->timestamp_slave_reply_send, uwb_tracker_raw_10->timestamp_master_request_2_recv, uwb_tracker_raw_10->timestamp_master_request_1, uwb_tracker_raw_10->timestamp_slave_reply, uwb_tracker_raw_10->timestamp_master_request_2);
}

/**
 * @brief Send a uwb_tracker_raw_10 message
 * @param chan MAVLink channel to send the message
 *
 * @param num_of_units Number of UWB units on the tracker.
 * @param address Address of UWB tracker.
 * @param remote_address Address of remote UWB unit that was used as slave.
 * @param timestamp_master_request_1_recv Timestamp of master request 1 on slave module.
 * @param timestamp_slave_reply_send Timestamp of slave reply on slave module.
 * @param timestamp_master_request_2_recv Timestamp of master request 2 on slave module.
 * @param timestamp_master_request_1 Timestamp of master request 1 on tracker modules.
 * @param timestamp_slave_reply Timestamp of slave reply on tracker modules.
 * @param timestamp_master_request_2 Timestamp of master request 2 on tracker modules.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_uwb_tracker_raw_10_send(mavlink_channel_t chan, uint8_t num_of_units, uint8_t address, uint8_t remote_address, uint64_t timestamp_master_request_1_recv, uint64_t timestamp_slave_reply_send, uint64_t timestamp_master_request_2_recv, const uint64_t *timestamp_master_request_1, const uint64_t *timestamp_slave_reply, const uint64_t *timestamp_master_request_2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN];
	_mav_put_uint64_t(buf, 0, timestamp_master_request_1_recv);
	_mav_put_uint64_t(buf, 8, timestamp_slave_reply_send);
	_mav_put_uint64_t(buf, 16, timestamp_master_request_2_recv);
	_mav_put_uint8_t(buf, 264, num_of_units);
	_mav_put_uint8_t(buf, 265, address);
	_mav_put_uint8_t(buf, 266, remote_address);
	_mav_put_uint64_t_array(buf, 24, timestamp_master_request_1, 10);
	_mav_put_uint64_t_array(buf, 104, timestamp_slave_reply, 10);
	_mav_put_uint64_t_array(buf, 184, timestamp_master_request_2, 10);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10, buf, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10, buf, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif
#else
	mavlink_uwb_tracker_raw_10_t packet;
	packet.timestamp_master_request_1_recv = timestamp_master_request_1_recv;
	packet.timestamp_slave_reply_send = timestamp_slave_reply_send;
	packet.timestamp_master_request_2_recv = timestamp_master_request_2_recv;
	packet.num_of_units = num_of_units;
	packet.address = address;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.timestamp_master_request_1, timestamp_master_request_1, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.timestamp_slave_reply, timestamp_slave_reply, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.timestamp_master_request_2, timestamp_master_request_2, sizeof(uint64_t)*10);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10, (const char *)&packet, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10, (const char *)&packet, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_uwb_tracker_raw_10_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t num_of_units, uint8_t address, uint8_t remote_address, uint64_t timestamp_master_request_1_recv, uint64_t timestamp_slave_reply_send, uint64_t timestamp_master_request_2_recv, const uint64_t *timestamp_master_request_1, const uint64_t *timestamp_slave_reply, const uint64_t *timestamp_master_request_2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, timestamp_master_request_1_recv);
	_mav_put_uint64_t(buf, 8, timestamp_slave_reply_send);
	_mav_put_uint64_t(buf, 16, timestamp_master_request_2_recv);
	_mav_put_uint8_t(buf, 264, num_of_units);
	_mav_put_uint8_t(buf, 265, address);
	_mav_put_uint8_t(buf, 266, remote_address);
	_mav_put_uint64_t_array(buf, 24, timestamp_master_request_1, 10);
	_mav_put_uint64_t_array(buf, 104, timestamp_slave_reply, 10);
	_mav_put_uint64_t_array(buf, 184, timestamp_master_request_2, 10);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10, buf, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10, buf, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif
#else
	mavlink_uwb_tracker_raw_10_t *packet = (mavlink_uwb_tracker_raw_10_t *)msgbuf;
	packet->timestamp_master_request_1_recv = timestamp_master_request_1_recv;
	packet->timestamp_slave_reply_send = timestamp_slave_reply_send;
	packet->timestamp_master_request_2_recv = timestamp_master_request_2_recv;
	packet->num_of_units = num_of_units;
	packet->address = address;
	packet->remote_address = remote_address;
	mav_array_memcpy(packet->timestamp_master_request_1, timestamp_master_request_1, sizeof(uint64_t)*10);
	mav_array_memcpy(packet->timestamp_slave_reply, timestamp_slave_reply, sizeof(uint64_t)*10);
	mav_array_memcpy(packet->timestamp_master_request_2, timestamp_master_request_2, sizeof(uint64_t)*10);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10, (const char *)packet, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10, (const char *)packet, MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UWB_TRACKER_RAW_10 UNPACKING


/**
 * @brief Get field num_of_units from uwb_tracker_raw_10 message
 *
 * @return Number of UWB units on the tracker.
 */
static inline uint8_t mavlink_msg_uwb_tracker_raw_10_get_num_of_units(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  264);
}

/**
 * @brief Get field address from uwb_tracker_raw_10 message
 *
 * @return Address of UWB tracker.
 */
static inline uint8_t mavlink_msg_uwb_tracker_raw_10_get_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  265);
}

/**
 * @brief Get field remote_address from uwb_tracker_raw_10 message
 *
 * @return Address of remote UWB unit that was used as slave.
 */
static inline uint8_t mavlink_msg_uwb_tracker_raw_10_get_remote_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  266);
}

/**
 * @brief Get field timestamp_master_request_1_recv from uwb_tracker_raw_10 message
 *
 * @return Timestamp of master request 1 on slave module.
 */
static inline uint64_t mavlink_msg_uwb_tracker_raw_10_get_timestamp_master_request_1_recv(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field timestamp_slave_reply_send from uwb_tracker_raw_10 message
 *
 * @return Timestamp of slave reply on slave module.
 */
static inline uint64_t mavlink_msg_uwb_tracker_raw_10_get_timestamp_slave_reply_send(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field timestamp_master_request_2_recv from uwb_tracker_raw_10 message
 *
 * @return Timestamp of master request 2 on slave module.
 */
static inline uint64_t mavlink_msg_uwb_tracker_raw_10_get_timestamp_master_request_2_recv(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Get field timestamp_master_request_1 from uwb_tracker_raw_10 message
 *
 * @return Timestamp of master request 1 on tracker modules.
 */
static inline uint16_t mavlink_msg_uwb_tracker_raw_10_get_timestamp_master_request_1(const mavlink_message_t* msg, uint64_t *timestamp_master_request_1)
{
	return _MAV_RETURN_uint64_t_array(msg, timestamp_master_request_1, 10,  24);
}

/**
 * @brief Get field timestamp_slave_reply from uwb_tracker_raw_10 message
 *
 * @return Timestamp of slave reply on tracker modules.
 */
static inline uint16_t mavlink_msg_uwb_tracker_raw_10_get_timestamp_slave_reply(const mavlink_message_t* msg, uint64_t *timestamp_slave_reply)
{
	return _MAV_RETURN_uint64_t_array(msg, timestamp_slave_reply, 10,  104);
}

/**
 * @brief Get field timestamp_master_request_2 from uwb_tracker_raw_10 message
 *
 * @return Timestamp of master request 2 on tracker modules.
 */
static inline uint16_t mavlink_msg_uwb_tracker_raw_10_get_timestamp_master_request_2(const mavlink_message_t* msg, uint64_t *timestamp_master_request_2)
{
	return _MAV_RETURN_uint64_t_array(msg, timestamp_master_request_2, 10,  184);
}

/**
 * @brief Decode a uwb_tracker_raw_10 message into a struct
 *
 * @param msg The message to decode
 * @param uwb_tracker_raw_10 C-struct to decode the message contents into
 */
static inline void mavlink_msg_uwb_tracker_raw_10_decode(const mavlink_message_t* msg, mavlink_uwb_tracker_raw_10_t* uwb_tracker_raw_10)
{
#if MAVLINK_NEED_BYTE_SWAP
	uwb_tracker_raw_10->timestamp_master_request_1_recv = mavlink_msg_uwb_tracker_raw_10_get_timestamp_master_request_1_recv(msg);
	uwb_tracker_raw_10->timestamp_slave_reply_send = mavlink_msg_uwb_tracker_raw_10_get_timestamp_slave_reply_send(msg);
	uwb_tracker_raw_10->timestamp_master_request_2_recv = mavlink_msg_uwb_tracker_raw_10_get_timestamp_master_request_2_recv(msg);
	mavlink_msg_uwb_tracker_raw_10_get_timestamp_master_request_1(msg, uwb_tracker_raw_10->timestamp_master_request_1);
	mavlink_msg_uwb_tracker_raw_10_get_timestamp_slave_reply(msg, uwb_tracker_raw_10->timestamp_slave_reply);
	mavlink_msg_uwb_tracker_raw_10_get_timestamp_master_request_2(msg, uwb_tracker_raw_10->timestamp_master_request_2);
	uwb_tracker_raw_10->num_of_units = mavlink_msg_uwb_tracker_raw_10_get_num_of_units(msg);
	uwb_tracker_raw_10->address = mavlink_msg_uwb_tracker_raw_10_get_address(msg);
	uwb_tracker_raw_10->remote_address = mavlink_msg_uwb_tracker_raw_10_get_remote_address(msg);
#else
	memcpy(uwb_tracker_raw_10, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UWB_TRACKER_RAW_10_LEN);
#endif
}
