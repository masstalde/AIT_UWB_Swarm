// MESSAGE UWB_STATUS PACKING

#define MAVLINK_MSG_ID_UWB_STATUS 190

typedef struct __mavlink_uwb_status_t
{
 uint8_t address; /*< Address of UWB tracker.*/
 char description[127]; /*< Status description.*/
} mavlink_uwb_status_t;

#define MAVLINK_MSG_ID_UWB_STATUS_LEN 128
#define MAVLINK_MSG_ID_190_LEN 128

#define MAVLINK_MSG_ID_UWB_STATUS_CRC 234
#define MAVLINK_MSG_ID_190_CRC 234

#define MAVLINK_MSG_UWB_STATUS_FIELD_DESCRIPTION_LEN 127

#define MAVLINK_MESSAGE_INFO_UWB_STATUS { \
	"UWB_STATUS", \
	2, \
	{  { "address", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_uwb_status_t, address) }, \
         { "description", NULL, MAVLINK_TYPE_CHAR, 127, 1, offsetof(mavlink_uwb_status_t, description) }, \
         } \
}


/**
 * @brief Pack a uwb_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param address Address of UWB tracker.
 * @param description Status description.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t address, const char *description)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, address);
	_mav_put_char_array(buf, 1, description, 127);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#else
	mavlink_uwb_status_t packet;
	packet.address = address;
	mav_array_memcpy(packet.description, description, sizeof(char)*127);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_STATUS_LEN, MAVLINK_MSG_ID_UWB_STATUS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif
}

/**
 * @brief Pack a uwb_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param address Address of UWB tracker.
 * @param description Status description.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t address,const char *description)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, address);
	_mav_put_char_array(buf, 1, description, 127);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#else
	mavlink_uwb_status_t packet;
	packet.address = address;
	mav_array_memcpy(packet.description, description, sizeof(char)*127);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_STATUS_LEN, MAVLINK_MSG_ID_UWB_STATUS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif
}

/**
 * @brief Encode a uwb_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param uwb_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_uwb_status_t* uwb_status)
{
	return mavlink_msg_uwb_status_pack(system_id, component_id, msg, uwb_status->address, uwb_status->description);
}

/**
 * @brief Encode a uwb_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uwb_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_uwb_status_t* uwb_status)
{
	return mavlink_msg_uwb_status_pack_chan(system_id, component_id, chan, msg, uwb_status->address, uwb_status->description);
}

/**
 * @brief Send a uwb_status message
 * @param chan MAVLink channel to send the message
 *
 * @param address Address of UWB tracker.
 * @param description Status description.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_uwb_status_send(mavlink_channel_t chan, uint8_t address, const char *description)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, address);
	_mav_put_char_array(buf, 1, description, 127);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_STATUS, buf, MAVLINK_MSG_ID_UWB_STATUS_LEN, MAVLINK_MSG_ID_UWB_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_STATUS, buf, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif
#else
	mavlink_uwb_status_t packet;
	packet.address = address;
	mav_array_memcpy(packet.description, description, sizeof(char)*127);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_STATUS, (const char *)&packet, MAVLINK_MSG_ID_UWB_STATUS_LEN, MAVLINK_MSG_ID_UWB_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_STATUS, (const char *)&packet, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UWB_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_uwb_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t address, const char *description)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, address);
	_mav_put_char_array(buf, 1, description, 127);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_STATUS, buf, MAVLINK_MSG_ID_UWB_STATUS_LEN, MAVLINK_MSG_ID_UWB_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_STATUS, buf, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif
#else
	mavlink_uwb_status_t *packet = (mavlink_uwb_status_t *)msgbuf;
	packet->address = address;
	mav_array_memcpy(packet->description, description, sizeof(char)*127);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_STATUS, (const char *)packet, MAVLINK_MSG_ID_UWB_STATUS_LEN, MAVLINK_MSG_ID_UWB_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_STATUS, (const char *)packet, MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UWB_STATUS UNPACKING


/**
 * @brief Get field address from uwb_status message
 *
 * @return Address of UWB tracker.
 */
static inline uint8_t mavlink_msg_uwb_status_get_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field description from uwb_status message
 *
 * @return Status description.
 */
static inline uint16_t mavlink_msg_uwb_status_get_description(const mavlink_message_t* msg, char *description)
{
	return _MAV_RETURN_char_array(msg, description, 127,  1);
}

/**
 * @brief Decode a uwb_status message into a struct
 *
 * @param msg The message to decode
 * @param uwb_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_uwb_status_decode(const mavlink_message_t* msg, mavlink_uwb_status_t* uwb_status)
{
#if MAVLINK_NEED_BYTE_SWAP
	uwb_status->address = mavlink_msg_uwb_status_get_address(msg);
	mavlink_msg_uwb_status_get_description(msg, uwb_status->description);
#else
	memcpy(uwb_status, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UWB_STATUS_LEN);
#endif
}

