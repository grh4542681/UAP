// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: emample.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_emample_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_emample_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_emample_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_emample_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_emample_2eproto;
namespace message {
namespace package {
class Example;
class ExampleDefaultTypeInternal;
extern ExampleDefaultTypeInternal _Example_default_instance_;
}  // namespace package
}  // namespace message
PROTOBUF_NAMESPACE_OPEN
template<> ::message::package::Example* Arena::CreateMaybeMessage<::message::package::Example>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace message {
namespace package {

// ===================================================================

class Example :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:message.package.Example) */ {
 public:
  Example();
  virtual ~Example();

  Example(const Example& from);
  Example(Example&& from) noexcept
    : Example() {
    *this = ::std::move(from);
  }

  inline Example& operator=(const Example& from) {
    CopyFrom(from);
    return *this;
  }
  inline Example& operator=(Example&& from) noexcept {
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
  static const Example& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Example* internal_default_instance() {
    return reinterpret_cast<const Example*>(
               &_Example_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Example& a, Example& b) {
    a.Swap(&b);
  }
  inline void Swap(Example* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Example* New() const final {
    return CreateMaybeMessage<Example>(nullptr);
  }

  Example* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Example>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Example& from);
  void MergeFrom(const Example& from);
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
  void InternalSwap(Example* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "message.package.Example";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_emample_2eproto);
    return ::descriptor_table_emample_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRepeatedInt32ValFieldNumber = 4,
    kRepeatedStringValFieldNumber = 5,
    kStringValFieldNumber = 1,
    kBytesValFieldNumber = 2,
  };
  // repeated int32 repeatedInt32Val = 4;
  int repeatedint32val_size() const;
  private:
  int _internal_repeatedint32val_size() const;
  public:
  void clear_repeatedint32val();
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_repeatedint32val(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      _internal_repeatedint32val() const;
  void _internal_add_repeatedint32val(::PROTOBUF_NAMESPACE_ID::int32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      _internal_mutable_repeatedint32val();
  public:
  ::PROTOBUF_NAMESPACE_ID::int32 repeatedint32val(int index) const;
  void set_repeatedint32val(int index, ::PROTOBUF_NAMESPACE_ID::int32 value);
  void add_repeatedint32val(::PROTOBUF_NAMESPACE_ID::int32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      repeatedint32val() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      mutable_repeatedint32val();

  // repeated string repeatedStringVal = 5;
  int repeatedstringval_size() const;
  private:
  int _internal_repeatedstringval_size() const;
  public:
  void clear_repeatedstringval();
  const std::string& repeatedstringval(int index) const;
  std::string* mutable_repeatedstringval(int index);
  void set_repeatedstringval(int index, const std::string& value);
  void set_repeatedstringval(int index, std::string&& value);
  void set_repeatedstringval(int index, const char* value);
  void set_repeatedstringval(int index, const char* value, size_t size);
  std::string* add_repeatedstringval();
  void add_repeatedstringval(const std::string& value);
  void add_repeatedstringval(std::string&& value);
  void add_repeatedstringval(const char* value);
  void add_repeatedstringval(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& repeatedstringval() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_repeatedstringval();
  private:
  const std::string& _internal_repeatedstringval(int index) const;
  std::string* _internal_add_repeatedstringval();
  public:

  // string stringVal = 1;
  void clear_stringval();
  const std::string& stringval() const;
  void set_stringval(const std::string& value);
  void set_stringval(std::string&& value);
  void set_stringval(const char* value);
  void set_stringval(const char* value, size_t size);
  std::string* mutable_stringval();
  std::string* release_stringval();
  void set_allocated_stringval(std::string* stringval);
  private:
  const std::string& _internal_stringval() const;
  void _internal_set_stringval(const std::string& value);
  std::string* _internal_mutable_stringval();
  public:

  // bytes bytesVal = 2;
  void clear_bytesval();
  const std::string& bytesval() const;
  void set_bytesval(const std::string& value);
  void set_bytesval(std::string&& value);
  void set_bytesval(const char* value);
  void set_bytesval(const void* value, size_t size);
  std::string* mutable_bytesval();
  std::string* release_bytesval();
  void set_allocated_bytesval(std::string* bytesval);
  private:
  const std::string& _internal_bytesval() const;
  void _internal_set_bytesval(const std::string& value);
  std::string* _internal_mutable_bytesval();
  public:

  // @@protoc_insertion_point(class_scope:message.package.Example)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 > repeatedint32val_;
  mutable std::atomic<int> _repeatedint32val_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> repeatedstringval_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr stringval_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr bytesval_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_emample_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Example

// string stringVal = 1;
inline void Example::clear_stringval() {
  stringval_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Example::stringval() const {
  // @@protoc_insertion_point(field_get:message.package.Example.stringVal)
  return _internal_stringval();
}
inline void Example::set_stringval(const std::string& value) {
  _internal_set_stringval(value);
  // @@protoc_insertion_point(field_set:message.package.Example.stringVal)
}
inline std::string* Example::mutable_stringval() {
  // @@protoc_insertion_point(field_mutable:message.package.Example.stringVal)
  return _internal_mutable_stringval();
}
inline const std::string& Example::_internal_stringval() const {
  return stringval_.GetNoArena();
}
inline void Example::_internal_set_stringval(const std::string& value) {
  
  stringval_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Example::set_stringval(std::string&& value) {
  
  stringval_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.package.Example.stringVal)
}
inline void Example::set_stringval(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  stringval_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.package.Example.stringVal)
}
inline void Example::set_stringval(const char* value, size_t size) {
  
  stringval_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.package.Example.stringVal)
}
inline std::string* Example::_internal_mutable_stringval() {
  
  return stringval_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Example::release_stringval() {
  // @@protoc_insertion_point(field_release:message.package.Example.stringVal)
  
  return stringval_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Example::set_allocated_stringval(std::string* stringval) {
  if (stringval != nullptr) {
    
  } else {
    
  }
  stringval_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), stringval);
  // @@protoc_insertion_point(field_set_allocated:message.package.Example.stringVal)
}

// bytes bytesVal = 2;
inline void Example::clear_bytesval() {
  bytesval_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Example::bytesval() const {
  // @@protoc_insertion_point(field_get:message.package.Example.bytesVal)
  return _internal_bytesval();
}
inline void Example::set_bytesval(const std::string& value) {
  _internal_set_bytesval(value);
  // @@protoc_insertion_point(field_set:message.package.Example.bytesVal)
}
inline std::string* Example::mutable_bytesval() {
  // @@protoc_insertion_point(field_mutable:message.package.Example.bytesVal)
  return _internal_mutable_bytesval();
}
inline const std::string& Example::_internal_bytesval() const {
  return bytesval_.GetNoArena();
}
inline void Example::_internal_set_bytesval(const std::string& value) {
  
  bytesval_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Example::set_bytesval(std::string&& value) {
  
  bytesval_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.package.Example.bytesVal)
}
inline void Example::set_bytesval(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  bytesval_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.package.Example.bytesVal)
}
inline void Example::set_bytesval(const void* value, size_t size) {
  
  bytesval_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.package.Example.bytesVal)
}
inline std::string* Example::_internal_mutable_bytesval() {
  
  return bytesval_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Example::release_bytesval() {
  // @@protoc_insertion_point(field_release:message.package.Example.bytesVal)
  
  return bytesval_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Example::set_allocated_bytesval(std::string* bytesval) {
  if (bytesval != nullptr) {
    
  } else {
    
  }
  bytesval_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), bytesval);
  // @@protoc_insertion_point(field_set_allocated:message.package.Example.bytesVal)
}

// repeated int32 repeatedInt32Val = 4;
inline int Example::_internal_repeatedint32val_size() const {
  return repeatedint32val_.size();
}
inline int Example::repeatedint32val_size() const {
  return _internal_repeatedint32val_size();
}
inline void Example::clear_repeatedint32val() {
  repeatedint32val_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Example::_internal_repeatedint32val(int index) const {
  return repeatedint32val_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Example::repeatedint32val(int index) const {
  // @@protoc_insertion_point(field_get:message.package.Example.repeatedInt32Val)
  return _internal_repeatedint32val(index);
}
inline void Example::set_repeatedint32val(int index, ::PROTOBUF_NAMESPACE_ID::int32 value) {
  repeatedint32val_.Set(index, value);
  // @@protoc_insertion_point(field_set:message.package.Example.repeatedInt32Val)
}
inline void Example::_internal_add_repeatedint32val(::PROTOBUF_NAMESPACE_ID::int32 value) {
  repeatedint32val_.Add(value);
}
inline void Example::add_repeatedint32val(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_add_repeatedint32val(value);
  // @@protoc_insertion_point(field_add:message.package.Example.repeatedInt32Val)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
Example::_internal_repeatedint32val() const {
  return repeatedint32val_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
Example::repeatedint32val() const {
  // @@protoc_insertion_point(field_list:message.package.Example.repeatedInt32Val)
  return _internal_repeatedint32val();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
Example::_internal_mutable_repeatedint32val() {
  return &repeatedint32val_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
Example::mutable_repeatedint32val() {
  // @@protoc_insertion_point(field_mutable_list:message.package.Example.repeatedInt32Val)
  return _internal_mutable_repeatedint32val();
}

// repeated string repeatedStringVal = 5;
inline int Example::_internal_repeatedstringval_size() const {
  return repeatedstringval_.size();
}
inline int Example::repeatedstringval_size() const {
  return _internal_repeatedstringval_size();
}
inline void Example::clear_repeatedstringval() {
  repeatedstringval_.Clear();
}
inline std::string* Example::add_repeatedstringval() {
  // @@protoc_insertion_point(field_add_mutable:message.package.Example.repeatedStringVal)
  return _internal_add_repeatedstringval();
}
inline const std::string& Example::_internal_repeatedstringval(int index) const {
  return repeatedstringval_.Get(index);
}
inline const std::string& Example::repeatedstringval(int index) const {
  // @@protoc_insertion_point(field_get:message.package.Example.repeatedStringVal)
  return _internal_repeatedstringval(index);
}
inline std::string* Example::mutable_repeatedstringval(int index) {
  // @@protoc_insertion_point(field_mutable:message.package.Example.repeatedStringVal)
  return repeatedstringval_.Mutable(index);
}
inline void Example::set_repeatedstringval(int index, const std::string& value) {
  // @@protoc_insertion_point(field_set:message.package.Example.repeatedStringVal)
  repeatedstringval_.Mutable(index)->assign(value);
}
inline void Example::set_repeatedstringval(int index, std::string&& value) {
  // @@protoc_insertion_point(field_set:message.package.Example.repeatedStringVal)
  repeatedstringval_.Mutable(index)->assign(std::move(value));
}
inline void Example::set_repeatedstringval(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  repeatedstringval_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:message.package.Example.repeatedStringVal)
}
inline void Example::set_repeatedstringval(int index, const char* value, size_t size) {
  repeatedstringval_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:message.package.Example.repeatedStringVal)
}
inline std::string* Example::_internal_add_repeatedstringval() {
  return repeatedstringval_.Add();
}
inline void Example::add_repeatedstringval(const std::string& value) {
  repeatedstringval_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:message.package.Example.repeatedStringVal)
}
inline void Example::add_repeatedstringval(std::string&& value) {
  repeatedstringval_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:message.package.Example.repeatedStringVal)
}
inline void Example::add_repeatedstringval(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  repeatedstringval_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:message.package.Example.repeatedStringVal)
}
inline void Example::add_repeatedstringval(const char* value, size_t size) {
  repeatedstringval_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:message.package.Example.repeatedStringVal)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
Example::repeatedstringval() const {
  // @@protoc_insertion_point(field_list:message.package.Example.repeatedStringVal)
  return repeatedstringval_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
Example::mutable_repeatedstringval() {
  // @@protoc_insertion_point(field_mutable_list:message.package.Example.repeatedStringVal)
  return &repeatedstringval_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace package
}  // namespace message

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_emample_2eproto