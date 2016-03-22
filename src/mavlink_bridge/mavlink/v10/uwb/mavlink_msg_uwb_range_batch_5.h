// MESSAGE UWB_RANGE_BATCH_5 PACKING

#define MAVLINK_MSG_ID_UWB_RANGE_BATCH_5 215

typedef struct __mavlink_uwb_range_batch_5_t
{
 float range[5]; /*< Ranges.*/
 uint8_t addresses[5]; /*< Addresses of UWB units.*/
 uint8_t remote_address; /*< Address of remote UWB unit that was used as an anchor.*/
} mavlink_uwb_range_batch_5_t;

#define MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN 26
#define MAVLINK_MSG_ID_215_LEN 26

#define MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_CRC 249
#define MAVLINK_MSG_ID_215_CRC 249

#define MAVLINK_MSG_UWB_RANGE_BATCH_5_FIELD_RANGE_LEN 5
#define MAVLINK_MSG_UWB_RANGE_BATCH_5_FIELD_ADDRESSES_LEN 5

#define MAVLINK_MESSAGE_INFO_UWB_RANGE_BATCH_5 { \
	"UWB_RANGE_BATCH_5", \
	3, \
	{  { "range", NULL, MAVLINK_TYPE_FLOAT, 5, 0, offsetof(mavlink_uwb_range_batch_5_t, range) }, \
         { "addresses", NULL, MAVLINK_TYPE_UINT8_T, 5, 20, offsetof(mavlink_uwb_range_batch_5_t, addresses) }, \
         { "remote_address", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_uwb_range_batch_5_t, remote_address) }, \
         } \
}


/**
 * @brief Pack a uwb_range_batch_5 message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addresses Addresses of UWB units.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param range Ranges.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_range_batch_5_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       const uint8_t *addresses, uint8_t remote_address, const float *range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN];
	_mav_put_uint8_t(buf, 25, remote_address);
	_mav_put_float_array(buf, 0, range, 5);
	_mav_put_uint8_t_array(buf, 20, addresses, 5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#else
	mavlink_uwb_range_batch_5_t packet;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.range, range, sizeof(float)*5);
	mav_array_memcpy(packet.addresses, addresses, sizeof(uint8_t)*5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_RANGE_BATCH_5;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif
}

/**
 * @brief Pack a uwb_range_batch_5 message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addresses Addresses of UWB units.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param range Ranges.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_range_batch_5_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           const uint8_t *addresses,uint8_t remote_address,const float *range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN];
	_mav_put_uint8_t(buf, 25, remote_address);
	_mav_put_float_array(buf, 0, range, 5);
	_mav_put_uint8_t_array(buf, 20, addresses, 5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#else
	mavlink_uwb_range_batch_5_t packet;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.range, range, sizeof(float)*5);
	mav_array_memcpy(packet.addresses, addresses, sizeof(uint8_t)*5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_RANGE_BATCH_5;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif
}

/**
 * @brief Encode a uwb_range_batch_5 struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param uwb_range_batch_5 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_range_batch_5_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_uwb_range_batch_5_t* uwb_range_batch_5)
{
	return mavlink_msg_uwb_range_batch_5_pack(system_id, component_id, msg, uwb_range_batch_5->addresses, uwb_range_batch_5->remote_address, uwb_range_batch_5->range);
}

/**
 * @brief Encode a uwb_range_batch_5 struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uwb_range_batch_5 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_range_batch_5_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_uwb_range_batch_5_t* uwb_range_batch_5)
{
	return mavlink_msg_uwb_range_batch_5_pack_chan(system_id, component_id, chan, msg, uwb_range_batch_5->addresses, uwb_range_batch_5->remote_address, uwb_range_batch_5->range);
}

/**
 * @brief Send a uwb_range_batch_5 message
 * @param chan MAVLink channel to send the message
 *
 * @param addresses Addresses of UWB units.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param range Ranges.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_uwb_range_batch_5_send(mavlink_channel_t chan, const uint8_t *addresses, uint8_t remote_address, const float *range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN];
	_mav_put_uint8_t(buf, 25, remote_address);
	_mav_put_float_array(buf, 0, range, 5);
	_mav_put_uint8_t_array(buf, 20, addresses, 5);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5, buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5, buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif
#else
	mavlink_uwb_range_batch_5_t packet;
	packet.remote_address = remote_address;
	mav_array_memcpy(packet.range, range, sizeof(float)*5);
	mav_array_memcpy(packet.addresses, addresses, sizeof(uint8_t)*5);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5, (const char *)&packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5, (const char *)&packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_uwb_range_batch_5_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addresses, uint8_t remote_address, const float *range)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 25, remote_address);
	_mav_put_float_array(buf, 0, range, 5);
	_mav_put_uint8_t_array(buf, 20, addresses, 5);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5, buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5, buf, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif
#else
	mavlink_uwb_range_batch_5_t *packet = (mavlink_uwb_range_batch_5_t *)msgbuf;
	packet->remote_address = remote_address;
	mav_array_memcpy(packet->range, range, sizeof(float)*5);
	mav_array_memcpy(packet->addresses, addresses, sizeof(uint8_t)*5);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5, (const char *)packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5, (const char *)packet, MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UWB_RANGE_BATCH_5 UNPACKING


/**
 * @brief Get field addresses from uwb_range_batch_5 message
 *
 * @return Addresses of UWB units.
 */
static inline uint16_t mavlink_msg_uwb_range_batch_5_get_addresses(const mavlink_message_t* msg, uint8_t *addresses)
{
	return _MAV_RETURN_uint8_t_array(msg, addresses, 5,  20);
}

/**
 * @brief Get field remote_address from uwb_range_batch_5 message
 *
 * @return Address of remote UWB unit that was used as an anchor.
 */
static inline uint8_t mavlink_msg_uwb_range_batch_5_get_remote_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  25);
}

/**
 * @brief Get field range from uwb_range_batch_5 message
 *
 * @return Ranges.
 */
static inline uint16_t mavlink_msg_uwb_range_batch_5_get_range(const mavlink_message_t* msg, float *range)
{
	return _MAV_RETURN_float_array(msg, range, 5,  0);
}

/**
 * @brief Decode a uwb_range_batch_5 message into a struct
 *
 * @param msg The message to decode
 * @param uwb_range_batch_5 C-struct to decode the message contents into
 */
static inline void mavlink_msg_uwb_range_batch_5_decode(const mavlink_message_t* msg, mavlink_uwb_range_batch_5_t* uwb_range_batch_5)
{
#if MAVLINK_NEED_BYTE_SWAP
	mavlink_msg_uwb_range_batch_5_get_range(msg, uwb_range_batch_5->range);
	mavlink_msg_uwb_range_batch_5_get_addresses(msg, uwb_range_batch_5->addresses);
	uwb_range_batch_5->remote_address = mavlink_msg_uwb_range_batch_5_get_remote_address(msg);
#else
	memcpy(uwb_range_batch_5, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UWB_RANGE_BATCH_5_LEN);
#endif
}
