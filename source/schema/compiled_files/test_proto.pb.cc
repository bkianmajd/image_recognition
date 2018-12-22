// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test_proto.proto

#include "test_proto.pb.h"

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
class TestProtoDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<TestProto>
      _instance;
} _TestProto_default_instance_;
namespace protobuf_test_5fproto_2eproto {
void InitDefaultsTestProtoImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::_TestProto_default_instance_;
    new (ptr) ::TestProto();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::TestProto::InitAsDefaultInstance();
}

void InitDefaultsTestProto() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsTestProtoImpl);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::TestProto, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::TestProto, test_bool_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::TestProto, test_int_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::TestProto)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::_TestProto_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "test_proto.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\020test_proto.proto\"0\n\tTestProto\022\021\n\ttest_"
      "bool\030\001 \001(\010\022\020\n\010test_int\030\002 \001(\005b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 76);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "test_proto.proto", &protobuf_RegisterTypes);
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
}  // namespace protobuf_test_5fproto_2eproto

// ===================================================================

void TestProto::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TestProto::kTestBoolFieldNumber;
const int TestProto::kTestIntFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TestProto::TestProto()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_test_5fproto_2eproto::InitDefaultsTestProto();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:TestProto)
}
TestProto::TestProto(const TestProto& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&test_bool_, &from.test_bool_,
    static_cast<size_t>(reinterpret_cast<char*>(&test_int_) -
    reinterpret_cast<char*>(&test_bool_)) + sizeof(test_int_));
  // @@protoc_insertion_point(copy_constructor:TestProto)
}

void TestProto::SharedCtor() {
  ::memset(&test_bool_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&test_int_) -
      reinterpret_cast<char*>(&test_bool_)) + sizeof(test_int_));
  _cached_size_ = 0;
}

TestProto::~TestProto() {
  // @@protoc_insertion_point(destructor:TestProto)
  SharedDtor();
}

void TestProto::SharedDtor() {
}

void TestProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TestProto::descriptor() {
  ::protobuf_test_5fproto_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_test_5fproto_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const TestProto& TestProto::default_instance() {
  ::protobuf_test_5fproto_2eproto::InitDefaultsTestProto();
  return *internal_default_instance();
}

TestProto* TestProto::New(::google::protobuf::Arena* arena) const {
  TestProto* n = new TestProto;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void TestProto::Clear() {
// @@protoc_insertion_point(message_clear_start:TestProto)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&test_bool_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&test_int_) -
      reinterpret_cast<char*>(&test_bool_)) + sizeof(test_int_));
  _internal_metadata_.Clear();
}

bool TestProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:TestProto)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // bool test_bool = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &test_bool_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 test_int = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &test_int_)));
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
  // @@protoc_insertion_point(parse_success:TestProto)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:TestProto)
  return false;
#undef DO_
}

void TestProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:TestProto)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bool test_bool = 1;
  if (this->test_bool() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->test_bool(), output);
  }

  // int32 test_int = 2;
  if (this->test_int() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->test_int(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:TestProto)
}

::google::protobuf::uint8* TestProto::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:TestProto)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bool test_bool = 1;
  if (this->test_bool() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->test_bool(), target);
  }

  // int32 test_int = 2;
  if (this->test_int() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->test_int(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:TestProto)
  return target;
}

size_t TestProto::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:TestProto)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // bool test_bool = 1;
  if (this->test_bool() != 0) {
    total_size += 1 + 1;
  }

  // int32 test_int = 2;
  if (this->test_int() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->test_int());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TestProto::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:TestProto)
  GOOGLE_DCHECK_NE(&from, this);
  const TestProto* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const TestProto>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:TestProto)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:TestProto)
    MergeFrom(*source);
  }
}

void TestProto::MergeFrom(const TestProto& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:TestProto)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.test_bool() != 0) {
    set_test_bool(from.test_bool());
  }
  if (from.test_int() != 0) {
    set_test_int(from.test_int());
  }
}

void TestProto::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:TestProto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TestProto::CopyFrom(const TestProto& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:TestProto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TestProto::IsInitialized() const {
  return true;
}

void TestProto::Swap(TestProto* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TestProto::InternalSwap(TestProto* other) {
  using std::swap;
  swap(test_bool_, other->test_bool_);
  swap(test_int_, other->test_int_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata TestProto::GetMetadata() const {
  protobuf_test_5fproto_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_test_5fproto_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
