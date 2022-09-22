/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#include "net_policy_callback_test.h"

#include "net_mgr_log_wrapper.h"
#include "net_policy_constants.h"

namespace OHOS {
namespace NetManagerStandard {
NetPolicyCallbackTest::NetPolicyCallbackTest() = default;

NetPolicyCallbackTest::~NetPolicyCallbackTest() = default;

void NetPolicyCallbackTest::NotifyAll()
{
    std::unique_lock<std::mutex> callbackLock(callbackMutex_);
    cv_.notify_all();
}

void NetPolicyCallbackTest::WaitFor(int32_t timeoutSecond)
{
    std::unique_lock<std::mutex> callbackLock(callbackMutex_);
    cv_.wait_for(callbackLock, std::chrono::seconds(timeoutSecond));
}

int32_t NetPolicyCallbackTest::NetUidPolicyChange(uint32_t uid, uint32_t policy)
{
    NETMGR_LOG_D("unittest NetUidPolicyChange, uid:[%{public}u], policy:[%{public}u]", uid,
                 static_cast<uint32_t>(policy));

    uid_ = uid;
    uidPolicy_ = policy;
    NotifyAll();

    return 0;
}

int32_t NetPolicyCallbackTest::NetUidRuleChange(uint32_t uid, uint32_t rule)
{
    NETMGR_LOG_D("unittest NetUidRuleChange, uid:[%{public}u], rule:[%{public}u]", uid, rule);
    uid_ = uid;
    rule_ = rule;
    NotifyAll();

    return 0;
}

int32_t NetPolicyCallbackTest::NetBackgroundPolicyChange(bool isBackgroundPolicyAllow)
{
    NETMGR_LOG_D("unittest NetBackgroundPolicyChange, isBackgroundPolicyAllow:[%{public}d]", isBackgroundPolicyAllow);

    isBackgroundPolicyAllow_ = isBackgroundPolicyAllow;
    NotifyAll();

    return 0;
}

int32_t NetPolicyCallbackTest::NetQuotaPolicyChange(const std::vector<NetQuotaPolicy> &quotaPolicies)
{
    NETMGR_LOG_D("unittest NetQuotaPolicyChange, quotaPolicies.size:[%{public}zu]", quotaPolicies.size());
    quotaPoliciesSize_ = quotaPolicies.size();
    NotifyAll();
    return 0;
}

int32_t NetPolicyCallbackTest::NetMeteredIfacesChange(std::vector<std::string> &ifaces)
{
    for (auto &iface : ifaces) {
        NETMGR_LOG_D("unittest NetMeteredIfacesChange, iface:[%{public}s]", iface.c_str());
    }
    NotifyAll();
    return 0;
}
} // namespace NetManagerStandard
} // namespace OHOS
