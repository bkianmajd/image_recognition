// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: image_request_response_commands.proto

#ifndef PROTOBUF_INCLUDED_image_5frequest_5fresponse_5fcommands_2eproto
#define PROTOBUF_INCLUDED_image_5frequest_5fresponse_5fcommands_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_image_5frequest_5fresponse_5fcommands_2eproto 

namespace protobuf_image_5frequest_5fresponse_5fcommands_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[4];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_image_5frequest_5fresponse_5fcommands_2eproto
namespace ipc_interface {
class StoreImageRequest;
class StoreImageRequestDefaultTypeInternal;
extern StoreImageRequestDefaultTypeInternal _StoreImageRequest_default_instance_;
class StoreImageResponse;
class StoreImageResponseDefaultTypeInternal;
extern StoreImageResponseDefaultTypeInternal _StoreImageResponse_default_instance_;
class TemplateMatchRequest;
class TemplateMatchRequestDefaultTypeInternal;
extern TemplateMatchRequestDefaultTypeInternal _TemplateMatchRequest_default_instance_;
class TemplateMatchResponse;
class TemplateMatchResponseDefaultTypeInternal;
extern TemplateMatchResponseDefaultTypeInternal _TemplateMatchResponse_default_instance_;
}  // namespace ipc_interface
namespace google {
namespace protobuf {
template<> ::ipc_interface::StoreImageRequest* Arena::CreateMaybeMessage<::ipc_interface::StoreImageRequest>(Arena*);
template<> ::ipc_interface::StoreImageResponse* Arena::CreateMaybeMessage<::ipc_interface::StoreImageResponse>(Arena*);
template<> ::ipc_interface::TemplateMatchRequest* Arena::CreateMaybeMessage<::ipc_interface::TemplateMatchRequest>(Arena*);
template<> ::ipc_interface::TemplateMatchResponse* Arena::CreateMaybeMessage<::ipc_interface::TemplateMatchResponse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace ipc_interface {

// ===================================================================

class StoreImageRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ipc_interface.StoreImageRequest) */ {
 public:
  StoreImageRequest();
  virtual ~StoreImageRequest();

  StoreImageRequest(const StoreImageRequest& from);

  inline StoreImageRequest& operator=(const StoreImageRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  StoreImageRequest(StoreImageRequest&& from) noexcept
    : StoreImageRequest() {
    *this = ::std::move(from);
  }

  inline StoreImageRequest& operator=(StoreImageRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const StoreImageRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const StoreImageRequest* internal_default_instance() {
    return reinterpret_cast<const StoreImageRequest*>(
               &_StoreImageRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(StoreImageRequest* other);
  friend void swap(StoreImageRequest& a, StoreImageRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline StoreImageRequest* New() const final {
    return CreateMaybeMessage<StoreImageRequest>(NULL);
  }

  StoreImageRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<StoreImageRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const StoreImageRequest& from);
  void MergeFrom(const StoreImageRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(StoreImageRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string image_name = 1;
  void clear_image_name();
  static const int kImageNameFieldNumber = 1;
  const ::std::string& image_name() const;
  void set_image_name(const ::std::string& value);
  #if LANG_CXX11
  void set_image_name(::std::string&& value);
  #endif
  void set_image_name(const char* value);
  void set_image_name(const char* value, size_t size);
  ::std::string* mutable_image_name();
  ::std::string* release_image_name();
  void set_allocated_image_name(::std::string* image_name);

  // bytes image = 2;
  void clear_image();
  static const int kImageFieldNumber = 2;
  const ::std::string& image() const;
  void set_image(const ::std::string& value);
  #if LANG_CXX11
  void set_image(::std::string&& value);
  #endif
  void set_image(const char* value);
  void set_image(const void* value, size_t size);
  ::std::string* mutable_image();
  ::std::string* release_image();
  void set_allocated_image(::std::string* image);

  // @@protoc_insertion_point(class_scope:ipc_interface.StoreImageRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr image_name_;
  ::google::protobuf::internal::ArenaStringPtr image_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_image_5frequest_5fresponse_5fcommands_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class StoreImageResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ipc_interface.StoreImageResponse) */ {
 public:
  StoreImageResponse();
  virtual ~StoreImageResponse();

  StoreImageResponse(const StoreImageResponse& from);

  inline StoreImageResponse& operator=(const StoreImageResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  StoreImageResponse(StoreImageResponse&& from) noexcept
    : StoreImageResponse() {
    *this = ::std::move(from);
  }

  inline StoreImageResponse& operator=(StoreImageResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const StoreImageResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const StoreImageResponse* internal_default_instance() {
    return reinterpret_cast<const StoreImageResponse*>(
               &_StoreImageResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(StoreImageResponse* other);
  friend void swap(StoreImageResponse& a, StoreImageResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline StoreImageResponse* New() const final {
    return CreateMaybeMessage<StoreImageResponse>(NULL);
  }

  StoreImageResponse* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<StoreImageResponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const StoreImageResponse& from);
  void MergeFrom(const StoreImageResponse& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(StoreImageResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string str_message = 2;
  void clear_str_message();
  static const int kStrMessageFieldNumber = 2;
  const ::std::string& str_message() const;
  void set_str_message(const ::std::string& value);
  #if LANG_CXX11
  void set_str_message(::std::string&& value);
  #endif
  void set_str_message(const char* value);
  void set_str_message(const char* value, size_t size);
  ::std::string* mutable_str_message();
  ::std::string* release_str_message();
  void set_allocated_str_message(::std::string* str_message);

  // bool success = 1;
  void clear_success();
  static const int kSuccessFieldNumber = 1;
  bool success() const;
  void set_success(bool value);

  // @@protoc_insertion_point(class_scope:ipc_interface.StoreImageResponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr str_message_;
  bool success_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_image_5frequest_5fresponse_5fcommands_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class TemplateMatchRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ipc_interface.TemplateMatchRequest) */ {
 public:
  TemplateMatchRequest();
  virtual ~TemplateMatchRequest();

  TemplateMatchRequest(const TemplateMatchRequest& from);

  inline TemplateMatchRequest& operator=(const TemplateMatchRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  TemplateMatchRequest(TemplateMatchRequest&& from) noexcept
    : TemplateMatchRequest() {
    *this = ::std::move(from);
  }

  inline TemplateMatchRequest& operator=(TemplateMatchRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const TemplateMatchRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TemplateMatchRequest* internal_default_instance() {
    return reinterpret_cast<const TemplateMatchRequest*>(
               &_TemplateMatchRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(TemplateMatchRequest* other);
  friend void swap(TemplateMatchRequest& a, TemplateMatchRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline TemplateMatchRequest* New() const final {
    return CreateMaybeMessage<TemplateMatchRequest>(NULL);
  }

  TemplateMatchRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<TemplateMatchRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const TemplateMatchRequest& from);
  void MergeFrom(const TemplateMatchRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TemplateMatchRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string big_image_name = 1;
  void clear_big_image_name();
  static const int kBigImageNameFieldNumber = 1;
  const ::std::string& big_image_name() const;
  void set_big_image_name(const ::std::string& value);
  #if LANG_CXX11
  void set_big_image_name(::std::string&& value);
  #endif
  void set_big_image_name(const char* value);
  void set_big_image_name(const char* value, size_t size);
  ::std::string* mutable_big_image_name();
  ::std::string* release_big_image_name();
  void set_allocated_big_image_name(::std::string* big_image_name);

  // string template_image_name = 2;
  void clear_template_image_name();
  static const int kTemplateImageNameFieldNumber = 2;
  const ::std::string& template_image_name() const;
  void set_template_image_name(const ::std::string& value);
  #if LANG_CXX11
  void set_template_image_name(::std::string&& value);
  #endif
  void set_template_image_name(const char* value);
  void set_template_image_name(const char* value, size_t size);
  ::std::string* mutable_template_image_name();
  ::std::string* release_template_image_name();
  void set_allocated_template_image_name(::std::string* template_image_name);

  // @@protoc_insertion_point(class_scope:ipc_interface.TemplateMatchRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr big_image_name_;
  ::google::protobuf::internal::ArenaStringPtr template_image_name_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_image_5frequest_5fresponse_5fcommands_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class TemplateMatchResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ipc_interface.TemplateMatchResponse) */ {
 public:
  TemplateMatchResponse();
  virtual ~TemplateMatchResponse();

  TemplateMatchResponse(const TemplateMatchResponse& from);

  inline TemplateMatchResponse& operator=(const TemplateMatchResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  TemplateMatchResponse(TemplateMatchResponse&& from) noexcept
    : TemplateMatchResponse() {
    *this = ::std::move(from);
  }

  inline TemplateMatchResponse& operator=(TemplateMatchResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const TemplateMatchResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TemplateMatchResponse* internal_default_instance() {
    return reinterpret_cast<const TemplateMatchResponse*>(
               &_TemplateMatchResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(TemplateMatchResponse* other);
  friend void swap(TemplateMatchResponse& a, TemplateMatchResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline TemplateMatchResponse* New() const final {
    return CreateMaybeMessage<TemplateMatchResponse>(NULL);
  }

  TemplateMatchResponse* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<TemplateMatchResponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const TemplateMatchResponse& from);
  void MergeFrom(const TemplateMatchResponse& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TemplateMatchResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bool success = 1;
  void clear_success();
  static const int kSuccessFieldNumber = 1;
  bool success() const;
  void set_success(bool value);

  // int32 x_location = 2;
  void clear_x_location();
  static const int kXLocationFieldNumber = 2;
  ::google::protobuf::int32 x_location() const;
  void set_x_location(::google::protobuf::int32 value);

  // int32 y_location = 3;
  void clear_y_location();
  static const int kYLocationFieldNumber = 3;
  ::google::protobuf::int32 y_location() const;
  void set_y_location(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ipc_interface.TemplateMatchResponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool success_;
  ::google::protobuf::int32 x_location_;
  ::google::protobuf::int32 y_location_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_image_5frequest_5fresponse_5fcommands_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// StoreImageRequest

// string image_name = 1;
inline void StoreImageRequest::clear_image_name() {
  image_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& StoreImageRequest::image_name() const {
  // @@protoc_insertion_point(field_get:ipc_interface.StoreImageRequest.image_name)
  return image_name_.GetNoArena();
}
inline void StoreImageRequest::set_image_name(const ::std::string& value) {
  
  image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ipc_interface.StoreImageRequest.image_name)
}
#if LANG_CXX11
inline void StoreImageRequest::set_image_name(::std::string&& value) {
  
  image_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:ipc_interface.StoreImageRequest.image_name)
}
#endif
inline void StoreImageRequest::set_image_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ipc_interface.StoreImageRequest.image_name)
}
inline void StoreImageRequest::set_image_name(const char* value, size_t size) {
  
  image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ipc_interface.StoreImageRequest.image_name)
}
inline ::std::string* StoreImageRequest::mutable_image_name() {
  
  // @@protoc_insertion_point(field_mutable:ipc_interface.StoreImageRequest.image_name)
  return image_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* StoreImageRequest::release_image_name() {
  // @@protoc_insertion_point(field_release:ipc_interface.StoreImageRequest.image_name)
  
  return image_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void StoreImageRequest::set_allocated_image_name(::std::string* image_name) {
  if (image_name != NULL) {
    
  } else {
    
  }
  image_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), image_name);
  // @@protoc_insertion_point(field_set_allocated:ipc_interface.StoreImageRequest.image_name)
}

// bytes image = 2;
inline void StoreImageRequest::clear_image() {
  image_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& StoreImageRequest::image() const {
  // @@protoc_insertion_point(field_get:ipc_interface.StoreImageRequest.image)
  return image_.GetNoArena();
}
inline void StoreImageRequest::set_image(const ::std::string& value) {
  
  image_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ipc_interface.StoreImageRequest.image)
}
#if LANG_CXX11
inline void StoreImageRequest::set_image(::std::string&& value) {
  
  image_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:ipc_interface.StoreImageRequest.image)
}
#endif
inline void StoreImageRequest::set_image(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  image_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ipc_interface.StoreImageRequest.image)
}
inline void StoreImageRequest::set_image(const void* value, size_t size) {
  
  image_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ipc_interface.StoreImageRequest.image)
}
inline ::std::string* StoreImageRequest::mutable_image() {
  
  // @@protoc_insertion_point(field_mutable:ipc_interface.StoreImageRequest.image)
  return image_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* StoreImageRequest::release_image() {
  // @@protoc_insertion_point(field_release:ipc_interface.StoreImageRequest.image)
  
  return image_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void StoreImageRequest::set_allocated_image(::std::string* image) {
  if (image != NULL) {
    
  } else {
    
  }
  image_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), image);
  // @@protoc_insertion_point(field_set_allocated:ipc_interface.StoreImageRequest.image)
}

// -------------------------------------------------------------------

// StoreImageResponse

// bool success = 1;
inline void StoreImageResponse::clear_success() {
  success_ = false;
}
inline bool StoreImageResponse::success() const {
  // @@protoc_insertion_point(field_get:ipc_interface.StoreImageResponse.success)
  return success_;
}
inline void StoreImageResponse::set_success(bool value) {
  
  success_ = value;
  // @@protoc_insertion_point(field_set:ipc_interface.StoreImageResponse.success)
}

// string str_message = 2;
inline void StoreImageResponse::clear_str_message() {
  str_message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& StoreImageResponse::str_message() const {
  // @@protoc_insertion_point(field_get:ipc_interface.StoreImageResponse.str_message)
  return str_message_.GetNoArena();
}
inline void StoreImageResponse::set_str_message(const ::std::string& value) {
  
  str_message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ipc_interface.StoreImageResponse.str_message)
}
#if LANG_CXX11
inline void StoreImageResponse::set_str_message(::std::string&& value) {
  
  str_message_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:ipc_interface.StoreImageResponse.str_message)
}
#endif
inline void StoreImageResponse::set_str_message(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  str_message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ipc_interface.StoreImageResponse.str_message)
}
inline void StoreImageResponse::set_str_message(const char* value, size_t size) {
  
  str_message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ipc_interface.StoreImageResponse.str_message)
}
inline ::std::string* StoreImageResponse::mutable_str_message() {
  
  // @@protoc_insertion_point(field_mutable:ipc_interface.StoreImageResponse.str_message)
  return str_message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* StoreImageResponse::release_str_message() {
  // @@protoc_insertion_point(field_release:ipc_interface.StoreImageResponse.str_message)
  
  return str_message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void StoreImageResponse::set_allocated_str_message(::std::string* str_message) {
  if (str_message != NULL) {
    
  } else {
    
  }
  str_message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), str_message);
  // @@protoc_insertion_point(field_set_allocated:ipc_interface.StoreImageResponse.str_message)
}

// -------------------------------------------------------------------

// TemplateMatchRequest

// string big_image_name = 1;
inline void TemplateMatchRequest::clear_big_image_name() {
  big_image_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& TemplateMatchRequest::big_image_name() const {
  // @@protoc_insertion_point(field_get:ipc_interface.TemplateMatchRequest.big_image_name)
  return big_image_name_.GetNoArena();
}
inline void TemplateMatchRequest::set_big_image_name(const ::std::string& value) {
  
  big_image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ipc_interface.TemplateMatchRequest.big_image_name)
}
#if LANG_CXX11
inline void TemplateMatchRequest::set_big_image_name(::std::string&& value) {
  
  big_image_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:ipc_interface.TemplateMatchRequest.big_image_name)
}
#endif
inline void TemplateMatchRequest::set_big_image_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  big_image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ipc_interface.TemplateMatchRequest.big_image_name)
}
inline void TemplateMatchRequest::set_big_image_name(const char* value, size_t size) {
  
  big_image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ipc_interface.TemplateMatchRequest.big_image_name)
}
inline ::std::string* TemplateMatchRequest::mutable_big_image_name() {
  
  // @@protoc_insertion_point(field_mutable:ipc_interface.TemplateMatchRequest.big_image_name)
  return big_image_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* TemplateMatchRequest::release_big_image_name() {
  // @@protoc_insertion_point(field_release:ipc_interface.TemplateMatchRequest.big_image_name)
  
  return big_image_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TemplateMatchRequest::set_allocated_big_image_name(::std::string* big_image_name) {
  if (big_image_name != NULL) {
    
  } else {
    
  }
  big_image_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), big_image_name);
  // @@protoc_insertion_point(field_set_allocated:ipc_interface.TemplateMatchRequest.big_image_name)
}

// string template_image_name = 2;
inline void TemplateMatchRequest::clear_template_image_name() {
  template_image_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& TemplateMatchRequest::template_image_name() const {
  // @@protoc_insertion_point(field_get:ipc_interface.TemplateMatchRequest.template_image_name)
  return template_image_name_.GetNoArena();
}
inline void TemplateMatchRequest::set_template_image_name(const ::std::string& value) {
  
  template_image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ipc_interface.TemplateMatchRequest.template_image_name)
}
#if LANG_CXX11
inline void TemplateMatchRequest::set_template_image_name(::std::string&& value) {
  
  template_image_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:ipc_interface.TemplateMatchRequest.template_image_name)
}
#endif
inline void TemplateMatchRequest::set_template_image_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  template_image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ipc_interface.TemplateMatchRequest.template_image_name)
}
inline void TemplateMatchRequest::set_template_image_name(const char* value, size_t size) {
  
  template_image_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ipc_interface.TemplateMatchRequest.template_image_name)
}
inline ::std::string* TemplateMatchRequest::mutable_template_image_name() {
  
  // @@protoc_insertion_point(field_mutable:ipc_interface.TemplateMatchRequest.template_image_name)
  return template_image_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* TemplateMatchRequest::release_template_image_name() {
  // @@protoc_insertion_point(field_release:ipc_interface.TemplateMatchRequest.template_image_name)
  
  return template_image_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TemplateMatchRequest::set_allocated_template_image_name(::std::string* template_image_name) {
  if (template_image_name != NULL) {
    
  } else {
    
  }
  template_image_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), template_image_name);
  // @@protoc_insertion_point(field_set_allocated:ipc_interface.TemplateMatchRequest.template_image_name)
}

// -------------------------------------------------------------------

// TemplateMatchResponse

// bool success = 1;
inline void TemplateMatchResponse::clear_success() {
  success_ = false;
}
inline bool TemplateMatchResponse::success() const {
  // @@protoc_insertion_point(field_get:ipc_interface.TemplateMatchResponse.success)
  return success_;
}
inline void TemplateMatchResponse::set_success(bool value) {
  
  success_ = value;
  // @@protoc_insertion_point(field_set:ipc_interface.TemplateMatchResponse.success)
}

// int32 x_location = 2;
inline void TemplateMatchResponse::clear_x_location() {
  x_location_ = 0;
}
inline ::google::protobuf::int32 TemplateMatchResponse::x_location() const {
  // @@protoc_insertion_point(field_get:ipc_interface.TemplateMatchResponse.x_location)
  return x_location_;
}
inline void TemplateMatchResponse::set_x_location(::google::protobuf::int32 value) {
  
  x_location_ = value;
  // @@protoc_insertion_point(field_set:ipc_interface.TemplateMatchResponse.x_location)
}

// int32 y_location = 3;
inline void TemplateMatchResponse::clear_y_location() {
  y_location_ = 0;
}
inline ::google::protobuf::int32 TemplateMatchResponse::y_location() const {
  // @@protoc_insertion_point(field_get:ipc_interface.TemplateMatchResponse.y_location)
  return y_location_;
}
inline void TemplateMatchResponse::set_y_location(::google::protobuf::int32 value) {
  
  y_location_ = value;
  // @@protoc_insertion_point(field_set:ipc_interface.TemplateMatchResponse.y_location)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace ipc_interface

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_image_5frequest_5fresponse_5fcommands_2eproto