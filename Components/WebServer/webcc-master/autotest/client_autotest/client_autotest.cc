#include <filesystem>
#include <fstream>
#include <iostream>

#include "boost/algorithm/string.hpp"
#include "gtest/gtest.h"
#include "json/json.h"

#include "webcc/client_session.h"
#include "webcc/string.h"

namespace sfs = std::filesystem;

// -----------------------------------------------------------------------------

// JSON helper functions (based on jsoncpp).

// Parse a string to JSON object.
static Json::Value StringToJson(const std::string& str) {
  Json::Value json;

  Json::CharReaderBuilder builder;
  std::istringstream stream{ str };
  std::string errors;
  if (!Json::parseFromStream(builder, stream, &json, &errors)) {
    std::cerr << errors << std::endl;
  }

  return json;
}

// -----------------------------------------------------------------------------

TEST(ClientTest, Head) {
  webcc::ClientSession session;

  try {
    auto r = session.Send(webcc::RequestBuilder{}.
                          Head("http://httpbin.org/get")
                          ());

    EXPECT_EQ(r->status(), webcc::status_codes::kOK);
    EXPECT_EQ(r->reason(), "OK");

    EXPECT_TRUE(r->HeaderExist(webcc::headers::kContentLength));

    // The response of HTTP HEAD method has no body.
    EXPECT_EQ(r->data(), "");

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

// -----------------------------------------------------------------------------

TEST(ClientTest, Get) {
  webcc::ClientSession session;

  try {
    auto r = session.Send(WEBCC_GET("http://httpbin.org/get")
                              .Query("key1", "value1")
                              .Query("key2", "value2")
                              .Header("Accept", "application/json")());

    EXPECT_EQ(r->status(), webcc::status_codes::kOK);
    EXPECT_EQ(r->reason(), "OK");

    Json::Value json = StringToJson(r->data());

    Json::Value& args = json["args"];
    EXPECT_EQ(args.size(), 2);
    EXPECT_EQ(args["key1"].asString(), "value1");
    EXPECT_EQ(args["key2"].asString(), "value2");

    Json::Value& headers = json["headers"];
    EXPECT_EQ(headers["Accept"].asString(), "application/json");
    EXPECT_EQ(headers["Accept-Encoding"].asString(), "identity");
    EXPECT_EQ(headers["Host"].asString(), "httpbin.org");

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

// Test the space in the query string could be encoded.
TEST(ClientTest, Get_QueryEncode) {
  webcc::ClientSession session;

  try {
    auto r = session.Send(WEBCC_GET("http://httpbin.org/get")
                              .Query("name", "Chunting Gu", true)());

    EXPECT_EQ(r->status(), webcc::status_codes::kOK);
    EXPECT_EQ(r->reason(), "OK");

    Json::Value json = StringToJson(r->data());

    Json::Value& args = json["args"];
    EXPECT_EQ(args.size(), 1);
    EXPECT_EQ(args["name"].asString(), "Chunting Gu");

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

TEST(ClientTest, Get_SSL) {
  webcc::ClientSession session;

  try {
    // HTTPS is auto-detected from the URL scheme.
    auto r = session.Send(WEBCC_GET("https://httpbin.org/get")
                              .Query("key1", "value1")
                              .Query("key2", "value2")
                              .Accept("application/json")());

    EXPECT_EQ(r->status(), webcc::status_codes::kOK);
    EXPECT_EQ(r->reason(), "OK");

    Json::Value json = StringToJson(r->data());

    Json::Value& args = json["args"];
    EXPECT_EQ(args.size(), 2);
    EXPECT_EQ(args["key1"].asString(), "value1");
    EXPECT_EQ(args["key2"].asString(), "value2");

    Json::Value& headers = json["headers"];
    EXPECT_EQ(headers["Accept"].asString(), "application/json");
    EXPECT_EQ(headers["Accept-Encoding"].asString(), "identity");
    EXPECT_EQ(headers["Host"].asString(), "httpbin.org");

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

// Get a JPEG image (without streaming).
TEST(ClientTest, Get_Jpeg_NoStream) {
  webcc::ClientSession session;

  try {
    auto r = session.Send(WEBCC_GET("http://httpbin.org/image/jpeg")());

    // TODO: Verify the response is a valid JPEG image.

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

TEST(ClientTest, Get_Jpeg_Stream) {
  webcc::ClientSession session;

  try {
    auto r = session.Send(WEBCC_GET("http://httpbin.org/image/jpeg")(), true);

    auto file_body = r->file_body();

    EXPECT_TRUE(file_body != nullptr);
    EXPECT_TRUE(!file_body->path().empty());

    // Backup the path of the temp file.
    const sfs::path ori_path = file_body->path();

    const sfs::path new_path{ "./wolf.jpeg" };

    bool moved = file_body->Move(new_path);
    EXPECT_TRUE(moved);
    EXPECT_TRUE(sfs::exists(new_path));
    // The file in the original path should not exist any more.
    EXPECT_TRUE(!sfs::exists(ori_path));

    // After move, the original path should be reset.
    EXPECT_TRUE(file_body->path().empty());

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

// Test whether the streamed file will be deleted or not at the end if it's
// not moved to another path by the user.
TEST(ClientTest, Get_Jpeg_Stream_NoMove) {
  webcc::ClientSession session;

  try {
    sfs::path ori_path;

    {
      auto r = session.Send(WEBCC_GET("http://httpbin.org/image/jpeg")(), true);

      auto file_body = r->file_body();

      ASSERT_TRUE(file_body != nullptr);
      EXPECT_TRUE(!file_body->path().empty());

      // Backup the path of the temp file.
      ori_path = file_body->path();
    }

    // The temp file should be deleted.
    EXPECT_TRUE(!sfs::exists(ori_path));

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

// -----------------------------------------------------------------------------

#if WEBCC_ENABLE_GZIP

// Test Gzip compressed response.
TEST(ClientTest, Get_Gzip) {
  webcc::ClientSession session;
  session.AcceptGzip();

  try {
    auto r = session.Send(WEBCC_GET("http://httpbin.org/gzip")());

    Json::Value json = StringToJson(r->data());

    EXPECT_TRUE(json["gzipped"].asBool());

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

// Test Deflate compressed response.
TEST(ClientTest, Get_Deflate) {
  webcc::ClientSession session;
  session.AcceptGzip();

  try {
    auto r = session.Send(WEBCC_GET("http://httpbin.org/deflate")());

    Json::Value json = StringToJson(r->data());

    EXPECT_TRUE(json["deflated"].asBool());

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

#endif  // WEBCC_ENABLE_GZIP

// -----------------------------------------------------------------------------

TEST(ClientTest, Post) {
  webcc::ClientSession session;

  try {
    const std::string data = "{'name'='Adam', 'age'=20}";

    auto r =
        session.Send(WEBCC_POST("http://httpbin.org/post").Body(data).Json()());

    EXPECT_EQ(r->status(), webcc::status_codes::kOK);
    EXPECT_EQ(r->reason(), "OK");

    Json::Value json = StringToJson(r->data());

    EXPECT_EQ(json["data"].asString(), data);

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

static sfs::path GenerateTempFile(const std::string& data) {
  try {
    sfs::path path = sfs::temp_directory_path() / webcc::RandomAsciiString(10);

    std::ofstream ofs;
    ofs.open(path, std::ios::binary);
    if (ofs.fail()) {
      return sfs::path{};
    }

    ofs << data;

    return path;

  } catch (const sfs::filesystem_error&) {
    return sfs::path{};
  }
}

TEST(ClientTest, Post_FileBody) {
  webcc::ClientSession session;

  const std::string data = "{'name'='Adam', 'age'=20}";

  auto path = GenerateTempFile(data);
  if (path.empty()) {
    return;
  }

  try {
    auto r = session.Send(WEBCC_POST("http://httpbin.org/post").File(path)());

    EXPECT_EQ(r->status(), webcc::status_codes::kOK);
    EXPECT_EQ(r->reason(), "OK");

    Json::Value json = StringToJson(r->data());

    EXPECT_EQ(json["data"].asString(), data);

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }

  // Remove the temp file.
  std::error_code ec;
  sfs::remove(path, ec);
}

#if WEBCC_ENABLE_GZIP
TEST(ClientTest, Post_Gzip_SmallData) {
  webcc::ClientSession session;

  try {
    // This data is too small to be compressed.
    const std::string data = "{'name'='Adam', 'age'=20}";

    // This doesn't really compress the body!
    auto r = session.Send(
        WEBCC_POST("http://httpbin.org/post").Body(data).Json().Gzip()());

    //Json::Value json = StringToJson(r->data());

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

// NOTE: Most servers don't support compressed requests!
TEST(ClientTest, Post_Gzip) {
  webcc::ClientSession session;

  try {
    // Use Boost.org home page as the POST data.
    auto r1 = session.Send(WEBCC_GET("https://www.boost.org/")());

    const std::string& data = r1->data();

    auto r2 =
        session.Send(WEBCC_POST("http://httpbin.org/post").Body(data).Gzip()());

    EXPECT_EQ(r2->status(), webcc::status_codes::kOK);
    EXPECT_EQ(r2->reason(), "OK");

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}
#endif  // WEBCC_ENABLE_GZIP

// -----------------------------------------------------------------------------

// Test persistent (keep-alive) connections.
//
// NOTE:
// Boost.org doesn't support persistent connection and always includes
// "Connection: Close" header in the response.
// Both Google and GitHub support persistent connection but they don't like
// to include "Connection: Keep-Alive" header in the responses.
// URLs:
//   "http://httpbin.org/get";
//   "https://www.boost.org/LICENSE_1_0.txt";
//   "https://www.google.com";
//   "https://api.github.com/events";
//
TEST(ClientTest, KeepAlive) {
  webcc::ClientSession session;

  const std::string url = "http://httpbin.org/get";

  try {
    // Keep-Alive by default.
    auto r = session.Send(webcc::RequestBuilder{}.Get(url)());
    EXPECT_TRUE(boost::iequals(r->GetHeader("Connection"), "Keep-Alive"));

    // Close by setting Connection header directly.
    r = session.Send(WEBCC_GET(url).Header("Connection", "Close")());
    EXPECT_TRUE(boost::iequals(r->GetHeader("Connection"), "Close"));

    // Close by using request builder.
    r = session.Send(webcc::RequestBuilder{}.Get(url).KeepAlive(false)());
    EXPECT_TRUE(boost::iequals(r->GetHeader("Connection"), "Close"));

    // Keep-Alive explicitly by using request builder.
    r = session.Send(webcc::RequestBuilder{}.Get(url).KeepAlive(true)());
    EXPECT_TRUE(boost::iequals(r->GetHeader("Connection"), "Keep-Alive"));

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

// Test that URL scheme is NOT case sensitive.
TEST(ClientTest, UpperCaseUrlScheme) {
  webcc::ClientSession session;

  try {
    auto r = session.Send(WEBCC_GET("HTTP://httpbin.org/get")());

    EXPECT_EQ(r->status(), webcc::status_codes::kOK);

  } catch (const webcc::Error& error) {
    std::cerr << error << std::endl;
  }
}

TEST(ClientTest, InvalidUrlScheme) {
  webcc::ClientSession session;

  int error_code = webcc::error_codes::kUnknownError;

  try {
    // NOTE: "httb" is not a valid/supported scheme.
    session.Send(WEBCC_GET("httb://httpbin.org/get")());

  } catch (const webcc::Error& error) {
    error_code = error.code();
  }

  EXPECT_EQ(error_code, webcc::error_codes::kSyntaxError);
}
