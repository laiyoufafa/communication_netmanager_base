/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef INCLUDE_FWMARK_NETWORK_H
#define INCLUDE_FWMARK_NETWORK_H

#include <atomic>
#include <cstdint>

#include "fwmark_command.h"

namespace OHOS {
namespace nmd {
class FwmarkNetwork {
public:
    FwmarkNetwork() = default;
    ~FwmarkNetwork() = default;

    void SetDefaultNetId(int32_t netId);
    void StartListener();

private:
    void CloseSocket(int32_t *socket, int32_t ret, int32_t errorCode);
    void SendMessage(int32_t *serverSockfd);
    int32_t SetMark(int32_t *socketFd, FwmarkCommand *command);

private:
    std::atomic<int32_t> defaultNetId_ = 0;
};
} // namespace nmd
} // namespace OHOS
#endif // INCLUDE_FWMARK_NETWORK_H
