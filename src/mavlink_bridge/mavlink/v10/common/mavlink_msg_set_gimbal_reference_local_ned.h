// MESSAGE SET_GIMBAL_REFERENCE_LOCAL_NED PACKING

#define MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED 94

typedef struct __mavlink_set_gimbal_reference_local_ned_t
{
 float roll; /*< Roll reference in local NED frame*/
 float pitch; /*< Pitch reference in local NED frame*/
 float yaw; /*< Yaw reference in local NED frame*/
 uint8_t gimbal_mode; /*< Mode in which gimbal is working*/
} mavlink_set_gimbal_reference_local_ned_t;

#define MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN 13
#define MAVLINK_MSG_ID_94_LEN 13

#define MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_CRC 57
#define MAVLINK_MSG_ID_94_CRC 57



#define MAVLINK_MESSAGE_INFO_SET_GIMBAL_REFERENCE_LOCAL_NED { \
	"SET_GIMBAL_REFERENCE_LOCAL_NED", \
	4, \
	{  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_gimbal_reference_local_ned_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_set_gimbal_reference_local_ned_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_set_gimbal_reference_local_ned_t, yaw) }, \
         { "gimbal_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_set_gimbal_reference_local_ned_t, gimbal_mode) }, \
         } \
}


/**
 * @brief Pack a set_gimbal_reference_local_ned message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll Roll reference in local NED frame
 * @param pitch Pitch reference in local NED frame
 * @param yaw Yaw reference in local NED frame
 * @param gimbal_mode Mode in which gimbal is working
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_gimbal_reference_local_ned_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float roll, float pitch, float yaw, uint8_t gimbal_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN];
	_mav_put_float(buf, 0, roll);
	_mav_put_float(buf, 4, pitch);
	_mav_put_float(buf, 8, yaw);
	_mav_put_uint8_t(buf, 12, gimbal_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#else
	mavlink_set_gimbal_reference_local_ned_t packet;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.gimbal_mode = gimbal_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif
}

/**
 * @brief Pack a set_gimbal_reference_local_ned message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll Roll reference in local NED frame
 * @param pitch Pitch reference in local NED frame
 * @param yaw Yaw reference in local NED frame
 * @param gimbal_mode Mode in which gimbal is working
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_gimbal_reference_local_ned_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float roll,float pitch,float yaw,uint8_t gimbal_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN];
	_mav_put_float(buf, 0, roll);
	_mav_put_float(buf, 4, pitch);
	_mav_put_float(buf, 8, yaw);
	_mav_put_uint8_t(buf, 12, gimbal_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#else
	mavlink_set_gimbal_reference_local_ned_t packet;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.gimbal_mode = gimbal_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif
}

/**
 * @brief Encode a set_gimbal_reference_local_ned struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_gimbal_reference_local_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_gimbal_reference_local_ned_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_gimbal_reference_local_ned_t* set_gimbal_reference_local_ned)
{
	return mavlink_msg_set_gimbal_reference_local_ned_pack(system_id, component_id, msg, set_gimbal_reference_local_ned->roll, set_gimbal_reference_local_ned->pitch, set_gimbal_reference_local_ned->yaw, set_gimbal_reference_local_ned->gimbal_mode);
}

/**
 * @brief Encode a set_gimbal_reference_local_ned struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_gimbal_reference_local_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_gimbal_reference_local_ned_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_gimbal_reference_local_ned_t* set_gimbal_reference_local_ned)
{
	return mavlink_msg_set_gimbal_reference_local_ned_pack_chan(system_id, component_id, chan, msg, set_gimbal_reference_local_ned->roll, set_gimbal_reference_local_ned->pitch, set_gimbal_reference_local_ned->yaw, set_gimbal_reference_local_ned->gimbal_mode);
}

/**
 * @brief Send a set_gimbal_reference_local_ned message
 * @param chan MAVLink channel to send the message
 *
 * @param roll Roll reference in local NED frame
 * @param pitch Pitch reference in local NED frame
 * @param yaw Yaw reference in local NED frame
 * @param gimbal_mode Mode in which gimbal is working
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_gimbal_reference_local_ned_send(mavlink_channel_t chan, float roll, float pitch, float yaw, uint8_t gimbal_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN];
	_mav_put_float(buf, 0, roll);
	_mav_put_float(buf, 4, pitch);
	_mav_put_float(buf, 8, yaw);
	_mav_put_uint8_t(buf, 12, gimbal_mode);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED, buf, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED, buf, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif
#else
	mavlink_set_gimbal_reference_local_ned_t packet;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.gimbal_mode = gimbal_mode;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED, (const char *)&packet, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED, (const char *)&packet, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_gimbal_reference_local_ned_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll, float pitch, float yaw, uint8_t gimbal_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, roll);
	_mav_put_float(buf, 4, pitch);
	_mav_put_float(buf, 8, yaw);
	_mav_put_uint8_t(buf, 12, gimbal_mode);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED, buf, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED, buf, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif
#else
	mavlink_set_gimbal_reference_local_ned_t *packet = (mavlink_set_gimbal_reference_local_ned_t *)msgbuf;
	packet->roll = roll;
	packet->pitch = pitch;
	packet->yaw = yaw;
	packet->gimbal_mode = gimbal_mode;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED, (const char *)packet, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED, (const char *)packet, MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE SET_GIMBAL_REFERENCE_LOCAL_NED UNPACKING


/**
 * @brief Get field roll from set_gimbal_reference_local_ned message
 *
 * @return Roll reference in local NED frame
 */
static inline float mavlink_msg_set_gimbal_reference_local_ned_get_roll(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch from set_gimbal_reference_local_ned message
 *
 * @return Pitch reference in local NED frame
 */
static inline float mavlink_msg_set_gimbal_reference_local_ned_get_pitch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field yaw from set_gimbal_reference_local_ned message
 *
 * @return Yaw reference in local NED frame
 */
static inline float mavlink_msg_set_gimbal_reference_local_ned_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field gimbal_mode from set_gimbal_reference_local_ned message
 *
 * @return Mode in which gimbal is working
 */
static inline uint8_t mavlink_msg_set_gimbal_reference_local_ned_get_gimbal_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Decode a set_gimbal_reference_local_ned message into a struct
 *
 * @param msg The message to decode
 * @param set_gimbal_reference_local_ned C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_gimbal_reference_local_ned_decode(const mavlink_message_t* msg, mavlink_set_gimbal_reference_local_ned_t* set_gimbal_reference_local_ned)
{
#if MAVLINK_NEED_BYTE_SWAP
	set_gimbal_reference_local_ned->roll = mavlink_msg_set_gimbal_reference_local_ned_get_roll(msg);
	set_gimbal_reference_local_ned->pitch = mavlink_msg_set_gimbal_reference_local_ned_get_pitch(msg);
	set_gimbal_reference_local_ned->yaw = mavlink_msg_set_gimbal_reference_local_ned_get_yaw(msg);
	set_gimbal_reference_local_ned->gimbal_mode = mavlink_msg_set_gimbal_reference_local_ned_get_gimbal_mode(msg);
#else
	memcpy(set_gimbal_reference_local_ned, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_SET_GIMBAL_REFERENCE_LOCAL_NED_LEN);
#endif
}
