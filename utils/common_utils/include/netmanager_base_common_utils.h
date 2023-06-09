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

#ifndef COMMUNICATIONNETMANAGER_BASE_COMMON_UTILS_H
#define COMMUNICATIONNETMANAGER_BASE_COMMON_UTILS_H

#include <string>
#include <vector>

namespace OHOS::NetManagerStandard::CommonUtils {
std::vector<std::string> Split(const std::string &str, const std::string &sep);

std::string Strip(const std::string &str, char ch = ' ');

std::string ToLower(const std::string &s);
} // namespace OHOS::NetManagerStandard::CommonUtils

#endif /* COMMUNICATIONNETMANAGER_BASE_COMMON_UTILS_H */
