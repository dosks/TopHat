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

#include "AirspacePolygon.hpp"
#include "Geo/Flat/FlatProjection.hpp"
#include "Geo/Flat/FlatRay.hpp"
#include "AirspaceIntersectSort.hpp"
#include "AirspaceIntersectionVector.hpp"

AirspacePolygon::AirspacePolygon(const std::vector<GeoPoint> &pts,
                                 const bool prune)
  :AbstractAirspace(Shape::POLYGON)
{
  assert(pts.size() >= 3);

  m_border.reserve(pts.size() + 1);

  for (const GeoPoint &pt : pts)
    m_border.emplace_back(pt);

  // ensure airspace is closed
  const GeoPoint &p_start = pts.front();
  const GeoPoint &p_end = pts.back();
  if (p_start != p_end)
    m_border.emplace_back(p_start);


  if (prune) {
    // only for testing
    m_border.PruneInterior();
    is_convex = TriState::TRUE;
  } else {
    is_convex = TriState::UNKNOWN;
  }
}

const GeoPoint
AirspacePolygon::GetReferenceLocation() const
{
  assert(m_border.size() >= 3);

  return m_border[0].GetLocation();
}

const GeoPoint
AirspacePolygon::GetCenter() const
{
  assert(m_border.size() >= 3);

  fixed lat(0), lon(0);

  for (const auto &pt : m_border) {
    lat += pt.GetLocation().latitude.Native();
    lon += pt.GetLocation().longitude.Native();
  }

  lon = lon / m_border.size();
  lat = lat / m_border.size();

  return GeoPoint(Angle::Native(lon), Angle::Native(lat));
}

bool
AirspacePolygon::Inside(const GeoPoint &loc) const
{
  return m_border.IsInside(loc);
}

AirspaceIntersectionVector
AirspacePolygon::Intersects(const GeoPoint &start, const GeoPoint &end,
                            const FlatProjection &projection) const
{
  const FlatRay ray(projection.ProjectInteger(start),
                    projection.ProjectInteger(end));

  AirspaceIntersectSort sorter(start, *this);

  for (auto it = m_border.begin(); it + 1 != m_border.end(); ++it) {

    const FlatRay r_seg(it->GetFlatLocation(), (it + 1)->GetFlatLocation());
    fixed t = ray.DistinctIntersection(r_seg);
    if (!negative(t))
      sorter.add(t, projection.Unproject(ray.Parametric(t)));
  }

  return sorter.all();
}

GeoPoint
AirspacePolygon::ClosestPoint(const GeoPoint &loc,
                              const FlatProjection &projection) const
{
  const FlatGeoPoint p = projection.ProjectInteger(loc);
  const FlatGeoPoint pb = m_border.NearestPoint(p);
  return projection.Unproject(pb);
}
