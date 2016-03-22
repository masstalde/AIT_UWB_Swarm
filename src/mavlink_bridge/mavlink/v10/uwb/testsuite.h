/** @file
 *	@brief MAVLink comm protocol testsuite generated from uwb.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef UWB_TESTSUITE_H
#define UWB_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_uwb(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_common(system_id, component_id, last_msg);
	mavlink_test_uwb(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_uwb_multi_range_raw_4(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_multi_range_raw_4_t packet_in = {
		93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,{ 93372036854777319, 93372036854777320, 93372036854777321, 93372036854777322 },{ 93372036854779335, 93372036854779336, 93372036854779337, 93372036854779338 },{ 93372036854781351, 93372036854781352, 93372036854781353, 93372036854781354 },109,176,243
    };
	mavlink_uwb_multi_range_raw_4_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.timestamp_master_request_recv = packet_in.timestamp_master_request_recv;
        	packet1.timestamp_slave_reply_send_1 = packet_in.timestamp_slave_reply_send_1;
        	packet1.timestamp_slave_reply_send_2 = packet_in.timestamp_slave_reply_send_2;
        	packet1.num_of_units = packet_in.num_of_units;
        	packet1.address = packet_in.address;
        	packet1.remote_address = packet_in.remote_address;
        
        	mav_array_memcpy(packet1.timestamp_master_request, packet_in.timestamp_master_request, sizeof(uint64_t)*4);
        	mav_array_memcpy(packet1.timestamp_slave_reply_1, packet_in.timestamp_slave_reply_1, sizeof(uint64_t)*4);
        	mav_array_memcpy(packet1.timestamp_slave_reply_2, packet_in.timestamp_slave_reply_2, sizeof(uint64_t)*4);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_multi_range_raw_4_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_multi_range_raw_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_multi_range_raw_4_pack(system_id, component_id, &msg , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_recv , packet1.timestamp_slave_reply_send_1 , packet1.timestamp_slave_reply_send_2 , packet1.timestamp_master_request , packet1.timestamp_slave_reply_1 , packet1.timestamp_slave_reply_2 );
	mavlink_msg_uwb_multi_range_raw_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_multi_range_raw_4_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_recv , packet1.timestamp_slave_reply_send_1 , packet1.timestamp_slave_reply_send_2 , packet1.timestamp_master_request , packet1.timestamp_slave_reply_1 , packet1.timestamp_slave_reply_2 );
	mavlink_msg_uwb_multi_range_raw_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_multi_range_raw_4_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_multi_range_raw_4_send(MAVLINK_COMM_1 , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_recv , packet1.timestamp_slave_reply_send_1 , packet1.timestamp_slave_reply_send_2 , packet1.timestamp_master_request , packet1.timestamp_slave_reply_1 , packet1.timestamp_slave_reply_2 );
	mavlink_msg_uwb_multi_range_raw_4_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_2way_multi_range_raw_10(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_2way_multi_range_raw_10_t packet_in = {
		93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,{ 93372036854777319, 93372036854777320, 93372036854777321, 93372036854777322, 93372036854777323, 93372036854777324, 93372036854777325, 93372036854777326, 93372036854777327, 93372036854777328 },{ 93372036854782359, 93372036854782360, 93372036854782361, 93372036854782362, 93372036854782363, 93372036854782364, 93372036854782365, 93372036854782366, 93372036854782367, 93372036854782368 },{ 93372036854787399, 93372036854787400, 93372036854787401, 93372036854787402, 93372036854787403, 93372036854787404, 93372036854787405, 93372036854787406, 93372036854787407, 93372036854787408 },29,96,163
    };
	mavlink_uwb_2way_multi_range_raw_10_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.timestamp_master_request_1_recv = packet_in.timestamp_master_request_1_recv;
        	packet1.timestamp_slave_reply_send = packet_in.timestamp_slave_reply_send;
        	packet1.timestamp_master_request_2_recv = packet_in.timestamp_master_request_2_recv;
        	packet1.num_of_units = packet_in.num_of_units;
        	packet1.address = packet_in.address;
        	packet1.remote_address = packet_in.remote_address;
        
        	mav_array_memcpy(packet1.timestamp_master_request_1, packet_in.timestamp_master_request_1, sizeof(uint64_t)*10);
        	mav_array_memcpy(packet1.timestamp_slave_reply, packet_in.timestamp_slave_reply, sizeof(uint64_t)*10);
        	mav_array_memcpy(packet1.timestamp_master_request_2, packet_in.timestamp_master_request_2, sizeof(uint64_t)*10);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_10_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_2way_multi_range_raw_10_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_10_pack(system_id, component_id, &msg , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_10_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_10_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_10_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_2way_multi_range_raw_10_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_10_send(MAVLINK_COMM_1 , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_10_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_2way_multi_range_raw_4(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_2way_multi_range_raw_4_t packet_in = {
		93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,{ 93372036854777319, 93372036854777320, 93372036854777321, 93372036854777322 },{ 93372036854779335, 93372036854779336, 93372036854779337, 93372036854779338 },{ 93372036854781351, 93372036854781352, 93372036854781353, 93372036854781354 },109,176,243
    };
	mavlink_uwb_2way_multi_range_raw_4_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.timestamp_master_request_1_recv = packet_in.timestamp_master_request_1_recv;
        	packet1.timestamp_slave_reply_send = packet_in.timestamp_slave_reply_send;
        	packet1.timestamp_master_request_2_recv = packet_in.timestamp_master_request_2_recv;
        	packet1.num_of_units = packet_in.num_of_units;
        	packet1.address = packet_in.address;
        	packet1.remote_address = packet_in.remote_address;
        
        	mav_array_memcpy(packet1.timestamp_master_request_1, packet_in.timestamp_master_request_1, sizeof(uint64_t)*4);
        	mav_array_memcpy(packet1.timestamp_slave_reply, packet_in.timestamp_slave_reply, sizeof(uint64_t)*4);
        	mav_array_memcpy(packet1.timestamp_master_request_2, packet_in.timestamp_master_request_2, sizeof(uint64_t)*4);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_4_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_2way_multi_range_raw_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_4_pack(system_id, component_id, &msg , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_4_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_2way_multi_range_raw_4_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_4_send(MAVLINK_COMM_1 , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_4_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_2way_multi_range_raw_5(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_2way_multi_range_raw_5_t packet_in = {
		93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,{ 93372036854777319, 93372036854777320, 93372036854777321, 93372036854777322, 93372036854777323 },{ 93372036854779839, 93372036854779840, 93372036854779841, 93372036854779842, 93372036854779843 },{ 93372036854782359, 93372036854782360, 93372036854782361, 93372036854782362, 93372036854782363 },181,248,59
    };
	mavlink_uwb_2way_multi_range_raw_5_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.timestamp_master_request_1_recv = packet_in.timestamp_master_request_1_recv;
        	packet1.timestamp_slave_reply_send = packet_in.timestamp_slave_reply_send;
        	packet1.timestamp_master_request_2_recv = packet_in.timestamp_master_request_2_recv;
        	packet1.num_of_units = packet_in.num_of_units;
        	packet1.address = packet_in.address;
        	packet1.remote_address = packet_in.remote_address;
        
        	mav_array_memcpy(packet1.timestamp_master_request_1, packet_in.timestamp_master_request_1, sizeof(uint64_t)*5);
        	mav_array_memcpy(packet1.timestamp_slave_reply, packet_in.timestamp_slave_reply, sizeof(uint64_t)*5);
        	mav_array_memcpy(packet1.timestamp_master_request_2, packet_in.timestamp_master_request_2, sizeof(uint64_t)*5);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_5_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_2way_multi_range_raw_5_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_5_pack(system_id, component_id, &msg , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_5_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_5_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_5_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_2way_multi_range_raw_5_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_2way_multi_range_raw_5_send(MAVLINK_COMM_1 , packet1.num_of_units , packet1.address , packet1.remote_address , packet1.timestamp_master_request_1_recv , packet1.timestamp_slave_reply_send , packet1.timestamp_master_request_2_recv , packet1.timestamp_master_request_1 , packet1.timestamp_slave_reply , packet1.timestamp_master_request_2 );
	mavlink_msg_uwb_2way_multi_range_raw_5_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_status_t packet_in = {
		5,"BCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU"
    };
	mavlink_uwb_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.address = packet_in.address;
        
        	mav_array_memcpy(packet1.description, packet_in.description, sizeof(char)*255);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_status_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_status_pack(system_id, component_id, &msg , packet1.address , packet1.description );
	mavlink_msg_uwb_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.address , packet1.description );
	mavlink_msg_uwb_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_status_send(MAVLINK_COMM_1 , packet1.address , packet1.description );
	mavlink_msg_uwb_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_error(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_error_t packet_in = {
		5,72,"CDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUV"
    };
	mavlink_uwb_error_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.address = packet_in.address;
        	packet1.type = packet_in.type;
        
        	mav_array_memcpy(packet1.description, packet_in.description, sizeof(char)*255);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_error_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_error_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_error_pack(system_id, component_id, &msg , packet1.address , packet1.type , packet1.description );
	mavlink_msg_uwb_error_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_error_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.address , packet1.type , packet1.description );
	mavlink_msg_uwb_error_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_error_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_error_send(MAVLINK_COMM_1 , packet1.address , packet1.type , packet1.description );
	mavlink_msg_uwb_error_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_prototyping(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_prototyping_t packet_in = {
		{ 93372036854775807, 93372036854775808, 93372036854775809, 93372036854775810, 93372036854775811, 93372036854775812, 93372036854775813, 93372036854775814, 93372036854775815, 93372036854775816 },{ 577.0, 578.0, 579.0, 580.0, 581.0, 582.0, 583.0, 584.0, 585.0, 586.0 },109
    };
	mavlink_uwb_prototyping_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.type = packet_in.type;
        
        	mav_array_memcpy(packet1.integers, packet_in.integers, sizeof(uint64_t)*10);
        	mav_array_memcpy(packet1.floats, packet_in.floats, sizeof(float)*10);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_prototyping_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_prototyping_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_prototyping_pack(system_id, component_id, &msg , packet1.type , packet1.integers , packet1.floats );
	mavlink_msg_uwb_prototyping_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_prototyping_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.type , packet1.integers , packet1.floats );
	mavlink_msg_uwb_prototyping_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_prototyping_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_prototyping_send(MAVLINK_COMM_1 , packet1.type , packet1.integers , packet1.floats );
	mavlink_msg_uwb_prototyping_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_range(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_range_t packet_in = {
		963497464,45.0,73.0,41,108
    };
	mavlink_uwb_range_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.stamp_us = packet_in.stamp_us;
        	packet1.round_trip_time = packet_in.round_trip_time;
        	packet1.range = packet_in.range;
        	packet1.address = packet_in.address;
        	packet1.remote_address = packet_in.remote_address;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_range_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_pack(system_id, component_id, &msg , packet1.address , packet1.remote_address , packet1.stamp_us , packet1.round_trip_time , packet1.range );
	mavlink_msg_uwb_range_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.address , packet1.remote_address , packet1.stamp_us , packet1.round_trip_time , packet1.range );
	mavlink_msg_uwb_range_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_range_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_send(MAVLINK_COMM_1 , packet1.address , packet1.remote_address , packet1.stamp_us , packet1.round_trip_time , packet1.range );
	mavlink_msg_uwb_range_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_range_stats(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_range_stats_t packet_in = {
		963497464,45.0,73.0,17859,17963,18067,18171,18275,18379,18483,18587,18691,18795,18899,19003,19107,19211,19315,19419,137,204
    };
	mavlink_uwb_range_stats_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.stamp_us = packet_in.stamp_us;
        	packet1.round_trip_time = packet_in.round_trip_time;
        	packet1.range = packet_in.range;
        	packet1.std_noise_1 = packet_in.std_noise_1;
        	packet1.std_noise_2 = packet_in.std_noise_2;
        	packet1.preamble_acc_count_1 = packet_in.preamble_acc_count_1;
        	packet1.preamble_acc_count_2 = packet_in.preamble_acc_count_2;
        	packet1.first_path_index_1 = packet_in.first_path_index_1;
        	packet1.first_path_index_2 = packet_in.first_path_index_2;
        	packet1.first_path_amp_1_1 = packet_in.first_path_amp_1_1;
        	packet1.first_path_amp_1_2 = packet_in.first_path_amp_1_2;
        	packet1.first_path_amp_2_1 = packet_in.first_path_amp_2_1;
        	packet1.first_path_amp_2_2 = packet_in.first_path_amp_2_2;
        	packet1.first_path_amp_3_1 = packet_in.first_path_amp_3_1;
        	packet1.first_path_amp_3_2 = packet_in.first_path_amp_3_2;
        	packet1.channel_impulse_response_power_1 = packet_in.channel_impulse_response_power_1;
        	packet1.channel_impulse_response_power_2 = packet_in.channel_impulse_response_power_2;
        	packet1.prf_1 = packet_in.prf_1;
        	packet1.prf_2 = packet_in.prf_2;
        	packet1.address = packet_in.address;
        	packet1.remote_address = packet_in.remote_address;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_stats_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_range_stats_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_stats_pack(system_id, component_id, &msg , packet1.address , packet1.remote_address , packet1.stamp_us , packet1.round_trip_time , packet1.range , packet1.std_noise_1 , packet1.std_noise_2 , packet1.preamble_acc_count_1 , packet1.preamble_acc_count_2 , packet1.first_path_index_1 , packet1.first_path_index_2 , packet1.first_path_amp_1_1 , packet1.first_path_amp_1_2 , packet1.first_path_amp_2_1 , packet1.first_path_amp_2_2 , packet1.first_path_amp_3_1 , packet1.first_path_amp_3_2 , packet1.channel_impulse_response_power_1 , packet1.channel_impulse_response_power_2 , packet1.prf_1 , packet1.prf_2 );
	mavlink_msg_uwb_range_stats_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_stats_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.address , packet1.remote_address , packet1.stamp_us , packet1.round_trip_time , packet1.range , packet1.std_noise_1 , packet1.std_noise_2 , packet1.preamble_acc_count_1 , packet1.preamble_acc_count_2 , packet1.first_path_index_1 , packet1.first_path_index_2 , packet1.first_path_amp_1_1 , packet1.first_path_amp_1_2 , packet1.first_path_amp_2_1 , packet1.first_path_amp_2_2 , packet1.first_path_amp_3_1 , packet1.first_path_amp_3_2 , packet1.channel_impulse_response_power_1 , packet1.channel_impulse_response_power_2 , packet1.prf_1 , packet1.prf_2 );
	mavlink_msg_uwb_range_stats_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_range_stats_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_stats_send(MAVLINK_COMM_1 , packet1.address , packet1.remote_address , packet1.stamp_us , packet1.round_trip_time , packet1.range , packet1.std_noise_1 , packet1.std_noise_2 , packet1.preamble_acc_count_1 , packet1.preamble_acc_count_2 , packet1.first_path_index_1 , packet1.first_path_index_2 , packet1.first_path_amp_1_1 , packet1.first_path_amp_1_2 , packet1.first_path_amp_2_1 , packet1.first_path_amp_2_2 , packet1.first_path_amp_3_1 , packet1.first_path_amp_3_2 , packet1.channel_impulse_response_power_1 , packet1.channel_impulse_response_power_2 , packet1.prf_1 , packet1.prf_2 );
	mavlink_msg_uwb_range_stats_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_range_batch_2(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_range_batch_2_t packet_in = {
		{ 17.0, 18.0 },{ 29, 30 },163
    };
	mavlink_uwb_range_batch_2_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.remote_address = packet_in.remote_address;
        
        	mav_array_memcpy(packet1.range, packet_in.range, sizeof(float)*2);
        	mav_array_memcpy(packet1.addresses, packet_in.addresses, sizeof(uint8_t)*2);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_2_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_range_batch_2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_2_pack(system_id, component_id, &msg , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_2_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_range_batch_2_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_2_send(MAVLINK_COMM_1 , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_2_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_range_batch_3(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_range_batch_3_t packet_in = {
		{ 17.0, 18.0, 19.0 },{ 41, 42, 43 },242
    };
	mavlink_uwb_range_batch_3_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.remote_address = packet_in.remote_address;
        
        	mav_array_memcpy(packet1.range, packet_in.range, sizeof(float)*3);
        	mav_array_memcpy(packet1.addresses, packet_in.addresses, sizeof(uint8_t)*3);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_3_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_range_batch_3_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_3_pack(system_id, component_id, &msg , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_3_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_3_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_3_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_range_batch_3_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_3_send(MAVLINK_COMM_1 , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_3_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_range_batch_4(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_range_batch_4_t packet_in = {
		{ 17.0, 18.0, 19.0, 20.0 },{ 53, 54, 55, 56 },65
    };
	mavlink_uwb_range_batch_4_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.remote_address = packet_in.remote_address;
        
        	mav_array_memcpy(packet1.range, packet_in.range, sizeof(float)*4);
        	mav_array_memcpy(packet1.addresses, packet_in.addresses, sizeof(uint8_t)*4);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_4_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_range_batch_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_4_pack(system_id, component_id, &msg , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_4_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_4_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_range_batch_4_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_4_send(MAVLINK_COMM_1 , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_4_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb_range_batch_5(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_uwb_range_batch_5_t packet_in = {
		{ 17.0, 18.0, 19.0, 20.0, 21.0 },{ 65, 66, 67, 68, 69 },144
    };
	mavlink_uwb_range_batch_5_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.remote_address = packet_in.remote_address;
        
        	mav_array_memcpy(packet1.range, packet_in.range, sizeof(float)*5);
        	mav_array_memcpy(packet1.addresses, packet_in.addresses, sizeof(uint8_t)*5);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_5_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_uwb_range_batch_5_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_5_pack(system_id, component_id, &msg , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_5_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_5_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_5_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_uwb_range_batch_5_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_uwb_range_batch_5_send(MAVLINK_COMM_1 , packet1.addresses , packet1.remote_address , packet1.range );
	mavlink_msg_uwb_range_batch_5_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_uwb(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_uwb_multi_range_raw_4(system_id, component_id, last_msg);
	mavlink_test_uwb_2way_multi_range_raw_10(system_id, component_id, last_msg);
	mavlink_test_uwb_2way_multi_range_raw_4(system_id, component_id, last_msg);
	mavlink_test_uwb_2way_multi_range_raw_5(system_id, component_id, last_msg);
	mavlink_test_uwb_status(system_id, component_id, last_msg);
	mavlink_test_uwb_error(system_id, component_id, last_msg);
	mavlink_test_uwb_prototyping(system_id, component_id, last_msg);
	mavlink_test_uwb_range(system_id, component_id, last_msg);
	mavlink_test_uwb_range_stats(system_id, component_id, last_msg);
	mavlink_test_uwb_range_batch_2(system_id, component_id, last_msg);
	mavlink_test_uwb_range_batch_3(system_id, component_id, last_msg);
	mavlink_test_uwb_range_batch_4(system_id, component_id, last_msg);
	mavlink_test_uwb_range_batch_5(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // UWB_TESTSUITE_H
