// concurrency_test.cc

#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "webcc/client_session.h"
#include "webcc/logger.h"

int main(int argc, const char* argv[]) {
  if (argc < 3) {
    std::cout << "Usage: concurrency_test <workers> <url>" << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "  $ concurrency_test 10 http://httpbin.org/get" << std::endl;
    std::cout << "  $ concurrency_test 10 http://localhost:8080/" << std::endl;
    return 1;
  }

  WEBCC_LOG_INIT("", webcc::LOG_CONSOLE);

  int workers = std::atoi(argv[1]);
  std::string url = argv[2];

  LOG_USER("Workers: %d", workers);
  LOG_USER("URL: %s", url.c_str());

  std::vector<std::thread> threads;

  for (int i = 0; i < workers; ++i) {
    threads.emplace_back([&url]() {
      // NOTE: Each thread has its own client session.
      webcc::ClientSession session;
      session.set_read_timeout(180);

      try {
        LOG_USER("Start");

        session.Send(webcc::RequestBuilder{}.Get(url)());

        LOG_USER("End");

      } catch (const webcc::Error& error) {
        std::cerr << error << std::endl;
      }
    });
  }

  for (int i = 0; i < workers; ++i) {
    threads[i].join();
  }

  return 0;
}
