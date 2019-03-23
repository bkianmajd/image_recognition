// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: poker_statistics.proto

#include "poker_statistics.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace poker {
class PreflopStatisticDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<PreflopStatistic>
      _instance;
} _PreflopStatistic_default_instance_;
class PreflopStatisticsDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<PreflopStatistics>
      _instance;
} _PreflopStatistics_default_instance_;
}  // namespace poker
namespace protobuf_poker_5fstatistics_2eproto {
void InitDefaultsPreflopStatisticImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::poker::_PreflopStatistic_default_instance_;
    new (ptr) ::poker::PreflopStatistic();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::poker::PreflopStatistic::InitAsDefaultInstance();
}

void InitDefaultsPreflopStatistic() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsPreflopStatisticImpl);
}

void InitDefaultsPreflopStatisticsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  protobuf_poker_5fstatistics_2eproto::InitDefaultsPreflopStatistic();
  {
    void* ptr = &::poker::_PreflopStatistics_default_instance_;
    new (ptr) ::poker::PreflopStatistics();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::poker::PreflopStatistics::InitAsDefaultInstance();
}

void InitDefaultsPreflopStatistics() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsPreflopStatisticsImpl);
}

::google::protobuf::Metadata file_level_metadata[2];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::poker::PreflopStatistic, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::poker::PreflopStatistic, left_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::poker::PreflopStatistic, right_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::poker::PreflopStatistic, losing_probability_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::poker::PreflopStatistics, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::poker::PreflopStatistics, preflop_statistics_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::poker::PreflopStatistic)},
  { 8, -1, sizeof(::poker::PreflopStatistics)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::poker::_PreflopStatistic_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::poker::_PreflopStatistics_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "poker_statistics.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\026poker_statistics.proto\022\005poker\"Q\n\020Prefl"
      "opStatistic\022\017\n\007left_id\030\001 \001(\005\022\020\n\010right_id"
      "\030\002 \001(\005\022\032\n\022losing_probability\030\003 \001(\001\"H\n\021Pr"
      "eflopStatistics\0223\n\022preflop_statistics\030\004 "
      "\003(\0132\027.poker.PreflopStatisticb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 196);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "poker_statistics.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_poker_5fstatistics_2eproto
namespace poker {

// ===================================================================

void PreflopStatistic::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PreflopStatistic::kLeftIdFieldNumber;
const int PreflopStatistic::kRightIdFieldNumber;
const int PreflopStatistic::kLosingProbabilityFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PreflopStatistic::PreflopStatistic()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_poker_5fstatistics_2eproto::InitDefaultsPreflopStatistic();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:poker.PreflopStatistic)
}
PreflopStatistic::PreflopStatistic(const PreflopStatistic& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&left_id_, &from.left_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&losing_probability_) -
    reinterpret_cast<char*>(&left_id_)) + sizeof(losing_probability_));
  // @@protoc_insertion_point(copy_constructor:poker.PreflopStatistic)
}

void PreflopStatistic::SharedCtor() {
  ::memset(&left_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&losing_probability_) -
      reinterpret_cast<char*>(&left_id_)) + sizeof(losing_probability_));
  _cached_size_ = 0;
}

PreflopStatistic::~PreflopStatistic() {
  // @@protoc_insertion_point(destructor:poker.PreflopStatistic)
  SharedDtor();
}

void PreflopStatistic::SharedDtor() {
}

void PreflopStatistic::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PreflopStatistic::descriptor() {
  ::protobuf_poker_5fstatistics_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_poker_5fstatistics_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PreflopStatistic& PreflopStatistic::default_instance() {
  ::protobuf_poker_5fstatistics_2eproto::InitDefaultsPreflopStatistic();
  return *internal_default_instance();
}

PreflopStatistic* PreflopStatistic::New(::google::protobuf::Arena* arena) const {
  PreflopStatistic* n = new PreflopStatistic;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void PreflopStatistic::Clear() {
// @@protoc_insertion_point(message_clear_start:poker.PreflopStatistic)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&left_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&losing_probability_) -
      reinterpret_cast<char*>(&left_id_)) + sizeof(losing_probability_));
  _internal_metadata_.Clear();
}

bool PreflopStatistic::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:poker.PreflopStatistic)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 left_id = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &left_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 right_id = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &right_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double losing_probability = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(25u /* 25 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &losing_probability_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:poker.PreflopStatistic)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:poker.PreflopStatistic)
  return false;
#undef DO_
}

void PreflopStatistic::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:poker.PreflopStatistic)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 left_id = 1;
  if (this->left_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->left_id(), output);
  }

  // int32 right_id = 2;
  if (this->right_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->right_id(), output);
  }

  // double losing_probability = 3;
  if (this->losing_probability() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->losing_probability(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:poker.PreflopStatistic)
}

::google::protobuf::uint8* PreflopStatistic::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:poker.PreflopStatistic)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 left_id = 1;
  if (this->left_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->left_id(), target);
  }

  // int32 right_id = 2;
  if (this->right_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->right_id(), target);
  }

  // double losing_probability = 3;
  if (this->losing_probability() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->losing_probability(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:poker.PreflopStatistic)
  return target;
}

size_t PreflopStatistic::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:poker.PreflopStatistic)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // int32 left_id = 1;
  if (this->left_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->left_id());
  }

  // int32 right_id = 2;
  if (this->right_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->right_id());
  }

  // double losing_probability = 3;
  if (this->losing_probability() != 0) {
    total_size += 1 + 8;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void PreflopStatistic::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:poker.PreflopStatistic)
  GOOGLE_DCHECK_NE(&from, this);
  const PreflopStatistic* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const PreflopStatistic>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:poker.PreflopStatistic)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:poker.PreflopStatistic)
    MergeFrom(*source);
  }
}

void PreflopStatistic::MergeFrom(const PreflopStatistic& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:poker.PreflopStatistic)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.left_id() != 0) {
    set_left_id(from.left_id());
  }
  if (from.right_id() != 0) {
    set_right_id(from.right_id());
  }
  if (from.losing_probability() != 0) {
    set_losing_probability(from.losing_probability());
  }
}

void PreflopStatistic::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:poker.PreflopStatistic)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PreflopStatistic::CopyFrom(const PreflopStatistic& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:poker.PreflopStatistic)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PreflopStatistic::IsInitialized() const {
  return true;
}

void PreflopStatistic::Swap(PreflopStatistic* other) {
  if (other == this) return;
  InternalSwap(other);
}
void PreflopStatistic::InternalSwap(PreflopStatistic* other) {
  using std::swap;
  swap(left_id_, other->left_id_);
  swap(right_id_, other->right_id_);
  swap(losing_probability_, other->losing_probability_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata PreflopStatistic::GetMetadata() const {
  protobuf_poker_5fstatistics_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_poker_5fstatistics_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void PreflopStatistics::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PreflopStatistics::kPreflopStatisticsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PreflopStatistics::PreflopStatistics()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_poker_5fstatistics_2eproto::InitDefaultsPreflopStatistics();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:poker.PreflopStatistics)
}
PreflopStatistics::PreflopStatistics(const PreflopStatistics& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      preflop_statistics_(from.preflop_statistics_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:poker.PreflopStatistics)
}

void PreflopStatistics::SharedCtor() {
  _cached_size_ = 0;
}

PreflopStatistics::~PreflopStatistics() {
  // @@protoc_insertion_point(destructor:poker.PreflopStatistics)
  SharedDtor();
}

void PreflopStatistics::SharedDtor() {
}

void PreflopStatistics::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PreflopStatistics::descriptor() {
  ::protobuf_poker_5fstatistics_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_poker_5fstatistics_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PreflopStatistics& PreflopStatistics::default_instance() {
  ::protobuf_poker_5fstatistics_2eproto::InitDefaultsPreflopStatistics();
  return *internal_default_instance();
}

PreflopStatistics* PreflopStatistics::New(::google::protobuf::Arena* arena) const {
  PreflopStatistics* n = new PreflopStatistics;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void PreflopStatistics::Clear() {
// @@protoc_insertion_point(message_clear_start:poker.PreflopStatistics)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  preflop_statistics_.Clear();
  _internal_metadata_.Clear();
}

bool PreflopStatistics::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:poker.PreflopStatistics)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .poker.PreflopStatistic preflop_statistics = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(input, add_preflop_statistics()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:poker.PreflopStatistics)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:poker.PreflopStatistics)
  return false;
#undef DO_
}

void PreflopStatistics::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:poker.PreflopStatistics)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .poker.PreflopStatistic preflop_statistics = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->preflop_statistics_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->preflop_statistics(static_cast<int>(i)), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:poker.PreflopStatistics)
}

::google::protobuf::uint8* PreflopStatistics::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:poker.PreflopStatistics)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .poker.PreflopStatistic preflop_statistics = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->preflop_statistics_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        4, this->preflop_statistics(static_cast<int>(i)), deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:poker.PreflopStatistics)
  return target;
}

size_t PreflopStatistics::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:poker.PreflopStatistics)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .poker.PreflopStatistic preflop_statistics = 4;
  {
    unsigned int count = static_cast<unsigned int>(this->preflop_statistics_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->preflop_statistics(static_cast<int>(i)));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void PreflopStatistics::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:poker.PreflopStatistics)
  GOOGLE_DCHECK_NE(&from, this);
  const PreflopStatistics* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const PreflopStatistics>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:poker.PreflopStatistics)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:poker.PreflopStatistics)
    MergeFrom(*source);
  }
}

void PreflopStatistics::MergeFrom(const PreflopStatistics& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:poker.PreflopStatistics)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  preflop_statistics_.MergeFrom(from.preflop_statistics_);
}

void PreflopStatistics::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:poker.PreflopStatistics)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PreflopStatistics::CopyFrom(const PreflopStatistics& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:poker.PreflopStatistics)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PreflopStatistics::IsInitialized() const {
  return true;
}

void PreflopStatistics::Swap(PreflopStatistics* other) {
  if (other == this) return;
  InternalSwap(other);
}
void PreflopStatistics::InternalSwap(PreflopStatistics* other) {
  using std::swap;
  preflop_statistics_.InternalSwap(&other->preflop_statistics_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata PreflopStatistics::GetMetadata() const {
  protobuf_poker_5fstatistics_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_poker_5fstatistics_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace poker

// @@protoc_insertion_point(global_scope)
