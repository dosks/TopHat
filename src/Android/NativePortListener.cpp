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

#include "NativePortListener.hpp"
#include "Device/Port/Listener.hpp"
#include "Java/Class.hxx"
#include "org_tophat_NativePortListener.h"

#include <stddef.h>

namespace NativePortListener {
  static Java::TrivialClass cls;
  static jmethodID ctor;
  static jfieldID ptr_field;
};

JNIEXPORT void JNICALL
Java_org_tophat_NativePortListener_portStateChanged(JNIEnv *env, jobject obj)
{
  jlong ptr = env->GetLongField(obj, NativePortListener::ptr_field);
  if (ptr == 0)
    /* not yet set */
    return;

  PortListener &listener = *(PortListener *)(void *)ptr;
  listener.PortStateChanged();
}

void
NativePortListener::Initialise(JNIEnv *env)
{
  cls.Find(env, "org/tophat/NativePortListener");

  ctor = env->GetMethodID(cls, "<init>", "(J)V");
  ptr_field = env->GetFieldID(cls, "ptr", "J");
}

void
NativePortListener::Deinitialise(JNIEnv *env)
{
  cls.Clear(env);
}

jobject
NativePortListener::Create(JNIEnv *env, PortListener &listener)
{
  assert(cls != nullptr);

  return env->NewObject(cls, ctor, (jlong)&listener);
}
