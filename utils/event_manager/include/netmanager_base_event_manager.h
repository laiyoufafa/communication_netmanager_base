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

#ifndef COMMUNICATIONNETMANAGER_BASE_EVENT_MANAGER_H
#define COMMUNICATIONNETMANAGER_BASE_EVENT_MANAGER_H

#include <list>
#include <mutex>

#include "netmanager_base_event_listener.h"
#include "uv.h"

namespace OHOS::NetManagerStandard {
class EventManager {
public:
    EventManager();

    void AddListener(napi_env env, const std::string &type, napi_value callback, bool once, bool asyncCallback);

    void DeleteListener(const std::string &type, napi_value callback);

    void Emit(const std::string &type, const std::pair<napi_value, napi_value> &argv);

    void SetData(void *data);

    [[nodiscard]] void *GetData();

    void EmitByUv(const std::string &type, void *data, void(Handler)(uv_work_t *, int status));

    bool HasEventListener(const std::string &type);

    void DeleteListener(const std::string &type);

private:
    std::mutex mutex_;

    std::list<EventListener> listeners_;

    void *data_;
};

struct UvWorkWrapper {
    UvWorkWrapper() = delete;

    explicit UvWorkWrapper(void *theData, napi_env theEnv, std::string eventType, EventManager *eventManager);

    void *data;
    napi_env env;
    std::string type;
    EventManager *manager;
};
} // namespace OHOS::NetManagerStandard
#endif /* COMMUNICATIONNETMANAGER_BASE_EVENT_MANAGER_H */
