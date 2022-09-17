/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
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

#ifndef NET_MONITOR_H
#define NET_MONITOR_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include "net_conn_types.h"
#include "refbase.h"
namespace OHOS {
namespace NetManagerStandard {
class NetMonitor : public virtual RefBase {
public:
    /**
     * Construct a new NetMonitor to detection a network
     *
     * @param netId Detection network's id
     * @param handle NetDetectionState's handle
     */
    NetMonitor(uint32_t netId, NetDetectionStateHandler handle);

    /**
     * Destroy the NetMonitor
     *
     */
    virtual ~NetMonitor();

    /**
     * Start detection
     *
     */
    void Start(bool needReport);

    /**
     * Stop detecting
     *
     */
    void Stop();

    /**
     * Determine NetMonitor is detecting or not
     *
     * @return bool NetMonitor is detecting or not
     */
    bool IsDetecting() const;

    /**
     * Get current detection result
     *
     * @return Current detection result
     */
    NetDetectionStatus GetDetectionResult() const;

    /**
     * Set network socket parameter
     *
     * @return Socket parameter setting result
     */
    int32_t SetSocketParameter(int32_t sockFd);

private:
    void Detection();
    NetDetectionStatus SendParallelHttpProbes();
    NetDetectionStatus SendHttpProbe(const std::string &defaultDomain, const std::string &defaultUrl,
                                     const uint16_t defaultPort);
    int32_t GetStatusCodeFromResponse(const std::string &strResponse);
    int32_t GetUrlRedirectFromResponse(const std::string &strResponse, std::string &urlRedirect);
    NetDetectionStatus dealRecvResult(const std::string &strResponse);
    int32_t ParseUrl(const std::string &url, std::string &domain, std::string &urlPath);
    int32_t GetIpAddr(const char *domain, std::string &ip_addr, int &socketType);

    /**
     * Non blocking socket connection
     *
     * @param sockFd Socket fd to connect
     * @param port Transport layer default port
     * @param ipAddr IP address
     *
     * @return Socket connect result
     */
    int32_t Connect(int32_t sockFd, int socketType, const uint16_t port, const std::string &ipAddr);

    /**
     * Connect ipv4 ip address socket
     *
     * @param sockFd Socket fd to connect
     * @param port Transport layer default port
     * @param ipAddr IP address
     *
     * @return Socket connect result
     */
    int32_t ConnectIpv4(int32_t sockFd, const uint16_t port, const std::string &ipAddr);

    /**
     * Connect ipv6 ip address socket
     *
     * @param sockFd Socket fd to connect
     * @param port Transport layer default port
     * @param ipAddr IP address
     *
     * @return Socket connect result
     */
    int32_t ConnectIpv6(int32_t sockFd, const uint16_t port, const std::string &ipAddr);

    /**
     * Ready for socket reading or writing
     *
     * @param sockFd Socket fd to connect
     * @param canRead Store readable status
     * @param canWrite Store writable status
     *
     * @return Socket preparation result
     */
    int32_t Wait(int32_t sockFd, uint8_t *canRead, uint8_t *canWrite);

    /**
     * Send data to socket
     *
     * @param sockFd Socket fd to send
     * @param domain Probe link
     * @param url Probe url
     *
     * @return Result of send data to socket
     */
    int32_t Send(int32_t sockFd, const std::string &domain, const std::string &url);

    /**
     * Receive data from socket
     *
     * @param sockFd Socket fd to receive
     * @param probResult Store received data
     *
     * @return Result of receive data from socket
     */
    int32_t Receive(int32_t sockFd, std::string &probResult);

private:
    uint32_t netId_;
    bool detecting_ = false;
    std::mutex detectionMtx_;
    std::condition_variable detectionCond_;
    std::thread detectionThread_;
    NetDetectionStatus result_ = INVALID_DETECTION_STATE;
    uint32_t detectionDelay_ = 0;
    uint32_t detectionSteps_ = 0;
    NetDetectionStateHandler netDetectionStatus_;
    std::string portalUrlRedirect_;
    bool needReport_ = false;
};
} // namespace NetManagerStandard
} // namespace OHOS
#endif // NET_MONITOR_H
