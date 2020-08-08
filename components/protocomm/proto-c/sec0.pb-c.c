/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: sec0.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "sec0.pb-c.h"
void   s0_session_cmd__init
                     (S0SessionCmd         *message)
{
  static const S0SessionCmd init_value = S0_SESSION_CMD__INIT;
  *message = init_value;
}
size_t s0_session_cmd__get_packed_size
                     (const S0SessionCmd *message)
{
  assert(message->base.descriptor == &s0_session_cmd__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t s0_session_cmd__pack
                     (const S0SessionCmd *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &s0_session_cmd__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t s0_session_cmd__pack_to_buffer
                     (const S0SessionCmd *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &s0_session_cmd__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
S0SessionCmd *
       s0_session_cmd__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (S0SessionCmd *)
     protobuf_c_message_unpack (&s0_session_cmd__descriptor,
                                allocator, len, data);
}
void   s0_session_cmd__free_unpacked
                     (S0SessionCmd *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &s0_session_cmd__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   s0_session_resp__init
                     (S0SessionResp         *message)
{
  static const S0SessionResp init_value = S0_SESSION_RESP__INIT;
  *message = init_value;
}
size_t s0_session_resp__get_packed_size
                     (const S0SessionResp *message)
{
  assert(message->base.descriptor == &s0_session_resp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t s0_session_resp__pack
                     (const S0SessionResp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &s0_session_resp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t s0_session_resp__pack_to_buffer
                     (const S0SessionResp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &s0_session_resp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
S0SessionResp *
       s0_session_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (S0SessionResp *)
     protobuf_c_message_unpack (&s0_session_resp__descriptor,
                                allocator, len, data);
}
void   s0_session_resp__free_unpacked
                     (S0SessionResp *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &s0_session_resp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sec0_payload__init
                     (Sec0Payload         *message)
{
  static const Sec0Payload init_value = SEC0_PAYLOAD__INIT;
  *message = init_value;
}
size_t sec0_payload__get_packed_size
                     (const Sec0Payload *message)
{
  assert(message->base.descriptor == &sec0_payload__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sec0_payload__pack
                     (const Sec0Payload *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sec0_payload__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sec0_payload__pack_to_buffer
                     (const Sec0Payload *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sec0_payload__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Sec0Payload *
       sec0_payload__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Sec0Payload *)
     protobuf_c_message_unpack (&sec0_payload__descriptor,
                                allocator, len, data);
}
void   sec0_payload__free_unpacked
                     (Sec0Payload *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &sec0_payload__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
#define s0_session_cmd__field_descriptors NULL
#define s0_session_cmd__field_indices_by_name NULL
#define s0_session_cmd__number_ranges NULL
const ProtobufCMessageDescriptor s0_session_cmd__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "S0SessionCmd",
  "S0SessionCmd",
  "S0SessionCmd",
  "",
  sizeof(S0SessionCmd),
  0,
  s0_session_cmd__field_descriptors,
  s0_session_cmd__field_indices_by_name,
  0,  s0_session_cmd__number_ranges,
  (ProtobufCMessageInit) s0_session_cmd__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor s0_session_resp__field_descriptors[1] =
{
  {
    "status",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(S0SessionResp, status),
    &status__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned s0_session_resp__field_indices_by_name[] = {
  0,   /* field[0] = status */
};
static const ProtobufCIntRange s0_session_resp__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor s0_session_resp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "S0SessionResp",
  "S0SessionResp",
  "S0SessionResp",
  "",
  sizeof(S0SessionResp),
  1,
  s0_session_resp__field_descriptors,
  s0_session_resp__field_indices_by_name,
  1,  s0_session_resp__number_ranges,
  (ProtobufCMessageInit) s0_session_resp__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sec0_payload__field_descriptors[3] =
{
  {
    "msg",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Sec0Payload, msg),
    &sec0_msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "sc",
    20,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Sec0Payload, payload_case),
    offsetof(Sec0Payload, sc),
    &s0_session_cmd__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "sr",
    21,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Sec0Payload, payload_case),
    offsetof(Sec0Payload, sr),
    &s0_session_resp__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sec0_payload__field_indices_by_name[] = {
  0,   /* field[0] = msg */
  1,   /* field[1] = sc */
  2,   /* field[2] = sr */
};
static const ProtobufCIntRange sec0_payload__number_ranges[2 + 1] =
{
  { 1, 0 },
  { 20, 1 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor sec0_payload__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Sec0Payload",
  "Sec0Payload",
  "Sec0Payload",
  "",
  sizeof(Sec0Payload),
  3,
  sec0_payload__field_descriptors,
  sec0_payload__field_indices_by_name,
  2,  sec0_payload__number_ranges,
  (ProtobufCMessageInit) sec0_payload__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue sec0_msg_type__enum_values_by_number[2] =
{
  { "S0_Session_Command", "SEC0_MSG_TYPE__S0_Session_Command", 0 },
  { "S0_Session_Response", "SEC0_MSG_TYPE__S0_Session_Response", 1 },
};
static const ProtobufCIntRange sec0_msg_type__value_ranges[] = {
{0, 0},{0, 2}
};
static const ProtobufCEnumValueIndex sec0_msg_type__enum_values_by_name[2] =
{
  { "S0_Session_Command", 0 },
  { "S0_Session_Response", 1 },
};
const ProtobufCEnumDescriptor sec0_msg_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Sec0MsgType",
  "Sec0MsgType",
  "Sec0MsgType",
  "",
  2,
  sec0_msg_type__enum_values_by_number,
  2,
  sec0_msg_type__enum_values_by_name,
  1,
  sec0_msg_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
