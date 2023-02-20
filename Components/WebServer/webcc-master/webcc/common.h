#ifndef WEBCC_COMMON_H_
#define WEBCC_COMMON_H_

#include <cassert>
#include <string>
#include <utility>
#include <vector>

#include "webcc/globals.h"

namespace webcc {

// -----------------------------------------------------------------------------

using Header = std::pair<std::string, std::string>;

class Headers {
public:
  std::size_t size() const {
    return headers_.size();
  }

  bool empty() const {
    return headers_.empty();
  }

  const std::vector<Header>& data() const {
    return headers_;
  }

  // Return false if either `key` or `value` is empty.
  bool Set(std::string_view key, std::string_view value);

  // Get header by index.
  const Header& Get(std::size_t index) const {
    assert(index < size());
    return headers_[index];
  }

  // Get header by key.
  // Return empty if there's no such header with the given key
  std::string_view Get(std::string_view key) const {
    auto it = Find(key);
    if (it != headers_.end()) {
      return it->second;
    }
    return std::string_view{};
  }

  void Clear() {
    headers_.clear();
  }

private:
  std::vector<Header>::iterator Find(std::string_view key);

  std::vector<Header>::const_iterator Find(std::string_view key) const {
    return const_cast<Headers*>(this)->Find(key);
  }

  std::vector<Header> headers_;
};

// -----------------------------------------------------------------------------

// The Content-Type header.
// Syntax:
//   Content-Type: text/html; charset=utf-8
//   Content-Type: multipart/form-data; boundary=something
class ContentType {
public:
  explicit ContentType(std::string_view str = "");

  void Parse(std::string_view str);

  void Clear();

  bool Valid() const;

  bool multipart() const {
    return multipart_;
  }

  const std::string& media_type() const {
    return media_type_;
  }

  const std::string& charset() const {
    assert(!multipart_);
    return additional_;
  }

  const std::string& boundary() const {
    assert(multipart_);
    return additional_;
  }

private:
  void Init(std::string_view str);

private:
  std::string media_type_;
  std::string additional_;
  bool multipart_ = false;
};

// -----------------------------------------------------------------------------

// The Content-Disposition header.
// Syntax:
//   Content-Disposition: form-data
//   Content-Disposition: form-data; name="fieldName"
//   Content-Disposition: form-data; name="fieldName"; filename="filename.jpg"
// https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Disposition
class ContentDisposition {
public:
  explicit ContentDisposition(std::string_view str) {
    valid_ = Init(str);
  }

  bool valid() const {
    return valid_;
  }

  const std::string& name() const {
    return name_;
  }

  const sfs::path& file_name() const {
    return file_name_;
  }

private:
  bool Init(std::string_view str);

private:
  std::string name_;
  sfs::path file_name_;
  bool valid_ = false;
};

// -----------------------------------------------------------------------------

class FormPart;
using FormPartPtr = std::shared_ptr<FormPart>;

// A part of the multipart form data.
class FormPart {
public:
  FormPart() = default;

  FormPart(const FormPart&) = delete;
  FormPart& operator=(const FormPart&) = delete;

  // Construct a non-file part.
  // The data will be moved, no file name is needed.
  // The media type is optional. If the data is a JSON string, you can specify
  // media type as "application/json".
  static FormPartPtr New(std::string_view name, std::string&& data,
                         std::string_view media_type = "");

  // Construct a file part.
  // The file name will be extracted from path.
  // The media type, if not provided, will be inferred from file extension.
  static FormPartPtr NewFile(std::string_view name, const sfs::path& path,
                             std::string_view media_type = "");

  // API: SERVER
  const std::string& name() const {
    return name_;
  }

  // API: SERVER/PARSER
  void set_name(const std::string& name) {
    name_ = name;
  }

  // API: SERVER
  const sfs::path& file_name() const {
    return file_name_;
  }

  // API: SERVER/PARSER
  void set_file_name(const sfs::path& file_name) {
    file_name_ = file_name;
  }

  // API: SERVER
  const std::string& media_type() const {
    return media_type_;
  }

  // API: SERVER
  const std::string& data() const {
    return data_;
  }

  // API: SERVER/PARSER
  void AppendData(const std::string& data) {
    data_.append(data);
  }

  // API: SERVER/PARSER
  void AppendData(const char* data, std::size_t count) {
    data_.append(data, count);
  }

  // API: CLIENT
  void Prepare(Payload* payload);

  // Free the memory of the data.
  void Free();

  // Get the size of the whole payload.
  // Used by the request to calculate content length.
  std::size_t GetSize();

  // Get the size of the data.
  std::size_t GetDataSize();

  // Dump to output stream for logging purpose.
  void Dump(std::ostream& os, std::string_view prefix) const;

private:
  // Generate headers from properties.
  void SetHeaders();

private:
  // The <input> name within the original HTML form.
  // E.g., given HTML form:
  //   <input name="file1" type="file">
  // the name will be "file1".
  std::string name_;

  // The path of the file to post.
  sfs::path path_;

  // The original local file name.
  sfs::path file_name_;

  // The content-type if the media type is known (e.g., inferred from the file
  // extension or operating system typing information) or as
  // application/octet-stream.
  // E.g., "image/jpeg".
  std::string media_type_;

  // Headers generated from the above properties.
  // Only used to prepare payload.
  Headers headers_;

  std::string data_;
};

}  // namespace webcc

#endif  // WEBCC_COMMON_H_
