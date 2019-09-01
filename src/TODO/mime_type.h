#pragma once

#include <string>

#include <boost/beast/core.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>

//------------------------------------------------------------------------------

// Return a reasonable mime type based on the extension of a file.
beast::string_view
mime_type(beast::string_view path);
