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
#include "dns_service_iface.h"
#include "dns_resolver_service.h"

namespace OHOS {
namespace NetManagerStandard {
int32_t DnsServiceIface::GetAddressesByName(const std::string &hostName, int32_t netId,
    std::vector<INetAddr> &addrInfo)
{
    return DelayedSingleton<DnsResolverService>::GetInstance()->GetAddressesByName(hostName, netId, addrInfo);
}
} // namespace NetManagerStandard
} // namespace OHOS