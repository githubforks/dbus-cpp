/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Thomas Voß <thomas.voss@canonical.com>
 */
#ifndef DBUS_ORG_FREEDESKTOP_DBUS_TYPES_ANY_H_
#define DBUS_ORG_FREEDESKTOP_DBUS_TYPES_ANY_H_

#include <memory>

namespace org
{
namespace freedesktop
{
namespace dbus
{
class Message;
namespace types
{
/**
 * @brief Any describes types for which no codec specialization is known at compile time.
 */
class Any
{
public:
    /**
      * @brief Constructs an empty instance.
      */
    Any(const std::shared_ptr<Message>& msg = std::shared_ptr<Message>{})
        : msg(msg)
    {
    }

    /**
     * @brief Provides non-mutable access to the contained message.
     *
     * Users of the library can rely on Any and access to the contained and cloned
     * message to postpone serialization until runtime. Usually, compile-time static
     * typing is preferred via template-specializations of Codec to ensure maximum
     * stability.
     */
    inline const std::shared_ptr<Message>& message() const
    {
        return msg;
    }

private:
    std::shared_ptr<Message> msg;
};
}
}
}
}

#endif // DBUS_ORG_FREEDESKTOP_DBUS_TYPES_ANY_H_
