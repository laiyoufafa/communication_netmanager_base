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
#ifndef NET_CONN_HTTP_PROBE_H
#define NET_CONN_HTTP_PROBE_H

#include <string>
#include <memory>
#include <stdint.h>

namespace OHOS {
namespace NetManagerStandard {
class HttpProbeResult {
public:
    static constexpr int32_t SUCCESS_CODE_MIN = 200;
    static constexpr int32_t SUCCESS_CODE_MAX = 299;
    static constexpr int32_t PORTAL_CODE_MIN = 300;
    static constexpr int32_t PORTAL_CODE_MAX = 399;

    HttpProbeResult() : code_(0), redirectUrl_("") {}

    HttpProbeResult(int32_t code, std::string redirectUrl) : code_(code), redirectUrl_(redirectUrl) {}

    int32_t GetCode() const
    {
        return code_;
    }

    std::string GetRedirectUrl() const
    {
        return redirectUrl_;
    }

    bool IsSuccessful() const
    {
        return (code_ >= SUCCESS_CODE_MIN && code_ <= SUCCESS_CODE_MAX);
    }

    bool IsPortal() const
    {
        return !IsSuccessful() && (code_ >= PORTAL_CODE_MIN) && (code_ <= PORTAL_CODE_MAX);
    }

    bool IsFailed() const
    {
        return !IsSuccessful() && !IsPortal();
    }

    void Clear()
    {
        code_ = 0;
        redirectUrl_ = "";
    }

    bool operator==(const HttpProbeResult &other) const
    {
        if (IsSuccessful() && other.IsSuccessful()) {
            return true;
        }
        if (IsPortal() && other.IsPortal() && (redirectUrl_ == other.redirectUrl_)) {
            return true;
        }
        if (IsFailed() && other.IsFailed()) {
            return true;
        }
        return false;
    }

    bool operator!=(const HttpProbeResult &other) const
    {
        return !(*this == other);
    }

private:
    int32_t code_{0};
    std::string redirectUrl_;
};

class HttpProbe {
public:
    enum ProbeType {
        PROBE_HTTP,
        PROBE_HTTPS
    };

    HttpProbe(ProbeType probeType, const std::string &url, int32_t sockFd = -1);

    virtual ~HttpProbe();

    HttpProbeResult GetResult() const;

    bool HasError() const;

    std::string ErrorString() const;

private:
    std::string GetHeaderField(const std::string &name) const;

private:
    std::unique_ptr<struct CurlOptions> curlOpts_;
};
} // namespace NetManagerStandard
} // namespace OHOS
#endif // NET_CONN_HTTP_PROBE_H