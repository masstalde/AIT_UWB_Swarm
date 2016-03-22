// MESSAGE UWB_RANGE_BATCH_2 PACKING

#define MAVLINK_MSG_ID_UWB_RANGE_BATCH_2 212

typedef struct __mavlink_uwb_range_batch_2_t
{
 float range[2]; /*< Ranges.*/
 uint8_t addresses[2]; /*< Addresses of UWB units.*/
 uint8_t remote_address; /*< Address of remote UWB unit that was used as an anchor.*/
} mavlink_uwb_range_batch_2_t;

#define MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN 11
#define MAVLINK_MSG_ID_212_LEN 11

#define MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_CRC 211
#define MAVLINK_MSG_ID_212_CRC 211

#define MAVLINK_MSG_UWB_RANGE_BATCH_2_FIELD_RANGE_LEN 2
#define MAVLINK_MSG_UWB_RANGE_BATCH_2_FIELD_ADDRESSES_LEN 2

#define MAVLINK_MESSAGE_INFO_UWB_RANGE_BATCH_2 { \
	"UWB_RANGE_BATCH_2", \
	3, \
	{  { "range", NULL, MAVLINK_TYPE_FLOAT, 2, 0, offsetof(mavlink_uwb_range_batch_2_t, range) }, \
         { "addresses", NULL, MAVLINK_TYPE_UINT8_T, 2, 8, offsetof(mavlink_uwb_range_batch_2_t, addresses) }, \
         { "remote_address", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_uwb_range_batch_2_t, remote_address) }, \
         } \
}


/**
 * @brief Pack a uwb_range_batch_2 message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addresses Addresses of UWB units.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param range Ranges.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_range_batch_2_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       const uint8_t *addresses, uint8_t remote_address, const float *range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN];
	_mav_put_uint8_t(buf, 10, remote_address);
	_mav_put_float_array(buf, 0, range, 2);
	_mav_put_uint8_t_array(buf, 8, addresses, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#else
	mavlink_uwb_range_batch_2_t packet;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.range, range, sizeof(float)*2);
	mav_array_memcpy(packet.addresses, addresses, sizeof(uint8_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_RANGE_BATCH_2;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif
}

/**
 * @brief Pack a uwb_range_batch_2 message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addresses Addresses of UWB units.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param range Ranges.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_range_batch_2_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           const uint8_t *addresses,uint8_t remote_address,const float *range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN];
	_mav_put_uint8_t(buf, 10, remote_address);
	_mav_put_float_array(buf, 0, range, 2);
	_mav_put_uint8_t_array(buf, 8, addresses, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#else
	mavlink_uwb_range_batch_2_t packet;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.range, range, sizeof(float)*2);
	mav_array_memcpy(packet.addresses, addresses, sizeof(uint8_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_RANGE_BATCH_2;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif
}

/**
 * @brief Encode a uwb_range_batch_2 struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param uwb_range_batch_2 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_range_batch_2_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_uwb_range_batch_2_t* uwb_range_batch_2)
{
	return mavlink_msg_uwb_range_batch_2_pack(system_id, component_id, msg, uwb_range_batch_2->addresses, uwb_range_batch_2->remote_address, uwb_range_batch_2->range);
}

/**
 * @brief Encode a uwb_range_batch_2 struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uwb_range_batch_2 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_range_batch_2_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_uwb_range_batch_2_t* uwb_range_batch_2)
{
	return mavlink_msg_uwb_range_batch_2_pack_chan(system_id, component_id, chan, msg, uwb_range_batch_2->addresses, uwb_range_batch_2->remote_address, uwb_range_batch_2->range);
}

/**
 * @brief Send a uwb_range_batch_2 message
 * @param chan MAVLink channel to send the message
 *
 * @param addresses Addresses of UWB units.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param range Ranges.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_uwb_range_batch_2_send(mavlink_channel_t chan, const uint8_t *addresses, uint8_t remote_address, const float *range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN];
	_mav_put_uint8_t(buf, 10, remote_address);
	_mav_put_float_array(buf, 0, range, 2);
	_mav_put_uint8_t_array(buf, 8, addresses, 2);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2, buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2, buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif
#else
	mavlink_uwb_range_batch_2_t packet;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.range, range, sizeof(float)*2);
	mav_array_memcpy(packet.addresses, addresses, sizeof(uint8_t)*2);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2, (const char *)&packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2, (const char *)&packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_uwb_range_batch_2_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addresses, uint8_t remote_address, const float *range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 10, remote_address);
	_mav_put_float_array(buf, 0, range, 2);
	_mav_put_uint8_t_array(buf, 8, addresses, 2);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2, buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2, buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif
#else
	mavlink_uwb_range_batch_2_t *packet = (mavlink_uwb_range_batch_2_t *)msgbuf;
	packet->remote_address = remote_address;
	mav_array_memcpy(packet->range, range, sizeof(float)*2);
	mav_array_memcpy(packet->addresses, addresses, sizeof(uint8_t)*2);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2, (const char *)packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2, (const char *)packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UWB_RANGE_BATCH_2 UNPACKING


/**
 * @brief Get field addresses from uwb_range_batch_2 message
 *
 * @return Addresses of UWB units.
 */
static inline uint16_t mavlink_msg_uwb_range_batch_2_get_addresses(const mavlink_message_t* msg, uint8_t *addresses)
{
	return _MAV_RETURN_uint8_t_array(msg, addresses, 2,  8);
}

/**
 * @brief Get field remote_address from uwb_range_batch_2 message
 *
 * @return Address of remote UWB unit that was used as an anchor.
 */
static inline uint8_t mavlink_msg_uwb_range_batch_2_get_remote_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field range from uwb_range_batch_2 message
 *
 * @return Ranges.
 */
static inline uint16_t mavlink_msg_uwb_range_batch_2_get_range(const mavlink_message_t* msg, float *range)
{
	return _MAV_RETURN_float_array(msg, range, 2,  0);
}

/**
 * @brief Decode a uwb_range_batch_2 message into a struct
 *
 * @param msg The message to decode
 * @param uwb_range_batch_2 C-struct to decode the message contents into
 */
static inline void mavlink_msg_uwb_range_batch_2_decode(const mavlink_message_t* msg, mavlink_uwb_range_batch_2_t* uwb_range_batch_2)
{
#if MAVLINK_NEED_BYTE_SWAP
	mavlink_msg_uwb_range_batch_2_get_range(msg, uwb_range_batch_2->range);
	mavlink_msg_uwb_range_batch_2_get_addresses(msg, uwb_range_batch_2->addresses);
	uwb_range_batch_2->remote_address = mavlink_msg_uwb_range_batch_2_get_remote_address(msg);
#else
	memcpy(uwb_range_batch_2, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UWB_RANGE_BATCH_2_LEN);
#endif
}
