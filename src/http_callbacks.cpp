/*#include <boost/log/core/record.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>

#include "mime_type.h"*/
#include "http_callbacks.h"

#include <iostream>

int http_callbacks1 = 122;

int http_callbacks2() {
    return 54;
}

#if defined(CLING_IS_ON)
static void http_callbacks_module_cling_prepare() {
    printf("called http_callbacks_prepare\n");
}

/*static void http_callbacks_module_cling_run_update() {
    printf("called http_callbacks_run_update\n");
}*/

static void http_callbacks_module_cling_run() {
    printf("called http_callbacks_run\n");
    setAnotherGlobal(1.43);
}

static void http_callbacks_module_cling_shutdown() {
    printf("called http_callbacks_shutdown\n");
}

void http_callbacks() {
    printf("called http_callbacks\n");
}
#endif // CLING_IS_ON
