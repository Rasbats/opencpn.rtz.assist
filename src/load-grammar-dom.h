#ifndef __RTZassistDom1__
#define __RTZassistDom1__

#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>

#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include <string>
#include <memory>   // std::auto_ptr
#include <cstddef>  // std::size_t
#include <iostream>

#include <wx/filename.h>

int mainValidator(int argc, const char* args[]);

#endif