// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message_req_connect.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_message_5freq_5fconnect_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_message_5freq_5fconnect_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_message_5freq_5fconnect_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_message_5freq_5fconnect_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_message_5freq_5fconnect_2eproto;
namespace message {
namespace protobuf {
class MessageReqConnectProtobuf;
class MessageReqConnectProtobufDefaultTypeInternal;
extern MessageReqConnectProtobufDefaultTypeInternal _MessageReqConnectProtobuf_default_instance_;
}  // namespace protobuf
}  // namespace message
PROTOBUF_NAMESPACE_OPEN
template<> ::message::protobuf::MessageReqConnectProtobuf* Arena::CreateMaybeMessage<::message::protobuf::MessageReqConnectProtobuf>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace message {
namespace protobuf {

// ===================================================================

class MessageReqConnectProtobuf :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:message.protobuf.MessageReqConnectProtobuf) */ {
 public:
  MessageReqConnectProtobuf();
  virtual ~MessageReqConnectProtobuf();

  MessageReqConnectProtobuf(const MessageReqConnectProtobuf& from);
  MessageReqConnectProtobuf(MessageReqConnectProtobuf&& from) noexcept
    : MessageReqConnectProtobuf() {
    *this = ::std::move(from);
  }

  inline MessageReqConnectProtobuf& operator=(const MessageReqConnectProtobuf& from) {
    CopyFrom(from);
    return *this;
  }
  inline MessageReqConnectProtobuf& operator=(MessageReqConnectProtobuf&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MessageReqConnectProtobuf& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageReqConnectProtobuf* internal_default_instance() {
    return reinterpret_cast<const MessageReqConnectProtobuf*>(
               &_MessageReqConnectProtobuf_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MessageReqConnectProtobuf& a, MessageReqConnectProtobuf& b) {
    a.Swap(&b);
  }
  inline void Swap(MessageReqConnectProtobuf* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MessageReqConnectProtobuf* New() const final {
    return CreateMaybeMessage<MessageReqConnectProtobuf>(nullptr);
  }

  MessageReqConnectProtobuf* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MessageReqConnectProtobuf>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MessageReqConnectProtobuf& from);
  void MergeFrom(const MessageReqConnectProtobuf& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MessageReqConnectProtobuf* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "message.protobuf.MessageReqConnectProtobuf";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_message_5freq_5fconnect_2eproto);
    return ::descriptor_table_message_5freq_5fconnect_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kOrigUriFieldNumber = 1,
    kDestUriFieldNumber = 2,
  };
  // string orig_uri = 1;
  void clear_orig_uri();
  const std::string& orig_uri() const;
  void set_orig_uri(const std::string& value);
  void set_orig_uri(std::string&& value);
  void set_orig_uri(const char* value);
  void set_orig_uri(const char* value, size_t size);
  std::string* mutable_orig_uri();
  std::string* release_orig_uri();
  void set_allocated_orig_uri(std::string* orig_uri);
  private:
  const std::string& _internal_orig_uri() const;
  void _internal_set_orig_uri(const std::string& value);
  std::string* _internal_mutable_orig_uri();
  public:

  // string dest_uri = 2;
  void clear_dest_uri();
  const std::string& dest_uri() const;
  void set_dest_uri(const std::string& value);
  void set_dest_uri(std::string&& value);
  void set_dest_uri(const char* value);
  void set_dest_uri(const char* value, size_t size);
  std::string* mutable_dest_uri();
  std::string* release_dest_uri();
  void set_allocated_dest_uri(std::string* dest_uri);
  private:
  const std::string& _internal_dest_uri() const;
  void _internal_set_dest_uri(const std::string& value);
  std::string* _internal_mutable_dest_uri();
  public:

  // @@protoc_insertion_point(class_scope:message.protobuf.MessageReqConnectProtobuf)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr orig_uri_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr dest_uri_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_message_5freq_5fconnect_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MessageReqConnectProtobuf

// string orig_uri = 1;
inline void MessageReqConnectProtobuf::clear_orig_uri() {
  orig_uri_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& MessageReqConnectProtobuf::orig_uri() const {
  // @@protoc_insertion_point(field_get:message.protobuf.MessageReqConnectProtobuf.orig_uri)
  return _internal_orig_uri();
}
inline void MessageReqConnectProtobuf::set_orig_uri(const std::string& value) {
  _internal_set_orig_uri(value);
  // @@protoc_insertion_point(field_set:message.protobuf.MessageReqConnectProtobuf.orig_uri)
}
inline std::string* MessageReqConnectProtobuf::mutable_orig_uri() {
  // @@protoc_insertion_point(field_mutable:message.protobuf.MessageReqConnectProtobuf.orig_uri)
  return _internal_mutable_orig_uri();
}
inline const std::string& MessageReqConnectProtobuf::_internal_orig_uri() const {
  return orig_uri_.GetNoArena();
}
inline void MessageReqConnectProtobuf::_internal_set_orig_uri(const std::string& value) {
  
  orig_uri_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void MessageReqConnectProtobuf::set_orig_uri(std::string&& value) {
  
  orig_uri_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.protobuf.MessageReqConnectProtobuf.orig_uri)
}
inline void MessageReqConnectProtobuf::set_orig_uri(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  orig_uri_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.protobuf.MessageReqConnectProtobuf.orig_uri)
}
inline void MessageReqConnectProtobuf::set_orig_uri(const char* value, size_t size) {
  
  orig_uri_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.protobuf.MessageReqConnectProtobuf.orig_uri)
}
inline std::string* MessageReqConnectProtobuf::_internal_mutable_orig_uri() {
  
  return orig_uri_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* MessageReqConnectProtobuf::release_orig_uri() {
  // @@protoc_insertion_point(field_release:message.protobuf.MessageReqConnectProtobuf.orig_uri)
  
  return orig_uri_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void MessageReqConnectProtobuf::set_allocated_orig_uri(std::string* orig_uri) {
  if (orig_uri != nullptr) {
    
  } else {
    
  }
  orig_uri_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), orig_uri);
  // @@protoc_insertion_point(field_set_allocated:message.protobuf.MessageReqConnectProtobuf.orig_uri)
}

// string dest_uri = 2;
inline void MessageReqConnectProtobuf::clear_dest_uri() {
  dest_uri_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& MessageReqConnectProtobuf::dest_uri() const {
  // @@protoc_insertion_point(field_get:message.protobuf.MessageReqConnectProtobuf.dest_uri)
  return _internal_dest_uri();
}
inline void MessageReqConnectProtobuf::set_dest_uri(const std::string& value) {
  _internal_set_dest_uri(value);
  // @@protoc_insertion_point(field_set:message.protobuf.MessageReqConnectProtobuf.dest_uri)
}
inline std::string* MessageReqConnectProtobuf::mutable_dest_uri() {
  // @@protoc_insertion_point(field_mutable:message.protobuf.MessageReqConnectProtobuf.dest_uri)
  return _internal_mutable_dest_uri();
}
inline const std::string& MessageReqConnectProtobuf::_internal_dest_uri() const {
  return dest_uri_.GetNoArena();
}
inline void MessageReqConnectProtobuf::_internal_set_dest_uri(const std::string& value) {
  
  dest_uri_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void MessageReqConnectProtobuf::set_dest_uri(std::string&& value) {
  
  dest_uri_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.protobuf.MessageReqConnectProtobuf.dest_uri)
}
inline void MessageReqConnectProtobuf::set_dest_uri(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  dest_uri_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.protobuf.MessageReqConnectProtobuf.dest_uri)
}
inline void MessageReqConnectProtobuf::set_dest_uri(const char* value, size_t size) {
  
  dest_uri_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.protobuf.MessageReqConnectProtobuf.dest_uri)
}
inline std::string* MessageReqConnectProtobuf::_internal_mutable_dest_uri() {
  
  return dest_uri_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* MessageReqConnectProtobuf::release_dest_uri() {
  // @@protoc_insertion_point(field_release:message.protobuf.MessageReqConnectProtobuf.dest_uri)
  
  return dest_uri_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void MessageReqConnectProtobuf::set_allocated_dest_uri(std::string* dest_uri) {
  if (dest_uri != nullptr) {
    
  } else {
    
  }
  dest_uri_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), dest_uri);
  // @@protoc_insertion_point(field_set_allocated:message.protobuf.MessageReqConnectProtobuf.dest_uri)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf
}  // namespace message

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_message_5freq_5fconnect_2eproto
