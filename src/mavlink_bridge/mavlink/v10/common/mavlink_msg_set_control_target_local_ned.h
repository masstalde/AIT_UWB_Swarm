// MESSAGE SET_CONTROL_TARGET_LOCAL_NED PACKING

#define MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED 93

typedef struct __mavlink_set_control_target_local_ned_t
{
 float x; /*< X reference in NED frame in meters, meters / s, meters / s^2 or N*/
 float y; /*< Y reference in NED frame in meters, meters / s, meters / s^2 or N*/
 float z; /*< Z reference in NED frame in meters, meters / s, meters / s^2 or N (note, altitude is negative in NED)*/
 float yaw; /*< yaw reference in rad or rad / s*/
 uint8_t target_system; /*< System ID*/
 uint8_t target_component; /*< Component ID*/
 uint8_t control_target; /*<  Choose reference type from MAV_CONTROL_TARGET enum*/
 uint8_t coordinate_frame; /*< Valid options are: MAV_FRAME_LOCAL_NED = 1, MAV_FRAME_LOCAL_OFFSET_NED = 7, MAV_FRAME_BODY_NED = 8, MAV_FRAME_BODY_OFFSET_NED = 9*/
} mavlink_set_control_target_local_ned_t;

#define MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN 20
#define MAVLINK_MSG_ID_93_LEN 20

#define MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_CRC 149
#define MAVLINK_MSG_ID_93_CRC 149



#define MAVLINK_MESSAGE_INFO_SET_CONTROL_TARGET_LOCAL_NED { \
	"SET_CONTROL_TARGET_LOCAL_NED", \
	8, \
	{  { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_control_target_local_ned_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_set_control_target_local_ned_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_set_control_target_local_ned_t, z) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_set_control_target_local_ned_t, yaw) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_set_control_target_local_ned_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_set_control_target_local_ned_t, target_component) }, \
         { "control_target", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_set_control_target_local_ned_t, control_target) }, \
         { "coordinate_frame", NULL, MAVLINK_TYPE_UINT8_T, 0, 19, offsetof(mavlink_set_control_target_local_ned_t, coordinate_frame) }, \
         } \
}


/**
 * @brief Pack a set_control_target_local_ned message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x X reference in NED frame in meters, meters / s, meters / s^2 or N
 * @param y Y reference in NED frame in meters, meters / s, meters / s^2 or N
 * @param z Z reference in NED frame in meters, meters / s, meters / s^2 or N (note, altitude is negative in NED)
 * @param yaw yaw reference in rad or rad / s
 * @param target_system System ID
 * @param target_component Component ID
 * @param control_target  Choose reference type from MAV_CONTROL_TARGET enum
 * @param coordinate_frame Valid options are: MAV_FRAME_LOCAL_NED = 1, MAV_FRAME_LOCAL_OFFSET_NED = 7, MAV_FRAME_BODY_NED = 8, MAV_FRAME_BODY_OFFSET_NED = 9
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_control_target_local_ned_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float x, float y, float z, float yaw, uint8_t target_system, uint8_t target_component, uint8_t control_target, uint8_t coordinate_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN];
	_mav_put_float(buf, 0, x);
	_mav_put_float(buf, 4, y);
	_mav_put_float(buf, 8, z);
	_mav_put_float(buf, 12, yaw);
	_mav_put_uint8_t(buf, 16, target_system);
	_mav_put_uint8_t(buf, 17, target_component);
	_mav_put_uint8_t(buf, 18, control_target);
	_mav_put_uint8_t(buf, 19, coordinate_frame);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#else
	mavlink_set_control_target_local_ned_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.yaw = yaw;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.control_target = control_target;
	packet.coordinate_frame = coordinate_frame;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif
}

/**
 * @brief Pack a set_control_target_local_ned message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x X reference in NED frame in meters, meters / s, meters / s^2 or N
 * @param y Y reference in NED frame in meters, meters / s, meters / s^2 or N
 * @param z Z reference in NED frame in meters, meters / s, meters / s^2 or N (note, altitude is negative in NED)
 * @param yaw yaw reference in rad or rad / s
 * @param target_system System ID
 * @param target_component Component ID
 * @param control_target  Choose reference type from MAV_CONTROL_TARGET enum
 * @param coordinate_frame Valid options are: MAV_FRAME_LOCAL_NED = 1, MAV_FRAME_LOCAL_OFFSET_NED = 7, MAV_FRAME_BODY_NED = 8, MAV_FRAME_BODY_OFFSET_NED = 9
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_control_target_local_ned_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float x,float y,float z,float yaw,uint8_t target_system,uint8_t target_component,uint8_t control_target,uint8_t coordinate_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN];
	_mav_put_float(buf, 0, x);
	_mav_put_float(buf, 4, y);
	_mav_put_float(buf, 8, z);
	_mav_put_float(buf, 12, yaw);
	_mav_put_uint8_t(buf, 16, target_system);
	_mav_put_uint8_t(buf, 17, target_component);
	_mav_put_uint8_t(buf, 18, control_target);
	_mav_put_uint8_t(buf, 19, coordinate_frame);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#else
	mavlink_set_control_target_local_ned_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.yaw = yaw;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.control_target = control_target;
	packet.coordinate_frame = coordinate_frame;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif
}

/**
 * @brief Encode a set_control_target_local_ned struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_control_target_local_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_control_target_local_ned_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_control_target_local_ned_t* set_control_target_local_ned)
{
	return mavlink_msg_set_control_target_local_ned_pack(system_id, component_id, msg, set_control_target_local_ned->x, set_control_target_local_ned->y, set_control_target_local_ned->z, set_control_target_local_ned->yaw, set_control_target_local_ned->target_system, set_control_target_local_ned->target_component, set_control_target_local_ned->control_target, set_control_target_local_ned->coordinate_frame);
}

/**
 * @brief Encode a set_control_target_local_ned struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_control_target_local_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_control_target_local_ned_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_control_target_local_ned_t* set_control_target_local_ned)
{
	return mavlink_msg_set_control_target_local_ned_pack_chan(system_id, component_id, chan, msg, set_control_target_local_ned->x, set_control_target_local_ned->y, set_control_target_local_ned->z, set_control_target_local_ned->yaw, set_control_target_local_ned->target_system, set_control_target_local_ned->target_component, set_control_target_local_ned->control_target, set_control_target_local_ned->coordinate_frame);
}

/**
 * @brief Send a set_control_target_local_ned message
 * @param chan MAVLink channel to send the message
 *
 * @param x X reference in NED frame in meters, meters / s, meters / s^2 or N
 * @param y Y reference in NED frame in meters, meters / s, meters / s^2 or N
 * @param z Z reference in NED frame in meters, meters / s, meters / s^2 or N (note, altitude is negative in NED)
 * @param yaw yaw reference in rad or rad / s
 * @param target_system System ID
 * @param target_component Component ID
 * @param control_target  Choose reference type from MAV_CONTROL_TARGET enum
 * @param coordinate_frame Valid options are: MAV_FRAME_LOCAL_NED = 1, MAV_FRAME_LOCAL_OFFSET_NED = 7, MAV_FRAME_BODY_NED = 8, MAV_FRAME_BODY_OFFSET_NED = 9
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_control_target_local_ned_send(mavlink_channel_t chan, float x, float y, float z, float yaw, uint8_t target_system, uint8_t target_component, uint8_t control_target, uint8_t coordinate_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN];
	_mav_put_float(buf, 0, x);
	_mav_put_float(buf, 4, y);
	_mav_put_float(buf, 8, z);
	_mav_put_float(buf, 12, yaw);
	_mav_put_uint8_t(buf, 16, target_system);
	_mav_put_uint8_t(buf, 17, target_component);
	_mav_put_uint8_t(buf, 18, control_target);
	_mav_put_uint8_t(buf, 19, coordinate_frame);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED, buf, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED, buf, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif
#else
	mavlink_set_control_target_local_ned_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.yaw = yaw;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.control_target = control_target;
	packet.coordinate_frame = coordinate_frame;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED, (const char *)&packet, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED, (const char *)&packet, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_control_target_local_ned_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float x, float y, float z, float yaw, uint8_t target_system, uint8_t target_component, uint8_t control_target, uint8_t coordinate_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, x);
	_mav_put_float(buf, 4, y);
	_mav_put_float(buf, 8, z);
	_mav_put_float(buf, 12, yaw);
	_mav_put_uint8_t(buf, 16, target_system);
	_mav_put_uint8_t(buf, 17, target_component);
	_mav_put_uint8_t(buf, 18, control_target);
	_mav_put_uint8_t(buf, 19, coordinate_frame);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED, buf, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED, buf, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif
#else
	mavlink_set_control_target_local_ned_t *packet = (mavlink_set_control_target_local_ned_t *)msgbuf;
	packet->x = x;
	packet->y = y;
	packet->z = z;
	packet->yaw = yaw;
	packet->target_system = target_system;
	packet->target_component = target_component;
	packet->control_target = control_target;
	packet->coordinate_frame = coordinate_frame;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED, (const char *)packet, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED, (const char *)packet, MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE SET_CONTROL_TARGET_LOCAL_NED UNPACKING


/**
 * @brief Get field x from set_control_target_local_ned message
 *
 * @return X reference in NED frame in meters, meters / s, meters / s^2 or N
 */
static inline float mavlink_msg_set_control_target_local_ned_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field y from set_control_target_local_ned message
 *
 * @return Y reference in NED frame in meters, meters / s, meters / s^2 or N
 */
static inline float mavlink_msg_set_control_target_local_ned_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field z from set_control_target_local_ned message
 *
 * @return Z reference in NED frame in meters, meters / s, meters / s^2 or N (note, altitude is negative in NED)
 */
static inline float mavlink_msg_set_control_target_local_ned_get_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field yaw from set_control_target_local_ned message
 *
 * @return yaw reference in rad or rad / s
 */
static inline float mavlink_msg_set_control_target_local_ned_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field target_system from set_control_target_local_ned message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_set_control_target_local_ned_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field target_component from set_control_target_local_ned message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_set_control_target_local_ned_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Get field control_target from set_control_target_local_ned message
 *
 * @return  Choose reference type from MAV_CONTROL_TARGET enum
 */
static inline uint8_t mavlink_msg_set_control_target_local_ned_get_control_target(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field coordinate_frame from set_control_target_local_ned message
 *
 * @return Valid options are: MAV_FRAME_LOCAL_NED = 1, MAV_FRAME_LOCAL_OFFSET_NED = 7, MAV_FRAME_BODY_NED = 8, MAV_FRAME_BODY_OFFSET_NED = 9
 */
static inline uint8_t mavlink_msg_set_control_target_local_ned_get_coordinate_frame(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  19);
}

/**
 * @brief Decode a set_control_target_local_ned message into a struct
 *
 * @param msg The message to decode
 * @param set_control_target_local_ned C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_control_target_local_ned_decode(const mavlink_message_t* msg, mavlink_set_control_target_local_ned_t* set_control_target_local_ned)
{
#if MAVLINK_NEED_BYTE_SWAP
	set_control_target_local_ned->x = mavlink_msg_set_control_target_local_ned_get_x(msg);
	set_control_target_local_ned->y = mavlink_msg_set_control_target_local_ned_get_y(msg);
	set_control_target_local_ned->z = mavlink_msg_set_control_target_local_ned_get_z(msg);
	set_control_target_local_ned->yaw = mavlink_msg_set_control_target_local_ned_get_yaw(msg);
	set_control_target_local_ned->target_system = mavlink_msg_set_control_target_local_ned_get_target_system(msg);
	set_control_target_local_ned->target_component = mavlink_msg_set_control_target_local_ned_get_target_component(msg);
	set_control_target_local_ned->control_target = mavlink_msg_set_control_target_local_ned_get_control_target(msg);
	set_control_target_local_ned->coordinate_frame = mavlink_msg_set_control_target_local_ned_get_coordinate_frame(msg);
#else
	memcpy(set_control_target_local_ned, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_SET_CONTROL_TARGET_LOCAL_NED_LEN);
#endif
}
