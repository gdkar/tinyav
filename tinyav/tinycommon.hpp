_Pragma("once")

extern "C" {
  #include <libavutil/avutil.h>
  #include <libavformat/avformat.h>
  #include <libavcodec/avcodec.h>
  #include <libavdevice/avdevice.h>
  #include <libswresample/swresample.h>
}

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>

#include <functional>
#include <type_traits>
#include <limits>
#include <memory>
#include <utility>
#include <algorithm>
#include <iterator>
#include <numeric>

#include <vector>
#include <string>
#include <deque>
#include <list>
#include <forward_list>
#include <unordered_map>
#include <array>
#include <map>

namespace tinyav {
    inline std::string tinyav_strerror(int err)
    {
        char str[128];
        va_strerror(err,str,sizeof(str));
        return std::string(str);
    }
};