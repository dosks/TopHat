/* Copyright_License {

  Top Hat Soaring Glide Computer - http://www.tophatsoaring.org/
  Copyright (C) 2000-2016 The Top Hat Soaring Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
 */

#ifndef XCSOAR_THREAD_GUARD_HPP
#define XCSOAR_THREAD_GUARD_HPP

#include "Poco/RWLock.h"

/**
 * This class protects its value with a mutex.  A user may get a lease
 * on the value, and the Lease objects locks the mutex during the
 * access.
 */
template<typename T>
class Guard {
protected:
  T &value;
  mutable Poco::RWLock mutex;

public:
  /**
   * A read-only lease on the guarded value.
   */
  class Lease {
    const Guard &guard;

  public:
    explicit Lease(const Guard &_guard):guard(_guard) {
      guard.mutex.readLock();
    }

    ~Lease() {
      guard.mutex.unlock();
    }

    operator const T&() const {
      return guard.value;
    }

    const T *operator->() const {
      return &guard.value;
    }
  };

  /**
   * A writable lease on the guarded value.
   */
  class ExclusiveLease {
    Guard &guard;

  public:
    explicit ExclusiveLease(Guard &_guard):guard(_guard) {
      guard.mutex.writeLock();
    }

    ~ExclusiveLease() {
      guard.mutex.unlock();
    }

    operator const T&() const {
      return guard.value;
    }

    operator T&() {
      return guard.value;
    }

    const T *operator->() const {
      return &guard.value;
    }

    T *operator->() {
      return &guard.value;
    }
  };

  /**
   * An unprotected writable lease on the value.  This is only allowed
   * when the other threads which might access the value are suspended
   * (e.g. during startup).
   */
  class UnprotectedLease {
    T &value;

  public:
    explicit UnprotectedLease(Guard &_guard)
      :value(_guard.value) {}

    operator const T&() const {
      return value;
    }

    operator T&() {
      return value;
    }

    const T *operator->() const {
      return &value;
    }

    T *operator->() {
      return &value;
    }
  };

public:
  explicit Guard(T &_value):value(_value) {}
};

#endif
