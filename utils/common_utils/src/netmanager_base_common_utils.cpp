/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#include "netmanager_base_common_utils.h"
#include "securec.h"

#include <algorithm>
#include <arpa/inet.h>

namespace OHOS::NetManagerStandard::CommonUtils {
constexpr int32_t INET_PTION_SUC = 1;
constexpr uint32_t CONST_MASK = 0x80000000;
std::vector<std::string> Split(const std::string &str, const std::string &sep)
{
    std::string s = str;
    std::vector<std::string> res;
    while (!s.empty()) {
        size_t pos = s.find(sep);
        if (pos == std::string::npos) {
            res.emplace_back(s);
            break;
        }
        res.emplace_back(s.substr(0, pos));
        s = s.substr(pos + sep.size());
    }
    return res;
}

std::string Strip(const std::string &str, char ch)
{
    int64_t i = 0;
    while (i < str.size() && str[i] == ch) {
        ++i;
    }
    int64_t j = static_cast<int64_t>(str.size()) - 1;
    while (j > 0 && str[j] == ch) {
        --j;
    }
    if (i >= 0 && i < str.size() && j >= 0 && j < str.size() && j - i + 1 > 0) {
        return str.substr(i, j - i + 1);
    }
    return "";
}

std::string ToLower(const std::string &s)
{
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), tolower);
    return res;
}

bool IsValidIPV4(const std::string &ip)
{
    if (ip.empty()) {
        return false;
    }
    struct in_addr s;
    int32_t result = inet_pton(AF_INET, ip.c_str(), reinterpret_cast<void*>(&s));
    if (result == INET_PTION_SUC) {
        return true;
    }
    return false;
}

bool IsValidIPV6(const std::string &ip)
{
    if (ip.empty()) {
        return false;
    }
    struct in6_addr s;
    int32_t result = inet_pton(AF_INET6, ip.c_str(), reinterpret_cast<void*>(&s));
    if (result == INET_PTION_SUC) {
        return true;
    }
    return false;
}

int8_t GetAddrFamily(const std::string &ip)
{
    if (IsValidIPV4(ip)) {
        return AF_INET;
    }
    if (IsValidIPV6(ip)) {
        return AF_INET6;
    }
    return 0;
}

int GetMaskLength(const std::string &mask)
{
    int netMask = 0;
    unsigned int maskTmp = ntohl(static_cast<int>(inet_addr(mask.c_str())));
    while (maskTmp & CONST_MASK) {
        ++netMask;
        maskTmp = (maskTmp << 1);
    }
    return netMask;
}

bool ParseInt(const char *str, int32_t *value)
{
    char *end;
    long long v = strtoll(str, &end, 10);
    if (end == str || *end != '\0' || v < INT_MIN || v > INT_MAX) {
        return false;
    }
    *value = v;
    return true;
}

int64_t ConvertToInt64(const std::string& str)
{
    return strtoll(str.c_str(), nullptr, 10);
}
} // namespace OHOS::NetManagerStandard::CommonUtils
