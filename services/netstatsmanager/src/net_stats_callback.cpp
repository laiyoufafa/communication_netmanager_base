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
#include "net_stats_callback.h"
#include "net_stats_constants.h"

#include "net_mgr_log_wrapper.h"

namespace OHOS {
namespace NetManagerStandard {
void NetStatsCallback::RegisterNetStatsCallback(const sptr<INetStatsCallback> &callback)
{
    if (callback == nullptr) {
        NETMGR_LOG_E("The parameter callback is null");
        return;
    }

    for (uint32_t i = 0; i < netStatsCallback_.size(); i++) {
        if (callback->AsObject().GetRefPtr() == netStatsCallback_[i]->AsObject().GetRefPtr()) {
            NETMGR_LOG_I("netPolicyCallback_ had this callback");
            return;
        }
    }

    netStatsCallback_.emplace_back(callback);
}

void NetStatsCallback::UnregisterNetStatsCallback(const sptr<INetStatsCallback> &callback)
{
    if (callback == nullptr) {
        NETMGR_LOG_E("The parameter of callback is null");
        return;
    }

    for (auto iter = netStatsCallback_.begin(); iter != netStatsCallback_.end(); ++iter) {
        if (callback->AsObject().GetRefPtr() == (*iter)->AsObject().GetRefPtr()) {
            netStatsCallback_.erase(iter);
            return;
        }
    }
}

int32_t NetStatsCallback::NotifyNetIfaceStatsChanged(const std::string &iface)
{
    NETMGR_LOG_D("NotifyNetIfaceStatsChanged info: iface[%{public}s]", iface.c_str());

    for (const auto &callback : netStatsCallback_) {
        if (callback != nullptr) {
            callback->NetIfaceStatsChanged(iface);
        }
    }

    return static_cast<int32_t>(NetStatsResultCode::ERR_NONE);
}

int32_t NetStatsCallback::NotifyNetUidStatsChanged(const std::string &iface, uint32_t uid)
{
    NETMGR_LOG_D("UpdateIfacesStats info: iface[%{public}s] uid[%{public}d]", iface.c_str(), uid);

    for (const auto &callback : netStatsCallback_) {
        if (callback != nullptr) {
            callback->NetUidStatsChanged(iface, uid);
        }
    }

    return static_cast<int32_t>(NetStatsResultCode::ERR_NONE);
}
} // namespace NetManagerStandard
} // namespace OHOS
