/*
Copyright_License {

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

#ifndef XCSOAR_EVENT_TIMER_HPP
#define XCSOAR_EVENT_TIMER_HPP

#include <atomic>

#include <assert.h>

/**
 * A timer that, once initialized, periodically calls OnTimer() after
 * a specified amount of time, until Cancel() gets called.
 *
 * Initially, this class does not schedule a timer.
 *
 * This class is not thread safe; all of the methods must be called
 * from the main thread.
 *
 * The class #WindowTimer is cheaper on WIN32; use it instead of this
 * class if you are implementing a #Window.
 */
class Timer {
  std::atomic<bool> enabled, queued;
  unsigned ms;

public:
  /**
   * Construct a Timer object that is not set initially.
   */
  Timer():enabled(false), queued(false) {}

  Timer(const Timer &other) = delete;

protected:
  /**
   * The move constructor may only be used on inactive timers.  This
   * shall only be used by derived classes to pass inactive instances
   * around.
   */
  Timer(Timer &&other) {
    assert(!IsActive());
    assert(!other.IsActive());
  }

public:
  ~Timer() {
    /* timer must be cleaned up explicitly */
    assert(!IsActive());

#ifdef USE_POLL_EVENT
    assert(!queued.load(std::memory_order_relaxed));
    assert(!enabled.load(std::memory_order_relaxed));
#endif
  }

  /**
   * Is the timer active, i.e. is it waiting for the current period to
   * end?
   */
  bool IsActive() const {
    return enabled.load(std::memory_order_relaxed);
  }

  /**
   * Schedule the timer.  Cancels the previous setting if there was
   * one.
   */
  void Schedule(unsigned ms);

  /**
   * Schedule the timer.  Preserves the previous setting if there was
   * one.
   */
  void SchedulePreserve(unsigned ms);

  /**
   * Cancels the scheduled timer, if any.  This is safe to be called
   * while the timer is running.
   */
  void Cancel();

protected:
  /**
   * This method gets called after the configured time has elapsed.
   * Implement it.
   */
  virtual void OnTimer() = 0;

public:
  void Invoke();
};

#endif
