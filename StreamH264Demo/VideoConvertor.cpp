#include "VideoConvertor.h"

VideoConvertor::VideoConvertor(int width, int height)
{
	encoder = std::make_shared<Encoder>(width, height);
	decoder = std::make_shared<Decoder>();
	vdecoder = std::make_shared<VideoDecoder>();
}

bool VideoConvertor::encode(const uint8_t* buffer, uint8_t** out, int& size, bool& isKey)
{
	return encoder->convert(buffer, out, size, isKey);
}

bool VideoConvertor::decode(const uint8_t* buffer, int data_size, std::function<void(uint8_t*, int, int)> cb)
{
	//// 当buff大小不够时自动扩容
	//if (data_size > inbufSize)
	//{
	//	inbufSize = data_size;
	//	inbuf = std::shared_ptr<uint8_t[]>(new uint8_t(inbufSize));
	//}

	//memcpy(inbuf.get(), buffer, data_size);
	//return decoder->convert(inbuf, data_size, cb);


	memcpy(vdecoder->inbuf, buffer, data_size);
	return vdecoder->decode(data_size, cb);
}



VideoConvertor::Encoder::Encoder(int width, int height)
{
	codec = avcodec_find_encoder(AV_CODEC_ID_H264);
	if (!codec)
	{
		exit(1);
	}
	c = avcodec_alloc_context3(codec);
	if (!c)
	{
		exit(1);
	}
	pkt = av_packet_alloc();
	if (!pkt)
		exit(1);

	c->bit_rate = 1200 * 1024;
	c->width = width;
	c->height = height;
	c->time_base = AVRational{ 1, 15 };
	c->framerate = AVRational{ 15, 1 };
	c->gop_size = 10;
	// 不要max_b_frames
	c->max_b_frames = 0;
	c->pix_fmt = AV_PIX_FMT_YUV420P;

	if (codec->id == AV_CODEC_ID_H264)
		av_opt_set(c->priv_data, "preset", "ultrafast", 0);

	av_opt_set(c->priv_data, "tune", "zerolatency", 0);
	av_opt_set(c->priv_data, "profile", "high", 0);

	int ret = avcodec_open2(c, codec, nullptr);
	if (ret < 0)
		exit(1);

	frame = av_frame_alloc();
	if (!frame)
		exit(1);

	frame->format = c->pix_fmt;
	frame->width = c->width;
	frame->height = c->height;

	ret = av_frame_get_buffer(frame, 0);
	if (ret < 0)
		exit(1);
}

VideoConvertor::Encoder::~Encoder()
{
	avcodec_free_context(&c);
	av_frame_free(&frame);
	av_packet_free(&pkt);
}

bool VideoConvertor::Encoder::convert(const uint8_t* buffer, uint8_t** out, int& size, bool& isKey)
{
	int ret;
	pkt->pts = pts;

	int y_size = frame->height * frame->width;
	frame->data[0] = const_cast<uint8_t*>(buffer);
	frame->data[1] = const_cast<uint8_t*>(buffer + y_size);
	frame->data[2] = const_cast<uint8_t*>(buffer + y_size * 5 / 4);

	frame->linesize[0] = frame->width;
	frame->linesize[1] = frame->width / 2;
	frame->linesize[2] = frame->width / 2;

	/* send the frame to the encoder */
	ret = avcodec_send_frame(c, frame);
	if (ret < 0)
		return false;

	while (ret >= 0)
	{
		ret = avcodec_receive_packet(c, pkt);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
			break;
		else if (ret < 0)
			return false;

		if (*out)
			delete[](*out);
		*out = new uint8_t[pkt->size];
		memcpy(*out, pkt->data, pkt->size);
		isKey = pkt->flags;
		size = pkt->size;
		//fwrite(pkt->data, 1, pkt->size, outfile);
		av_packet_unref(pkt);
		pts++;
	}
	return true;
}

VideoConvertor::Decoder::Decoder()
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

VideoConvertor::Decoder::~Decoder()
{
	av_parser_close(parser);
	avcodec_free_context(&c);
	av_frame_free(&frame);
	av_packet_free(&pkt);
}

bool VideoConvertor::Decoder::convert(const std::shared_ptr<uint8_t[]> inbuf, int data_size, std::function<void(uint8_t*, int, int)> cb)
{
	uint8_t* data = inbuf.get();
	int ret;
	if (!data_size)
		return false;
	while (data_size > 0)
	{
		ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size, data, data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
		if (ret < 0)
		{
			//fprintf(stderr, "Error while parsing\n");
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

			//printf("saving frame %3d\n", c->frame_number);
			//fflush(stdout);
			int width = frame->width, height = frame->height;
			int y_size = width * height;

			std::shared_ptr<uint8_t[]> yuvData(new uint8_t(frame->width * frame->height * 1.5));
			uint8_t* p = yuvData.get();

			//==============去除对齐=================
			auto DiscardMargin = [&p](uint8_t* buf, int wrap, int xsize, int ysize) {
				for (int i = 0; i < ysize; i++)
				{
					memcpy(p, buf + i * wrap, xsize);
					p += xsize;
				}
			};
			DiscardMargin(frame->data[0], frame->linesize[0], frame->width, frame->height);
			DiscardMargin(frame->data[1], frame->linesize[1], frame->width / 2, frame->height / 2);
			DiscardMargin(frame->data[2], frame->linesize[2], frame->width / 2, frame->height / 2);
			//===================================

			cb(yuvData.get(), width, height);
		}
	}


	return true;
}
