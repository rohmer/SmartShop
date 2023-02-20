#include "webcc/utility.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>  // for put_time
#include <iostream>
#include <sstream>

#include "webcc/string.h"
#include "webcc/version.h"

namespace webcc {
namespace utility {

const std::string& UserAgent() {
  static const std::string s_user_agent = std::string("Webcc/") + WEBCC_VERSION;
  return s_user_agent;
}

std::string HttpDate() {
  std::time_t t = std::time(nullptr);
  std::tm gmt = *std::gmtime(&t);
  return FormatHttpDate(gmt);
}

std::string FormatHttpDate(const std::tm& gmt) {
  std::ostringstream date;
  date.imbue(std::locale::classic());  // Use classic C locale
  date << std::put_time(&gmt, "%a, %d %b %Y %H:%M:%S GMT");
  return date.str();
}

std::size_t TellSize(const sfs::path& path) {
  // Flag "ate": seek to the end of stream immediately after open.
  std::ifstream stream{ path, std::ios::binary | std::ios::ate };
  if (stream.fail()) {
    return kInvalidSize;
  }
  return static_cast<std::size_t>(stream.tellg());
}

bool ReadFile(const sfs::path& path, std::string* bytes) {
  // Flag "ate": seek to the end of stream immediately after open.
  std::ifstream stream{ path, std::ios::binary | std::ios::ate };
  if (stream.fail()) {
    return false;
  }

  auto size = stream.tellg();
  bytes->resize(static_cast<std::size_t>(size), '\0');
  stream.seekg(std::ios::beg);
  stream.read(bytes->data(), size);
  if (stream.fail()) {
    return false;
  }
  return true;
}

bool WriteFile(const sfs::path& path, const std::string& bytes) {
  std::ofstream stream{ path, std::ios::binary };
  if (stream.fail()) {
    return false;
  }

  stream.write(bytes.data(), bytes.size());
  return !stream.fail();
}

void DumpByLine(const std::string& data, std::ostream& os,
                std::string_view prefix) {
  std::vector<std::string_view> lines;
  Split(data, '\n', false, &lines);

  std::size_t size = 0;

  for (const auto& line : lines) {
    os << prefix;

    if (line.size() + size > kMaxDumpSize) {
      os.write(line.data(), kMaxDumpSize - size);
      os << "..." << std::endl;
      break;
    } else {
      os << line << std::endl;
      size += line.size();
    }
  }
}

}  // namespace utility
}  // namespace webcc
