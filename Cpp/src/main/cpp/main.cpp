#include <chrono>
#include <thread>
#include <fmt/format.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/DoubleTopic.h>

int main() {
  // set up server
  auto server = nt::CreateInstance();
  nt::StartServer(server, "big2.json", "", 10001, 10000);

  // create 10 very large entries
  std::array<NT_Entry, 10> pubs;
  for (int i = 0; i < 10; ++i) {
    pubs[i] = nt::GetEntry(nt::GetTopic(server, fmt::format("bigentry{}", i)),
                           NT_RAW, "raw");
  }

  std::vector<uint8_t> bigvalue;
  bigvalue.resize(100000);
  for (auto pub : pubs) {
    nt::SetRaw(pub, bigvalue);
  }

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(100s);
}
