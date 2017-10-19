// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AddressBook_v3.proto

#ifndef PROTOBUF_AddressBook_5fv3_2eproto__INCLUDED
#define PROTOBUF_AddressBook_5fv3_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace tutorial_v3 {
class AddressBook;
class AddressBookDefaultTypeInternal;
extern AddressBookDefaultTypeInternal _AddressBook_default_instance_;
class Person;
class PersonDefaultTypeInternal;
extern PersonDefaultTypeInternal _Person_default_instance_;
class Person_PhoneNumber;
class Person_PhoneNumberDefaultTypeInternal;
extern Person_PhoneNumberDefaultTypeInternal _Person_PhoneNumber_default_instance_;
}  // namespace tutorial_v3

namespace tutorial_v3 {

namespace protobuf_AddressBook_5fv3_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_AddressBook_5fv3_2eproto

enum Person_PhoneType {
  Person_PhoneType_MOBILE = 0,
  Person_PhoneType_HOME = 1,
  Person_PhoneType_WORK = 2,
  Person_PhoneType_Person_PhoneType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Person_PhoneType_Person_PhoneType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Person_PhoneType_IsValid(int value);
const Person_PhoneType Person_PhoneType_PhoneType_MIN = Person_PhoneType_MOBILE;
const Person_PhoneType Person_PhoneType_PhoneType_MAX = Person_PhoneType_WORK;
const int Person_PhoneType_PhoneType_ARRAYSIZE = Person_PhoneType_PhoneType_MAX + 1;

const ::google::protobuf::EnumDescriptor* Person_PhoneType_descriptor();
inline const ::std::string& Person_PhoneType_Name(Person_PhoneType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Person_PhoneType_descriptor(), value);
}
inline bool Person_PhoneType_Parse(
    const ::std::string& name, Person_PhoneType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Person_PhoneType>(
    Person_PhoneType_descriptor(), name, value);
}
// ===================================================================

class Person_PhoneNumber : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tutorial_v3.Person.PhoneNumber) */ {
 public:
  Person_PhoneNumber();
  virtual ~Person_PhoneNumber();

  Person_PhoneNumber(const Person_PhoneNumber& from);

  inline Person_PhoneNumber& operator=(const Person_PhoneNumber& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Person_PhoneNumber& default_instance();

  static inline const Person_PhoneNumber* internal_default_instance() {
    return reinterpret_cast<const Person_PhoneNumber*>(
               &_Person_PhoneNumber_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Person_PhoneNumber* other);

  // implements Message ----------------------------------------------

  inline Person_PhoneNumber* New() const PROTOBUF_FINAL { return New(NULL); }

  Person_PhoneNumber* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Person_PhoneNumber& from);
  void MergeFrom(const Person_PhoneNumber& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Person_PhoneNumber* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string number = 1;
  void clear_number();
  static const int kNumberFieldNumber = 1;
  const ::std::string& number() const;
  void set_number(const ::std::string& value);
  #if LANG_CXX11
  void set_number(::std::string&& value);
  #endif
  void set_number(const char* value);
  void set_number(const char* value, size_t size);
  ::std::string* mutable_number();
  ::std::string* release_number();
  void set_allocated_number(::std::string* number);

  // .tutorial_v3.Person.PhoneType type = 2;
  void clear_type();
  static const int kTypeFieldNumber = 2;
  ::tutorial_v3::Person_PhoneType type() const;
  void set_type(::tutorial_v3::Person_PhoneType value);

  // @@protoc_insertion_point(class_scope:tutorial_v3.Person.PhoneNumber)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr number_;
  int type_;
  mutable int _cached_size_;
  friend struct protobuf_AddressBook_5fv3_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Person : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tutorial_v3.Person) */ {
 public:
  Person();
  virtual ~Person();

  Person(const Person& from);

  inline Person& operator=(const Person& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Person& default_instance();

  static inline const Person* internal_default_instance() {
    return reinterpret_cast<const Person*>(
               &_Person_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(Person* other);

  // implements Message ----------------------------------------------

  inline Person* New() const PROTOBUF_FINAL { return New(NULL); }

  Person* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Person& from);
  void MergeFrom(const Person& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Person* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef Person_PhoneNumber PhoneNumber;

  typedef Person_PhoneType PhoneType;
  static const PhoneType MOBILE =
    Person_PhoneType_MOBILE;
  static const PhoneType HOME =
    Person_PhoneType_HOME;
  static const PhoneType WORK =
    Person_PhoneType_WORK;
  static inline bool PhoneType_IsValid(int value) {
    return Person_PhoneType_IsValid(value);
  }
  static const PhoneType PhoneType_MIN =
    Person_PhoneType_PhoneType_MIN;
  static const PhoneType PhoneType_MAX =
    Person_PhoneType_PhoneType_MAX;
  static const int PhoneType_ARRAYSIZE =
    Person_PhoneType_PhoneType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  PhoneType_descriptor() {
    return Person_PhoneType_descriptor();
  }
  static inline const ::std::string& PhoneType_Name(PhoneType value) {
    return Person_PhoneType_Name(value);
  }
  static inline bool PhoneType_Parse(const ::std::string& name,
      PhoneType* value) {
    return Person_PhoneType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated .tutorial_v3.Person.PhoneNumber phone = 4;
  int phone_size() const;
  void clear_phone();
  static const int kPhoneFieldNumber = 4;
  const ::tutorial_v3::Person_PhoneNumber& phone(int index) const;
  ::tutorial_v3::Person_PhoneNumber* mutable_phone(int index);
  ::tutorial_v3::Person_PhoneNumber* add_phone();
  ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person_PhoneNumber >*
      mutable_phone();
  const ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person_PhoneNumber >&
      phone() const;

  // string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // string email = 3;
  void clear_email();
  static const int kEmailFieldNumber = 3;
  const ::std::string& email() const;
  void set_email(const ::std::string& value);
  #if LANG_CXX11
  void set_email(::std::string&& value);
  #endif
  void set_email(const char* value);
  void set_email(const char* value, size_t size);
  ::std::string* mutable_email();
  ::std::string* release_email();
  void set_allocated_email(::std::string* email);

  // int32 id = 2;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:tutorial_v3.Person)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person_PhoneNumber > phone_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr email_;
  ::google::protobuf::int32 id_;
  mutable int _cached_size_;
  friend struct protobuf_AddressBook_5fv3_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class AddressBook : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tutorial_v3.AddressBook) */ {
 public:
  AddressBook();
  virtual ~AddressBook();

  AddressBook(const AddressBook& from);

  inline AddressBook& operator=(const AddressBook& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AddressBook& default_instance();

  static inline const AddressBook* internal_default_instance() {
    return reinterpret_cast<const AddressBook*>(
               &_AddressBook_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(AddressBook* other);

  // implements Message ----------------------------------------------

  inline AddressBook* New() const PROTOBUF_FINAL { return New(NULL); }

  AddressBook* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const AddressBook& from);
  void MergeFrom(const AddressBook& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(AddressBook* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .tutorial_v3.Person person = 1;
  int person_size() const;
  void clear_person();
  static const int kPersonFieldNumber = 1;
  const ::tutorial_v3::Person& person(int index) const;
  ::tutorial_v3::Person* mutable_person(int index);
  ::tutorial_v3::Person* add_person();
  ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person >*
      mutable_person();
  const ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person >&
      person() const;

  // @@protoc_insertion_point(class_scope:tutorial_v3.AddressBook)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person > person_;
  mutable int _cached_size_;
  friend struct protobuf_AddressBook_5fv3_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Person_PhoneNumber

// string number = 1;
inline void Person_PhoneNumber::clear_number() {
  number_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Person_PhoneNumber::number() const {
  // @@protoc_insertion_point(field_get:tutorial_v3.Person.PhoneNumber.number)
  return number_.GetNoArena();
}
inline void Person_PhoneNumber::set_number(const ::std::string& value) {
  
  number_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tutorial_v3.Person.PhoneNumber.number)
}
#if LANG_CXX11
inline void Person_PhoneNumber::set_number(::std::string&& value) {
  
  number_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tutorial_v3.Person.PhoneNumber.number)
}
#endif
inline void Person_PhoneNumber::set_number(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  number_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tutorial_v3.Person.PhoneNumber.number)
}
inline void Person_PhoneNumber::set_number(const char* value, size_t size) {
  
  number_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tutorial_v3.Person.PhoneNumber.number)
}
inline ::std::string* Person_PhoneNumber::mutable_number() {
  
  // @@protoc_insertion_point(field_mutable:tutorial_v3.Person.PhoneNumber.number)
  return number_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person_PhoneNumber::release_number() {
  // @@protoc_insertion_point(field_release:tutorial_v3.Person.PhoneNumber.number)
  
  return number_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person_PhoneNumber::set_allocated_number(::std::string* number) {
  if (number != NULL) {
    
  } else {
    
  }
  number_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), number);
  // @@protoc_insertion_point(field_set_allocated:tutorial_v3.Person.PhoneNumber.number)
}

// .tutorial_v3.Person.PhoneType type = 2;
inline void Person_PhoneNumber::clear_type() {
  type_ = 0;
}
inline ::tutorial_v3::Person_PhoneType Person_PhoneNumber::type() const {
  // @@protoc_insertion_point(field_get:tutorial_v3.Person.PhoneNumber.type)
  return static_cast< ::tutorial_v3::Person_PhoneType >(type_);
}
inline void Person_PhoneNumber::set_type(::tutorial_v3::Person_PhoneType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:tutorial_v3.Person.PhoneNumber.type)
}

// -------------------------------------------------------------------

// Person

// string name = 1;
inline void Person::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Person::name() const {
  // @@protoc_insertion_point(field_get:tutorial_v3.Person.name)
  return name_.GetNoArena();
}
inline void Person::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tutorial_v3.Person.name)
}
#if LANG_CXX11
inline void Person::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tutorial_v3.Person.name)
}
#endif
inline void Person::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tutorial_v3.Person.name)
}
inline void Person::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tutorial_v3.Person.name)
}
inline ::std::string* Person::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:tutorial_v3.Person.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person::release_name() {
  // @@protoc_insertion_point(field_release:tutorial_v3.Person.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:tutorial_v3.Person.name)
}

// int32 id = 2;
inline void Person::clear_id() {
  id_ = 0;
}
inline ::google::protobuf::int32 Person::id() const {
  // @@protoc_insertion_point(field_get:tutorial_v3.Person.id)
  return id_;
}
inline void Person::set_id(::google::protobuf::int32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:tutorial_v3.Person.id)
}

// string email = 3;
inline void Person::clear_email() {
  email_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Person::email() const {
  // @@protoc_insertion_point(field_get:tutorial_v3.Person.email)
  return email_.GetNoArena();
}
inline void Person::set_email(const ::std::string& value) {
  
  email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tutorial_v3.Person.email)
}
#if LANG_CXX11
inline void Person::set_email(::std::string&& value) {
  
  email_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tutorial_v3.Person.email)
}
#endif
inline void Person::set_email(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tutorial_v3.Person.email)
}
inline void Person::set_email(const char* value, size_t size) {
  
  email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tutorial_v3.Person.email)
}
inline ::std::string* Person::mutable_email() {
  
  // @@protoc_insertion_point(field_mutable:tutorial_v3.Person.email)
  return email_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person::release_email() {
  // @@protoc_insertion_point(field_release:tutorial_v3.Person.email)
  
  return email_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_email(::std::string* email) {
  if (email != NULL) {
    
  } else {
    
  }
  email_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), email);
  // @@protoc_insertion_point(field_set_allocated:tutorial_v3.Person.email)
}

// repeated .tutorial_v3.Person.PhoneNumber phone = 4;
inline int Person::phone_size() const {
  return phone_.size();
}
inline void Person::clear_phone() {
  phone_.Clear();
}
inline const ::tutorial_v3::Person_PhoneNumber& Person::phone(int index) const {
  // @@protoc_insertion_point(field_get:tutorial_v3.Person.phone)
  return phone_.Get(index);
}
inline ::tutorial_v3::Person_PhoneNumber* Person::mutable_phone(int index) {
  // @@protoc_insertion_point(field_mutable:tutorial_v3.Person.phone)
  return phone_.Mutable(index);
}
inline ::tutorial_v3::Person_PhoneNumber* Person::add_phone() {
  // @@protoc_insertion_point(field_add:tutorial_v3.Person.phone)
  return phone_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person_PhoneNumber >*
Person::mutable_phone() {
  // @@protoc_insertion_point(field_mutable_list:tutorial_v3.Person.phone)
  return &phone_;
}
inline const ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person_PhoneNumber >&
Person::phone() const {
  // @@protoc_insertion_point(field_list:tutorial_v3.Person.phone)
  return phone_;
}

// -------------------------------------------------------------------

// AddressBook

// repeated .tutorial_v3.Person person = 1;
inline int AddressBook::person_size() const {
  return person_.size();
}
inline void AddressBook::clear_person() {
  person_.Clear();
}
inline const ::tutorial_v3::Person& AddressBook::person(int index) const {
  // @@protoc_insertion_point(field_get:tutorial_v3.AddressBook.person)
  return person_.Get(index);
}
inline ::tutorial_v3::Person* AddressBook::mutable_person(int index) {
  // @@protoc_insertion_point(field_mutable:tutorial_v3.AddressBook.person)
  return person_.Mutable(index);
}
inline ::tutorial_v3::Person* AddressBook::add_person() {
  // @@protoc_insertion_point(field_add:tutorial_v3.AddressBook.person)
  return person_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person >*
AddressBook::mutable_person() {
  // @@protoc_insertion_point(field_mutable_list:tutorial_v3.AddressBook.person)
  return &person_;
}
inline const ::google::protobuf::RepeatedPtrField< ::tutorial_v3::Person >&
AddressBook::person() const {
  // @@protoc_insertion_point(field_list:tutorial_v3.AddressBook.person)
  return person_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace tutorial_v3

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::tutorial_v3::Person_PhoneType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::tutorial_v3::Person_PhoneType>() {
  return ::tutorial_v3::Person_PhoneType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AddressBook_5fv3_2eproto__INCLUDED
