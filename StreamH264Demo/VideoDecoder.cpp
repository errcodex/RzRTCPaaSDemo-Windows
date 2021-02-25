#include "VideoDecoder.h"
#pragma warning(disable : 4996)
//#include <libyuv.h>
uint8_t VideoDecoder::inbuf[INBUF_SIZE];
VideoDecoder::VideoDecoder()
{
    pkt = av_packet_alloc();
    if (!pkt)
        exit(1);

    /* set end of buffer to 0 (this ensures that no overreading happens for damaged MPEG streams) */
    //memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    /* find the MPEG-1 video decoder */
    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec)
    {
        exit(1);
    }

    parser = av_parser_init(codec->id);
    if (!parser)
    {
        exit(1);
    }

    c = avcodec_alloc_context3(codec);
    if (!c)
    {
        exit(1);
    }

    c->codec_type = AVMEDIA_TYPE_VIDEO;

    /* For some codecs, such as msmpeg4 and mpeg4, width and height
	   MUST be initialized there because this information is not
	   available in the bitstream. */

    /* open it */
    if (avcodec_open2(c, codec, NULL) < 0)
    {
        exit(1);
    }

    frame = av_frame_alloc();
    if (!frame)
    {
        exit(1);
    }
}

VideoDecoder::~VideoDecoder()
{
    av_parser_close(parser);
    avcodec_free_context(&c);
    av_frame_free(&frame);
    av_packet_free(&pkt);
}

bool VideoDecoder::decode(int data_size, std::function<void(uint8_t*, int, int)> f)
{
    uint8_t* data = inbuf;
    int ret;
    if (!data_size)
        return false;
    while (data_size > 0)
    {
        ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size, data, data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
        if (ret < 0)
        {
            fprintf(stderr, "Error while parsing\n");
            exit(1);
        }
        data += ret;
        data_size -= ret;

        if (!pkt->size)
            return false;


        ret = avcodec_send_packet(c, pkt);
        if (ret < 0)
        {
            exit(1);
        }

        while (ret >= 0)
        {
            ret = avcodec_receive_frame(c, frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                break;
            else if (ret < 0)
                return false;

            printf("saving frame %3d\n", c->frame_number);
            fflush(stdout);
            int width = frame->width, height = frame->height;
            int y_size = width * height;

            uint8_t* out = new uint8_t[frame->width * frame->height * 1.5];
            uint8_t* p = out;
            //libyuv::I420Copy(frame->data[0], frame->linesize[0], frame->data[1], frame->linesize[1], frame->data[2], frame->linesize[2],
            //    out, width / 2,
            //    out + y_size, width / 2,
            //    out + y_size * 5 / 4, width / 2,
            //    width, height);
            
            
            //=======test========================
            auto g = [&p](uint8_t* buf, int wrap, int xsize, int ysize) {
                for (int i = 0; i < ysize; i++)
                {
                    memcpy(p, buf + i * wrap, xsize);
                    p += xsize;
                }
            };
            g(frame->data[0], frame->linesize[0], frame->width, frame->height);
            g(frame->data[1], frame->linesize[1], frame->width/2, frame->height/2);
            g(frame->data[2], frame->linesize[2], frame->width/2, frame->height/2);
            
            //===================================

            f(out, width, height);
            delete[] out;

        }
    }


    return true;
}
