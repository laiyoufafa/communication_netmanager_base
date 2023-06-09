/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "net_stats_service_iface.h"
#include "net_stats_constants.h"
#include "net_stats_service.h"

namespace OHOS {
namespace NetManagerStandard {
int32_t NetStatsServiceIface::GetIfaceStatsDetail(const std::string &iface, uint32_t start, uint32_t end,
    NetStatsInfo &info)
{
    NetStatsResultCode result = DelayedSingleton<NetStatsService>::GetInstance()->GetIfaceStatsDetail(iface, start,
        end, info);
    return static_cast<int32_t>(result);
}

int32_t NetStatsServiceIface::ResetStatsFactory()
{
    NetStatsResultCode result = DelayedSingleton<NetStatsService>::GetInstance()->ResetFactory();
    return static_cast<int32_t>(result);
}
} // namespace NetManagerStandard
} // namespace OHOS
