_Pragma("once")

#include "tinycommon.hpp"
#include "avobject.hpp"
namespace tinyav {
    class avformat_ctx : public avobject<avformat_ctx, AVFormatContext> {
    public:
        AVFormatContext     *m_d{nullptr};
        avformat_ctx() = default;
        avformat_ctx(AVFormatContext *f)
            : m_d(f) { }
        avformat_ctx(avformat_ctx &&o)
            : m_d(o.release()) { }
        avformat_ctx(const avformat_ctx &o) = delete;
        avformat_ctx &operator = (AVFormatContext *f)
        {
            reset(f);
            return *this;
        }
        avformat_ctx &operator = (const AVFormatContext *f) = delete;
            avformat_ctx &operator =(avformat_ctx &&o)
        {
            reset(o.release());
            return *this;
        }
        avformat_ctx &operator = (const avformat_ctx &o) = delete;
       ~avformat_ctx()
       {
           close();
       }
        void swap(avformat_ctx &o)
        {
            std::swap(m_d,o.m_d);
        }
        void reset(AVFormatContext *f = nullptr)
        {
            if(f != m_d)
                close();
            m_d = f;
        }
        AVFormatContext *release() { auto ret = m_d; m_d = nullptr; return ret;}
        AVFormatContext *get() const { return m_d;}
        AVFormatContext *operator ->() { return m_d; }
        AVFormatContext *operator ->() const { return m_d;}
        AVFormatContext &operator *() { return *m_d;}
        const AVFormatContext &operator *() const { return *m_d;}
        int open_output(const char *filename, AVOutputFormat *fmt = nullptr, const char *fmt_name = nullptr)
        {
            return avformat_alloc_output_context2(&m_d,fmt,fmt_name,filename);
        }
        int open_input(const char *filename, AVInputFormat *fmt = nullptr, AVDictionary **opts = nullptr)
        {
            return avformat_open_input(&m_d, filename, fmt, opts);
        }
        bool is_input() const
        {
            return m_d && !!m_d->iformat;
        }
        bool is_output() const
        {
            return m_d && !!m_d->oformat;
        }
        void close()
        {
            if(is_input())
                avformat_close_input(&m_d);
            if(is_output()) {
                avformat_free_context(m_d);
                m_d = nullptr;
            }
        }
        operator bool() const { return !!m_d;}
        operator AVFormatContext *() const { return m_d;}
        void alloc()
        {
            if(!m_d)
                m_d = avformat_alloc_context();
        }
        int read_frame(AVPacket *pkt) { return av_read_frame(m_d, pkt);}
        int seek_frame(int sid, int64_t ts, int flags = 0)
        {
            return av_seek_frame(m_d, sid, ts,flags);
        }
        int seek_file(int sid, int64_t min_ts, int64_t ts, int64_t max_ts, int flags = 0)
        {
            return avformat_seek_file(m_d,sid,min_ts,ts,max_ts,flags);
        }
        int flush() { return avformat_flush(m_d);}
        int find_stream_info(AVDictionary **opts) { return avformat_find_stream_info(m_d, opts);}
        int find_best_stream(AVMediaType type, int desired, int related, AVCodec **codec, int flags = 0)
        {
            return av_find_best_stream(m_d,type,desired,related,codec,flags);
        }
        int read_play() { return av_read_play(m_d);}
        int read_pause() { return av_read_pause(m_d);}
        void dump(int offset, const char *filename, bool is_out) const
        {
            av_dump_format(m_d, offset, filename, is_out);
        }
    };
};
inline void swap(tinyav::avformat_ctx &lhs, tinyav::avformat_ctx &rhs){ lhs.swap(rhs);}
