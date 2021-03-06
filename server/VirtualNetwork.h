/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <set>

#include "Network.h"

namespace android::net {

// A VirtualNetwork may be "secure" or not.
//
// A secure VPN is the usual type of VPN that grabs the default route (and thus all user traffic).
// Only a few privileged UIDs may skip the VPN and go directly to the underlying physical network.
//
// A non-secure VPN ("bypassable" VPN) also grabs all user traffic by default. But all apps are
// permitted to skip it and pick any other network for their connections.
class VirtualNetwork : public Network {
public:
    VirtualNetwork(unsigned netId, bool secure);
    virtual ~VirtualNetwork();
    [[nodiscard]] int addUsers(const UidRanges& uidRanges, uint32_t subPriority) override;
    [[nodiscard]] int removeUsers(const UidRanges& uidRanges, uint32_t subPriority) override;
    bool isVirtual() override { return true; }
    bool canAddUsers() override { return true; }

  private:
    std::string getTypeString() const override { return "VIRTUAL"; };
    [[nodiscard]] int addInterface(const std::string& interface) override;
    [[nodiscard]] int removeInterface(const std::string& interface) override;
    bool isValidSubPriority(uint32_t priority) override;
};

}  // namespace android::net
