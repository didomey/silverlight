#pragma once

namespace Cmn {
namespace Player {
enum class ConnectionStatusType {
  Offline = 0x0,
  Remote = 0x2,
};

enum class LocalStatusType {
  LocalPlayer = 0x0,
  TeamAlphaRemotePlayer = 0x1,
  TeamBravoRemotePlayer = 0x2,
};
} // namespace Player
} // namespace Cmn
