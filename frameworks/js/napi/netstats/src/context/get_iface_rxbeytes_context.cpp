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

#include "get_iface_rxbeytes_context.h"

#include "constant.h"
#include "napi_utils.h"

namespace OHOS {
namespace NetManagerStandard {
GetIfaceRxBytesContext::GetIfaceRxBytesContext(napi_env env, EventManager *manager) : BaseContext(env, manager) {}

void GetIfaceRxBytesContext::ParseParams(napi_value *params, size_t paramsCount)
{
    if (!CheckParamsType(params, paramsCount)) {
        return;
    }

    nic_ = NapiUtils::GetStringFromValueUtf8(GetEnv(), params[ARG_INDEX_0]);

    if (paramsCount == PARAM_OPTIONS_AND_CALLBACK) {
        SetParseOK(SetCallback(params[ARG_INDEX_1]) == napi_ok);
        return;
    }
    SetParseOK(true);
}

bool GetIfaceRxBytesContext::CheckParamsType(napi_value *params, size_t paramsCount)
{
    if (paramsCount == PARAM_JUST_OPTIONS) {
        return NapiUtils::GetValueType(GetEnv(), params[ARG_INDEX_0]) == napi_string;
    }

    if (paramsCount == PARAM_OPTIONS_AND_CALLBACK) {
        return NapiUtils::GetValueType(GetEnv(), params[ARG_INDEX_1]) == napi_function &&
               NapiUtils::GetValueType(GetEnv(), params[ARG_INDEX_0]) == napi_string;
    }
    return false;
}

void GetIfaceRxBytesContext::SetNic(std::string nic)
{
    nic_ = nic;
}

void GetIfaceRxBytesContext::SetBytes64(int64_t bytes64)
{
    bytes64_ = bytes64;
}

void GetIfaceRxBytesContext::SetInterfaceName(std::string interfaceName)
{
    interfaceName_ = interfaceName;
}

std::string GetIfaceRxBytesContext::GetNic()
{
    return nic_;
}

int64_t GetIfaceRxBytesContext::GetBytes64()
{
    return bytes64_;
}

std::string GetIfaceRxBytesContext::GetInterfaceName()
{
    return interfaceName_;
}
} // namespace NetManagerStandard
} // namespace OHOS
