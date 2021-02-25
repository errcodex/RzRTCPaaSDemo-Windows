#pragma once
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
#include <functional>
class VideoDecoder
{
public:
    VideoDecoder();
    ~VideoDecoder();
    bool decode(int data_size, std::function<void(uint8_t*, int, int)> f);

    static const uint32_t INBUF_SIZE = 40960U;
    static uint8_t inbuf[];

private:
    const AVCodec* codec = nullptr;
    AVCodecParserContext* parser = nullptr;
    AVCodecContext* c = nullptr;
    AVFrame* frame = nullptr;
    AVPacket* pkt = nullptr;
};