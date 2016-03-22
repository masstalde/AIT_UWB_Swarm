// MESSAGE UWB_PROTOTYPING PACKING

#define MAVLINK_MSG_ID_UWB_PROTOTYPING 195

typedef struct __mavlink_uwb_prototyping_t
{
 uint64_t integers[10]; /*< Arbitrary integer values.*/
 float floats[10]; /*< Arbitrary float values.*/
 uint8_t type; /*< Message type description.*/
} mavlink_uwb_prototyping_t;

#define MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN 121
#define MAVLINK_MSG_ID_195_LEN 121

#define MAVLINK_MSG_ID_UWB_PROTOTYPING_CRC 71
#define MAVLINK_MSG_ID_195_CRC 71

#define MAVLINK_MSG_UWB_PROTOTYPING_FIELD_INTEGERS_LEN 10
#define MAVLINK_MSG_UWB_PROTOTYPING_FIELD_FLOATS_LEN 10

#define MAVLINK_MESSAGE_INFO_UWB_PROTOTYPING { \
	"UWB_PROTOTYPING", \
	3, \
	{  { "integers", NULL, MAVLINK_TYPE_UINT64_T, 10, 0, offsetof(mavlink_uwb_prototyping_t, integers) }, \
         { "floats", NULL, MAVLINK_TYPE_FLOAT, 10, 80, offsetof(mavlink_uwb_prototyping_t, floats) }, \
         { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 120, offsetof(mavlink_uwb_prototyping_t, type) }, \
         } \
}


/**
 * @brief Pack a uwb_prototyping message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param type Message type description.
 * @param integers Arbitrary integer values.
 * @param floats Arbitrary float values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_prototyping_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t type, const uint64_t *integers, const float *floats)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN];
	_mav_put_uint8_t(buf, 120, type);
	_mav_put_uint64_t_array(buf, 0, integers, 10);
	_mav_put_float_array(buf, 80, floats, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#else
	mavlink_uwb_prototyping_t packet;
	packet.type = type;
	mav_array_memcpy(packet.integers, integers, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.floats, floats, sizeof(float)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_PROTOTYPING;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN, MAVLINK_MSG_ID_UWB_PROTOTYPING_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif
}

/**
 * @brief Pack a uwb_prototyping message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param type Message type description.
 * @param integers Arbitrary integer values.
 * @param floats Arbitrary float values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_prototyping_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t type,const uint64_t *integers,const float *floats)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN];
	_mav_put_uint8_t(buf, 120, type);
	_mav_put_uint64_t_array(buf, 0, integers, 10);
	_mav_put_float_array(buf, 80, floats, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#else
	mavlink_uwb_prototyping_t packet;
	packet.type = type;
	mav_array_memcpy(packet.integers, integers, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.floats, floats, sizeof(float)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_PROTOTYPING;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN, MAVLINK_MSG_ID_UWB_PROTOTYPING_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif
}

/**
 * @brief Encode a uwb_prototyping struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param uwb_prototyping C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_prototyping_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_uwb_prototyping_t* uwb_prototyping)
{
	return mavlink_msg_uwb_prototyping_pack(system_id, component_id, msg, uwb_prototyping->type, uwb_prototyping->integers, uwb_prototyping->floats);
}

/**
 * @brief Encode a uwb_prototyping struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uwb_prototyping C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_prototyping_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_uwb_prototyping_t* uwb_prototyping)
{
	return mavlink_msg_uwb_prototyping_pack_chan(system_id, component_id, chan, msg, uwb_prototyping->type, uwb_prototyping->integers, uwb_prototyping->floats);
}

/**
 * @brief Send a uwb_prototyping message
 * @param chan MAVLink channel to send the message
 *
 * @param type Message type description.
 * @param integers Arbitrary integer values.
 * @param floats Arbitrary float values.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_uwb_prototyping_send(mavlink_channel_t chan, uint8_t type, const uint64_t *integers, const float *floats)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN];
	_mav_put_uint8_t(buf, 120, type);
	_mav_put_uint64_t_array(buf, 0, integers, 10);
	_mav_put_float_array(buf, 80, floats, 10);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_PROTOTYPING, buf, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN, MAVLINK_MSG_ID_UWB_PROTOTYPING_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_PROTOTYPING, buf, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif
#else
	mavlink_uwb_prototyping_t packet;
	packet.type = type;
	mav_array_memcpy(packet.integers, integers, sizeof(uint64_t)*10);
	mav_array_memcpy(packet.floats, floats, sizeof(float)*10);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_PROTOTYPING, (const char *)&packet, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN, MAVLINK_MSG_ID_UWB_PROTOTYPING_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_PROTOTYPING, (const char *)&packet, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_uwb_prototyping_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t type, const uint64_t *integers, const float *floats)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 120, type);
	_mav_put_uint64_t_array(buf, 0, integers, 10);
	_mav_put_float_array(buf, 80, floats, 10);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_PROTOTYPING, buf, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN, MAVLINK_MSG_ID_UWB_PROTOTYPING_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_PROTOTYPING, buf, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif
#else
	mavlink_uwb_prototyping_t *packet = (mavlink_uwb_prototyping_t *)msgbuf;
	packet->type = type;
	mav_array_memcpy(packet->integers, integers, sizeof(uint64_t)*10);
	mav_array_memcpy(packet->floats, floats, sizeof(float)*10);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_PROTOTYPING, (const char *)packet, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN, MAVLINK_MSG_ID_UWB_PROTOTYPING_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_PROTOTYPING, (const char *)packet, MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UWB_PROTOTYPING UNPACKING


/**
 * @brief Get field type from uwb_prototyping message
 *
 * @return Message type description.
 */
static inline uint8_t mavlink_msg_uwb_prototyping_get_type(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  120);
}

/**
 * @brief Get field integers from uwb_prototyping message
 *
 * @return Arbitrary integer values.
 */
static inline uint16_t mavlink_msg_uwb_prototyping_get_integers(const mavlink_message_t* msg, uint64_t *integers)
{
	return _MAV_RETURN_uint64_t_array(msg, integers, 10,  0);
}

/**
 * @brief Get field floats from uwb_prototyping message
 *
 * @return Arbitrary float values.
 */
static inline uint16_t mavlink_msg_uwb_prototyping_get_floats(const mavlink_message_t* msg, float *floats)
{
	return _MAV_RETURN_float_array(msg, floats, 10,  80);
}

/**
 * @brief Decode a uwb_prototyping message into a struct
 *
 * @param msg The message to decode
 * @param uwb_prototyping C-struct to decode the message contents into
 */
static inline void mavlink_msg_uwb_prototyping_decode(const mavlink_message_t* msg, mavlink_uwb_prototyping_t* uwb_prototyping)
{
#if MAVLINK_NEED_BYTE_SWAP
	mavlink_msg_uwb_prototyping_get_integers(msg, uwb_prototyping->integers);
	mavlink_msg_uwb_prototyping_get_floats(msg, uwb_prototyping->floats);
	uwb_prototyping->type = mavlink_msg_uwb_prototyping_get_type(msg);
#else
	memcpy(uwb_prototyping, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UWB_PROTOTYPING_LEN);
#endif
}
