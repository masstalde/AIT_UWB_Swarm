// MESSAGE UWB_ERROR PACKING

#define MAVLINK_MSG_ID_UWB_ERROR 191

typedef struct __mavlink_uwb_error_t
{
 uint8_t address; /*< Address of UWB tracker.*/
 uint8_t type; /*< Error type.*/
 char description[127]; /*< Error description.*/
} mavlink_uwb_error_t;

#define MAVLINK_MSG_ID_UWB_ERROR_LEN 129
#define MAVLINK_MSG_ID_191_LEN 129

#define MAVLINK_MSG_ID_UWB_ERROR_CRC 223
#define MAVLINK_MSG_ID_191_CRC 223

#define MAVLINK_MSG_UWB_ERROR_FIELD_DESCRIPTION_LEN 127

#define MAVLINK_MESSAGE_INFO_UWB_ERROR { \
	"UWB_ERROR", \
	3, \
	{  { "address", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_uwb_error_t, address) }, \
         { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_uwb_error_t, type) }, \
         { "description", NULL, MAVLINK_TYPE_CHAR, 127, 2, offsetof(mavlink_uwb_error_t, description) }, \
         } \
}


/**
 * @brief Pack a uwb_error message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param address Address of UWB tracker.
 * @param type Error type.
 * @param description Error description.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_error_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t address, uint8_t type, const char *description)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_ERROR_LEN];
	_mav_put_uint8_t(buf, 0, address);
	_mav_put_uint8_t(buf, 1, type);
	_mav_put_char_array(buf, 2, description, 127);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#else
	mavlink_uwb_error_t packet;
	packet.address = address;
	packet.type = type;
	mav_array_memcpy(packet.description, description, sizeof(char)*127);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_ERROR;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_ERROR_LEN, MAVLINK_MSG_ID_UWB_ERROR_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif
}

/**
 * @brief Pack a uwb_error message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param address Address of UWB tracker.
 * @param type Error type.
 * @param description Error description.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_error_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t address,uint8_t type,const char *description)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_ERROR_LEN];
	_mav_put_uint8_t(buf, 0, address);
	_mav_put_uint8_t(buf, 1, type);
	_mav_put_char_array(buf, 2, description, 127);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#else
	mavlink_uwb_error_t packet;
	packet.address = address;
	packet.type = type;
	mav_array_memcpy(packet.description, description, sizeof(char)*127);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_ERROR;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_ERROR_LEN, MAVLINK_MSG_ID_UWB_ERROR_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif
}

/**
 * @brief Encode a uwb_error struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param uwb_error C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_error_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_uwb_error_t* uwb_error)
{
	return mavlink_msg_uwb_error_pack(system_id, component_id, msg, uwb_error->address, uwb_error->type, uwb_error->description);
}

/**
 * @brief Encode a uwb_error struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uwb_error C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_error_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_uwb_error_t* uwb_error)
{
	return mavlink_msg_uwb_error_pack_chan(system_id, component_id, chan, msg, uwb_error->address, uwb_error->type, uwb_error->description);
}

/**
 * @brief Send a uwb_error message
 * @param chan MAVLink channel to send the message
 *
 * @param address Address of UWB tracker.
 * @param type Error type.
 * @param description Error description.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_uwb_error_send(mavlink_channel_t chan, uint8_t address, uint8_t type, const char *description)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_ERROR_LEN];
	_mav_put_uint8_t(buf, 0, address);
	_mav_put_uint8_t(buf, 1, type);
	_mav_put_char_array(buf, 2, description, 127);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_ERROR, buf, MAVLINK_MSG_ID_UWB_ERROR_LEN, MAVLINK_MSG_ID_UWB_ERROR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_ERROR, buf, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif
#else
	mavlink_uwb_error_t packet;
	packet.address = address;
	packet.type = type;
	mav_array_memcpy(packet.description, description, sizeof(char)*127);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_ERROR, (const char *)&packet, MAVLINK_MSG_ID_UWB_ERROR_LEN, MAVLINK_MSG_ID_UWB_ERROR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_ERROR, (const char *)&packet, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UWB_ERROR_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_uwb_error_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t address, uint8_t type, const char *description)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, address);
	_mav_put_uint8_t(buf, 1, type);
	_mav_put_char_array(buf, 2, description, 127);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_ERROR, buf, MAVLINK_MSG_ID_UWB_ERROR_LEN, MAVLINK_MSG_ID_UWB_ERROR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_ERROR, buf, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif
#else
	mavlink_uwb_error_t *packet = (mavlink_uwb_error_t *)msgbuf;
	packet->address = address;
	packet->type = type;
	mav_array_memcpy(packet->description, description, sizeof(char)*127);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_ERROR, (const char *)packet, MAVLINK_MSG_ID_UWB_ERROR_LEN, MAVLINK_MSG_ID_UWB_ERROR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_ERROR, (const char *)packet, MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UWB_ERROR UNPACKING


/**
 * @brief Get field address from uwb_error message
 *
 * @return Address of UWB tracker.
 */
static inline uint8_t mavlink_msg_uwb_error_get_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field type from uwb_error message
 *
 * @return Error type.
 */
static inline uint8_t mavlink_msg_uwb_error_get_type(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field description from uwb_error message
 *
 * @return Error description.
 */
static inline uint16_t mavlink_msg_uwb_error_get_description(const mavlink_message_t* msg, char *description)
{
	return _MAV_RETURN_char_array(msg, description, 127,  2);
}

/**
 * @brief Decode a uwb_error message into a struct
 *
 * @param msg The message to decode
 * @param uwb_error C-struct to decode the message contents into
 */
static inline void mavlink_msg_uwb_error_decode(const mavlink_message_t* msg, mavlink_uwb_error_t* uwb_error)
{
#if MAVLINK_NEED_BYTE_SWAP
	uwb_error->address = mavlink_msg_uwb_error_get_address(msg);
	uwb_error->type = mavlink_msg_uwb_error_get_type(msg);
	mavlink_msg_uwb_error_get_description(msg, uwb_error->description);
#else
	memcpy(uwb_error, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UWB_ERROR_LEN);
#endif
}

