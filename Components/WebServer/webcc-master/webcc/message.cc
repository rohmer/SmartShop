#include "webcc/message.h"

#include <sstream>

#include "boost/algorithm/string.hpp"

#include "webcc/internal/globals.h"
#include "webcc/logger.h"
#include "webcc/utility.h"

namespace webcc {

Message::Message() : body_(new Body{}) {
}

void Message::SetBody(BodyPtr body, bool set_length) {
  if (body == body_) {
    return;
  }

  if (!body) {
    body_.reset(new Body{});
  } else {
    body_ = body;
  }

  if (set_length) {
    content_length_ = body_->GetSize();
    SetHeader(headers::kContentLength, std::to_string(content_length_));
  }
}

const std::string& Message::data() const {
  static const std::string kEmptyData;

  StringBodyPtr string_body = std::dynamic_pointer_cast<StringBody>(body_);
  if (string_body == nullptr) {
    return kEmptyData;
  }
  return string_body->data();
}

bool Message::IsConnectionKeepAlive() const {
  std::string_view value = GetHeader(headers::kConnection);
  if (value.empty()) {
    // The Connection header doesn't exist.
    // Return true since keep-alive is by default for HTTP/1.1.
    return true;
  }
  return boost::iequals(value, "Keep-Alive");
}

ContentEncoding Message::GetContentEncoding() const {
  std::string_view value = GetHeader(headers::kContentEncoding);
  if (value == "gzip") {
    return ContentEncoding::kGzip;
  } else if (value == "deflate") {
    return ContentEncoding::kDeflate;
  } else {
    return ContentEncoding::kUnknown;
  }
}

void Message::SetContentType(std::string_view media_type,
                             std::string_view charset) {
  if (!media_type.empty()) {
    if (charset.empty()) {
      SetHeader(headers::kContentType, media_type);
    } else {
      std::string value{ media_type };
      value += "; charset=";
      value += charset;
      SetHeader(headers::kContentType, value);
    }
  }
}

Payload Message::GetPayload() const {
  using boost::asio::buffer;
  namespace literal_buffers = internal::literal_buffers;

  Payload payload;

  payload.push_back(buffer(start_line_));
  payload.push_back(buffer(literal_buffers::CRLF));

  for (const Header& h : headers_.data()) {
    payload.push_back(buffer(h.first));
    payload.push_back(buffer(literal_buffers::HEADER_SEPARATOR));
    payload.push_back(buffer(h.second));
    payload.push_back(buffer(literal_buffers::CRLF));
  }

  payload.push_back(buffer(literal_buffers::CRLF));

  return payload;
}

void Message::Dump(std::ostream& os, std::string_view prefix) const {
  os << prefix << start_line_ << std::endl;

  for (const Header& h : headers_.data()) {
    os << prefix << h.first << ": " << h.second << std::endl;
  }

  os << prefix << std::endl;

  body_->Dump(os, prefix);
}

std::string Message::Dump(std::string_view prefix) const {
  std::ostringstream ss;
  Dump(ss, prefix);
  return ss.str();
}

}  // namespace webcc
