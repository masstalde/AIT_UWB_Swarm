// MESSAGE UWB_RANGE PACKING

#define MAVLINK_MSG_ID_UWB_RANGE 200

typedef struct __mavlink_uwb_range_t
{
 uint32_t stamp_us; /*< Timestamp of measurement in microseconds.*/
 float round_trip_time; /*< Round trip time in nanoseconds.*/
 float range; /*< Range.*/
 uint8_t address; /*< Address of UWB unit.*/
 uint8_t remote_address; /*< Address of remote UWB unit that was used as an anchor.*/
} mavlink_uwb_range_t;

#define MAVLINK_MSG_ID_UWB_RANGE_LEN 14
#define MAVLINK_MSG_ID_200_LEN 14

#define MAVLINK_MSG_ID_UWB_RANGE_CRC 105
#define MAVLINK_MSG_ID_200_CRC 105



#define MAVLINK_MESSAGE_INFO_UWB_RANGE { \
	"UWB_RANGE", \
	5, \
	{  { "stamp_us", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_uwb_range_t, stamp_us) }, \
         { "round_trip_time", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_uwb_range_t, round_trip_time) }, \
         { "range", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_uwb_range_t, range) }, \
         { "address", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_uwb_range_t, address) }, \
         { "remote_address", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_uwb_range_t, remote_address) }, \
         } \
}


/**
 * @brief Pack a uwb_range message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param address Address of UWB unit.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param stamp_us Timestamp of measurement in microseconds.
 * @param round_trip_time Round trip time in nanoseconds.
 * @param range Range.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_range_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t address, uint8_t remote_address, uint32_t stamp_us, float round_trip_time, float range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_LEN];
	_mav_put_uint32_t(buf, 0, stamp_us);
	_mav_put_float(buf, 4, round_trip_time);
	_mav_put_float(buf, 8, range);
	_mav_put_uint8_t(buf, 12, address);
	_mav_put_uint8_t(buf, 13, remote_address);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#else
	mavlink_uwb_range_t packet;
	packet.stamp_us = stamp_us;
	packet.round_trip_time = round_trip_time;
	packet.range = range;
	packet.address = address;
	packet.remote_address = remote_address;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_RANGE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_RANGE_LEN, MAVLINK_MSG_ID_UWB_RANGE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif
}

/**
 * @brief Pack a uwb_range message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param address Address of UWB unit.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param stamp_us Timestamp of measurement in microseconds.
 * @param round_trip_time Round trip time in nanoseconds.
 * @param range Range.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_range_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t address,uint8_t remote_address,uint32_t stamp_us,float round_trip_time,float range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_LEN];
	_mav_put_uint32_t(buf, 0, stamp_us);
	_mav_put_float(buf, 4, round_trip_time);
	_mav_put_float(buf, 8, range);
	_mav_put_uint8_t(buf, 12, address);
	_mav_put_uint8_t(buf, 13, remote_address);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#else
	mavlink_uwb_range_t packet;
	packet.stamp_us = stamp_us;
	packet.round_trip_time = round_trip_time;
	packet.range = range;
	packet.address = address;
	packet.remote_address = remote_address;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_RANGE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_RANGE_LEN, MAVLINK_MSG_ID_UWB_RANGE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif
}

/**
 * @brief Encode a uwb_range struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param uwb_range C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_range_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_uwb_range_t* uwb_range)
{
	return mavlink_msg_uwb_range_pack(system_id, component_id, msg, uwb_range->address, uwb_range->remote_address, uwb_range->stamp_us, uwb_range->round_trip_time, uwb_range->range);
}

/**
 * @brief Encode a uwb_range struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uwb_range C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_range_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_uwb_range_t* uwb_range)
{
	return mavlink_msg_uwb_range_pack_chan(system_id, component_id, chan, msg, uwb_range->address, uwb_range->remote_address, uwb_range->stamp_us, uwb_range->round_trip_time, uwb_range->range);
}

/**
 * @brief Send a uwb_range message
 * @param chan MAVLink channel to send the message
 *
 * @param address Address of UWB unit.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param stamp_us Timestamp of measurement in microseconds.
 * @param round_trip_time Round trip time in nanoseconds.
 * @param range Range.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_uwb_range_send(mavlink_channel_t chan, uint8_t address, uint8_t remote_address, uint32_t stamp_us, float round_trip_time, float range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_LEN];
	_mav_put_uint32_t(buf, 0, stamp_us);
	_mav_put_float(buf, 4, round_trip_time);
	_mav_put_float(buf, 8, range);
	_mav_put_uint8_t(buf, 12, address);
	_mav_put_uint8_t(buf, 13, remote_address);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE, buf, MAVLINK_MSG_ID_UWB_RANGE_LEN, MAVLINK_MSG_ID_UWB_RANGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE, buf, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif
#else
	mavlink_uwb_range_t packet;
	packet.stamp_us = stamp_us;
	packet.round_trip_time = round_trip_time;
	packet.range = range;
	packet.address = address;
	packet.remote_address = remote_address;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE, (const char *)&packet, MAVLINK_MSG_ID_UWB_RANGE_LEN, MAVLINK_MSG_ID_UWB_RANGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE, (const char *)&packet, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UWB_RANGE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_uwb_range_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t address, uint8_t remote_address, uint32_t stamp_us, float round_trip_time, float range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, stamp_us);
	_mav_put_float(buf, 4, round_trip_time);
	_mav_put_float(buf, 8, range);
	_mav_put_uint8_t(buf, 12, address);
	_mav_put_uint8_t(buf, 13, remote_address);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE, buf, MAVLINK_MSG_ID_UWB_RANGE_LEN, MAVLINK_MSG_ID_UWB_RANGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE, buf, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif
#else
	mavlink_uwb_range_t *packet = (mavlink_uwb_range_t *)msgbuf;
	packet->stamp_us = stamp_us;
	packet->round_trip_time = round_trip_time;
	packet->range = range;
	packet->address = address;
	packet->remote_address = remote_address;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE, (const char *)packet, MAVLINK_MSG_ID_UWB_RANGE_LEN, MAVLINK_MSG_ID_UWB_RANGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE, (const char *)packet, MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UWB_RANGE UNPACKING


/**
 * @brief Get field address from uwb_range message
 *
 * @return Address of UWB unit.
 */
static inline uint8_t mavlink_msg_uwb_range_get_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field remote_address from uwb_range message
 *
 * @return Address of remote UWB unit that was used as an anchor.
 */
static inline uint8_t mavlink_msg_uwb_range_get_remote_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field stamp_us from uwb_range message
 *
 * @return Timestamp of measurement in microseconds.
 */
static inline uint32_t mavlink_msg_uwb_range_get_stamp_us(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field round_trip_time from uwb_range message
 *
 * @return Round trip time in nanoseconds.
 */
static inline float mavlink_msg_uwb_range_get_round_trip_time(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field range from uwb_range message
 *
 * @return Range.
 */
static inline float mavlink_msg_uwb_range_get_range(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a uwb_range message into a struct
 *
 * @param msg The message to decode
 * @param uwb_range C-struct to decode the message contents into
 */
static inline void mavlink_msg_uwb_range_decode(const mavlink_message_t* msg, mavlink_uwb_range_t* uwb_range)
{
#if MAVLINK_NEED_BYTE_SWAP
	uwb_range->stamp_us = mavlink_msg_uwb_range_get_stamp_us(msg);
	uwb_range->round_trip_time = mavlink_msg_uwb_range_get_round_trip_time(msg);
	uwb_range->range = mavlink_msg_uwb_range_get_range(msg);
	uwb_range->address = mavlink_msg_uwb_range_get_address(msg);
	uwb_range->remote_address = mavlink_msg_uwb_range_get_remote_address(msg);
#else
	memcpy(uwb_range, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UWB_RANGE_LEN);
#endif
}
