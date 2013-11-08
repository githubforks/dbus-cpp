/*
 * Copyright © 2013 Canonical Ltd.
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

#include "org/freedesktop/dbus/message.h"

#include <gtest/gtest.h>

#include <chrono>
#include <memory>

TEST(Message, BuildingAMethodCallMessageSucceedsForValidArguments)
{
    const std::string destination = DBUS_SERVICE_DBUS;
    const std::string path = DBUS_PATH_DBUS;
    const std::string interface = DBUS_SERVICE_DBUS;
    const std::string member = "ListNames";

    std::shared_ptr<org::freedesktop::dbus::Message> msg;
    EXPECT_NO_THROW(msg = org::freedesktop::dbus::Message::make_method_call(destination, path, interface, member););
    EXPECT_NE(nullptr, msg.get());
}

TEST(Message, BuildingAMethodCallMessageThrowsForInvalidArguments)
{
    const std::string destination = DBUS_SERVICE_DBUS;
    const std::string path = "an:invalid:path";
    const std::string interface = DBUS_SERVICE_DBUS;
    const std::string member = "ListNames";

    std::shared_ptr<org::freedesktop::dbus::Message> msg;
    EXPECT_ANY_THROW(msg = org::freedesktop::dbus::Message::make_method_call(destination, path, interface, member););
    EXPECT_EQ(nullptr, msg.get());
}

TEST(Message, AccessingAReaderOnAnEmptyMessageThrows)
{
    const std::string destination = DBUS_SERVICE_DBUS;
    const std::string path = DBUS_PATH_DBUS;
    const std::string interface = DBUS_SERVICE_DBUS;
    const std::string member = "ListNames";

    auto msg = org::freedesktop::dbus::Message::make_method_call(destination, path, interface, member);

    EXPECT_ANY_THROW(msg->reader());
}

TEST(Message, AccessingAWriterOnAnyMessageSucceeds)
{
    const std::string destination = DBUS_SERVICE_DBUS;
    const std::string path = DBUS_PATH_DBUS;
    const std::string interface = DBUS_SERVICE_DBUS;
    const std::string member = "ListNames";

    auto msg = org::freedesktop::dbus::Message::make_method_call(
                destination,
                path,
                interface,
                member);

    EXPECT_NO_THROW(auto writer = msg->writer());

    {
        msg->writer().push_int16(43);
        msg->writer().push_int16(42);
    }

    EXPECT_NO_THROW(auto writer = msg->writer(););
}

TEST(Message, WriteAndSuccessiveReadAreIdempotent)
{
    const std::string destination = DBUS_SERVICE_DBUS;
    const std::string path = DBUS_PATH_DBUS;
    const std::string interface = DBUS_SERVICE_DBUS;
    const std::string member = "ListNames";

    auto msg = org::freedesktop::dbus::Message::make_method_call(
                destination,
                path,
                interface,
                member);

    const unsigned int expected_integer_value
    {
        43
    };
    const double expected_floating_point_value
    {
        42.
    };

    {
        auto writer = msg->writer();
        writer.push_int32(expected_integer_value);
        writer.push_floating_point(expected_floating_point_value);
    }

    auto reader = msg->reader();
    auto i = reader.pop_int32();
    auto d = reader.pop_floating_point();

    EXPECT_EQ(expected_integer_value, i);
    EXPECT_EQ(expected_floating_point_value, d);
}
