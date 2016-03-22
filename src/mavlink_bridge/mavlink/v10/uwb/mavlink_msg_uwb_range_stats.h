// MESSAGE UWB_RANGE_STATS PACKING

#define MAVLINK_MSG_ID_UWB_RANGE_STATS 201

typedef struct __mavlink_uwb_range_stats_t
{
 uint32_t stamp_us; /*< Timestamp of measurement in microseconds.*/
 float round_trip_time; /*< Round trip time in nanoseconds.*/
 float range; /*< Range.*/
 uint16_t std_noise_1; /*< Noise 1.*/
 uint16_t std_noise_2; /*< Noise 2.*/
 uint16_t preamble_acc_count_1; /*< Preamble accumulator count 1.*/
 uint16_t preamble_acc_count_2; /*< Preamble accumulator count 2.*/
 uint16_t first_path_index_1; /*< First path index 1.*/
 uint16_t first_path_index_2; /*< First path index 2.*/
 uint16_t first_path_amp_1_1; /*< First path amplitude 1 1.*/
 uint16_t first_path_amp_1_2; /*< First path amplitude 1 2.*/
 uint16_t first_path_amp_2_1; /*< First path amplitude 2 1.*/
 uint16_t first_path_amp_2_2; /*< First path amplitude 2 2.*/
 uint16_t first_path_amp_3_1; /*< First path amplitude 3 1.*/
 uint16_t first_path_amp_3_2; /*< First path amplitude 3 2.*/
 uint16_t channel_impulse_response_power_1; /*< Channel impulse response power 1.*/
 uint16_t channel_impulse_response_power_2; /*< Channel impulse response power 2.*/
 uint16_t prf_1; /*< PRF 1.*/
 uint16_t prf_2; /*< PRF 2.*/
 uint8_t address; /*< Address of UWB unit.*/
 uint8_t remote_address; /*< Address of remote UWB unit that was used as an anchor.*/
} mavlink_uwb_range_stats_t;

#define MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN 46
#define MAVLINK_MSG_ID_201_LEN 46

#define MAVLINK_MSG_ID_UWB_RANGE_STATS_CRC 219
#define MAVLINK_MSG_ID_201_CRC 219



#define MAVLINK_MESSAGE_INFO_UWB_RANGE_STATS { \
	"UWB_RANGE_STATS", \
	21, \
	{  { "stamp_us", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_uwb_range_stats_t, stamp_us) }, \
         { "round_trip_time", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_uwb_range_stats_t, round_trip_time) }, \
         { "range", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_uwb_range_stats_t, range) }, \
         { "std_noise_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_uwb_range_stats_t, std_noise_1) }, \
         { "std_noise_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_uwb_range_stats_t, std_noise_2) }, \
         { "preamble_acc_count_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_uwb_range_stats_t, preamble_acc_count_1) }, \
         { "preamble_acc_count_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_uwb_range_stats_t, preamble_acc_count_2) }, \
         { "first_path_index_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_uwb_range_stats_t, first_path_index_1) }, \
         { "first_path_index_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_uwb_range_stats_t, first_path_index_2) }, \
         { "first_path_amp_1_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_uwb_range_stats_t, first_path_amp_1_1) }, \
         { "first_path_amp_1_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 26, offsetof(mavlink_uwb_range_stats_t, first_path_amp_1_2) }, \
         { "first_path_amp_2_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_uwb_range_stats_t, first_path_amp_2_1) }, \
         { "first_path_amp_2_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 30, offsetof(mavlink_uwb_range_stats_t, first_path_amp_2_2) }, \
         { "first_path_amp_3_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 32, offsetof(mavlink_uwb_range_stats_t, first_path_amp_3_1) }, \
         { "first_path_amp_3_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 34, offsetof(mavlink_uwb_range_stats_t, first_path_amp_3_2) }, \
         { "channel_impulse_response_power_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 36, offsetof(mavlink_uwb_range_stats_t, channel_impulse_response_power_1) }, \
         { "channel_impulse_response_power_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 38, offsetof(mavlink_uwb_range_stats_t, channel_impulse_response_power_2) }, \
         { "prf_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 40, offsetof(mavlink_uwb_range_stats_t, prf_1) }, \
         { "prf_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 42, offsetof(mavlink_uwb_range_stats_t, prf_2) }, \
         { "address", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_uwb_range_stats_t, address) }, \
         { "remote_address", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_uwb_range_stats_t, remote_address) }, \
         } \
}


/**
 * @brief Pack a uwb_range_stats message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param address Address of UWB unit.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param stamp_us Timestamp of measurement in microseconds.
 * @param round_trip_time Round trip time in nanoseconds.
 * @param range Range.
 * @param std_noise_1 Noise 1.
 * @param std_noise_2 Noise 2.
 * @param preamble_acc_count_1 Preamble accumulator count 1.
 * @param preamble_acc_count_2 Preamble accumulator count 2.
 * @param first_path_index_1 First path index 1.
 * @param first_path_index_2 First path index 2.
 * @param first_path_amp_1_1 First path amplitude 1 1.
 * @param first_path_amp_1_2 First path amplitude 1 2.
 * @param first_path_amp_2_1 First path amplitude 2 1.
 * @param first_path_amp_2_2 First path amplitude 2 2.
 * @param first_path_amp_3_1 First path amplitude 3 1.
 * @param first_path_amp_3_2 First path amplitude 3 2.
 * @param channel_impulse_response_power_1 Channel impulse response power 1.
 * @param channel_impulse_response_power_2 Channel impulse response power 2.
 * @param prf_1 PRF 1.
 * @param prf_2 PRF 2.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_range_stats_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t address, uint8_t remote_address, uint32_t stamp_us, float round_trip_time, float range, uint16_t std_noise_1, uint16_t std_noise_2, uint16_t preamble_acc_count_1, uint16_t preamble_acc_count_2, uint16_t first_path_index_1, uint16_t first_path_index_2, uint16_t first_path_amp_1_1, uint16_t first_path_amp_1_2, uint16_t first_path_amp_2_1, uint16_t first_path_amp_2_2, uint16_t first_path_amp_3_1, uint16_t first_path_amp_3_2, uint16_t channel_impulse_response_power_1, uint16_t channel_impulse_response_power_2, uint16_t prf_1, uint16_t prf_2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN];
	_mav_put_uint32_t(buf, 0, stamp_us);
	_mav_put_float(buf, 4, round_trip_time);
	_mav_put_float(buf, 8, range);
	_mav_put_uint16_t(buf, 12, std_noise_1);
	_mav_put_uint16_t(buf, 14, std_noise_2);
	_mav_put_uint16_t(buf, 16, preamble_acc_count_1);
	_mav_put_uint16_t(buf, 18, preamble_acc_count_2);
	_mav_put_uint16_t(buf, 20, first_path_index_1);
	_mav_put_uint16_t(buf, 22, first_path_index_2);
	_mav_put_uint16_t(buf, 24, first_path_amp_1_1);
	_mav_put_uint16_t(buf, 26, first_path_amp_1_2);
	_mav_put_uint16_t(buf, 28, first_path_amp_2_1);
	_mav_put_uint16_t(buf, 30, first_path_amp_2_2);
	_mav_put_uint16_t(buf, 32, first_path_amp_3_1);
	_mav_put_uint16_t(buf, 34, first_path_amp_3_2);
	_mav_put_uint16_t(buf, 36, channel_impulse_response_power_1);
	_mav_put_uint16_t(buf, 38, channel_impulse_response_power_2);
	_mav_put_uint16_t(buf, 40, prf_1);
	_mav_put_uint16_t(buf, 42, prf_2);
	_mav_put_uint8_t(buf, 44, address);
	_mav_put_uint8_t(buf, 45, remote_address);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#else
	mavlink_uwb_range_stats_t packet;
	packet.stamp_us = stamp_us;
	packet.round_trip_time = round_trip_time;
	packet.range = range;
	packet.std_noise_1 = std_noise_1;
	packet.std_noise_2 = std_noise_2;
	packet.preamble_acc_count_1 = preamble_acc_count_1;
	packet.preamble_acc_count_2 = preamble_acc_count_2;
	packet.first_path_index_1 = first_path_index_1;
	packet.first_path_index_2 = first_path_index_2;
	packet.first_path_amp_1_1 = first_path_amp_1_1;
	packet.first_path_amp_1_2 = first_path_amp_1_2;
	packet.first_path_amp_2_1 = first_path_amp_2_1;
	packet.first_path_amp_2_2 = first_path_amp_2_2;
	packet.first_path_amp_3_1 = first_path_amp_3_1;
	packet.first_path_amp_3_2 = first_path_amp_3_2;
	packet.channel_impulse_response_power_1 = channel_impulse_response_power_1;
	packet.channel_impulse_response_power_2 = channel_impulse_response_power_2;
	packet.prf_1 = prf_1;
	packet.prf_2 = prf_2;
	packet.address = address;
	packet.remote_address = remote_address;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_RANGE_STATS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN, MAVLINK_MSG_ID_UWB_RANGE_STATS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif
}

/**
 * @brief Pack a uwb_range_stats message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param address Address of UWB unit.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param stamp_us Timestamp of measurement in microseconds.
 * @param round_trip_time Round trip time in nanoseconds.
 * @param range Range.
 * @param std_noise_1 Noise 1.
 * @param std_noise_2 Noise 2.
 * @param preamble_acc_count_1 Preamble accumulator count 1.
 * @param preamble_acc_count_2 Preamble accumulator count 2.
 * @param first_path_index_1 First path index 1.
 * @param first_path_index_2 First path index 2.
 * @param first_path_amp_1_1 First path amplitude 1 1.
 * @param first_path_amp_1_2 First path amplitude 1 2.
 * @param first_path_amp_2_1 First path amplitude 2 1.
 * @param first_path_amp_2_2 First path amplitude 2 2.
 * @param first_path_amp_3_1 First path amplitude 3 1.
 * @param first_path_amp_3_2 First path amplitude 3 2.
 * @param channel_impulse_response_power_1 Channel impulse response power 1.
 * @param channel_impulse_response_power_2 Channel impulse response power 2.
 * @param prf_1 PRF 1.
 * @param prf_2 PRF 2.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_uwb_range_stats_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t address,uint8_t remote_address,uint32_t stamp_us,float round_trip_time,float range,uint16_t std_noise_1,uint16_t std_noise_2,uint16_t preamble_acc_count_1,uint16_t preamble_acc_count_2,uint16_t first_path_index_1,uint16_t first_path_index_2,uint16_t first_path_amp_1_1,uint16_t first_path_amp_1_2,uint16_t first_path_amp_2_1,uint16_t first_path_amp_2_2,uint16_t first_path_amp_3_1,uint16_t first_path_amp_3_2,uint16_t channel_impulse_response_power_1,uint16_t channel_impulse_response_power_2,uint16_t prf_1,uint16_t prf_2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN];
	_mav_put_uint32_t(buf, 0, stamp_us);
	_mav_put_float(buf, 4, round_trip_time);
	_mav_put_float(buf, 8, range);
	_mav_put_uint16_t(buf, 12, std_noise_1);
	_mav_put_uint16_t(buf, 14, std_noise_2);
	_mav_put_uint16_t(buf, 16, preamble_acc_count_1);
	_mav_put_uint16_t(buf, 18, preamble_acc_count_2);
	_mav_put_uint16_t(buf, 20, first_path_index_1);
	_mav_put_uint16_t(buf, 22, first_path_index_2);
	_mav_put_uint16_t(buf, 24, first_path_amp_1_1);
	_mav_put_uint16_t(buf, 26, first_path_amp_1_2);
	_mav_put_uint16_t(buf, 28, first_path_amp_2_1);
	_mav_put_uint16_t(buf, 30, first_path_amp_2_2);
	_mav_put_uint16_t(buf, 32, first_path_amp_3_1);
	_mav_put_uint16_t(buf, 34, first_path_amp_3_2);
	_mav_put_uint16_t(buf, 36, channel_impulse_response_power_1);
	_mav_put_uint16_t(buf, 38, channel_impulse_response_power_2);
	_mav_put_uint16_t(buf, 40, prf_1);
	_mav_put_uint16_t(buf, 42, prf_2);
	_mav_put_uint8_t(buf, 44, address);
	_mav_put_uint8_t(buf, 45, remote_address);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#else
	mavlink_uwb_range_stats_t packet;
	packet.stamp_us = stamp_us;
	packet.round_trip_time = round_trip_time;
	packet.range = range;
	packet.std_noise_1 = std_noise_1;
	packet.std_noise_2 = std_noise_2;
	packet.preamble_acc_count_1 = preamble_acc_count_1;
	packet.preamble_acc_count_2 = preamble_acc_count_2;
	packet.first_path_index_1 = first_path_index_1;
	packet.first_path_index_2 = first_path_index_2;
	packet.first_path_amp_1_1 = first_path_amp_1_1;
	packet.first_path_amp_1_2 = first_path_amp_1_2;
	packet.first_path_amp_2_1 = first_path_amp_2_1;
	packet.first_path_amp_2_2 = first_path_amp_2_2;
	packet.first_path_amp_3_1 = first_path_amp_3_1;
	packet.first_path_amp_3_2 = first_path_amp_3_2;
	packet.channel_impulse_response_power_1 = channel_impulse_response_power_1;
	packet.channel_impulse_response_power_2 = channel_impulse_response_power_2;
	packet.prf_1 = prf_1;
	packet.prf_2 = prf_2;
	packet.address = address;
	packet.remote_address = remote_address;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UWB_RANGE_STATS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN, MAVLINK_MSG_ID_UWB_RANGE_STATS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif
}

/**
 * @brief Encode a uwb_range_stats struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param uwb_range_stats C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_range_stats_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_uwb_range_stats_t* uwb_range_stats)
{
	return mavlink_msg_uwb_range_stats_pack(system_id, component_id, msg, uwb_range_stats->address, uwb_range_stats->remote_address, uwb_range_stats->stamp_us, uwb_range_stats->round_trip_time, uwb_range_stats->range, uwb_range_stats->std_noise_1, uwb_range_stats->std_noise_2, uwb_range_stats->preamble_acc_count_1, uwb_range_stats->preamble_acc_count_2, uwb_range_stats->first_path_index_1, uwb_range_stats->first_path_index_2, uwb_range_stats->first_path_amp_1_1, uwb_range_stats->first_path_amp_1_2, uwb_range_stats->first_path_amp_2_1, uwb_range_stats->first_path_amp_2_2, uwb_range_stats->first_path_amp_3_1, uwb_range_stats->first_path_amp_3_2, uwb_range_stats->channel_impulse_response_power_1, uwb_range_stats->channel_impulse_response_power_2, uwb_range_stats->prf_1, uwb_range_stats->prf_2);
}

/**
 * @brief Encode a uwb_range_stats struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uwb_range_stats C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_uwb_range_stats_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_uwb_range_stats_t* uwb_range_stats)
{
	return mavlink_msg_uwb_range_stats_pack_chan(system_id, component_id, chan, msg, uwb_range_stats->address, uwb_range_stats->remote_address, uwb_range_stats->stamp_us, uwb_range_stats->round_trip_time, uwb_range_stats->range, uwb_range_stats->std_noise_1, uwb_range_stats->std_noise_2, uwb_range_stats->preamble_acc_count_1, uwb_range_stats->preamble_acc_count_2, uwb_range_stats->first_path_index_1, uwb_range_stats->first_path_index_2, uwb_range_stats->first_path_amp_1_1, uwb_range_stats->first_path_amp_1_2, uwb_range_stats->first_path_amp_2_1, uwb_range_stats->first_path_amp_2_2, uwb_range_stats->first_path_amp_3_1, uwb_range_stats->first_path_amp_3_2, uwb_range_stats->channel_impulse_response_power_1, uwb_range_stats->channel_impulse_response_power_2, uwb_range_stats->prf_1, uwb_range_stats->prf_2);
}

/**
 * @brief Send a uwb_range_stats message
 * @param chan MAVLink channel to send the message
 *
 * @param address Address of UWB unit.
 * @param remote_address Address of remote UWB unit that was used as an anchor.
 * @param stamp_us Timestamp of measurement in microseconds.
 * @param round_trip_time Round trip time in nanoseconds.
 * @param range Range.
 * @param std_noise_1 Noise 1.
 * @param std_noise_2 Noise 2.
 * @param preamble_acc_count_1 Preamble accumulator count 1.
 * @param preamble_acc_count_2 Preamble accumulator count 2.
 * @param first_path_index_1 First path index 1.
 * @param first_path_index_2 First path index 2.
 * @param first_path_amp_1_1 First path amplitude 1 1.
 * @param first_path_amp_1_2 First path amplitude 1 2.
 * @param first_path_amp_2_1 First path amplitude 2 1.
 * @param first_path_amp_2_2 First path amplitude 2 2.
 * @param first_path_amp_3_1 First path amplitude 3 1.
 * @param first_path_amp_3_2 First path amplitude 3 2.
 * @param channel_impulse_response_power_1 Channel impulse response power 1.
 * @param channel_impulse_response_power_2 Channel impulse response power 2.
 * @param prf_1 PRF 1.
 * @param prf_2 PRF 2.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_uwb_range_stats_send(mavlink_channel_t chan, uint8_t address, uint8_t remote_address, uint32_t stamp_us, float round_trip_time, float range, uint16_t std_noise_1, uint16_t std_noise_2, uint16_t preamble_acc_count_1, uint16_t preamble_acc_count_2, uint16_t first_path_index_1, uint16_t first_path_index_2, uint16_t first_path_amp_1_1, uint16_t first_path_amp_1_2, uint16_t first_path_amp_2_1, uint16_t first_path_amp_2_2, uint16_t first_path_amp_3_1, uint16_t first_path_amp_3_2, uint16_t channel_impulse_response_power_1, uint16_t channel_impulse_response_power_2, uint16_t prf_1, uint16_t prf_2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN];
	_mav_put_uint32_t(buf, 0, stamp_us);
	_mav_put_float(buf, 4, round_trip_time);
	_mav_put_float(buf, 8, range);
	_mav_put_uint16_t(buf, 12, std_noise_1);
	_mav_put_uint16_t(buf, 14, std_noise_2);
	_mav_put_uint16_t(buf, 16, preamble_acc_count_1);
	_mav_put_uint16_t(buf, 18, preamble_acc_count_2);
	_mav_put_uint16_t(buf, 20, first_path_index_1);
	_mav_put_uint16_t(buf, 22, first_path_index_2);
	_mav_put_uint16_t(buf, 24, first_path_amp_1_1);
	_mav_put_uint16_t(buf, 26, first_path_amp_1_2);
	_mav_put_uint16_t(buf, 28, first_path_amp_2_1);
	_mav_put_uint16_t(buf, 30, first_path_amp_2_2);
	_mav_put_uint16_t(buf, 32, first_path_amp_3_1);
	_mav_put_uint16_t(buf, 34, first_path_amp_3_2);
	_mav_put_uint16_t(buf, 36, channel_impulse_response_power_1);
	_mav_put_uint16_t(buf, 38, channel_impulse_response_power_2);
	_mav_put_uint16_t(buf, 40, prf_1);
	_mav_put_uint16_t(buf, 42, prf_2);
	_mav_put_uint8_t(buf, 44, address);
	_mav_put_uint8_t(buf, 45, remote_address);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_STATS, buf, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN, MAVLINK_MSG_ID_UWB_RANGE_STATS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_STATS, buf, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif
#else
	mavlink_uwb_range_stats_t packet;
	packet.stamp_us = stamp_us;
	packet.round_trip_time = round_trip_time;
	packet.range = range;
	packet.std_noise_1 = std_noise_1;
	packet.std_noise_2 = std_noise_2;
	packet.preamble_acc_count_1 = preamble_acc_count_1;
	packet.preamble_acc_count_2 = preamble_acc_count_2;
	packet.first_path_index_1 = first_path_index_1;
	packet.first_path_index_2 = first_path_index_2;
	packet.first_path_amp_1_1 = first_path_amp_1_1;
	packet.first_path_amp_1_2 = first_path_amp_1_2;
	packet.first_path_amp_2_1 = first_path_amp_2_1;
	packet.first_path_amp_2_2 = first_path_amp_2_2;
	packet.first_path_amp_3_1 = first_path_amp_3_1;
	packet.first_path_amp_3_2 = first_path_amp_3_2;
	packet.channel_impulse_response_power_1 = channel_impulse_response_power_1;
	packet.channel_impulse_response_power_2 = channel_impulse_response_power_2;
	packet.prf_1 = prf_1;
	packet.prf_2 = prf_2;
	packet.address = address;
	packet.remote_address = remote_address;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_STATS, (const char *)&packet, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN, MAVLINK_MSG_ID_UWB_RANGE_STATS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_STATS, (const char *)&packet, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_uwb_range_stats_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t address, uint8_t remote_address, uint32_t stamp_us, float round_trip_time, float range, uint16_t std_noise_1, uint16_t std_noise_2, uint16_t preamble_acc_count_1, uint16_t preamble_acc_count_2, uint16_t first_path_index_1, uint16_t first_path_index_2, uint16_t first_path_amp_1_1, uint16_t first_path_amp_1_2, uint16_t first_path_amp_2_1, uint16_t first_path_amp_2_2, uint16_t first_path_amp_3_1, uint16_t first_path_amp_3_2, uint16_t channel_impulse_response_power_1, uint16_t channel_impulse_response_power_2, uint16_t prf_1, uint16_t prf_2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, stamp_us);
	_mav_put_float(buf, 4, round_trip_time);
	_mav_put_float(buf, 8, range);
	_mav_put_uint16_t(buf, 12, std_noise_1);
	_mav_put_uint16_t(buf, 14, std_noise_2);
	_mav_put_uint16_t(buf, 16, preamble_acc_count_1);
	_mav_put_uint16_t(buf, 18, preamble_acc_count_2);
	_mav_put_uint16_t(buf, 20, first_path_index_1);
	_mav_put_uint16_t(buf, 22, first_path_index_2);
	_mav_put_uint16_t(buf, 24, first_path_amp_1_1);
	_mav_put_uint16_t(buf, 26, first_path_amp_1_2);
	_mav_put_uint16_t(buf, 28, first_path_amp_2_1);
	_mav_put_uint16_t(buf, 30, first_path_amp_2_2);
	_mav_put_uint16_t(buf, 32, first_path_amp_3_1);
	_mav_put_uint16_t(buf, 34, first_path_amp_3_2);
	_mav_put_uint16_t(buf, 36, channel_impulse_response_power_1);
	_mav_put_uint16_t(buf, 38, channel_impulse_response_power_2);
	_mav_put_uint16_t(buf, 40, prf_1);
	_mav_put_uint16_t(buf, 42, prf_2);
	_mav_put_uint8_t(buf, 44, address);
	_mav_put_uint8_t(buf, 45, remote_address);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_STATS, buf, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN, MAVLINK_MSG_ID_UWB_RANGE_STATS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_STATS, buf, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif
#else
	mavlink_uwb_range_stats_t *packet = (mavlink_uwb_range_stats_t *)msgbuf;
	packet->stamp_us = stamp_us;
	packet->round_trip_time = round_trip_time;
	packet->range = range;
	packet->std_noise_1 = std_noise_1;
	packet->std_noise_2 = std_noise_2;
	packet->preamble_acc_count_1 = preamble_acc_count_1;
	packet->preamble_acc_count_2 = preamble_acc_count_2;
	packet->first_path_index_1 = first_path_index_1;
	packet->first_path_index_2 = first_path_index_2;
	packet->first_path_amp_1_1 = first_path_amp_1_1;
	packet->first_path_amp_1_2 = first_path_amp_1_2;
	packet->first_path_amp_2_1 = first_path_amp_2_1;
	packet->first_path_amp_2_2 = first_path_amp_2_2;
	packet->first_path_amp_3_1 = first_path_amp_3_1;
	packet->first_path_amp_3_2 = first_path_amp_3_2;
	packet->channel_impulse_response_power_1 = channel_impulse_response_power_1;
	packet->channel_impulse_response_power_2 = channel_impulse_response_power_2;
	packet->prf_1 = prf_1;
	packet->prf_2 = prf_2;
	packet->address = address;
	packet->remote_address = remote_address;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_STATS, (const char *)packet, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN, MAVLINK_MSG_ID_UWB_RANGE_STATS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UWB_RANGE_STATS, (const char *)packet, MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UWB_RANGE_STATS UNPACKING


/**
 * @brief Get field address from uwb_range_stats message
 *
 * @return Address of UWB unit.
 */
static inline uint8_t mavlink_msg_uwb_range_stats_get_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  44);
}

/**
 * @brief Get field remote_address from uwb_range_stats message
 *
 * @return Address of remote UWB unit that was used as an anchor.
 */
static inline uint8_t mavlink_msg_uwb_range_stats_get_remote_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  45);
}

/**
 * @brief Get field stamp_us from uwb_range_stats message
 *
 * @return Timestamp of measurement in microseconds.
 */
static inline uint32_t mavlink_msg_uwb_range_stats_get_stamp_us(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field round_trip_time from uwb_range_stats message
 *
 * @return Round trip time in nanoseconds.
 */
static inline float mavlink_msg_uwb_range_stats_get_round_trip_time(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field range from uwb_range_stats message
 *
 * @return Range.
 */
static inline float mavlink_msg_uwb_range_stats_get_range(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field std_noise_1 from uwb_range_stats message
 *
 * @return Noise 1.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_std_noise_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field std_noise_2 from uwb_range_stats message
 *
 * @return Noise 2.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_std_noise_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Get field preamble_acc_count_1 from uwb_range_stats message
 *
 * @return Preamble accumulator count 1.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_preamble_acc_count_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field preamble_acc_count_2 from uwb_range_stats message
 *
 * @return Preamble accumulator count 2.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_preamble_acc_count_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  18);
}

/**
 * @brief Get field first_path_index_1 from uwb_range_stats message
 *
 * @return First path index 1.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_first_path_index_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field first_path_index_2 from uwb_range_stats message
 *
 * @return First path index 2.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_first_path_index_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  22);
}

/**
 * @brief Get field first_path_amp_1_1 from uwb_range_stats message
 *
 * @return First path amplitude 1 1.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_first_path_amp_1_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field first_path_amp_1_2 from uwb_range_stats message
 *
 * @return First path amplitude 1 2.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_first_path_amp_1_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  26);
}

/**
 * @brief Get field first_path_amp_2_1 from uwb_range_stats message
 *
 * @return First path amplitude 2 1.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_first_path_amp_2_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  28);
}

/**
 * @brief Get field first_path_amp_2_2 from uwb_range_stats message
 *
 * @return First path amplitude 2 2.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_first_path_amp_2_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  30);
}

/**
 * @brief Get field first_path_amp_3_1 from uwb_range_stats message
 *
 * @return First path amplitude 3 1.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_first_path_amp_3_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  32);
}

/**
 * @brief Get field first_path_amp_3_2 from uwb_range_stats message
 *
 * @return First path amplitude 3 2.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_first_path_amp_3_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  34);
}

/**
 * @brief Get field channel_impulse_response_power_1 from uwb_range_stats message
 *
 * @return Channel impulse response power 1.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_channel_impulse_response_power_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  36);
}

/**
 * @brief Get field channel_impulse_response_power_2 from uwb_range_stats message
 *
 * @return Channel impulse response power 2.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_channel_impulse_response_power_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  38);
}

/**
 * @brief Get field prf_1 from uwb_range_stats message
 *
 * @return PRF 1.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_prf_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  40);
}

/**
 * @brief Get field prf_2 from uwb_range_stats message
 *
 * @return PRF 2.
 */
static inline uint16_t mavlink_msg_uwb_range_stats_get_prf_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  42);
}

/**
 * @brief Decode a uwb_range_stats message into a struct
 *
 * @param msg The message to decode
 * @param uwb_range_stats C-struct to decode the message contents into
 */
static inline void mavlink_msg_uwb_range_stats_decode(const mavlink_message_t* msg, mavlink_uwb_range_stats_t* uwb_range_stats)
{
#if MAVLINK_NEED_BYTE_SWAP
	uwb_range_stats->stamp_us = mavlink_msg_uwb_range_stats_get_stamp_us(msg);
	uwb_range_stats->round_trip_time = mavlink_msg_uwb_range_stats_get_round_trip_time(msg);
	uwb_range_stats->range = mavlink_msg_uwb_range_stats_get_range(msg);
	uwb_range_stats->std_noise_1 = mavlink_msg_uwb_range_stats_get_std_noise_1(msg);
	uwb_range_stats->std_noise_2 = mavlink_msg_uwb_range_stats_get_std_noise_2(msg);
	uwb_range_stats->preamble_acc_count_1 = mavlink_msg_uwb_range_stats_get_preamble_acc_count_1(msg);
	uwb_range_stats->preamble_acc_count_2 = mavlink_msg_uwb_range_stats_get_preamble_acc_count_2(msg);
	uwb_range_stats->first_path_index_1 = mavlink_msg_uwb_range_stats_get_first_path_index_1(msg);
	uwb_range_stats->first_path_index_2 = mavlink_msg_uwb_range_stats_get_first_path_index_2(msg);
	uwb_range_stats->first_path_amp_1_1 = mavlink_msg_uwb_range_stats_get_first_path_amp_1_1(msg);
	uwb_range_stats->first_path_amp_1_2 = mavlink_msg_uwb_range_stats_get_first_path_amp_1_2(msg);
	uwb_range_stats->first_path_amp_2_1 = mavlink_msg_uwb_range_stats_get_first_path_amp_2_1(msg);
	uwb_range_stats->first_path_amp_2_2 = mavlink_msg_uwb_range_stats_get_first_path_amp_2_2(msg);
	uwb_range_stats->first_path_amp_3_1 = mavlink_msg_uwb_range_stats_get_first_path_amp_3_1(msg);
	uwb_range_stats->first_path_amp_3_2 = mavlink_msg_uwb_range_stats_get_first_path_amp_3_2(msg);
	uwb_range_stats->channel_impulse_response_power_1 = mavlink_msg_uwb_range_stats_get_channel_impulse_response_power_1(msg);
	uwb_range_stats->channel_impulse_response_power_2 = mavlink_msg_uwb_range_stats_get_channel_impulse_response_power_2(msg);
	uwb_range_stats->prf_1 = mavlink_msg_uwb_range_stats_get_prf_1(msg);
	uwb_range_stats->prf_2 = mavlink_msg_uwb_range_stats_get_prf_2(msg);
	uwb_range_stats->address = mavlink_msg_uwb_range_stats_get_address(msg);
	uwb_range_stats->remote_address = mavlink_msg_uwb_range_stats_get_remote_address(msg);
#else
	memcpy(uwb_range_stats, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UWB_RANGE_STATS_LEN);
#endif
}
