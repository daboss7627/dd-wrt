/* Platform independent version definitions... */

#ifndef BOINC_VERSION_H
#define BOINC_VERSION_H

/* Major part of BOINC version number */
#define BOINC_MAJOR_VERSION 7

/* Minor part of BOINC version number */
#define BOINC_MINOR_VERSION 20

/* Release part of BOINC version number */
#define BOINC_RELEASE 5

// wrapper version number
// when you change this, change .exe file names in VS project files
#define WRAPPER_RELEASE 26017

// vboxwrapper version number
// when you change this, change .exe file names in VS project files
#define VBOXWRAPPER_RELEASE 26206

/* String representation of BOINC version number */
#define BOINC_VERSION_STRING "7.20.5"

/* Package is a pre-release (Alpha/Beta) package */
//#define BOINC_PRERELEASE 1

#if (defined(_WIN32) || defined(__APPLE__))
/* Name of package */
#define PACKAGE "boinc"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "BOINC"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "BOINC 7.20.5"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "boinc"

/* Define to the version of this package. */
#define PACKAGE_VERSION "7.20.5"

#endif /* #if (defined(_WIN32) || defined(__APPLE__)) */

#endif /* #ifndef BOINC_VERSION_H */

