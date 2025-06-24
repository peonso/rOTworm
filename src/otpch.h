#ifndef __OTSERV_OTCP_H__ // <--- CHANGE: Use a standard #ifndef guard
#define __OTSERV_OTCP_H__ // <--- CHANGE: Define the guard right away

// Definitions should be global.
#include "definitions.h"

#ifdef __USE_OTPCH__

#ifdef __WINDOWS__
#include <winerror.h>
#endif

//libxml
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/threads.h>
//boost
#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
//std
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <random>
//lua
extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
//otserv
#include "thing.h"

#endif // __USE_OTPCH__

#endif // __OTSERV_OTCP_H__  <--- CHANGE: End the #ifndef block