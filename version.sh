
# Package versioning information for ImageMagick.
#
# This file is sourced by a Bourne shell (/bin/sh) script so it must
# observe Bourne shell syntax.
#

#
# Package change and release dates.
#
PACKAGE_RELEASE_DATE_RAW=`date +%F`
PACKAGE_CHANGE_DATE=`awk '/^[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]/ { print substr($1,1,4) substr($1,6,2) substr($1,9,2); exit; }' ${srcdir}/ChangeLog`
PACKAGE_RELEASE_DATE_REPRODUCIBLE="${PACKAGE_CHANGE_DATE}"

#
# Versions are denoted using a standard triplet of integers:
# MAJOR.MINOR.PATCH. The basic intent is that MAJOR versions are
# incompatible, large-scale upgrades of the API. MINOR versions retain
# source and binary compatibility with older minor versions, and changes
# in the PATCH level are perfectly compatible, forwards and backwards.
# See http://apr.apache.org/versioning.html.
#
# PLEASE NOTE that doing a SO BUMP aka raising the CURRENT REVISION
# could be avoided using libversioning aka map files.  You MUST change .map
# files if you raise these versions.
#
# Bump the minor release # whenever there is an SOVersion bump.
MAGICK_LIBRARY_CURRENT=6
MAGICK_LIBRARY_REVISION=0
MAGICK_LIBRARY_AGE=0

# magick++
MAGICKPP_LIBRARY_CURRENT=8
MAGICKPP_LIBRARY_REVISION=0
MAGICKPP_LIBRARY_AGE=0
