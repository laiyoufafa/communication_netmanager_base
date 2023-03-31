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

#include "network_exec.h"

#include "network_constant.h"
#include "net_conn_client.h"
#include "network_observer.h"
#include "netmanager_base_log.h"
#include "napi_utils.h"
#include "securec.h"

static constexpr const int ERROR_PARAM_NUM = 2;

static constexpr const char *ERROR_MSG = "failed";

static constexpr const uint32_t DEFAULT_TIMEOUT_MS = 1000;

namespace OHOS::NetManagerStandard {
bool NetworkExec::ExecGetType(GetTypeContext *context)
{
    NETMANAGER_BASE_LOGI("NetworkExec::ExecGetType");
    EventManager *manager = context->GetManager();
    sptr<INetConnCallback> callback = g_observerMap[manager];
    if (callback == nullptr) {
        return false;
    }

    sptr<NetSpecifier> specifier = new NetSpecifier;
    specifier->netCapabilities_.netCaps_.insert(NET_CAPABILITY_INTERNET);
    DelayedSingleton<NetConnClient>::GetInstance()->UnregisterNetConnCallback(callback);
    int32_t ret = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetConnCallback(specifier, callback,
                                                                                          DEFAULT_TIMEOUT_MS);
    context->SetErrorCode(ret);
    return ret == NETMANAGER_SUCCESS;
}

napi_value NetworkExec::GetTypeCallback(GetTypeContext *context)
{
    if (!context->IsExecOK()) {
        napi_value fail = context->GetFailCallback();
        if (NapiUtils::GetValueType(context->GetEnv(), fail) == napi_function) {
            napi_value argv[ERROR_PARAM_NUM] = {
                NapiUtils::CreateStringUtf8(context->GetEnv(), ERROR_MSG),
                NapiUtils::CreateInt32(context->GetEnv(), context->GetErrorCode()),
            };
            NapiUtils::CallFunction(context->GetEnv(), NapiUtils::GetUndefined(context->GetEnv()), fail,
                                    ERROR_PARAM_NUM, argv);
        }

        napi_value complete = context->GetCompleteCallback();
        // if ok complete will be called in observer
        if (NapiUtils::GetValueType(context->GetEnv(), complete) == napi_function) {
            NapiUtils::CallFunction(context->GetEnv(), NapiUtils::GetUndefined(context->GetEnv()), complete, 0,
                                    nullptr);
        }

        auto manager = context->GetManager();
        napi_value success = context->GetSuccessCallback();
        if (NapiUtils::GetValueType(context->GetEnv(), success) == napi_function) {
            manager->DeleteListener(EVENT_GET_TYPE, success);
        }
    }

    return NapiUtils::GetUndefined(context->GetEnv());
}

bool NetworkExec::ExecSubscribe(SubscribeContext *context)
{
    NETMANAGER_BASE_LOGI("NetworkExec::ExecSubscribe");
    EventManager *manager = context->GetManager();
    sptr<INetConnCallback> callback = g_observerMap[manager];
    if (callback == nullptr) {
        return false;
    }

    sptr<NetSpecifier> specifier = new NetSpecifier;
    specifier->netCapabilities_.netCaps_.insert(NET_CAPABILITY_INTERNET);
    DelayedSingleton<NetConnClient>::GetInstance()->UnregisterNetConnCallback(callback);
    int32_t ret = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetConnCallback(specifier, callback,
                                                                                          DEFAULT_TIMEOUT_MS);
    context->SetErrorCode(ret);
    return ret == NETMANAGER_SUCCESS;
}

napi_value NetworkExec::SubscribeCallback(SubscribeContext *context)
{
    if (!context->IsExecOK()) {
        napi_value fail = context->GetFailCallback();
        if (NapiUtils::GetValueType(context->GetEnv(), fail) == napi_function) {
            napi_value argv[ERROR_PARAM_NUM] = {
                NapiUtils::CreateStringUtf8(context->GetEnv(), ERROR_MSG),
                NapiUtils::CreateInt32(context->GetEnv(), context->GetErrorCode()),
            };
            NapiUtils::CallFunction(context->GetEnv(), NapiUtils::GetUndefined(context->GetEnv()), fail,
                                    ERROR_PARAM_NUM, argv);
        }
    }

    return NapiUtils::GetUndefined(context->GetEnv());
}

bool NetworkExec::ExecUnsubscribe(UnsubscribeContext *context)
{
    EventManager *manager = context->GetManager();
    sptr<INetConnCallback> callback = g_observerMap[manager];
    if (callback == nullptr) {
        return false;
    }

    int32_t ret = DelayedSingleton<NetConnClient>::GetInstance()->UnregisterNetConnCallback(callback);
    context->SetErrorCode(ret);
    return ret == NETMANAGER_SUCCESS;
}

napi_value NetworkExec::UnsubscribeCallback(UnsubscribeContext *context)
{
    context->GetManager()->DeleteListener(EVENT_GET_TYPE);
    context->GetManager()->DeleteListener(EVENT_SUBSCRIBE);
    return NapiUtils::GetUndefined(context->GetEnv());
}
} // namespace OHOS::NetManagerStandard