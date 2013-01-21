#ifndef IGSXML_COMMON_H
#define IGSXML_COMMON_H

#if defined(_WIN32) || defined(WIN32)
#ifdef IGS_XML_EXPORTS
#define IGSXML __declspec(dllexport)
#else
#define IGSXML __declspec(dllimport)
#endif
#else
#define IGSXML
#endif

#endif

// EOF

