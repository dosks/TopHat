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

#ifndef XCSOAR_IGC_PARSER_HPP
#define XCSOAR_IGC_PARSER_HPP

#include "Util/StaticString.hxx"

struct IGCFix;
struct IGCHeader;
struct IGCExtensions;
struct IGCDeclarationHeader;
struct IGCDeclarationTurnpoint;
struct BrokenDate;
struct BrokenTime;
struct GeoPoint;
struct LoggerSettings;

/**
 * used by AnalyseFlight()
 */
typedef StaticString<64> GliderType;

/**
 * Parse an IGC "A" record.
 *
 * @return true on success, false if the line was not recognized
 */
bool
IGCParseHeader(const char *line, IGCHeader &header);

/**
 * Parse an IGC "HFDTE" record.
 *
 * @return true on success, false if the line was not recognized
 */
bool
IGCParseDateRecord(const char *line, BrokenDate &date);

/**
 * parses one IGC "H" header row into IGC Header structure
 * returns true if the row was an "H" record
 * All H records are grouped at top of IGC file per IGC standard
 * after initial A record
 */
bool
IGCParseHRecords(const char *line, GliderType &glider_type,
                 LoggerSettings &logger_settings);
/**
 * parses Pilot record
 * @param upper_line.  Input line in all upper case, trimmed right spaces
 */
bool
IGCParsePilotRecord(const char *upper_line, LoggerSettings &logger_settings);

bool
IGCParseGliderType(const char *upper_line, GliderType &glider_type);

bool
IGCParseGliderIDRecord(const char *upper_line, LoggerSettings &logger_settings);

bool
IGCParseCompetitionIDRecord(const char *upper_line, LoggerSettings &logger_settings);

/**
 * Parse an IGC "I" record.
 *
 * @return true on success, false if the line was not recognized
 */
bool
IGCParseExtensions(const char *buffer, IGCExtensions &extensions);

/**
 * Parse a location in IGC file format. (DDMMmmm[N/S]DDDMMmmm[E/W])
 *
 * @return true on success, false if the location was not recognized
 */
bool
IGCParseLocation(const char *buffer, GeoPoint &location);

/**
 * Parse an IGC "B" record.
 *
 * @return true on success, false if the line was not recognized
 */
bool
IGCParseFix(const char *buffer, const IGCExtensions &extensions, IGCFix &fix);

/**
 * Parse a time in IGC file format (HHMMSS).
 *
 * @return true on success, false if the time was not recognized
 */
bool
IGCParseTime(const char *buffer, BrokenTime &time);

/**
 * Parse an IGC "C" header record.
 *
 * @return true on success, false if the line was not recognized
 */
bool
IGCParseDeclarationHeader(const char *line, IGCDeclarationHeader &header);

/**
 * Parse an IGC "C" turnpoint record.
 *
 * @return true on success, false if the line was not recognized
 */
bool
IGCParseDeclarationTurnpoint(const char *line, IGCDeclarationTurnpoint &tp);

#endif
